#include "cpu6502_opcodes.h"

/* OPCODE + ADDRESSING_MODE table */
const OpcodeInfo OPCODE_TABLE[256] = {
    /* 0x00 - 0x0F */
    {Instruction::BRK, AddressingMode::Implied, 7},    // 0x00
    {Instruction::ORA, AddressingMode::IndirectX, 6},  // 0x01
    {Instruction::SAX, AddressingMode::ZeroPageIndirect, 6}, // 0x02    
    {Instruction::SLO, AddressingMode::IndirectY, 8},// 0x03
    {Instruction::NOP, AddressingMode::ZeroPage, 3}, // 0x04
    {Instruction::ORA, AddressingMode::ZeroPage, 3},   // 0x05
    {Instruction::ASL, AddressingMode::ZeroPage, 5},   // 0x06
    {Instruction::SLO, AddressingMode::ZeroPage, 5}, // 0x07
    {Instruction::PHP, AddressingMode::Implied, 3},    // 0x08
    {Instruction::ORA, AddressingMode::Immediate, 2},  // 0x09
    {Instruction::ASL, AddressingMode::Accumulator, 2},// 0x0A
    {Instruction::ANC, AddressingMode::Immediate, 2}, // $0B
    {Instruction::NOP, AddressingMode::Absolute, 4},// 0x0C
    {Instruction::ORA, AddressingMode::Absolute, 4},   // 0x0D
    {Instruction::ASL, AddressingMode::Absolute, 6},   // 0x0E
    {Instruction::SLO, AddressingMode::Absolute, 6}, // 0x0F

    /* 0x10 - 0x1F */
    {Instruction::BPL, AddressingMode::Relative, 2},    // 0x10
    {Instruction::ORA, AddressingMode::IndirectY, 5},   // 0x11
    {Instruction::ORA, AddressingMode::Indirect, 5}, // 0x12
    {Instruction::SLO, AddressingMode::IndirectY, 8}, // 0x13
    {Instruction::NOP, AddressingMode::ZeroPageX, 4}, // 0x14
    {Instruction::ORA, AddressingMode::ZeroPageX, 4},   // 0x15
    {Instruction::ASL, AddressingMode::ZeroPageX, 6},   // 0x16
    {Instruction::SLO, AddressingMode::ZeroPageX, 6}, // 0x17    
    {Instruction::CLC, AddressingMode::Implied, 2},     // 0x18
    {Instruction::ORA, AddressingMode::AbsoluteY, 4},   // 0x19
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0x1A
    {Instruction::SLO, AddressingMode::AbsoluteY, 7}, // 0x1B
    {Instruction::NOP, AddressingMode::AbsoluteX, 4}, // $1C
    {Instruction::ORA, AddressingMode::AbsoluteX, 4},   // 0x1D
    {Instruction::ASL, AddressingMode::AbsoluteX, 7},   // 0x1E
    {Instruction::SLO, AddressingMode::AbsoluteX, 7}, // 0x1F

    /* 0x20 - 0x2F */
    {Instruction::JSR, AddressingMode::Absolute, 6},    // 0x20
    {Instruction::AND, AddressingMode::IndirectX, 6},   // 0x21
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0x22
    {Instruction::RLA, AddressingMode::IndirectX, 8}, // 0x23
    {Instruction::BIT, AddressingMode::ZeroPage, 3},    // 0x24
    {Instruction::AND, AddressingMode::ZeroPage, 3},    // 0x25
    {Instruction::ROL, AddressingMode::ZeroPage, 5},    // 0x26
    {Instruction::RLA, AddressingMode::ZeroPage, 5}, // 0x27
    {Instruction::PLP, AddressingMode::Implied, 4},     // 0x28
    {Instruction::AND, AddressingMode::Immediate, 2},   // 0x29
    {Instruction::ROL, AddressingMode::Accumulator, 2},// 0x2A
    {Instruction::ANC, AddressingMode::Immediate, 2}, // $2B
    {Instruction::BIT, AddressingMode::Absolute, 4},    // 0x2C
    {Instruction::AND, AddressingMode::Absolute, 4},    // 0x2D
    {Instruction::ROL, AddressingMode::Absolute, 6},    // 0x2E
    {Instruction::RLA, AddressingMode::Absolute, 6}, // 0x2F

    /* 0x30 - 0x3F */
    {Instruction::BMI, AddressingMode::Relative, 2},    // 0x30
    {Instruction::AND, AddressingMode::IndirectY, 5},   // 0x31
    {Instruction::AND, AddressingMode::Indirect, 5}, // 0x32
    {Instruction::RLA, AddressingMode::IndirectY, 8}, // 0x33
    {Instruction::NOP, AddressingMode::ZeroPageX, 4}, // 0x34
    {Instruction::AND, AddressingMode::ZeroPageX, 4},   // 0x35
    {Instruction::ROL, AddressingMode::ZeroPageX, 6},   // 0x36
    {Instruction::RLA, AddressingMode::ZeroPage, 5}, // 0x37
    {Instruction::SEC, AddressingMode::Implied, 2},     // 0x38
    {Instruction::AND, AddressingMode::AbsoluteY, 4},   // 0x39
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0x3A
    {Instruction::RLA, AddressingMode::AbsoluteY, 7}, // 0x3B
    {Instruction::NOP, AddressingMode::AbsoluteX, 4}, // 0x3C
    {Instruction::AND, AddressingMode::AbsoluteX, 4},   // 0x3D
    {Instruction::ROL, AddressingMode::AbsoluteX, 7},   // 0x3E
    {Instruction::RLA, AddressingMode::AbsoluteX, 7}, // 0x3F

    /* 0x40 - 0x4F */
    {Instruction::RTI, AddressingMode::Implied, 6},     // 0x40
    {Instruction::EOR, AddressingMode::IndirectX, 6},   // 0x41
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0x42
    {Instruction::SRE, AddressingMode::IndirectX, 8}, // 0x43
    {Instruction::NOP, AddressingMode::ZeroPage, 2}, // 0x44
    {Instruction::EOR, AddressingMode::ZeroPage, 3},    // 0x45
    {Instruction::LSR, AddressingMode::ZeroPage, 5},    // 0x46
    {Instruction::SRE, AddressingMode::ZeroPage, 5}, // 0x47
    {Instruction::PHA, AddressingMode::Implied, 3},     // 0x48
    {Instruction::EOR, AddressingMode::Immediate, 2},   // 0x49
    {Instruction::LSR, AddressingMode::Accumulator, 2}, // 0x4A
    {Instruction::ALR, AddressingMode::Immediate, 2}, // $4B
    {Instruction::JMP, AddressingMode::Absolute, 3},    // 0x4C
    {Instruction::EOR, AddressingMode::Absolute, 4},    // 0x4D
    {Instruction::LSR, AddressingMode::Absolute, 6},    // 0x4E
    {Instruction::SRE, AddressingMode::Absolute, 6}, // 0x4F

    /* 0x50 - 0x5F */
    {Instruction::BVC, AddressingMode::Relative, 2},    // 0x50
    {Instruction::EOR, AddressingMode::IndirectY, 5},   // 0x51
    {Instruction::EOR, AddressingMode::Indirect, 5}, // 0x52
    {Instruction::SRE, AddressingMode::IndirectY, 8}, // 0x53
    {Instruction::NOP, AddressingMode::ZeroPageX, 4}, // 0x54
    {Instruction::EOR, AddressingMode::ZeroPageX, 4},   // 0x55
    {Instruction::LSR, AddressingMode::ZeroPageX, 6},   // 0x56
    {Instruction::SRE, AddressingMode::ZeroPageX, 6}, // 0x57
    {Instruction::CLI, AddressingMode::Implied, 2},     // 0x58
    {Instruction::EOR, AddressingMode::AbsoluteY, 4},   // 0x59
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0x5A
    {Instruction::SRE, AddressingMode::AbsoluteY, 7}, // 0x5B
    {Instruction::NOP, AddressingMode::AbsoluteX, 4}, // 0x5C
    {Instruction::EOR, AddressingMode::AbsoluteX, 4},   // 0x5D
    {Instruction::LSR, AddressingMode::AbsoluteX, 7},   // 0x5E
    {Instruction::SRE, AddressingMode::AbsoluteX, 7}, // 0x5F

    /* 0x60 - 0x6F */
    {Instruction::RTS, AddressingMode::Implied, 6},     // 0x60
    {Instruction::ADC, AddressingMode::IndirectX, 6},   // 0x61
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0x62
    {Instruction::RRA, AddressingMode::IndirectX, 8}, // 0x63
    {Instruction::NOP, AddressingMode::ZeroPage, 3}, // 0x64
    {Instruction::ADC, AddressingMode::ZeroPage, 3},    // 0x65
    {Instruction::ROR, AddressingMode::ZeroPage, 5},    // 0x66
    {Instruction::RRA, AddressingMode::ZeroPage, 5}, // 0x67
    {Instruction::PLA, AddressingMode::Implied, 4},     // 0x68
    {Instruction::ADC, AddressingMode::Immediate, 2},   // 0x69
    {Instruction::ROR, AddressingMode::Accumulator, 2}, // 0x6A
    {Instruction::ARR, AddressingMode::Immediate, 2}, // $6B
    {Instruction::JMP, AddressingMode::Indirect, 5},    // 0x6C
    {Instruction::ADC, AddressingMode::Absolute, 4},    // 0x6D
    {Instruction::ROR, AddressingMode::Absolute, 6},    // 0x6E
    {Instruction::RRA, AddressingMode::Absolute, 6}, // 0x6F

    /* 0x70 - 0x7F */
    {Instruction::BVS, AddressingMode::Relative, 2},    // 0x70
    {Instruction::ADC, AddressingMode::IndirectY, 5},   // 0x71
    {Instruction::ADC, AddressingMode::Indirect, 5}, // 0x72
    {Instruction::RRA, AddressingMode::IndirectX, 8}, // 0x73
    {Instruction::NOP, AddressingMode::ZeroPageX, 4}, // 0x74
    {Instruction::ADC, AddressingMode::ZeroPageX, 4},   // 0x75
    {Instruction::ROR, AddressingMode::ZeroPageX, 6},   // 0x76
    {Instruction::RRA, AddressingMode::ZeroPageX, 6}, // 0x77
    {Instruction::SEI, AddressingMode::Implied, 2},     // 0x78
    {Instruction::ADC, AddressingMode::AbsoluteY, 4},   // 0x79
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0x7A
    {Instruction::RRA, AddressingMode::AbsoluteY, 7}, // 0x7B
    {Instruction::NOP, AddressingMode::AbsoluteX, 4}, // 0x7C
    {Instruction::ADC, AddressingMode::AbsoluteX, 4},   // 0x7D
    {Instruction::ROR, AddressingMode::AbsoluteX, 7},   // 0x7E
    {Instruction::RRA, AddressingMode::AbsoluteX, 7}, // 0x7F

    /* 0x80 - 0x8F */
    {Instruction::NOP, AddressingMode::Immediate, 2}, // 0x80
    {Instruction::STA, AddressingMode::IndirectX, 6},   // 0x81
    {Instruction::NOP, AddressingMode::Immediate, 2}, // 0x82
    {Instruction::SAX, AddressingMode::IndirectX, 6}, // 0x83
    {Instruction::STY, AddressingMode::ZeroPage, 3},    // 0x84
    {Instruction::STA, AddressingMode::ZeroPage, 3},    // 0x85
    {Instruction::STX, AddressingMode::ZeroPage, 3},    // 0x86
    {Instruction::SAX, AddressingMode::ZeroPage, 3}, // 0x87
    {Instruction::DEY, AddressingMode::Implied, 2},     // 0x88
    {Instruction::NOP, AddressingMode::Immediate, 2}, // 0x89
    {Instruction::TXA, AddressingMode::Implied, 2},     // 0x8A
    {Instruction::XAA, AddressingMode::Immediate, 2}, // 0x8B
    {Instruction::STY, AddressingMode::Absolute, 4},    // 0x8C
    {Instruction::STA, AddressingMode::Absolute, 4},    // 0x8D
    {Instruction::STX, AddressingMode::Absolute, 4},    // 0x8E
    {Instruction::SAX, AddressingMode::Absolute, 4},  // 0x8F

    /* 0x90 - 0x9F */
    {Instruction::BCC, AddressingMode::Relative, 2},    // 0x90
    {Instruction::STA, AddressingMode::IndirectY, 6},   // 0x91
    {Instruction::STA, AddressingMode::IndirectY, 5}, // 0x92
    {Instruction::AHX, AddressingMode::IndirectY, 6}, // 0x93
    {Instruction::STY, AddressingMode::ZeroPageX, 4},   // 0x94
    {Instruction::STA, AddressingMode::ZeroPageX, 4},   // 0x95
    {Instruction::STX, AddressingMode::ZeroPageY, 4},   // 0x96
    {Instruction::SAX, AddressingMode::ZeroPageY, 4}, // 0x97
    {Instruction::TYA, AddressingMode::Implied, 2},     // 0x98
    {Instruction::STA, AddressingMode::AbsoluteY, 5},   // 0x99
    {Instruction::TXS, AddressingMode::Implied, 2},     // 0x9A
    {Instruction::TAS, AddressingMode::AbsoluteY, 5}, // 0x9B
    {Instruction::SHY, AddressingMode::AbsoluteX, 5}, // 0x9C
    {Instruction::STA, AddressingMode::AbsoluteX, 5},   // 0x9D
    {Instruction::SHX, AddressingMode::AbsoluteY, 5}, // 0x9E
    {Instruction::SHX, AddressingMode::AbsoluteY, 5}, // 0x9F

    /* 0xA0 - 0xAF */
    {Instruction::LDY, AddressingMode::Immediate, 2},   // 0xA0
    {Instruction::LDA, AddressingMode::IndirectX, 6},   // 0xA1
    {Instruction::LDX, AddressingMode::Immediate, 2},   // 0xA2
    {Instruction::LAX, AddressingMode::IndirectX, 6}, // 0xA3
    {Instruction::LDY, AddressingMode::ZeroPage, 3},    // 0xA4
    {Instruction::LDA, AddressingMode::ZeroPage, 3},    // 0xA5
    {Instruction::LDX, AddressingMode::ZeroPage, 3},    // 0xA6
    {Instruction::LAX, AddressingMode::ZeroPage, 3}, // 0xA7
    {Instruction::TAY, AddressingMode::Implied, 2},     // 0xA8
    {Instruction::LDA, AddressingMode::Immediate, 2},   // 0xA9
    {Instruction::TAX, AddressingMode::Implied, 2},     // 0xAA
    {Instruction::LAX, AddressingMode::Immediate, 2}, // 0xAB
    {Instruction::LDY, AddressingMode::Absolute, 4},    // 0xAC
    {Instruction::LDA, AddressingMode::Absolute, 4},    // 0xAD
    {Instruction::LDX, AddressingMode::Absolute, 4},    // 0xAE
    {Instruction::LAX, AddressingMode::Absolute, 4}, // 0xAF

    /* 0xB0 - 0xBF */
    {Instruction::BCS, AddressingMode::Relative, 2},    // 0xB0
    {Instruction::LDA, AddressingMode::IndirectY, 5},   // 0xB1
    {Instruction::LDA, AddressingMode::Indirect, 5}, // 0xB2
    {Instruction::LAX, AddressingMode::IndirectY, 5}, // 0xB3
    {Instruction::LDY, AddressingMode::ZeroPageX, 4},   // 0xB4
    {Instruction::LDA, AddressingMode::ZeroPageX, 4},   // 0xB5
    {Instruction::LDX, AddressingMode::ZeroPageY, 4},   // 0xB6
    {Instruction::LAX, AddressingMode::ZeroPageY, 4}, // 0xB7
    {Instruction::CLV, AddressingMode::Implied, 2},     // 0xB8
    {Instruction::LDA, AddressingMode::AbsoluteY, 4},   // 0xB9
    {Instruction::TSX, AddressingMode::Implied, 2},     // 0xBA
    {Instruction::LAS, AddressingMode::AbsoluteY, 4}, // 0xBB
    {Instruction::LDY, AddressingMode::AbsoluteX, 4},   // 0xBC
    {Instruction::LDA, AddressingMode::AbsoluteX, 4},   // 0xBD
    {Instruction::LDX, AddressingMode::AbsoluteY, 4},   // 0xBE
    {Instruction::LAX, AddressingMode::AbsoluteY, 4}, // 0xBF

    /* 0xC0 - 0xCF */
    {Instruction::CPY, AddressingMode::Immediate, 2},   // 0xC0
    {Instruction::CMP, AddressingMode::IndirectX, 6},   // 0xC1
    {Instruction::NOP, AddressingMode::Immediate, 2}, // 0xC2
    {Instruction::DCP, AddressingMode::IndirectX, 8}, // 0xC3
    {Instruction::CPY, AddressingMode::ZeroPage, 3},    // 0xC4
    {Instruction::CMP, AddressingMode::ZeroPage, 3},    // 0xC5
    {Instruction::DEC, AddressingMode::ZeroPage, 5},    // 0xC6
    {Instruction::DCP, AddressingMode::ZeroPage, 5}, // 0xC7
    {Instruction::INY, AddressingMode::Implied, 2},     // 0xC8
    {Instruction::CMP, AddressingMode::Immediate, 2},   // 0xC9
    {Instruction::DEX, AddressingMode::Implied, 2},     // 0xCA
    {Instruction::AXS, AddressingMode::Immediate, 2}, // 0xCB
    {Instruction::CPY, AddressingMode::Absolute, 4},    // 0xCC
    {Instruction::CMP, AddressingMode::Absolute, 4},    // 0xCD
    {Instruction::DEC, AddressingMode::Absolute, 6},    // 0xCE
    {Instruction::DCP, AddressingMode::AbsoluteX, 7}, // 0xCF


    /* 0xD0 - 0xDF */
    {Instruction::BNE, AddressingMode::Relative, 2},    // 0xD0
    {Instruction::CMP, AddressingMode::IndirectY, 5},   // 0xD1
    {Instruction::CMP, AddressingMode::Indirect, 5}, // 0xD2
    {Instruction::DCP, AddressingMode::IndirectY, 8}, // 0xD3
    {Instruction::NOP, AddressingMode::ZeroPageX, 4}, // 0xD4
    {Instruction::CMP, AddressingMode::ZeroPageX, 4},   // 0xD5
    {Instruction::DEC, AddressingMode::ZeroPageX, 6},   // 0xD6
    {Instruction::DCP, AddressingMode::ZeroPageX, 6}, // 0xD7
    {Instruction::CLD, AddressingMode::Implied, 2},     // 0xD8
    {Instruction::CMP, AddressingMode::AbsoluteY, 4},   // 0xD9
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0xDA
    {Instruction::DCP, AddressingMode::AbsoluteY, 7}, // 0xDB
    {Instruction::NOP, AddressingMode::Absolute, 4}, // 0xDC
    {Instruction::CMP, AddressingMode::AbsoluteX, 4},   // 0xDD
    {Instruction::DEC, AddressingMode::AbsoluteX, 7},   // 0xDE
    {Instruction::DCP, AddressingMode::AbsoluteX, 7}, // 0xDF

    /* 0xE0 - 0xEF */
    {Instruction::CPX, AddressingMode::Immediate, 2},   // 0xE0
    {Instruction::SBC, AddressingMode::IndirectX, 6},   // 0xE1
    {Instruction::NOP, AddressingMode::Immediate, 2}, // 0xE2
    {Instruction::ISC, AddressingMode::IndirectX, 8}, // 0xE3
    {Instruction::CPX, AddressingMode::ZeroPage, 3},    // 0xE4
    {Instruction::SBC, AddressingMode::ZeroPage, 3},    // 0xE5
    {Instruction::INC, AddressingMode::ZeroPage, 5},    // 0xE6
    {Instruction::ISC, AddressingMode::ZeroPage, 5},    // 0xE7
    {Instruction::INX, AddressingMode::Implied, 2},     // 0xE8
    {Instruction::SBC, AddressingMode::Immediate, 2},   // 0xE9
    {Instruction::NOP, AddressingMode::Implied, 2},     // 0xEA
    {Instruction::SBC, AddressingMode::Immediate, 2}, // 0xEB
    {Instruction::CPX, AddressingMode::Absolute, 4},    // 0xEC
    {Instruction::SBC, AddressingMode::Absolute, 4},    // 0xED
    {Instruction::INC, AddressingMode::Absolute, 6},    // 0xEE
    {Instruction::ISC, AddressingMode::Absolute, 6}, // 0xEF

    /* 0xF0 - 0xFF */
    {Instruction::BEQ, AddressingMode::Relative, 2},    // 0xF0
    {Instruction::SBC, AddressingMode::IndirectY, 5},   // 0xF1
    {Instruction::SBC, AddressingMode::Indirect, 5}, // 0xF2
    {Instruction::ISC, AddressingMode::IndirectY, 8}, // 0xF3
    {Instruction::NOP, AddressingMode::ZeroPageX, 4}, // 0xF4
    {Instruction::SBC, AddressingMode::ZeroPageX, 4},   // 0xF5
    {Instruction::INC, AddressingMode::ZeroPageX, 6},   // 0xF6
    {Instruction::ISC, AddressingMode::ZeroPageX, 6}, // 0xF7
    {Instruction::SED, AddressingMode::Implied, 2},     // 0xF8
    {Instruction::SBC, AddressingMode::AbsoluteY, 4},   // 0xF9
    {Instruction::NOP, AddressingMode::Implied, 2}, // 0xFA
    {Instruction::ISC, AddressingMode::AbsoluteY, 7}, // 0xFB
    {Instruction::NOP, AddressingMode::AbsoluteX, 4}, // 0xFC
    {Instruction::SBC, AddressingMode::AbsoluteX, 4},   // 0xFD
    {Instruction::INC, AddressingMode::AbsoluteX, 7},   // 0xFE
    {Instruction::ISC, AddressingMode::AbsoluteX, 7}, // 0xFF
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
    {Instruction::TXS, "TXS"}, {Instruction::TYA, "TYA"}, {Instruction::SLO, "SLO"},
    {Instruction::SAX, "SAX"}, {Instruction::DCP, "DCP"}, {Instruction::RLA, "RLA"}, 
    {Instruction::ISC, "ISC"}, {Instruction::RRA, "RRA"}, {Instruction::LAX, "LAX"},
    {Instruction::TAS, "TAS"}, {Instruction::ANC, "ANC"}, {Instruction::ALR, "ALR"}, 
    {Instruction::ARR, "ARR"}, {Instruction::XAA, "XAA"}, {Instruction::AHX, "AHX"}, 
    {Instruction::LAS, "LAS"}, {Instruction::SHX, "SHX"}, {Instruction::SRE, "SRE"}, 
    {Instruction::SHY, "SHY"}, {Instruction::AXS, "AXS"}, {Instruction::INVALID, "???"}
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
    {AddressingMode::ZeroPageIndirect, "ZeroPageIndirect"},
    {AddressingMode::INVALID, "INVALID"}
};