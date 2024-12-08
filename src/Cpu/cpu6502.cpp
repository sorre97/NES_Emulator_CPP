#include "cpu6502.h"
#include "cpu6502_memory_map.h"
#include "cpu6502_opcodes.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>

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


void CPU6502::handleInterrupt(uint16_t vectorAddress) {
    // Push the program counter and status register onto the stack
    pushStack((PC >> 8) & 0xFF); // High byte of PC
    pushStack(PC & 0xFF);        // Low byte of PC
    setFlag(StatusFlag::BREAK_FLAG, false); // Clear Break flag
    setFlag(StatusFlag::UNUSED_FLAG, true);         // Set Unused flag
    pushStack(getStatusRegister());

    // Disable further IRQs
    setFlag(StatusFlag::INTERRUPT_DISABLE_FLAG, true);

    // Load the interrupt vector address into PC
    uint8_t lo = read(vectorAddress);
    uint8_t hi = read(vectorAddress + 1);
    PC = (hi << 8) | lo;

    // Account for interrupt overhead cycles
    cycles += 7;
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

void CPU6502::triggerNMI() {
    nmiPending = true;
}

void CPU6502::triggerIRQ() {
    irqPending = true;
}

/* Execute single instruction */
void CPU6502::step() {
    if (cycles > 0) {
        --cycles; // Decrement remaining cycles for the current instruction
        return;
    }

    // Check for pending interrupts
    if (nmiPending) {
        handleInterrupt(0xFFFA); // Handle NMI using its vector
        nmiPending = false; // Clear the NMI pending flag
    } else if (irqPending && !getFlag(StatusFlag::INTERRUPT_DISABLE_FLAG)) {
        handleInterrupt(0xFFFE); // Handle IRQ using its vector
        irqPending = false; // Clear the IRQ pending flag
    } else {

        uint8_t opcode = read(PC);
        ++PC;

        const OpcodeInfo& info = OPCODE_TABLE[opcode];

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
                executeSTX(info.addressingMode);
                break;
            case Instruction::SAX: // Store X Register
                executeSAX(info.addressingMode);
                break;
            case Instruction::STY: // Store Y Register
                executeSTY(info.addressingMode);
                break;

            // Register Transfers
            case Instruction::TAX: // Transfer Accumulator to X
                executeTAX();
                break;
            case Instruction::TXA: // Transfer X to Accumulator
                executeTXA();
                break;
            case Instruction::TAY: // Transfer Accumulator to Y
                executeTAY();
                break;
            case Instruction::TYA: // Transfer Y to Accumulator
                executeTYA();
                break;

            // Stack Operations
            case Instruction::TSX: // Transfer Stack Pointer to X
                executeTSX();
                break;
            case Instruction::TXS: // Transfer X to Stack Pointer
                executeTXS();
                break;
            case Instruction::PHA: // Push Accumulator
                executePHA();
                break;
            case Instruction::PLA: // Pull Accumulator
                executePLA();
                break;
            case Instruction::PHP: // Push Processor Status
                executePHP();
                break;
            case Instruction::PLP: // Pull Processor Status
                executePLP();
                break;

            // Logical Operations
            case Instruction::AND: // Logical AND
                executeAND(info.addressingMode);
                break;
            case Instruction::ORA: // Logical OR
                executeORA(info.addressingMode);
                break;
            case Instruction::EOR: // Exclusive OR
                executeEOR(info.addressingMode);
                break;

            // Arithmetic Operations
            case Instruction::ADC: // Add with Carry
                executeADC(info.addressingMode);
                break;
            case Instruction::SBC: // Subtract with Carry
                executeSBC(info.addressingMode);
                break;
            case Instruction::CMP: // Compare Accumulator
                executeCMP(info.addressingMode);
                break;
            case Instruction::CPX: // Compare X Register
                executeCPX(info.addressingMode);
                break;
            case Instruction::CPY: // Compare Y Register
                executeCPY(info.addressingMode);
                break;

            // Increment/Decrement Operations
            case Instruction::INC: // Increment Memory
                executeINC(info.addressingMode);
                break;
            case Instruction::INX: // Increment X Register
                executeINX();
                break;
            case Instruction::INY: // Increment Y Register
                executeINY();
                break;
            case Instruction::DEC: // Decrement Memory
                executeDEC(info.addressingMode);
                break;
            case Instruction::DEX: // Decrement X Register
                executeDEX();
                break;
            case Instruction::DEY: // Decrement Y Register
                executeDEY();
                break;

            // Shifts
            case Instruction::ASL: // Arithmetic Shift Left
                executeASL(info.addressingMode);
                break;
            case Instruction::LSR: // Logical Shift Right
                executeLSR(info.addressingMode);
                break;
            case Instruction::ROL: // Rotate Left
                executeROL(info.addressingMode);
                break;
            case Instruction::ROR: // Rotate Right
                executeROR(info.addressingMode);
                break;
            case Instruction::SLO: // Rotate Right
                executeSLO(info.addressingMode);
                break;

            // Control Flow
            case Instruction::JMP: // Jump
                executeJMP(info.addressingMode);
                break;
            case Instruction::JSR: // Jump to Subroutine
                executeJSR();
                break;
            case Instruction::RTS: // Return from Subroutine
                executeRTS();
                break;
            case Instruction::RTI: // Return from Interrupt
                executeRTI();
                break;

            // Branching
            case Instruction::BCC: // Branch if Carry Clear
                executeBCC();
                break;
            case Instruction::BCS: // Branch if Carry Set
                executeBCS();
                break;
            case Instruction::BEQ: // Branch if Equal
                executeBEQ();
                break;
            case Instruction::BMI: // Branch if Minus
                executeBMI();
                break;
            case Instruction::BNE: // Branch if Not Equal
                executeBNE();
                break;
            case Instruction::BPL: // Branch if Positive
                executeBPL();
                break;
            case Instruction::BVC: // Branch if Overflow Clear
                executeBVC();
                break;
            case Instruction::BVS: // Branch if Overflow Set
                executeBVS();
                break;
            case Instruction::BIT:
                executeBIT(info.addressingMode);
                break;
                
            // System Functions
            case Instruction::CLC: // Clear Carry Flag
                executeCLC();
                break;
            case Instruction::SEC: // Set Carry Flag
                executeSEC();
                break;
            case Instruction::CLI: // Clear Interrupt Disable
                executeCLI();
                break;
            case Instruction::SEI: // Set Interrupt Disable
                executeSEI();
                break;
            case Instruction::CLD: // Clear Decimal Mode
                executeCLD();
                break;
            case Instruction::SED: // Set Decimal Mode
                executeSED();
                break;
            case Instruction::CLV: // Clear Overflow Flag
                executeCLV();
                break;
            case Instruction::DCP:
                executeDCP(info.addressingMode);
                break;
            case Instruction::RLA: // Force Break
                executeRLA(info.addressingMode);
                break;
            // Break/No-op
            case Instruction::BRK: // Force Break
                executeBRK();
                break;
            case Instruction::NOP: // No Operation
                executeNOP(info.addressingMode);
                break;

            case Instruction::ISC: // No Operation
                executeISC(info.addressingMode);
                break;

            case Instruction::RRA: // No Operation
                executeRRA(info.addressingMode);
                break;

            case Instruction::LAX: // No Operation
                executeLAX(info.addressingMode);
                break;

            case Instruction::TAS:
                executeTAS(info.addressingMode);
                break;

            case Instruction::ANC:
                executeANC(info.addressingMode);
                break;

            case Instruction::ALR:
                executeALR(info.addressingMode);
                break;

            case Instruction::ARR:
                executeARR(info.addressingMode);
                break;

            case Instruction::XAA:
                executeXAA(info.addressingMode);
                break;

            case Instruction::AHX:
                executeAHX(info.addressingMode);
                break;

            case Instruction::LAS:
                executeLAS(info.addressingMode);
                break;

            case Instruction::SHX:
                executeSHX(info.addressingMode);
                break;

            case Instruction::SRE:
                executeSRE(info.addressingMode);
                break;

            case Instruction::SHY:
                executeSHY(info.addressingMode);
                break;

            case Instruction::AXS:
                executeAXS(info.addressingMode);
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
        case AddressingMode::ZeroPageX: {
            uint8_t zpAddress = read(PC++);          // Fetch zero-page base address
            uint8_t effectiveAddress = (zpAddress + X) & 0xFF; // Add X with wraparound
            return effectiveAddress;
        }
                case AddressingMode::ZeroPageY: {
            uint8_t zpAddress = read(PC++);          // Fetch zero-page base address
            uint8_t effectiveAddress = (zpAddress + Y) & 0xFF; // Add Y with wraparound
            return effectiveAddress;
        }
        case AddressingMode::AbsoluteX: {
            uint8_t lo = read(PC++);
            uint8_t hi = read(PC++);
            uint16_t baseAddress = (hi << 8) | lo;
            uint16_t effectiveAddress = baseAddress + X;

            // Add a cycle if page boundary is crossed
            if ((baseAddress & 0xFF00) != (effectiveAddress & 0xFF00)) {
                cycles++;
            }

            return effectiveAddress;
        }
        case AddressingMode::AbsoluteY: {
            uint8_t lo = read(PC++);
            uint8_t hi = read(PC++);
            uint16_t baseAddress = (hi << 8) | lo;
            uint16_t effectiveAddress = baseAddress + Y;

            // Add a cycle if page boundary is crossed
            if ((baseAddress & 0xFF00) != (effectiveAddress & 0xFF00)) {
                cycles++;
            }

            return effectiveAddress;
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
        case AddressingMode::Indirect: {
            uint8_t lo = read(PC++);
            uint8_t hi = read(PC++);
            uint16_t pointer = (hi << 8) | lo;

            // 6502 bug: Handle page boundary wraparound for indirect JMP
            uint8_t lowByte = read(pointer);
            uint8_t highByte = read((pointer & 0xFF00) | ((pointer + 1) & 0x00FF));
            return (highByte << 8) | lowByte;
        }
        case AddressingMode::Relative: {
            int8_t offset = static_cast<int8_t>(read(PC++)); // Signed 8-bit offset
            return PC + static_cast<uint16_t>(offset); // Calculate the effective address (unsigned wrap-around subtraction)
        }
        case AddressingMode::ZeroPageIndirect: {
            // Fetch zero-page address from the current PC
            uint8_t zpAddress = read(PC++);
            uint8_t lo = read(zpAddress);
            uint8_t hi = read((zpAddress + 1) & 0xFF); // Wrap around zero-page
            return (hi << 8) | lo; // Combine high and low bytes to get the effective address
        }
        default:
            std::stringstream ss;
            ss << std::string(__PRETTY_FUNCTION__) << " - "
            << "Unsupported addressing mode";
            throw std::runtime_error(ss.str());
    }
}

uint8_t CPU6502::getStatusRegister() const {
    uint8_t status = 0;
    if (getFlag(StatusFlag::NEGATIVE_FLAG))    status |= (1 << 7);
    if (getFlag(StatusFlag::OVERFLOW_FLAG))    status |= (1 << 6);
    status |= (1 << 5); // Unused bit, always set to 1
    if (getFlag(StatusFlag::BREAK_FLAG))       status |= (1 << 4);
    if (getFlag(StatusFlag::DECIMAL_MODE_FLAG)) status |= (1 << 3);
    if (getFlag(StatusFlag::INTERRUPT_DISABLE_FLAG)) status |= (1 << 2);
    if (getFlag(StatusFlag::ZERO_FLAG))        status |= (1 << 1);
    if (getFlag(StatusFlag::CARRY_FLAG))       status |= (1 << 0);
    return status;
}

void CPU6502::setStatusRegister(uint8_t value) {
    setFlag(StatusFlag::NEGATIVE_FLAG,    value & (1 << 7));
    setFlag(StatusFlag::OVERFLOW_FLAG,    value & (1 << 6));
    // Bit 5 is ignored when writing to the status register
    setFlag(StatusFlag::BREAK_FLAG,       value & (1 << 4));
    setFlag(StatusFlag::DECIMAL_MODE_FLAG, value & (1 << 3));
    setFlag(StatusFlag::INTERRUPT_DISABLE_FLAG, value & (1 << 2));
    setFlag(StatusFlag::ZERO_FLAG,        value & (1 << 1));
    setFlag(StatusFlag::CARRY_FLAG,       value & (1 << 0));
}


void CPU6502::pushStack(uint8_t value) {
    write(0x0100 + SP, value); // Stack is located at $0100-$01FF
    --SP;                      // Decrement the stack pointer
}

uint8_t CPU6502::pullStack() {
    ++SP;                       // Increment the stack pointer
    return read(0x0100 + SP);   // Read the value from the stack
}

void CPU6502::executeBIT(AddressingMode mode) {
    uint16_t address = resolveAddress(mode); // Resolve the operand address
    uint8_t value = read(address);           // Read the value from memory

    // Test bits
    setFlag(StatusFlag::ZERO_FLAG, (A & value) == 0);      // Set Z if (A & value) == 0
    setFlag(StatusFlag::NEGATIVE_FLAG, value & 0x80);      // Set N to bit 7 of value
    setFlag(StatusFlag::OVERFLOW_FLAG, value & 0x40);      // Set V to bit 6 of value
}


void CPU6502::executeSRE(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);

    // Logical shift right
    setFlag(StatusFlag::CARRY_FLAG, value & 0x01); // Set carry flag from LSB
    value >>= 1;
    write(address, value);

    // Exclusive OR with the accumulator
    A ^= value;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeSHY(AddressingMode mode) {
    if (mode != AddressingMode::AbsoluteX) {
        std::stringstream ss;
            ss << std::string(__PRETTY_FUNCTION__) << " - "
            << "Unsupported addressing mode";
            throw std::runtime_error(ss.str());
    }

    uint16_t address = resolveAddress(mode);
    uint8_t result = Y & ((address >> 8) + 1); // Compute Y AND (high-byte + 1)
    write(address, result);
}

void CPU6502::executeAXS(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = A & X; // Compute A AND X
    write(address, value);
}

void CPU6502::executeANC(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    A &= read(address);
    updateZeroNegativeFlags(A);
    setFlag(StatusFlag::CARRY_FLAG, A & 0x80); // Set Carry if MSB is 1
}

void CPU6502::executeALR(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    A &= read(address);
    setFlag(StatusFlag::CARRY_FLAG, A & 0x01); // Set Carry from LSB
    A >>= 1;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeARR(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    A &= read(address);
    A = (A >> 1) | (getFlag(StatusFlag::CARRY_FLAG) << 7);
    updateZeroNegativeFlags(A);
    setFlag(StatusFlag::CARRY_FLAG, A & 0x40); // Special handling
    setFlag(StatusFlag::OVERFLOW_FLAG, ((A & 0x40) >> 6) ^ ((A & 0x20) >> 5));
}

void CPU6502::executeXAA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    A = X & read(address);
    updateZeroNegativeFlags(A);
}

void CPU6502::executeAHX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t result = A & X & ((address >> 8) + 1);
    write(address, result);
}

void CPU6502::executeLAS(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address) & SP;
    A = value;
    X = value;
    SP = value;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeSHX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t result = X & ((address >> 8) + 1);
    write(address, result);
}

void CPU6502::executeTAS(AddressingMode mode) {
    if (mode != AddressingMode::AbsoluteY) {
        std::stringstream ss;
            ss << std::string(__PRETTY_FUNCTION__) << " - "
            << "Unsupported addressing mode";
            throw std::runtime_error(ss.str());
    }

    // Step 1: Calculate A AND X
    uint8_t value = A & X;

    // Step 2: Transfer the result to SP
    SP = value;

    // Step 3: Calculate memory address with AbsoluteY addressing
    uint16_t address = resolveAddress(mode);

    // Step 4: Store (A AND X AND high-byte of the address + 1) into memory
    uint8_t result = value & ((address >> 8) + 1);
    write(address, result);
}


void CPU6502::executeRRA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);

    // Rotate Right
    bool carry = getFlag(StatusFlag::CARRY_FLAG);
    setFlag(StatusFlag::CARRY_FLAG, value & 0x01);
    value = (value >> 1) | (carry << 7);

    write(address, value);

    // Add Memory to Accumulator with Carry
    uint16_t result = A + value + getFlag(StatusFlag::CARRY_FLAG);
    setFlag(StatusFlag::CARRY_FLAG, result > 0xFF);
    setFlag(StatusFlag::OVERFLOW_FLAG, (~(A ^ value) & (A ^ result) & 0x80) != 0);
    A = result & 0xFF;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeLAX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);

    A = value;
    X = value;

    updateZeroNegativeFlags(A);
}


void CPU6502::executeISC(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address) + 1;
    write(address, value);

    // Subtract Memory from Accumulator with Borrow
    value = ~value; // 1's complement for subtraction
    uint16_t result = A + value + getFlag(StatusFlag::CARRY_FLAG);
    setFlag(StatusFlag::CARRY_FLAG, result > 0xFF);
    setFlag(StatusFlag::OVERFLOW_FLAG, (~(A ^ value) & (A ^ result) & 0x80) != 0);
    A = result & 0xFF;
    updateZeroNegativeFlags(A);
}



void CPU6502::executeRLA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);

    // Rotate Left
    bool carry = getFlag(StatusFlag::CARRY_FLAG);
    setFlag(StatusFlag::CARRY_FLAG, value & 0x80);
    value = (value << 1) | carry;

    write(address, value);

    // AND with Accumulator
    A &= value;
    updateZeroNegativeFlags(A);
}


void CPU6502::executeDCP(AddressingMode mode) {
    uint16_t address = resolveAddress(mode); // Resolve effective address

    // Step 1: Decrement memory
    uint8_t value = read(address);          // Read current value
    value -= 1;                             // Decrement
    write(address, value);                  // Write back to memory

    // Step 2: Compare with Accumulator
    uint16_t result = static_cast<uint16_t>(A) - value;
    setFlag(StatusFlag::CARRY_FLAG, A >= value);  // Set if no borrow
    setFlag(StatusFlag::ZERO_FLAG, result == 0); // Set if result is zero
    setFlag(StatusFlag::NEGATIVE_FLAG, result & 0x80); // Set if result is negative
}


void CPU6502::executeSAX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode); // Resolve effective address
    uint8_t value = A & X;                  // Compute A AND X
    write(address, value);                  // Store the result in memory
}


void CPU6502::executeSLO(AddressingMode mode) {
    // Resolve the address based on the addressing mode
    uint16_t address = resolveAddress(mode);

    // Read the value at the resolved address
    uint8_t value = read(address);

    // Perform ASL (Arithmetic Shift Left)
    setFlag(StatusFlag::CARRY_FLAG, value & 0x80); // Set carry from MSB
    value <<= 1; // Shift left

    // Write the result back to memory
    write(address, value);

    // OR the result with the accumulator
    A |= value;

    // Update Zero and Negative flags based on the accumulator
    updateZeroNegativeFlags(A);
}


void CPU6502::executeSTX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    write(address, X);
}

void CPU6502::executeSTY(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    write(address, Y);
}

void CPU6502::executeTAX() {
    X = A;
    updateZeroNegativeFlags(X);
}

void CPU6502::executeTXA() {
    A = X;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeTAY() {
    Y = A;
    updateZeroNegativeFlags(Y);
}

void CPU6502::executeTYA() {
    A = Y;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeTSX() {
    X = SP;
    updateZeroNegativeFlags(X);
}

void CPU6502::executePHA() {
    pushStack(A);
}

void CPU6502::executePLA() {
    A = pullStack();
    updateZeroNegativeFlags(A);
}

void CPU6502::executePHP() {
    pushStack(getStatusRegister() | 0x10); // Push with B flag set
}

void CPU6502::executePLP() {
    setStatusRegister(pullStack());
}

void CPU6502::executeAND(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    A &= read(address);
    updateZeroNegativeFlags(A);
}

void CPU6502::executeORA(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    A |= read(address);
    updateZeroNegativeFlags(A);
}

void CPU6502::executeEOR(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    A ^= read(address);
    updateZeroNegativeFlags(A);
}

void CPU6502::executeADC(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);
    uint16_t sum = A + value + getFlag(StatusFlag::CARRY_FLAG);
    setFlag(StatusFlag::CARRY_FLAG, sum > 0xFF);
    setFlag(StatusFlag::OVERFLOW_FLAG, (~(A ^ value) & (A ^ sum) & 0x80) != 0);
    A = sum & 0xFF;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeSBC(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address) ^ 0xFF; // 1's complement for subtraction
    uint16_t sum = A + value + getFlag(StatusFlag::CARRY_FLAG);
    setFlag(StatusFlag::CARRY_FLAG, sum > 0xFF);
    setFlag(StatusFlag::OVERFLOW_FLAG, (~(A ^ value) & (A ^ sum) & 0x80) != 0);
    A = sum & 0xFF;
    updateZeroNegativeFlags(A);
}

void CPU6502::executeCPX(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);
    uint16_t result = X - value;
    setFlag(StatusFlag::CARRY_FLAG, X >= value);
    updateZeroNegativeFlags(result & 0xFF);
}

void CPU6502::executeCPY(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);
    uint16_t result = Y - value;
    setFlag(StatusFlag::CARRY_FLAG, Y >= value);
    updateZeroNegativeFlags(result & 0xFF);
}

void CPU6502::executeINC(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address) + 1;
    write(address, value);
    updateZeroNegativeFlags(value);
}

void CPU6502::executeINX() {
    ++X;
    updateZeroNegativeFlags(X);
}

void CPU6502::executeINY() {
    ++Y;
    updateZeroNegativeFlags(Y);
}

void CPU6502::executeDEC(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address) - 1;
    write(address, value);
    updateZeroNegativeFlags(value);
}

void CPU6502::executeDEX() {
    --X;
    updateZeroNegativeFlags(X);
}

void CPU6502::executeDEY() {
    --Y;
    updateZeroNegativeFlags(Y);
}

void CPU6502::executeASL(AddressingMode mode) {
    if (mode == AddressingMode::Accumulator) {
        // Handle Accumulator Mode
        setFlag(StatusFlag::CARRY_FLAG, A & 0x80); // Set carry flag to bit 7 of A
        A <<= 1;                                  // Shift accumulator left by 1
        updateZeroNegativeFlags(A);               // Update zero and negative flags
    } else {
        // Handle Memory Addressing Modes
        uint16_t address = resolveAddress(mode);
        uint8_t value = read(address);
        setFlag(StatusFlag::CARRY_FLAG, value & 0x80); // Set carry flag to bit 7 of value
        value <<= 1;                                  // Shift value left by 1
        write(address, value);                        // Write result back to memory
        updateZeroNegativeFlags(value);               // Update zero and negative flags
    }
}


void CPU6502::executeLSR(AddressingMode mode) {
    if (mode == AddressingMode::Accumulator) {
        // Perform the shift directly on the accumulator
        setFlag(StatusFlag::CARRY_FLAG, A & 0x01); // Set the carry flag to bit 0 of A
        A >>= 1;                             // Logical shift right
        setFlag(StatusFlag::ZERO_FLAG, A == 0);   // Set zero flag if A is now zero
        setFlag(StatusFlag::NEGATIVE_FLAG, false); // LSR always clears the negative flag
    } else {
        uint16_t address = resolveAddress(mode);
        uint8_t value = read(address);
        setFlag(StatusFlag::CARRY_FLAG, value & 0x01);
        value >>= 1;
        write(address, value);
        updateZeroNegativeFlags(value);
    }
}

void CPU6502::executeROL(AddressingMode mode) {
    if (mode == AddressingMode::Accumulator) {
        // Handle Accumulator Mode
        bool carry = getFlag(StatusFlag::CARRY_FLAG); // Save the current carry flag
        setFlag(StatusFlag::CARRY_FLAG, A & 0x80);    // Set carry flag to bit 7 of A
        A = (A << 1) | carry;                         // Rotate left with carry
        updateZeroNegativeFlags(A);                   // Update zero and negative flags
    } else {
        // Handle Memory Addressing Modes
        uint16_t address = resolveAddress(mode);
        uint8_t value = read(address);
        bool carry = getFlag(StatusFlag::CARRY_FLAG); // Save the current carry flag
        setFlag(StatusFlag::CARRY_FLAG, value & 0x80); // Set carry flag to bit 7 of value
        value = (value << 1) | carry;                 // Rotate left with carry
        write(address, value);
        updateZeroNegativeFlags(value);               // Update zero and negative flags
    }
}


void CPU6502::executeROR(AddressingMode mode) {
    uint16_t address = resolveAddress(mode);
    uint8_t value = read(address);
    bool carry = getFlag(StatusFlag::CARRY_FLAG);
    setFlag(StatusFlag::CARRY_FLAG, value & 0x01);
    value = (value >> 1) | (carry << 7);
    write(address, value);
    updateZeroNegativeFlags(value);
}

void CPU6502::executeJMP(AddressingMode mode) {
    PC = resolveAddress(mode);
}

void CPU6502::executeJSR() {
    uint16_t jumpAddress = resolveAddress(AddressingMode::Absolute);
    pushStack((PC - 1) >> 8); // High byte
    pushStack((PC - 1) & 0xFF); // Low byte
    PC = jumpAddress;
}

void CPU6502::executeRTS() {
    uint8_t lo = pullStack();
    uint8_t hi = pullStack();
    PC = (hi << 8) | lo;
    ++PC;
}

void CPU6502::executeRTI() {
    setStatusRegister(pullStack());
    uint8_t lo = pullStack();
    uint8_t hi = pullStack();
    PC = (hi << 8) | lo;
}

void CPU6502::executeBCC() {
    uint16_t targetAddress = resolveAddress(AddressingMode::Relative);
    if (!getFlag(StatusFlag::CARRY_FLAG)) {
        if ((PC & 0xFF00) != (targetAddress & 0xFF00)) {
            cycles++;
        }
        PC = targetAddress;
        cycles++;
    }
}

void CPU6502::executeBEQ() {
    uint16_t targetAddress = resolveAddress(AddressingMode::Relative);
    if (getFlag(StatusFlag::ZERO_FLAG)) {
        if ((PC & 0xFF00) != (targetAddress & 0xFF00)) {
            cycles++;
        }
        PC = targetAddress;
        cycles++;
    }
}

void CPU6502::executeBMI() {
    uint16_t targetAddress = resolveAddress(AddressingMode::Relative);
    if (getFlag(StatusFlag::NEGATIVE_FLAG)) {
        if ((PC & 0xFF00) != (targetAddress & 0xFF00)) {
            cycles++;
        }
        PC = targetAddress;
        cycles++;
    }
}

void CPU6502::executeBNE() {
    uint16_t targetAddress = resolveAddress(AddressingMode::Relative);
    
    if (!getFlag(StatusFlag::ZERO_FLAG)) {
        if ((PC & 0xFF00) != (targetAddress & 0xFF00)) {
            cycles++;
        }
        PC = targetAddress;
        cycles++;
    }
}

void CPU6502::executeBVC() {
    uint16_t targetAddress = resolveAddress(AddressingMode::Relative);
    if (!getFlag(StatusFlag::OVERFLOW_FLAG)) {
        if ((PC & 0xFF00) != (targetAddress & 0xFF00)) {
            cycles++;
        }
        PC = targetAddress;
        cycles++;
    }
}

void CPU6502::executeBVS() {
    uint16_t targetAddress = resolveAddress(AddressingMode::Relative);
    if (getFlag(StatusFlag::OVERFLOW_FLAG)) {
        if ((PC & 0xFF00) != (targetAddress & 0xFF00)) {
            cycles++;
        }
        PC = targetAddress;
        cycles++;
    }
}

void CPU6502::executeCLC() {
    setFlag(StatusFlag::CARRY_FLAG, false);
}

void CPU6502::executeSEC() {
    setFlag(StatusFlag::CARRY_FLAG, true);
}

void CPU6502::executeCLI() {
    setFlag(StatusFlag::INTERRUPT_DISABLE_FLAG, false);
}

void CPU6502::executeSED() {
    setFlag(StatusFlag::DECIMAL_MODE_FLAG, true);
}

void CPU6502::executeCLV() {
    setFlag(StatusFlag::OVERFLOW_FLAG, false);
}

void CPU6502::executeBRK() {
    PC++;
    setFlag(StatusFlag::BREAK_FLAG, true);
    pushStack((PC >> 8) & 0xFF);
    pushStack(PC & 0xFF);
    pushStack(getStatusRegister() | 0x10); // Push with B flag set
    setFlag(StatusFlag::INTERRUPT_DISABLE_FLAG, true);
    PC = (read(0xFFFF) << 8) | read(0xFFFE);
}

void CPU6502::executeNOP(AddressingMode mode) {
    // Handle different NOPs based on their addressing mode
    switch (mode) {
        case AddressingMode::Immediate:
        case AddressingMode::ZeroPage:
        case AddressingMode::Absolute:
        case AddressingMode::AbsoluteX:
            // Simply resolve the address to advance PC without doing anything
            resolveAddress(mode);
            break;

        case AddressingMode::Implied:
            // Standard NOP; nothing to do
            break;

        default:
            throw std::runtime_error("Unsupported NOP addressing mode");
    }
}



void CPU6502::executeBCS()
{
    int8_t offset = static_cast<int8_t>(read(PC++)); // Fetch signed 8-bit offset
    if (getFlag(StatusFlag::CARRY_FLAG)) {          // Check if Carry flag is set
        uint16_t oldPC = PC;                        // Store the old PC for boundary check
        PC += offset;                               // Add the offset to the PC
        cycles++;                                   // Add one cycle for the branch

        if ((oldPC & 0xFF00) != (PC & 0xFF00)) {    // Check if page boundary is crossed
            cycles++;
        }
    } else {
        // No branching
    }
}

void CPU6502::executeCMP(AddressingMode mode) { 
    uint16_t address = resolveAddress(mode); // Get the effective address
    uint8_t value = read(address);           // Read the value to compare with A

    uint8_t result = A - value;              // Perform subtraction, keep lower 8 bits

    // Update Carry flag: Set if A >= value
    setFlag(StatusFlag::CARRY_FLAG, A >= value);

    // Update Zero flag: Set if result is 0
    setFlag(StatusFlag::ZERO_FLAG, result == 0);

    // Update Negative flag: Set if the MSB of the result is 1
    setFlag(StatusFlag::NEGATIVE_FLAG, result & 0x80);
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
    uint16_t targetAddress = resolveAddress(AddressingMode::Relative); // Use resolveAddress
    if (!getFlag(StatusFlag::NEGATIVE_FLAG)) {           // Check if Negative Flag is clear
        uint16_t oldPC = PC;
        PC = targetAddress;                         // Apply the branch offset
        cycles++;                                   // Add cycle for taking the branch
        if ((oldPC & 0xFF00) != (PC & 0xFF00)) {    // Check if page boundary is crossed
            cycles++;
        }
    }
}

void CPU6502::updateZeroNegativeFlags(uint8_t value) {
    // Update Zero flag
    setFlag(StatusFlag::ZERO_FLAG, value == 0);

    // Update Negative flag (7th bit of the value)
    setFlag(StatusFlag::NEGATIVE_FLAG, value & (1 << 7));
}


uint8_t CPU6502::read(uint16_t address) const {
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
        return busInterface->cpuBusRead(address);
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        uint16_t mirroredAddress = PPU_REGISTERS_STARTADDR + (address % 8);
        return busInterface->cpuBusRead(mirroredAddress);
    }

    /* APU and I/O register access: $4000 - $401F */
    if (address >= APU_IO_STARTADDR && address < APU_IO_ENDADDR) {
        return busInterface->cpuBusRead(address);
    }

    /* Cartridge SRAM space access: $6000 - $7FFF */
    if (address >= CARTRIDGE_SRAM_STARTADDR && address < CARTRIDGE_SRAM_ENDADDR) {
        return busInterface->cpuBusRead(address);
    }

    /* Cartridge ROM space access: $8000 - $FFFF */
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        return busInterface->cpuBusRead(address);
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
        busInterface->cpuBusWrite(address, value);
        return;
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        uint16_t mirroredAddress = PPU_REGISTERS_STARTADDR + (address % 8);
        busInterface->cpuBusWrite(mirroredAddress, value);
        return;
    }

    /* APU and I/O register access: $4000 - $401F */
    if (address >= APU_IO_STARTADDR && address < APU_IO_ENDADDR) {
        busInterface->cpuBusWrite(address, value);
        return;
    }

    /* Cartridge SRAM space access: $6000 - $7FFF */
    if (address >= CARTRIDGE_SRAM_STARTADDR && address < CARTRIDGE_SRAM_ENDADDR) {
        busInterface->cpuBusWrite(address, value);
        return;
    }

    /* Cartridge ROM space access: $8000 - $FFFF */
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        // ROM write ignored
        return;
    }

    /* Out of range write */
}


uint16_t CPU6502::getPC() const {
    return PC; // Assuming `pc` is the member variable for the Program Counter
}
