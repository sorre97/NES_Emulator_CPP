#include "disassembler.h"
#include "Cpu/cpu6502_opcodes.h"
#include <iostream>
#include "Cpu/cpu6502_memory_map.h"
#include <iomanip>
#include <thread>
#include <chrono>

// ANSI escape codes for colors
const std::string WHITE = "\033[1;37m"; // Bold white
const std::string GREY = "\033[1;30m";  // Bold gray
const std::string RESET = "\033[0m";    // Reset to default

Disassembler::Disassembler(std::shared_ptr<CPU6502> cpu, std::shared_ptr<BusInterface> bus)
    : cpu(cpu), bus(bus) { decompileCartridge(); }

void Disassembler::decompileCartridge() {
    uint16_t currentAddress = CARTRIDGE_ROM_STARTADDR;

    while (currentAddress <= CARTRIDGE_ROM_ENDADDR) {
        uint8_t opcode = bus->cpuBusRead(currentAddress);
        const OpcodeInfo& info = OPCODE_TABLE[opcode];

        if (info.instruction == Instruction::INVALID) {
            break; // Stop decompiling on invalid opcode
        }

        // Decode the instruction and add to the vector
        std::string decoded = decodeInstruction(currentAddress);
        // Store in map
        instructions[currentAddress] = decoded;

        // Move to the next instruction
        currentAddress += calculateInstructionSize(info);
    }
}

std::string Disassembler::decodeInstruction(uint16_t address) const {
    uint8_t opcode = bus->cpuBusRead(address);
    const OpcodeInfo& info = OPCODE_TABLE[opcode];

    if (info.instruction == Instruction::INVALID) {
        return "??? (INVALID)";
    }

    std::ostringstream oss;
    oss << InstructionToStringMap.at(info.instruction) << " (0x" 
        << std::hex << std::uppercase << static_cast<int>(opcode) << ") "
        << AddressingModeToStringMap.at(info.addressingMode) 
        << " PC: " << std::hex << std::uppercase << static_cast<int>(address) << ")";

    return oss.str();
}

uint8_t Disassembler::calculateInstructionSize(const OpcodeInfo& info) const {
    switch (info.addressingMode) {
        case AddressingMode::Accumulator:
            // No operands, the instruction operates on the accumulator directly
            return 1; // Only the opcode
            break;

        case AddressingMode::Immediate:
            // Immediate values are 2 bytes: 1 byte for opcode, 1 byte for the immediate value
            return 2;
            break;

        case AddressingMode::ZeroPage:
            // Zero-page addressing is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
            return 2;
            break;

        case AddressingMode::ZeroPageX:
            // Zero-page indexed by X is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
            return 2;
            break;

        case AddressingMode::ZeroPageY:
            // Zero-page indexed by Y is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
            return 2;
            break;

        case AddressingMode::Absolute:
            // Absolute addressing is 3 bytes: 1 byte for opcode, 2 bytes for the address
            return 3;
            break;

        case AddressingMode::AbsoluteX:
            // Absolute addressing indexed by X is 3 bytes: 1 byte for opcode, 2 bytes for the address
            return 3;
            break;

        case AddressingMode::AbsoluteY:
            // Absolute addressing indexed by Y is 3 bytes: 1 byte for opcode, 2 bytes for the address
            return 3;
            break;

        case AddressingMode::Implied:
            // Implied mode has no operands, the instruction operates on fixed registers
            return 1; // Only the opcode
            break;

        case AddressingMode::Indirect:
            // Indirect addressing is 3 bytes: 1 byte for opcode, 2 bytes for the indirect address
            return 3;
            break;

        case AddressingMode::IndirectX:
            // Indexed indirect (pre-indexed) is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
            return 2;
            break;

        case AddressingMode::IndirectY:
            // Indirect indexed (post-indexed) is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
            return 2;
            break;

        case AddressingMode::Relative:
            // Relative addressing is 2 bytes: 1 byte for opcode, 1 byte for the signed offset
            return 2;
            break;
        default:
            throw std::runtime_error("Unsupported addressing mode");
    }
}

void Disassembler::print() const {
    uint16_t pc = cpu->getPC();

    // Clear the console
    std::cout << "\033[2J\033[H";

    // Print three instructions before and after the current PC
    auto currentIt = instructions.find(pc);
    if (currentIt == instructions.end()) {
        std::cerr << "Error: PC not found in disassembled instructions.\n";
        return;
    }

    auto startIt = currentIt;
    auto endIt = currentIt;

    // Move iterators to include three instructions before and after
    for (int i = 0; i < 3 && startIt != instructions.begin(); ++i) {
        --startIt;
    }
    for (int i = 0; i < 3 && std::next(endIt) != instructions.end(); ++i) {
        ++endIt;
    }

    // Print instructions in range
    for (auto it = startIt; it != std::next(endIt); ++it) {
        if (it == currentIt) {
            // Highlight current instruction
            std::cout << WHITE << "> " << it->second << RESET << "\n";
        } else {
            // Gray for other instructions
            std::cout << GREY << "  " << it->second << RESET << "\n";
        }
    }
}

// void Disassembler::print() const {
//     const uint16_t PC = cpu->getPC(); // Get current program counter

//     // Only proceed if the PC has advanced
//     if (PC == lastPC) {
//         return; // Skip updating if PC hasn't changed
//     }

//     // Update lastPC
//     lastPC = PC;

//     // Clear the console
//     std::cout << "\033[2J\033[H"; // Clear screen and move cursor to the top-left corner

//     uint16_t currentAddress = PC;

//     // Print cached instructions
//     for (const auto& entry : cache) {
//         std::cout << GREY << " " << entry.decodedInstruction << RESET << "\n";
//     }

//     for (int offset = 0; offset <= INSTRUCTIONS_TO_SHOW; ++offset) {
//         // Read opcode at current address
//         uint8_t opcode = bus->cpuBusRead(currentAddress);
//         const OpcodeInfo& info = OPCODE_TABLE[opcode];

//         // Decode instruction
//         std::string instruction = InstructionToStringMap.at(info.instruction);
//         std::string addressingMode = AddressingModeToStringMap.at(info.addressingMode);

//         // Print the current or upcoming instruction
//         if (offset == 0) {
//             // Current instruction: White
//             std::cout << WHITE;

//             std::ostringstream oss;
//             oss << instruction << " (0x" << std::hex << std::uppercase << static_cast<int>(opcode) << ") " << addressingMode;
//             std::string decoded = oss.str();
//             addToCache(currentAddress, decoded);  

//         } else {
//             // Future instructions: Gray
//             std::cout << GREY;
//         }

//         // Print the instruction with its opcode
//         std::cout << (offset == 0 ? "> " : " ") << instruction << " (0x" 
//                   <<  std::hex << std::uppercase 
//                   << static_cast<int>(opcode) << ") " << addressingMode << "\n";

//         if(info.instruction == Instruction::INVALID)
//         {
//             currentAddress += 1;
//             continue;
//         }

//         // Move to the next instruction based on the size of the current instruction
//         switch (info.addressingMode) {
//             case AddressingMode::Accumulator:
//                 // No operands, the instruction operates on the accumulator directly
//                 currentAddress += 1; // Only the opcode
//                 break;

//             case AddressingMode::Immediate:
//                 // Immediate values are 2 bytes: 1 byte for opcode, 1 byte for the immediate value
//                 currentAddress += 2;
//                 break;

//             case AddressingMode::ZeroPage:
//                 // Zero-page addressing is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
//                 currentAddress += 2;
//                 break;

//             case AddressingMode::ZeroPageX:
//                 // Zero-page indexed by X is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
//                 currentAddress += 2;
//                 break;

//             case AddressingMode::ZeroPageY:
//                 // Zero-page indexed by Y is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
//                 currentAddress += 2;
//                 break;

//             case AddressingMode::Absolute:
//                 // Absolute addressing is 3 bytes: 1 byte for opcode, 2 bytes for the address
//                 currentAddress += 3;
//                 break;

//             case AddressingMode::AbsoluteX:
//                 // Absolute addressing indexed by X is 3 bytes: 1 byte for opcode, 2 bytes for the address
//                 currentAddress += 3;
//                 break;

//             case AddressingMode::AbsoluteY:
//                 // Absolute addressing indexed by Y is 3 bytes: 1 byte for opcode, 2 bytes for the address
//                 currentAddress += 3;
//                 break;

//             case AddressingMode::Implied:
//                 // Implied mode has no operands, the instruction operates on fixed registers
//                 currentAddress += 1; // Only the opcode
//                 break;

//             case AddressingMode::Indirect:
//                 // Indirect addressing is 3 bytes: 1 byte for opcode, 2 bytes for the indirect address
//                 currentAddress += 3;
//                 break;

//             case AddressingMode::IndirectX:
//                 // Indexed indirect (pre-indexed) is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
//                 currentAddress += 2;
//                 break;

//             case AddressingMode::IndirectY:
//                 // Indirect indexed (post-indexed) is 2 bytes: 1 byte for opcode, 1 byte for the zero-page address
//                 currentAddress += 2;
//                 break;

//             case AddressingMode::Relative:
//                 // Relative addressing is 2 bytes: 1 byte for opcode, 1 byte for the signed offset
//                 currentAddress += 2;
//                 break;

//             default:
//                 break;
//         }
//     }
// }