#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "Cpu/cpu6502.h"
#include "Bus/businterface.h"
#include <string>
#include <map>
#include <memory>

class Disassembler {
public:
    /**
     * @brief Constructs a Disassembler with shared pointers to CPU and BusInterface.
     * @param cpu Shared pointer to the CPU6502 instance.
     * @param bus Shared pointer to the BusInterface instance.
     */
    Disassembler(std::shared_ptr<CPU6502> cpu, std::shared_ptr<BusInterface> bus);

    /**
     * @brief Prints the disassembled instructions around the current program counter.
     */
    void print() const;

private:
    struct InstructionEntry {
        uint16_t address;
        std::string decodedInstruction;
    };

    std::shared_ptr<CPU6502> cpu; ///< Shared pointer to the CPU instance.
    std::shared_ptr<BusInterface> bus; ///< Shared pointer to the BusInterface instance.
    std::map<uint16_t, std::string> instructions; ///< Map of address to decoded instructions

    /**
     * @brief Decodes a single instruction at the given address.
     * @param address The memory address of the instruction.
     * @return The decoded instruction as a string.
     */
    std::string decodeInstruction(uint16_t address) const;

    /**
     * @brief Calculates the size of an instruction based on its opcode and addressing mode.
     * @param info The opcode information.
     * @return The size in bytes.
     */
    uint8_t calculateInstructionSize(const OpcodeInfo& info) const;

    /**
     * @brief Decompiles the entire cartridge's PRG-ROM upfront.
     */
    void decompileCartridge();
};

#endif // DISASSEMBLER_H
