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
    // Fetch the reset vector (little-endian)
    uint8_t lo = bus->cpuBusRead(0xFFFC);
    uint8_t hi = bus->cpuBusRead(0xFFFD);
    uint16_t currentAddress = static_cast<uint16_t>(hi) << 8 | lo;

    while (currentAddress <= CARTRIDGE_ROM_ENDADDR) {
        // Check for overflow
        if (currentAddress < CARTRIDGE_ROM_STARTADDR || currentAddress > CARTRIDGE_ROM_ENDADDR) {
            std::cerr << "Warning: PC out-of-bounds detected at address 0x"
                      << std::hex << currentAddress << std::endl;
            break;
        }

        uint8_t opcode = bus->cpuBusRead(currentAddress);
        const OpcodeInfo& info = OPCODE_TABLE[opcode];

        // Decode the instruction and add to the vector
        std::string decoded = decodeInstruction(currentAddress);
        // Store in map
        instructions[currentAddress] = decoded;

        if (info.instruction == Instruction::INVALID) {
            std::cout << "Invalid opcode 0x" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << bus->cpuBusRead(currentAddress) << std::endl;
            std::cout << "Stopped decompiling at: PC = 0x" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << currentAddress << std::endl;
            std::cin.get();
            break; // Stop decompiling on invalid opcode
        }

        // Move to the next instruction
        currentAddress += calculateInstructionSize(info);
    }

    std::cout << "Disassemble of cartridge completed" << std::endl;

    // uint16_t targetAddress = 0xC79E;
    // int range = 10;
    // if (instructions.empty()) {
    //     std::cerr << "Instruction map is empty. Nothing to display." << std::endl;
    //     return;
    // }

    // // Find the closest available address to the target
    // auto it = instructions.lower_bound(targetAddress);
    // if (it == instructions.end()) {
    //     --it; // Use the last available instruction if targetAddress is beyond the range
    // }

    // // Move iterator backward for context
    // for (int i = 0; i < range && it != instructions.begin(); ++i) {
    //     --it;
    // }

    // // Print instructions around the target address
    // std::cout << "Disassembled instructions around address 0x" 
    //           << std::hex << targetAddress << ":\n";

    // for (int i = 0; i < 2 * range && it != instructions.end(); ++i, ++it) {
    //     std::cout << "0x" << std::hex << it->first << ": " << it->second << std::endl;
    // }
    
    std::cin.get();
}

std::string Disassembler::decodeInstruction(uint16_t address) const {
    uint8_t opcode = bus->cpuBusRead(address);
    const OpcodeInfo& info = OPCODE_TABLE[opcode];

    std::ostringstream oss;
    oss << (info.instruction == Instruction::INVALID ? "???" : InstructionToStringMap.at(info.instruction))
        << " (0x" << std::hex << std::uppercase << static_cast<int>(opcode) << ") "
        << AddressingModeToStringMap.at(info.addressingMode) 
        << " PC: " << std::hex << std::uppercase << static_cast<int>(address) << ")";
    std::cout << oss.str() << std::endl;
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
        case AddressingMode::ZeroPageIndirect:
            return 2;
            break;
        default:
            std::stringstream ss;
            ss << std::string(__PRETTY_FUNCTION__) << " - "
            << "Unsupported addressing mode";
            throw std::runtime_error(ss.str());
    }
}

void Disassembler::print() const {
    uint16_t pc = cpu->getPC();

    // Clear the console
    std::cout << "\033[2J\033[H";

    // Print three instructions before and after the current PC
    auto currentIt = instructions.find(pc);
    if (currentIt == instructions.end()) {
        std::cerr << std::hex << pc << std::endl;
        std::cerr << "Error: PC not found in disassembled instructions.\n";
        exit(-1);
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