#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include <cstdint>
#include <array>

// Enum for instructions
enum class Instruction {
    ADC, AND, ASL, BCC, BCS, BEQ, BIT, BMI, BNE, BPL,
    BRK, BVC, BVS, CLC, CLD, CLI, CLV, CMP, CPX, CPY,
    DEC, DEX, DEY, EOR, INC, INX, INY, JMP, JSR, LDA,
    LDX, LDY, LSR, NOP, ORA, PHA, PHP, PLA, PLP, ROL,
    ROR, RTI, RTS, SBC, SEC, SED, SEI, STA, STX, STY,
    TAX, TAY, TSX, TXA, TXS, TYA, INVALID
};

// Enum for addressing modes
enum class AddressingMode {
    Accumulator, Absolute, AbsoluteX, AbsoluteY, Immediate,
    Implied, Indirect, IndirectX, IndirectY, Relative,
    ZeroPage, ZeroPageX, ZeroPageY, INVALID
};

// Struct for opcode information
struct OpcodeInfo {
    Instruction instruction;
    AddressingMode addressingMode;
    uint8_t cycles;
};

// Declare the opcode table as an external constant array
//extern const std::array<OpcodeInfo, 256> OPCODE_TABLE;
extern const OpcodeInfo OPCODE_TABLE[256];

namespace NES {

class CPU
{
    public:
        /* Constructors and Destructors */
        CPU() = delete;
        explicit CPU(Memory& memory);
        ~CPU() = default;

        /* CPU reset internal registers */
        void reset();

        /* Execute single instruction */
        void step();

        /* Getters for debugging and testing */
        uint16_t getProgramCounter() const { return PC; }
        uint8_t getAccumulator() const { return A; }
        uint8_t getXRegister() const { return X; }
        uint8_t getYRegister() const { return Y; }
        uint8_t getStatus() const { return P; }
        uint8_t getStackPointer() const { return SP; }

        std::string toString(Instruction instruction) const;
        std::string toString(AddressingMode mode) const;

        void printCPUState() const;

    private:
        /* Internal CPU registers */
        uint8_t A;    // Accumulator
        uint8_t X;    // X Index Register
        uint8_t Y;    // Y Index Register
        uint8_t SP;   // Stack Pointer
        uint16_t PC;  // Program Counter
        uint8_t P;    // Processor Status Flags

        /* Instruction clock cycles */
        uint8_t cycles;

        // Reference to Memory object
        Memory& memory;

        /* Memory access functions */
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

        // Status flag management
        enum StatusFlag {
            CARRY = 1 << 0,
            ZERO = 1 << 1,
            INTERRUPT_DISABLE = 1 << 2,
            DECIMAL_MODE = 1 << 3,  // Unused in NES
            BREAK_COMMAND = 1 << 4,
            UNUSED = 1 << 5,
            OVERFLOW_FLAG = 1 << 6,
            NEGATIVE = 1 << 7
        };
        void setFlag(StatusFlag flag, bool value);
        bool getFlag(StatusFlag flag) const;
        void updateZeroNegativeFlags(uint8_t value);

        /* Instructions */
        void executeLDA(AddressingMode mode);
        void executeSEI();
        void executeCLD();
        void executeSTA(AddressingMode mode);
        void executeLDX(AddressingMode mode);
        void executeTXS();
        void executeBPL();
        uint16_t resolveAddress(AddressingMode mode);


};

} // namespace NES

#endif // CPU_H