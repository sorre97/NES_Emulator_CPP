#include "cpu6502_opcodes.h"

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
    {Instruction::LDY, AddressingMode::Immediate, 0},    // 0xA0
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

// Static map initialization
const std::unordered_map<Instruction, std::string> InstructionToStringMap = {
    {Instruction::ADC, "ADC"}, {Instruction::AND, "AND"}, {Instruction::ASL, "ASL"},
    {Instruction::BCC, "BCC"}, {Instruction::BCS, "BCS"}, {Instruction::BEQ, "BEQ"},
    {Instruction::BIT, "BIT"}, {Instruction::BMI, "BMI"}, {Instruction::BNE, "BNE"},
    {Instruction::BPL, "BPL"}, {Instruction::BRK, "BRK"}, {Instruction::BVC, "BVC"},
    {Instruction::BVS, "BVS"}, {Instruction::CLC, "CLC"}, {Instruction::CLD, "CLD"},
    {Instruction::CLI, "CLI"}, {Instruction::CLV, "CLV"}, {Instruction::CMP, "CMP"},
    {Instruction::CPX, "CPX"}, {Instruction::CPY, "CPY"}, {Instruction::DEC, "DEC"},
    {Instruction::DEX, "DEX"}, {Instruction::DEY, "DEY"}, {Instruction::EOR, "EOR"},
    {Instruction::INC, "INC"}, {Instruction::INX, "INX"}, {Instruction::INY, "INY"},
    {Instruction::JMP, "JMP"}, {Instruction::JSR, "JSR"}, {Instruction::LDA, "LDA"},
    {Instruction::LDX, "LDX"}, {Instruction::LDY, "LDY"}, {Instruction::LSR, "LSR"},
    {Instruction::NOP, "NOP"}, {Instruction::ORA, "ORA"}, {Instruction::PHA, "PHA"},
    {Instruction::PHP, "PHP"}, {Instruction::PLA, "PLA"}, {Instruction::PLP, "PLP"},
    {Instruction::ROL, "ROL"}, {Instruction::ROR, "ROR"}, {Instruction::RTI, "RTI"},
    {Instruction::RTS, "RTS"}, {Instruction::SBC, "SBC"}, {Instruction::SEC, "SEC"},
    {Instruction::SED, "SED"}, {Instruction::SEI, "SEI"}, {Instruction::STA, "STA"},
    {Instruction::STX, "STX"}, {Instruction::STY, "STY"}, {Instruction::TAX, "TAX"},
    {Instruction::TAY, "TAY"}, {Instruction::TSX, "TSX"}, {Instruction::TXA, "TXA"},
    {Instruction::TXS, "TXS"}, {Instruction::TYA, "TYA"}, {Instruction::INVALID, "???"}
};

// Define and populate the AddressingModeToStringMap
const std::unordered_map<AddressingMode, std::string> AddressingModeToStringMap = {
    {AddressingMode::Accumulator, "Accumulator"},
    {AddressingMode::Absolute, "Absolute"},
    {AddressingMode::AbsoluteX, "AbsoluteX"},
    {AddressingMode::AbsoluteY, "AbsoluteY"},
    {AddressingMode::Immediate, "Immediate"},
    {AddressingMode::Implied, "Implied"},
    {AddressingMode::Indirect, "Indirect"},
    {AddressingMode::IndirectX, "IndirectX"},
    {AddressingMode::IndirectY, "IndirectY"},
    {AddressingMode::Relative, "Relative"},
    {AddressingMode::ZeroPage, "ZeroPage"},
    {AddressingMode::ZeroPageX, "ZeroPageX"},
    {AddressingMode::ZeroPageY, "ZeroPageY"},
    {AddressingMode::INVALID, "INVALID"}
};