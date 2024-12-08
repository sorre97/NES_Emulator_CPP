/**
 * @file cpu6502_types.h
 * @brief Defines types and enums used by the 6502 processor.
 */

#ifndef CPU6502_TYPES_H
#define CPU6502_TYPES_H

#include <cstdint>

/**
 * @enum StatusFlag
 * @brief Represents the processor status flags in the NES 6502 CPU.
 *
 * The 6502 CPU uses an 8-bit status register (P) to store various flags
 * representing the state of the processor. Each bit corresponds to a specific flag.
 */
enum class StatusFlag : uint8_t {
    CARRY_FLAG = 1 << 0,              /**< Carry flag: Set if an arithmetic operation generates a carry out or borrow. */
    ZERO_FLAG = 1 << 1,               /**< Zero flag: Set if the result of an operation is zero. */
    INTERRUPT_DISABLE_FLAG = 1 << 2,  /**< Interrupt disable flag: Set to disable interrupts. */
    DECIMAL_MODE_FLAG = 1 << 3,       /**< Decimal mode flag: Not used in the NES. */
    BREAK_FLAG = 1 << 4,              /**< Break flag: Set when a BRK instruction is executed. */
    UNUSED_FLAG = 1 << 5,             /**< Unused flag: Always set in the NES. */
    OVERFLOW_FLAG = 1 << 6,           /**< Overflow flag: Set if an arithmetic operation causes a signed overflow. */
    NEGATIVE_FLAG = 1 << 7            /**< Negative flag: Set if the result of an operation is negative (bit 7 is set). */
};


/**
 * @enum Instruction
 * @brief Enumerates all instructions supported by the 6502 processor.
 */
enum class Instruction : uint8_t {
    ADC, AND, ASL, BCC, BCS, BEQ, BIT, BMI, BNE, BPL,
    BRK, BVC, BVS, CLC, CLD, CLI, CLV, CMP, CPX, CPY,
    DEC, DEX, DEY, EOR, INC, INX, INY, JMP, JSR, LDA,
    LDX, LDY, LSR, NOP, ORA, PHA, PHP, PLA, PLP, ROL,
    ROR, RTI, RTS, SBC, SEC, SED, SEI, STA, STX, STY,
    TAX, TAY, TSX, TXA, TXS, TYA, SLO, SAX, DCP, RLA,
    ISC, RRA, LAX, TAS, ANC, ALR, ARR, XAA, AHX, LAS,
    SHX, SRE, SHY, AXS, INVALID
};

/**
 * @enum AddressingMode
 * @brief Enumerates the addressing modes used by the 6502 processor.
 */
enum class AddressingMode : uint8_t {
    Accumulator, Absolute, AbsoluteX, AbsoluteY, Immediate,
    Implied, Indirect, IndirectX, IndirectY, Relative,
    ZeroPage, ZeroPageX, ZeroPageY, ZeroPageIndirect, INVALID
};

/**
 * @struct OpcodeInfo
 * @brief Contains information for a single opcode, including instruction, addressing mode, and cycle count.
 */
struct OpcodeInfo {
    Instruction instruction;       /**< The instruction for the opcode. */
    AddressingMode addressingMode; /**< The addressing mode for the opcode. */
    uint8_t cycles;                /**< The base number of cycles for the opcode. */
};

#endif // CPU6502_TYPES_H
