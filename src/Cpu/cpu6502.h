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

    void triggerNMI();
    void triggerIRQ();
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

    /**
     * @brief Pushes a value onto the stack.
     * @param value The 8-bit value to push.
     */
    void pushStack(uint8_t value);

    /**
     * @brief Pulls a value from the stack.
     * @return The 8-bit value pulled from the stack.
     */
    uint8_t pullStack();

    /** @name Instruction Implementations */
    ///@{

    /**
     * @brief Executes the LDA (Load Accumulator) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeLDA(AddressingMode mode);

    /**
     * @brief Executes the SEI (Set Interrupt Disable) instruction.
     */
    void executeSEI();

    /**
     * @brief Executes the CLD (Clear Decimal Mode) instruction.
     */
    void executeCLD();

    /**
     * @brief Executes the STA (Store Accumulator) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeSTA(AddressingMode mode);

    /**
     * @brief Executes the LDX (Load X Register) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeLDX(AddressingMode mode);

    /**
     * @brief Executes the TXS (Transfer X to Stack Pointer) instruction.
     */
    void executeTXS();

    /**
     * @brief Executes the BPL (Branch on Plus) instruction.
     */
    void executeBPL();

    /**
     * @brief Executes the LDY (Load Y Register) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeLDY(AddressingMode mode);

    /**
     * @brief Executes the CMP (Compare Accumulator) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeCMP(AddressingMode mode);

    /**
     * @brief Executes the BCS (Branch if Carry Set) instruction.
     */
    void executeBCS();

    /**
     * @brief Executes the STX (Store X Register) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeSTX(AddressingMode mode);

    /**
     * @brief Executes the STY (Store Y Register) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeSTY(AddressingMode mode);

    /**
     * @brief Executes the TAX (Transfer Accumulator to X) instruction.
     */
    void executeTAX();

    /**
     * @brief Executes the TXA (Transfer X to Accumulator) instruction.
     */
    void executeTXA();

    /**
     * @brief Executes the TAY (Transfer Accumulator to Y) instruction.
     */
    void executeTAY();

    /**
     * @brief Executes the TYA (Transfer Y to Accumulator) instruction.
     */
    void executeTYA();

    /**
     * @brief Executes the TSX (Transfer Stack Pointer to X) instruction.
     */
    void executeTSX();

    /**
     * @brief Executes the PHA (Push Accumulator) instruction.
     */
    void executePHA();

    /**
     * @brief Executes the PLA (Pull Accumulator) instruction.
     */
    void executePLA();

    /**
     * @brief Executes the PHP (Push Processor Status) instruction.
     */
    void executePHP();

    /**
     * @brief Executes the PLP (Pull Processor Status) instruction.
     */
    void executePLP();

    /**
     * @brief Executes the AND (Logical AND) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeAND(AddressingMode mode);

    /**
     * @brief Executes the ORA (Logical OR) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeORA(AddressingMode mode);

    /**
     * @brief Executes the EOR (Exclusive OR) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeEOR(AddressingMode mode);

    /**
     * @brief Executes the ADC (Add with Carry) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeADC(AddressingMode mode);

    /**
     * @brief Executes the SBC (Subtract with Carry) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeSBC(AddressingMode mode);

    /**
     * @brief Executes the CPX (Compare X Register) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeCPX(AddressingMode mode);

    /**
     * @brief Executes the CPY (Compare Y Register) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeCPY(AddressingMode mode);

    /**
     * @brief Executes the INC (Increment Memory) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeINC(AddressingMode mode);

    /**
     * @brief Executes the INX (Increment X Register) instruction.
     */
    void executeINX();

    /**
     * @brief Executes the INY (Increment Y Register) instruction.
     */
    void executeINY();

    /**
     * @brief Executes the DEC (Decrement Memory) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeDEC(AddressingMode mode);

    /**
     * @brief Executes the DEX (Decrement X Register) instruction.
     */
    void executeDEX();

    /**
     * @brief Executes the DEY (Decrement Y Register) instruction.
     */
    void executeDEY();

    /**
     * @brief Executes the ASL (Arithmetic Shift Left) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeASL(AddressingMode mode);

    /**
     * @brief Executes the LSR (Logical Shift Right) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeLSR(AddressingMode mode);

    /**
     * @brief Executes the ROL (Rotate Left) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeROL(AddressingMode mode);

    /**
     * @brief Executes the ROR (Rotate Right) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeROR(AddressingMode mode);

    /**
     * @brief Executes the JMP (Jump) instruction.
     * @param mode The addressing mode of the instruction.
     */
    void executeJMP(AddressingMode mode);

    /**
     * @brief Executes the JSR (Jump to Subroutine) instruction.
     */
    void executeJSR();

    /**
     * @brief Executes the RTS (Return from Subroutine) instruction.
     */
    void executeRTS();

    /**
     * @brief Executes the RTI (Return from Interrupt) instruction.
     */
    void executeRTI();

    /**
     * @brief Executes the BCC (Branch if Carry Clear) instruction.
     */
    void executeBCC();

    /**
     * @brief Executes the BEQ (Branch if Equal) instruction.
     */
    void executeBEQ();

    /**
     * @brief Executes the BMI (Branch if Minus) instruction.
     */
    void executeBMI();

    /**
     * @brief Executes the BNE (Branch if Not Equal) instruction.
     */
    void executeBNE();

    /**
     * @brief Executes the BVC (Branch if Overflow Clear) instruction.
     */
    void executeBVC();

    /**
     * @brief Executes the BVS (Branch if Overflow Set) instruction.
     */
    void executeBVS();

    /**
     * @brief Executes the CLC (Clear Carry Flag) instruction.
     */
    void executeCLC();

    /**
     * @brief Executes the SEC (Set Carry Flag) instruction.
     */
    void executeSEC();

    /**
     * @brief Executes the CLI (Clear Interrupt Disable) instruction.
     */
    void executeCLI();

    /**
     * @brief Executes the SED (Set Decimal Mode) instruction.
     */
    void executeSED();

    /**
     * @brief Executes the CLV (Clear Overflow Flag) instruction.
     */
    void executeCLV();

    /**
     * @brief Executes the BRK (Force Break) instruction.
     */
    void executeBRK();

        /**
     * @brief Executes the NOP (No Operation) instruction.
     * @details This instruction performs no operation and advances the program counter.
     *          Often used as padding or timing adjustments in program code.
     * @param mode The addressing mode used by the instruction.
     */
    void executeNOP(AddressingMode mode);
    ///@}

    /**
     * @brief Executes the SLO (Shift Left and OR) instruction.
     * @details Combines ASL (Arithmetic Shift Left) and ORA (Logical Inclusive OR) operations.
     *          Shifts the operand left by 1 bit and ORs the result with the accumulator.
     * @param mode The addressing mode used by the instruction.
     */
    void executeSLO(AddressingMode mode);

    /**
     * @brief Executes the SAX (Store A AND X) instruction.
     * @details Stores the bitwise AND of the accumulator (A) and the X register into memory.
     * @param mode The addressing mode used by the instruction.
     */
    void executeSAX(AddressingMode mode);
    
    /**
     * @brief Executes the DCP (Decrement and Compare) instruction.
     * @details Decrements a memory value by 1 and compares the result with the accumulator (A).
     *          Updates flags based on the comparison.
     * @param mode The addressing mode used by the instruction.
     */
    void executeDCP(AddressingMode mode);

    /**
     * @brief Executes the RLA (Rotate Left and AND) instruction.
     * @details Combines ROL (Rotate Left) and AND operations. Rotates the operand left by 1 bit,
     *          then ANDs the result with the accumulator.
     * @param mode The addressing mode used by the instruction.
     */
    void executeRLA(AddressingMode mode);

    /**
     * @brief Executes the ISC (Increment and Subtract with Carry) instruction.
     * @details Increments a memory value by 1, then subtracts it (with the carry flag) from the accumulator.
     * @param mode The addressing mode used by the instruction.
     */
    void executeISC(AddressingMode mode);

    /**
     * @brief Executes the RRA (Rotate Right and Add) instruction.
     * @details Combines ROR (Rotate Right) and ADC (Add with Carry). Rotates the operand right by 1 bit,
     *          then adds it (with the carry flag) to the accumulator.
     * @param mode The addressing mode used by the instruction.
     */
    void executeRRA(AddressingMode mode);

    /**
     * @brief Executes the LAX (Load A and X) instruction.
     * @details Loads a memory value into both the accumulator (A) and the X register.
     * @param mode The addressing mode used by the instruction.
     */
    void executeLAX(AddressingMode mode);

    /**
     * @brief Executes the TAS (Transfer A AND X to Stack Pointer) instruction.
     * @details Sets the stack pointer (SP) to the bitwise AND of the accumulator (A) and the X register.
     *          Stores a value in memory based on the high byte of the effective address.
     * @param mode The addressing mode used by the instruction.
     */
    void executeTAS(AddressingMode mode);

    /**
     * @brief Executes the ANC (AND and Compare) instruction.
     * @details Performs a bitwise AND between the accumulator (A) and an immediate value,
     *          then updates the carry flag based on the result.
     * @param mode The addressing mode used by the instruction.
     */
    void executeANC(AddressingMode mode); 
    
    /**
     * @brief Executes the ALR (AND and Logical Shift Right) instruction.
     * @details Performs a bitwise AND between the accumulator (A) and an immediate value,
     *          then shifts the result one bit to the right.
     * @param mode The addressing mode used by the instruction.
     */
    void executeALR(AddressingMode mode); 
    
    /**
     * @brief Executes the ARR (AND and Rotate Right) instruction.
     * @details Combines AND and ROR (Rotate Right) operations on the accumulator (A).
     * @param mode The addressing mode used by the instruction.
     */
    void executeARR(AddressingMode mode); 
    
    /**
     * @brief Executes the XAA (Transfer X AND A) instruction.
     * @details Transfers the bitwise AND of the X register and the accumulator (A) into A.
     * @param mode The addressing mode used by the instruction.
     */
    void executeXAA(AddressingMode mode); 
    
    /**
     * @brief Executes the AHX (Store A AND X and High Byte) instruction.
     * @details Stores the bitwise AND of A and X with the high byte of the effective address.
     * @param mode The addressing mode used by the instruction.
     */
    void executeAHX(AddressingMode mode); 
    
    /**
     * @brief Executes the LAS (Load A, X, and SP) instruction.
     * @details Loads a memory value into A, X, and the stack pointer (SP).
     * @param mode The addressing mode used by the instruction.
     */
    void executeLAS(AddressingMode mode); 
    
    /**
     * @brief Executes the SHX (Store X and High Byte) instruction.
     * @details Stores the bitwise AND of the X register with the high byte of the effective address.
     * @param mode The addressing mode used by the instruction.
     */
    void executeSHX(AddressingMode mode);

    /**
     * @brief Executes the SRE (Shift Right and Exclusive OR) instruction.
     * @details Combines LSR (Logical Shift Right) and EOR (Exclusive OR). Shifts the operand right by 1 bit,
     *          then XORs the result with the accumulator.
     * @param mode The addressing mode used by the instruction.
     */
    void executeSRE(AddressingMode mode);

    /**
     * @brief Executes the SHY (Store Y and High Byte) instruction.
     * @details Stores the bitwise AND of the Y register with the high byte of the effective address.
     * @param mode The addressing mode used by the instruction.
     */
    void executeSHY(AddressingMode mode);

    /**
     * @brief Executes the AXS (AND X with Immediate and Store) instruction.
     * @details Performs a bitwise AND between the X register and an immediate value, then stores the result.
     * @param mode The addressing mode used by the instruction.
     */
    void executeAXS(AddressingMode mode);

    /**
     * @brief Executes the BIT (Bit Test) instruction.
     * @details Tests bits in a memory location against the accumulator (A) without modifying A.
     *          Updates the Zero (Z), Negative (N), and Overflow (V) flags based on the result.
     * @param mode The addressing mode used by the instruction.
     */
    void executeBIT(AddressingMode mode);

    /**
     * @brief Gets the current processor status register.
     * @return The value of the status register as an 8-bit unsigned integer.
     */
    uint8_t getStatusRegister() const;

    /**
     * @brief Sets the processor status register.
     * @param value The value to set in the status register.
     */
    void setStatusRegister(uint8_t value);

    void handleInterrupt(uint16_t vectorAddress);

    bool nmiPending = false;
    bool irqPending = false;
};

#endif // CPU6502_H
