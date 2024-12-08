#include "cpu.h"
#include <iostream>
#include <iomanip>
#include "config.h"
#include <sstream>

/* OPCODE + ADDRESSING_MODE table */
const OpcodeInfo OPCODE_TABLE[256] = {
    /* 0x00 - 0x0F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x00
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x01
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x02
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x03
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x04
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x05
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x06
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x07
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x08
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x09
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x0A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x0B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x0C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x0D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x0E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x0F

    /* 0x10 - 0x1F */
    {Instruction::BPL, AddressingMode::Relative, 2},    // 0x10
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x11
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x12
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x13
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x14
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x15
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x16
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x17
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x18
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x19
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x1A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x1B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x1C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x1D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x1E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x1F

    /* 0x20 - 0x2F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x20
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x21
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x22
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x23
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x24
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x25
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x26
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x27
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x28
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x29
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x2A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x2B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x2C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x2D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x2E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x2F

    /* 0x30 - 0x3F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x30
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x31
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x32
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x33
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x34
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x35
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x36
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x37
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x38
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x39
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x3A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x3B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x3C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x3D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x3E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x3F

    /* 0x40 - 0x4F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x40
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x41
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x42
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x43
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x44
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x45
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x46
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x47
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x48
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x49
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x4A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x4B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x4C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x4D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x4E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x4F

    /* 0x50 - 0x5F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x50
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x51
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x52
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x53
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x54
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x55
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x56
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x57
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x58
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x59
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x5A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x5B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x5C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x5D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x5E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x5F

    /* 0x60 - 0x6F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x60
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x61
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x62
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x63
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x64
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x65
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x66
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x67
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x68
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x69
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x6A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x6B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x6C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x6D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x6E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x6F

    /* 0x70 - 0x7F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x70
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x71
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x72
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x73
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x74
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x75
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x76
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x77
    {Instruction::SEI, AddressingMode::Implied, 2},    // 0x78
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x79
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x7A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x7B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x7C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x7D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x7E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x7F

    /* 0x80 - 0x8F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x80
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x81
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x82
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x83
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x84
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x85
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x86
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x87
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x88
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x89
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x8A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x8B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x8C
    {Instruction::STA, AddressingMode::Absolute, 4},    // 0x8D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x8E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x8F

    /* 0x90 - 0x9F */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x90
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x91
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x92
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x93
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x94
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x95
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x96
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x97
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x98
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x99
    {Instruction::TXS, AddressingMode::Implied, 2},    // 0x9A
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x9B
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x9C
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x9D
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x9E
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0x9F

    /* 0xA0 - 0xAF */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA0
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA1
    {Instruction::LDX, AddressingMode::Immediate, 2},    // 0xA2
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA3
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA4
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA5
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA6
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA7
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xA8
    {Instruction::LDA, AddressingMode::Immediate, 2},      // 0xA9
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xAA
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xAB
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xAC
    {Instruction::LDA, AddressingMode::Absolute, 4},    // 0xAD
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xAE
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xAF

    /* 0xB0 - 0xBF */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB0
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB1
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB2
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB3
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB4
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB5
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB6
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB7
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB8
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xB9
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xBA
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xBB
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xBC
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xBD
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xBE
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xBF

    /* 0xC0 - 0xCF */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc0
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc1
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc2
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc3
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc4
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc5
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc6
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc7
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc8
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xc9
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xcA
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xcB
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xcC
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xcD
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xcE
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xcF

    /* 0xD0 - 0xDF */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD0
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD1
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD2
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD3
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD4
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD5
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD6
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD7
    {Instruction::CLD, AddressingMode::Implied, 2},    // 0xD8
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xD9
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xDA
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xDB
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xDC
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xDD
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xDE
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xDF

    /* 0xE0 - 0xEF */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE0
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE1
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE2
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE3
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE4
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE5
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE6
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE7
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE8
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xE9
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xEA
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xEB
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xEC
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xED
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xEE
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xEF

    /* 0xF0 - 0xFF */
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF0
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF1
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF2
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF3
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF4
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF5
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF6
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF7
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF8
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xF9
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xFA
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xFB
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xFC
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xFD
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xFE
    {Instruction::INVALID, AddressingMode::INVALID, 0},    // 0xFF
};


namespace NES {

CPU::CPU(Memory& memory)
    : A(0), X(0), Y(0), SP(0xFD), PC(0), P(0x34), memory(memory) {}

void CPU::reset() {
    // Fetch reset vector ($FFFC-$FFFD)
    uint16_t lo = read(0xFFFC);
    uint16_t hi = read(0xFFFD);
    PC = (hi << 8) | lo;

    // Set default register values
    SP = 0xFD; // Stack Pointer default
    P = INTERRUPT_DISABLE | UNUSED; // Default flags
    A = X = Y = 0;
}

void CPU::step() {
    if (cycles > 0) {
        --cycles; // Decrement remaining cycles for the current instruction
        return;
    }

    uint8_t opcode = read(PC++);
    const OpcodeInfo& info = OPCODE_TABLE[opcode];

    // Print debug information
    if(DEBUG)
    {
        std::cout << "Executing opcode: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                << static_cast<int>(opcode)
                << " | Instruction: " << toString(info.instruction)
                << " | Addressing Mode: " << toString(info.addressingMode)
                << " | Cycles: " << static_cast<int>(info.cycles)
                << std::endl;
    }

    if (info.instruction == Instruction::INVALID) {
        // Print unsupported opcode in hex format
        std::stringstream ss;
        ss << "Unsupported opcode: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(opcode);
        throw std::runtime_error(ss.str());
    }

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
            //executeLDY(info.addressingMode);
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
            throw std::runtime_error("Unimplemented instruction: " +
                                    std::to_string(static_cast<int>(info.instruction)));
    }


    // Set the cycle count for the current instruction
    cycles = info.cycles - 1; // Account for the current cycle spent fetching

    if(DEBUG)
    {
        printCPUState();
    }
}

std::string CPU::toString(Instruction instruction) const {
    switch (instruction) {
        case Instruction::ADC: return "ADC";
        case Instruction::AND: return "AND";
        case Instruction::ASL: return "ASL";
        case Instruction::BCC: return "BCC";
        case Instruction::BCS: return "BCS";
        case Instruction::BEQ: return "BEQ";
        case Instruction::BIT: return "BIT";
        case Instruction::BMI: return "BMI";
        case Instruction::BNE: return "BNE";
        case Instruction::BPL: return "BPL";
        case Instruction::BRK: return "BRK";
        case Instruction::BVC: return "BVC";
        case Instruction::BVS: return "BVS";
        case Instruction::CLC: return "CLC";
        case Instruction::CLD: return "CLD";
        case Instruction::CLI: return "CLI";
        case Instruction::CLV: return "CLV";
        case Instruction::CMP: return "CMP";
        case Instruction::CPX: return "CPX";
        case Instruction::CPY: return "CPY";
        case Instruction::DEC: return "DEC";
        case Instruction::DEX: return "DEX";
        case Instruction::DEY: return "DEY";
        case Instruction::EOR: return "EOR";
        case Instruction::INC: return "INC";
        case Instruction::INX: return "INX";
        case Instruction::INY: return "INY";
        case Instruction::JMP: return "JMP";
        case Instruction::JSR: return "JSR";
        case Instruction::LDA: return "LDA";
        case Instruction::LDX: return "LDX";
        case Instruction::LDY: return "LDY";
        case Instruction::LSR: return "LSR";
        case Instruction::NOP: return "NOP";
        case Instruction::ORA: return "ORA";
        case Instruction::PHA: return "PHA";
        case Instruction::PHP: return "PHP";
        case Instruction::PLA: return "PLA";
        case Instruction::PLP: return "PLP";
        case Instruction::ROL: return "ROL";
        case Instruction::ROR: return "ROR";
        case Instruction::RTI: return "RTI";
        case Instruction::RTS: return "RTS";
        case Instruction::SBC: return "SBC";
        case Instruction::SEC: return "SEC";
        case Instruction::SED: return "SED";
        case Instruction::SEI: return "SEI";
        case Instruction::STA: return "STA";
        case Instruction::STX: return "STX";
        case Instruction::STY: return "STY";
        case Instruction::TAX: return "TAX";
        case Instruction::TAY: return "TAY";
        case Instruction::TSX: return "TSX";
        case Instruction::TXA: return "TXA";
        case Instruction::TXS: return "TXS";
        case Instruction::TYA: return "TYA";
        default: return "INVALID";
    }
}

std::string CPU::toString(AddressingMode mode) const {
    switch (mode) {
        case AddressingMode::Immediate: return "Immediate";
        case AddressingMode::ZeroPage: return "Zero Page";
        case AddressingMode::ZeroPageX: return "Zero Page, X";
        case AddressingMode::ZeroPageY: return "Zero Page, Y";
        case AddressingMode::Absolute: return "Absolute";
        case AddressingMode::AbsoluteX: return "Absolute, X";
        case AddressingMode::AbsoluteY: return "Absolute, Y";
        case AddressingMode::IndirectX: return "Indirect, X";
        case AddressingMode::IndirectY: return "Indirect, Y";
        case AddressingMode::Implied: return "Implied";
        case AddressingMode::Accumulator: return "Accumulator";
        case AddressingMode::Relative: return "Relative";
        default: return "INVALID";
    }
}

void CPU::executeLDA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = (mode == AddressingMode::Immediate) ? read(address) : read(address);
    A = value;

    updateZeroNegativeFlags(A);

    if (DEBUG) {
        std::cout << "Executed LDA: Loaded A with value 0x" << std::hex << std::uppercase
                  << static_cast<int>(A) << " from address 0x" << std::setw(4) << std::setfill('0')
                  << address << std::endl;
    }
}

void CPU::executeSEI() {
    setFlag(StatusFlag::INTERRUPT_DISABLE, true);

    if (DEBUG) {
        std::cout << "Executed SEI: Interrupt Disable flag set." << std::endl;
    }
}

void CPU::executeCLD() {
    setFlag(StatusFlag::DECIMAL_MODE, false);

    if (DEBUG) {
        std::cout << "Executed CLD: Decimal Mode flag cleared." << std::endl;
    }
}

void CPU::executeSTA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    write(address, A);

    if (DEBUG) {
        uint8_t readBackValue = read(address);
        std::cout << "Executed STA: Stored A (0x" << std::hex << std::uppercase
                  << static_cast<int>(A) << ") to address 0x" << std::setw(4) << address
                  << " | Read-back value: 0x" << std::setw(2) << static_cast<int>(readBackValue) 
                  << (readBackValue == A ? " (Verified)" : " (Mismatch!)") 
                  << std::endl;
    }
}

void CPU::executeLDX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    X = (mode == AddressingMode::Immediate) ? read(address) : read(address);

    // Update Zero and Negative flags
    updateZeroNegativeFlags(X);

    if (DEBUG) {
        std::cout << "Executed LDX: Loaded X with value 0x" << std::hex << std::uppercase
                  << static_cast<int>(X)
                  << " from address 0x" << std::setw(4) << std::setfill('0') << address
                  << " | Value: 0x" << std::setw(2) << std::setfill('0') << static_cast<int>(read(address))
                  << std::endl;
    }
}

void CPU::executeTXS() {
    SP = X;

    if (DEBUG) {
        std::cout << "Executed TXS: Transferred X (0x" << std::hex << std::uppercase
                  << static_cast<int>(X) << ") to Stack Pointer (SP)." << std::endl;
    }
}

void CPU::executeBPL() {
    if (!getFlag(StatusFlag::NEGATIVE)) {           // Check if Negative Flag is clear
        uint16_t targetAddress = resolveAddress(AddressingMode::Relative); // Use resolveAddress
        uint16_t oldPC = PC;
        PC = targetAddress;                         // Apply the branch offset
        cycles++;                                   // Add cycle for taking the branch
        if ((oldPC & 0xFF00) != (PC & 0xFF00)) {    // Check if page boundary is crossed
            cycles++;
        }

        if (DEBUG) {
            int8_t offset = static_cast<int8_t>(static_cast<int16_t>(PC) - static_cast<int16_t>(oldPC));
            std::cout << "Executed BPL: Branch taken from 0x" << std::hex << std::setw(4)
                    << std::setfill('0') << oldPC << " to 0x" << std::hex << std::setw(4)
                    << std::setfill('0') << PC << " (Offset: " << std::dec << static_cast<int>(offset) << ")" 
                    << std::endl;
        }
    } else {
        resolveAddress(AddressingMode::Relative);   // Consume the relative byte without branching
        if (DEBUG) {
            std::cout << "Executed BPL: No branch taken" << std::endl;
        }
    }
}


uint16_t CPU::resolveAddress(AddressingMode mode) {
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
            std::stringstream ss;
            ss << std::string(__PRETTY_FUNCTION__) << " - "
            << "Unsupported addressing mode";
            throw std::runtime_error(ss.str());
    }
}

void CPU::updateZeroNegativeFlags(uint8_t value) {
    // Update Zero flag
    setFlag(StatusFlag::ZERO, value == 0);

    // Update Negative flag (7th bit of the value)
    setFlag(StatusFlag::NEGATIVE, value & 0x80);
}


uint8_t CPU::read(uint16_t address) {
    return memory.CPUread(address);
}

void CPU::write(uint16_t address, uint8_t value) {
    memory.CPUwrite(address, value);
}

// Flag manipulation
void CPU::setFlag(StatusFlag flag, bool value) {
    if (value) {
        P |= flag;
    } else {
        P &= ~flag;
    }
}

bool CPU::getFlag(StatusFlag flag) const {
    return P & flag;
}

void CPU::printCPUState() const {
    std::cout << "\n+---------------------+" << std::endl;
    std::cout << "|    CPU STATE       |" << std::endl;
    std::cout << "+---------------------+" << std::endl;

    // Registers
    std::cout << "| Registers           |" << std::endl;
    std::cout << "+---------------------+" << std::endl;
    std::cout << "| A  | 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(A) << "      |" << std::endl;
    std::cout << "| X  | 0x" << std::setw(2) << static_cast<int>(X) << "      |" << std::endl;
    std::cout << "| Y  | 0x" << std::setw(2) << static_cast<int>(Y) << "      |" << std::endl;
    std::cout << "| SP | 0x" << std::setw(2) << static_cast<int>(SP) << "      |" << std::endl;
    std::cout << "| PC | 0x" << std::setw(4) << PC << "   |" << std::endl;

    // Status Flags
    std::cout << "+---------------------+" << std::endl;
    std::cout << "| Status Flags        |" << std::endl;
    std::cout << "+---------------------+" << std::endl;
    std::cout << "| N (Negative)   | " << ((P & NEGATIVE) ? "1" : "0") << "   |" << std::endl;
    std::cout << "| V (Overflow)   | " << ((P & OVERFLOW_FLAG) ? "1" : "0") << "   |" << std::endl;
    std::cout << "| D (Decimal)    | " << ((P & DECIMAL_MODE) ? "1" : "0") << "   |" << std::endl;
    std::cout << "| I (Interrupt Disable)  | " << ((P & INTERRUPT_DISABLE) ? "1" : "0") << "   |" << std::endl;
    std::cout << "| Z (Zero)       | " << ((P & ZERO) ? "1" : "0") << "   |" << std::endl;
    std::cout << "| C (Carry)      | " << ((P & CARRY) ? "1" : "0") << "   |" << std::endl;
    std::cout << "+---------------------+" << std::endl;
}

} // namespace NES