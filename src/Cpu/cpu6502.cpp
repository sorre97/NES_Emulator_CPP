#include "cpu6502.h"
#include "cpu6502_memory_map.h"
#include "cpu6502_opcodes.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

CPU6502::CPU6502(std::shared_ptr<BusInterface> bus)
    : WRAM(2 * 1024, 0), A(0), X(0), Y(0), SP(0xFD), PC(0), P(0x34), busInterface(bus) {}

void CPU6502::setFlag(StatusFlag flag, bool value) {
    if (value) {
        statusReg |= static_cast<uint8_t>(flag);
    } else {
        statusReg &= ~static_cast<uint8_t>(flag);
    }
}

bool CPU6502::getFlag(StatusFlag flag) const {
    return (statusReg & static_cast<uint8_t>(flag)) != 0;
}

/* CPU reset internal registers */
void CPU6502::reset()
{
    // Reset internal registers
    A = 0;    // Clear Accumulator
    X = 0;    // Clear X Register
    Y = 0;    // Clear Y Register
    SP = 0xFD; // Reset Stack Pointer to default
    statusReg = 0x34; // Set default status register (IRQ disabled)

    // Fetch the reset vector (little-endian)
    uint8_t lo = read(0xFFFC);
    uint8_t hi = read(0xFFFD);
    PC = static_cast<uint16_t>(hi) << 8 | lo;

    P = static_cast<uint8_t>(StatusFlag::INTERRUPT_DISABLE_FLAG) | 
        static_cast<uint8_t>(StatusFlag::UNUSED_FLAG);
}

/* Execute single instruction */
void CPU6502::step() {
    if (cycles > 0) {
        --cycles; // Decrement remaining cycles for the current instruction
        return;
    }

    uint8_t opcode = read(PC);
    ++PC;

    const OpcodeInfo& info = OPCODE_TABLE[opcode];

    // if (info.instruction == Instruction::INVALID) {
    //     // Print unsupported opcode in hex format
    //     std::stringstream ss;
    //     ss << "Unsupported opcode: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(opcode);
    //     throw std::runtime_error(ss.str());
    // }

    std::stringstream ss;
    ss << "Executing instruction: 0x" << std::hex << std::uppercase
       << static_cast<int>(opcode);
    std::cout << ss.str() << std::endl;

    // Handle the instruction (execution logic here)
    // Execute the instruction
    switch (info.instruction) {
        // Load/Store Operations
        case Instruction::LDA: // Load Accumulator
            executeLDA(info.addressingMode);
            break;
        case Instruction::LDX: // Load X Register
            executeLDX(info.addressingMode);
            break;
        case Instruction::LDY: // Load Y Register
            executeLDY(info.addressingMode);
            break;
        case Instruction::STA: // Store Accumulator
            executeSTA(info.addressingMode);
            break;
        case Instruction::STX: // Store X Register
            //executeSTX(info.addressingMode);
            break;
        case Instruction::STY: // Store Y Register
            //executeSTY(info.addressingMode);
            break;

        // Register Transfers
        case Instruction::TAX: // Transfer Accumulator to X
            //executeTAX();
            break;
        case Instruction::TXA: // Transfer X to Accumulator
            //executeTXA();
            break;
        case Instruction::TAY: // Transfer Accumulator to Y
            //executeTAY();
            break;
        case Instruction::TYA: // Transfer Y to Accumulator
            //executeTYA();
            break;

        // Stack Operations
        case Instruction::TSX: // Transfer Stack Pointer to X
            //executeTSX();
            break;
        case Instruction::TXS: // Transfer X to Stack Pointer
            executeTXS();
            break;
        case Instruction::PHA: // Push Accumulator
            //executePHA();
            break;
        case Instruction::PLA: // Pull Accumulator
            //executePLA();
            break;
        case Instruction::PHP: // Push Processor Status
            //executePHP();
            break;
        case Instruction::PLP: // Pull Processor Status
            //executePLP();
            break;

        // Logical Operations
        case Instruction::AND: // Logical AND
            //executeAND(info.addressingMode);
            break;
        case Instruction::ORA: // Logical OR
            //executeORA(info.addressingMode);
            break;
        case Instruction::EOR: // Exclusive OR
            //executeEOR(info.addressingMode);
            break;

        // Arithmetic Operations
        case Instruction::ADC: // Add with Carry
            //executeADC(info.addressingMode);
            break;
        case Instruction::SBC: // Subtract with Carry
            //executeSBC(info.addressingMode);
            break;
        case Instruction::CMP: // Compare Accumulator
            //executeCMP(info.addressingMode);
            break;
        case Instruction::CPX: // Compare X Register
            //executeCPX(info.addressingMode);
            break;
        case Instruction::CPY: // Compare Y Register
            //executeCPY(info.addressingMode);
            break;

        // Increment/Decrement Operations
        case Instruction::INC: // Increment Memory
            //executeINC(info.addressingMode);
            break;
        case Instruction::INX: // Increment X Register
            //executeINX();
            break;
        case Instruction::INY: // Increment Y Register
            //executeINY();
            break;
        case Instruction::DEC: // Decrement Memory
            //executeDEC(info.addressingMode);
            break;
        case Instruction::DEX: // Decrement X Register
            //executeDEX();
            break;
        case Instruction::DEY: // Decrement Y Register
            //executeDEY();
            break;

        // Shifts
        case Instruction::ASL: // Arithmetic Shift Left
            //executeASL(info.addressingMode);
            break;
        case Instruction::LSR: // Logical Shift Right
            //executeLSR(info.addressingMode);
            break;
        case Instruction::ROL: // Rotate Left
            //executeROL(info.addressingMode);
            break;
        case Instruction::ROR: // Rotate Right
            //executeROR(info.addressingMode);
            break;

        // Control Flow
        case Instruction::JMP: // Jump
            //executeJMP(info.addressingMode);
            break;
        case Instruction::JSR: // Jump to Subroutine
            //executeJSR();
            break;
        case Instruction::RTS: // Return from Subroutine
            //executeRTS();
            break;
        case Instruction::RTI: // Return from Interrupt
            //executeRTI();
            break;

        // Branching
        case Instruction::BCC: // Branch if Carry Clear
            //executeBCC();
            break;
        case Instruction::BCS: // Branch if Carry Set
            //executeBCS();
            break;
        case Instruction::BEQ: // Branch if Equal
            //executeBEQ();
            break;
        case Instruction::BMI: // Branch if Minus
            //executeBMI();
            break;
        case Instruction::BNE: // Branch if Not Equal
            //executeBNE();
            break;
        case Instruction::BPL: // Branch if Positive
            executeBPL();
            break;
        case Instruction::BVC: // Branch if Overflow Clear
            //executeBVC();
            break;
        case Instruction::BVS: // Branch if Overflow Set
            //executeBVS();
            break;

        // System Functions
        case Instruction::CLC: // Clear Carry Flag
            //executeCLC();
            break;
        case Instruction::SEC: // Set Carry Flag
            //executeSEC();
            break;
        case Instruction::CLI: // Clear Interrupt Disable
            //executeCLI();
            break;
        case Instruction::SEI: // Set Interrupt Disable
            executeSEI();
            break;
        case Instruction::CLD: // Clear Decimal Mode
            executeCLD();
            break;
        case Instruction::SED: // Set Decimal Mode
            //executeSED();
            break;
        case Instruction::CLV: // Clear Overflow Flag
            //executeCLV();
            break;

        // Break/No-op
        case Instruction::BRK: // Force Break
            //executeBRK();
            break;
        case Instruction::NOP: // No Operation
            //executeNOP();
            break;

        // Default case for unimplemented or invalid instructions
        default:
            throw std::runtime_error("Unimplemented instruction: 0x" +
                         [&]() -> std::string {
                             std::stringstream ss;
                             ss << std::hex << std::uppercase << static_cast<int>(info.instruction);
                             return ss.str();
                         }());
    }


    // Set the cycle count for the current instruction
    cycles = info.cycles - 1; // Account for the current cycle spent fetching
}

uint16_t CPU6502::resolveAddress(AddressingMode mode) {
    switch (mode) {
        case AddressingMode::Immediate:
        {
            // Return the address of the immediate value (current PC), then increment PC
            return PC++;
        }
        case AddressingMode::ZeroPage:
        {
            // Fetch the zero-page address from the current PC
            return read(PC++);
        }
        case AddressingMode::Absolute:
        {
            // Fetch the 16-bit absolute address from the next two bytes
            uint8_t lo = read(PC++);
            uint8_t hi = read(PC++);
            return (hi << 8) | lo;
        }
        case AddressingMode::IndirectX: {
            // Fetch zero-page address and add X register, wrap around in zero-page
            uint8_t zpAddress = (read(PC++) + X) & 0xFF;
            uint8_t lo = read(zpAddress);
            uint8_t hi = read((zpAddress + 1) & 0xFF); // Wrap around zero-page
            return (hi << 8) | lo;
        }
        case AddressingMode::IndirectY: {
            // Fetch zero-page pointer and add Y register, wrap around zero-page
            uint8_t zpAddress = read(PC++);
            uint8_t lo = read(zpAddress);
            uint8_t hi = read((zpAddress + 1) & 0xFF); // Wrap around zero-page
            uint16_t baseAddress = (hi << 8) | lo;
            return baseAddress + Y; // Add Y for final effective address
        }
        case AddressingMode::Relative: {
            int8_t offset = static_cast<int8_t>(read(PC++)); // Signed 8-bit offset
            return PC + static_cast<uint16_t>(offset); // Calculate the effective address (unsigned wrap-around subtraction)
        }
        default:
            throw std::runtime_error("Unsupported addressing mode");
    }
}

void CPU6502::executeLDY(AddressingMode mode) { 
    uint16_t address = resolveAddress(mode); // Resolve the effective address
    Y = read(address); // Load the value into the Y register

    updateZeroNegativeFlags(Y); // Update Zero and Negative flags
}

void CPU6502::executeLDA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);
    A = value;

    updateZeroNegativeFlags(A);

    // if (DEBUG) {
    //     std::cout << "Executed LDA: Loaded A with value 0x" << std::hex << std::uppercase
    //               << static_cast<int>(A) << " from address 0x" << std::setw(4) << std::setfill('0')
    //               << address << std::endl;
    // }
}

void CPU6502::executeSEI() {
    setFlag(StatusFlag::INTERRUPT_DISABLE_FLAG, true);

    // if (DEBUG) {
    //     std::cout << "Executed SEI: Interrupt Disable flag set." << std::endl;
    // }
}

void CPU6502::executeCLD() {
    setFlag(StatusFlag::DECIMAL_MODE_FLAG, false);

    // if (DEBUG) {
    //     std::cout << "Executed CLD: Decimal Mode flag cleared." << std::endl;
    // }
}

void CPU6502::executeSTA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    write(address, A);

    // if (DEBUG) {
    //     uint8_t readBackValue = read(address);
    //     std::cout << "Executed STA: Stored A (0x" << std::hex << std::uppercase
    //               << static_cast<int>(A) << ") to address 0x" << std::setw(4) << address
    //               << " | Read-back value: 0x" << std::setw(2) << static_cast<int>(readBackValue) 
    //               << (readBackValue == A ? " (Verified)" : " (Mismatch!)") 
    //               << std::endl;
    // }
}

void CPU6502::executeLDX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    X = (mode == AddressingMode::Immediate) ? read(address) : read(address);

    // Update Zero and Negative flags
    updateZeroNegativeFlags(X);

    // if (DEBUG) {
    //     std::cout << "Executed LDX: Loaded X with value 0x" << std::hex << std::uppercase
    //               << static_cast<int>(X)
    //               << " from address 0x" << std::setw(4) << std::setfill('0') << address
    //               << " | Value: 0x" << std::setw(2) << std::setfill('0') << static_cast<int>(read(address))
    //               << std::endl;
    // }
}

void CPU6502::executeTXS() {
    SP = X;

    // if (DEBUG) {
    //     std::cout << "Executed TXS: Transferred X (0x" << std::hex << std::uppercase
    //               << static_cast<int>(X) << ") to Stack Pointer (SP)." << std::endl;
    // }
}

void CPU6502::executeBPL() {
    if (!getFlag(StatusFlag::NEGATIVE_FLAG)) {           // Check if Negative Flag is clear
        uint16_t targetAddress = resolveAddress(AddressingMode::Relative); // Use resolveAddress
        uint16_t oldPC = PC;
        PC = targetAddress;                         // Apply the branch offset
        cycles++;                                   // Add cycle for taking the branch
        if ((oldPC & 0xFF00) != (PC & 0xFF00)) {    // Check if page boundary is crossed
            cycles++;
        }

        // if (DEBUG) {
        //     int8_t offset = static_cast<int8_t>(static_cast<int16_t>(PC) - static_cast<int16_t>(oldPC));
        //     std::cout << "Executed BPL: Branch taken from 0x" << std::hex << std::setw(4)
        //             << std::setfill('0') << oldPC << " to 0x" << std::hex << std::setw(4)
        //             << std::setfill('0') << PC << " (Offset: " << std::dec << static_cast<int>(offset) << ")" 
        //             << std::endl;
        // }
    } else {
        resolveAddress(AddressingMode::Relative);   // Consume the relative byte without branching
        // if (DEBUG) {
        //     std::cout << "Executed BPL: No branch taken" << std::endl;
        // }
    }
}

void CPU6502::updateZeroNegativeFlags(uint8_t value) {
    // Update Zero flag
    setFlag(StatusFlag::ZERO_FLAG, value == 0);

    // Update Negative flag (7th bit of the value)
    setFlag(StatusFlag::NEGATIVE_FLAG, value & 0x80);
}


uint8_t CPU6502::read(uint16_t address) const
{
    /* WRAM access: $0000 - $07FF */
    if (address >= WRAM_STARTADDR && address < WRAM_ENDADDR) {
        return WRAM[address];
    }
    
    /* WRAM mirrored access: $0800 - $1FFF */
    if (address >= WRAM_MIRRORS_STARTADDR && address < WRAM_MIRRORS_ENDADDR) {
        uint16_t mirror_address = address % (WRAM_ENDADDR - WRAM_STARTADDR);
        return WRAM[mirror_address];
    }

    /* PPU register access: $2000 - $2007 */
    if (address >= PPU_REGISTERS_STARTADDR && address < PPU_REGISTERS_ENDADDR) {
        // Placeholder for future PPU implementation
        return 0xFF; //TODO: ppu.readRegister(address);
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        uint16_t mirroredAddress = PPU_REGISTERS_STARTADDR + (address % 8);
        return 0xFF; //TODO: ppu.readRegister(mirroredAddress);
    }

    /* APU and I/O register access: $4000 - $401F */
    if (address >= APU_IO_STARTADDR && address < APU_IO_ENDADDR) {
        // Placeholder for future APU/IO implementation
        return 0xFF; //TODO:
    }

    /* Cartridge SRAM space access: $6000 - $7FFF */
    if (address >= CARTRIDGE_SRAM_STARTADDR && address < CARTRIDGE_SRAM_ENDADDR) {
        // Placeholder for cartridge handling
        return 0xFF; //TODO:
    }

    /* Cartridge ROM space access: $8000 - $FFFF */
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        
        return busInterface->cpuBusRead(address); //TODO: PRGROM[mapper->translatePRGaddr(address)];
    }

    /* Out of range read */
    return 0xFF;
}

void CPU6502::write(uint16_t address, uint8_t value) {
    /* WRAM access: $0000 - $07FF */
    if (address >= WRAM_STARTADDR && address < WRAM_ENDADDR) {
        WRAM[address] = value;
        return;
    }

    /* WRAM mirrored access: $0800 - $1FFF */
    if (address >= WRAM_MIRRORS_STARTADDR && address < WRAM_MIRRORS_ENDADDR) {
        uint16_t mirror_address = address % (WRAM_ENDADDR - WRAM_STARTADDR);
        WRAM[mirror_address] = value;
        return;
    }

    /* PPU register access: $2000 - $2007 */
    if (address >= PPU_REGISTERS_STARTADDR && address < PPU_REGISTERS_ENDADDR) {
        //TODO: ppu.writeRegister(address, value);
        return;
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        uint16_t mirroredAddress = PPU_REGISTERS_STARTADDR + (address % 8);
        //TODO: ppu.writeRegister(mirroredAddress, value);
        return;
    }

    /* APU and I/O register access: $4000 - $401F */
    if (address >= APU_IO_STARTADDR && address < APU_IO_ENDADDR) {
        // Placeholder for future APU/IO implementation
        return;
    }

    /* Cartridge SRAM space access: $6000 - $7FFF */
    if (address >= CARTRIDGE_SRAM_STARTADDR && address < CARTRIDGE_SRAM_ENDADDR) {
        // Placeholder for cartridge handling
        return;
    }

    /* Cartridge ROM space access: $8000 - $FFFF */
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        // ROM write ignored
        return;
    }
}

uint16_t CPU6502::getPC() const {
    return PC; // Assuming `pc` is the member variable for the Program Counter
}
