/**
 * @file cpu6502_opcodes.h
 * @brief Declares the opcode table for the 6502 processor.
 */

#ifndef CPU6502_OPCODES_H
#define CPU6502_OPCODES_H

#include "cpu6502_types.h"
#include <unordered_map>
#include <string> // Required for std::string

/**
 * @var OPCODE_TABLE
 * @brief Lookup table for all 6502 opcodes, including instruction, addressing mode, and cycle count.
 */
extern const OpcodeInfo OPCODE_TABLE[256];

extern const std::unordered_map<Instruction, std::string> InstructionToStringMap;

// Extern map declaration
extern const std::unordered_map<AddressingMode, std::string> AddressingModeToStringMap;

#endif // CPU6502_OPCODES_H
