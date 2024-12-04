/**
 * @file cpu6502.h
 * @brief Represents the MOS 6502 CPU core used in the NES emulator.
 *
 * This file defines the CPU6502 class, which emulates the 6502 CPU,
 * including its internal registers, status flags, and interaction with the system bus.
 */

#ifndef CPU6502_H
#define CPU6502_H

#include "cpu6502_types.h"
#include <memory>
#include <cstdint>
#include "Bus/businterface.h"
#include <vector>

/**
 * @class CPU6502
 * @brief Emulates the 6502 CPU core used in the NES, handling instructions and memory operations.
 */
class CPU6502 {
public:
    /**
     * @brief Constructs a CPU6502 instance with a shared BusInterface.
     * @param busInterface A shared pointer to the BusInterface instance used for memory and device access.
     */
    explicit CPU6502(std::shared_ptr<BusInterface> busInterface);

    /**
     * @brief Default destructor.
     */
    ~CPU6502() = default;

    /**
     * @brief Deleted default constructor to enforce proper initialization with a BusInterface.
     */
    CPU6502() = delete;

    /**
     * @brief Resets the CPU state, initializing registers and loading the reset vector.
     */
    void reset();

    /**
     * @brief Executes a single instruction, fetching, decoding, and executing it.
     */
    void step();

    /**
     * @brief Gets the current value of the Program Counter (PC).
     * @return The 16-bit value of the Program Counter.
     */
    uint16_t getPC() const;
private:
    /**
     * @brief Shared pointer to the BusInterface instance.
     * Used for memory reads and writes as well as device communication.
     */
    std::shared_ptr<BusInterface> busInterface;

    /** @name Internal CPU Registers */
    ///@{
    uint8_t A;    /**< Accumulator register. */
    uint8_t X;    /**< X Index register. */
    uint8_t Y;    /**< Y Index register. */
    uint8_t SP;   /**< Stack Pointer register. */
    uint16_t PC;  /**< Program Counter register. */
    uint8_t P;    /**< Processor Status Flags register. */
    ///@}

    /**
     * @brief Internal CPU status register for managing flags.
     */
    uint8_t statusReg;

    /**
     * @brief Sets or clears a specific status flag.
     * @param flag The status flag to modify.
     * @param value The value to set the flag to (true for set, false for clear).
     */
    void setFlag(StatusFlag flag, bool value);

    /**
     * @brief Retrieves the current state of a specific status flag.
     * @param flag The status flag to check.
     * @return True if the flag is set, false otherwise.
     */
    bool getFlag(StatusFlag flag) const;

    /**
     * @brief Updates the zero and negative flags based on the given value.
     * @param value The value to evaluate for flag updates.
     */
    void updateZeroNegativeFlags(uint8_t value);

    /**
     * @brief Internal Work RAM (2 KB mirrored up to 8 KB).
     */
    std::vector<uint8_t> WRAM;

    /**
     * @brief Reads a byte from the specified memory address.
     * @param address The memory address to read from.
     * @return The byte read from memory.
     */
    uint8_t read(uint16_t address) const;

    /**
     * @brief Writes a byte to the specified memory address.
     * @param address The memory address to write to.
     * @param data The byte to write.
     */
    void write(uint16_t address, uint8_t data);

    /**
     * @brief Number of cycles remaining for the current instruction.
     */
    uint8_t cycles;

    /**
     * @brief Resolves the effective memory address based on the addressing mode.
     * @param mode The addressing mode to decode.
     * @return The resolved memory address.
     */
    uint16_t resolveAddress(AddressingMode mode);

    /** @name Instruction Implementations */
    ///@{
    void executeLDA(AddressingMode mode); /**< Executes the LDA (Load Accumulator) instruction. */
    void executeSEI();                    /**< Executes the SEI (Set Interrupt Disable) instruction. */
    void executeCLD();                    /**< Executes the CLD (Clear Decimal Mode) instruction. */
    void executeSTA(AddressingMode mode); /**< Executes the STA (Store Accumulator) instruction. */
    void executeLDX(AddressingMode mode); /**< Executes the LDX (Load X Register) instruction. */
    void executeTXS();                    /**< Executes the TXS (Transfer X to Stack Pointer) instruction. */
    void executeBPL();                    /**< Executes the BPL (Branch on Plus) instruction. */
    void executeLDY(AddressingMode mode);

    ///@}
};

#endif // CPU6502_H
