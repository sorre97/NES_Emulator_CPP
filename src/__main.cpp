#include "cartridge.h"
#include "Cpu/cpu6502.h"
#include "Bus/businterface.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <iomanip>

// ANSI escape codes for colors
const std::string RESET = "\033[0m";
const std::string WHITE = "\033[1;37m";  // Bold white
const std::string GREY = "\033[1;30m";   // Bold grey

// Simulated instruction memory
std::vector<std::string> instructionMemory = {
    "NOP", "LDA #$44", "STA $0200", "LDX #$02", "JMP $C000",
    "AND #$0F", "ASL", "BNE $FD", "BRK", "RTS"
};

// Simulated CPU registers
void displayRegisters() {
    std::cout << std::setw(20) << std::left << " "
              << "| A: 0x34 | X: 0x02 | Y: 0xFF | PC: 0x8003 | SP: 0xFD |"
              << std::endl;
}

// Simulated disassembler view
void displayInstructions(int currentIndex) {
    std::system("clear");  // Clear terminal (UNIX systems)

    for (int i = -2; i <= 2; ++i) {
        int idx = currentIndex + i;
        if (idx < 0 || idx >= instructionMemory.size()) continue;  // Bounds check

        if (i < 0) {  // Past instructions
            std::cout << GREY << std::setw(20) << std::left << instructionMemory[idx] << RESET;
        } else if (i == 0) {  // Current instruction
            std::cout << WHITE << std::setw(20) << std::left << instructionMemory[idx] << RESET;
        } else {  // Future instructions
            std::cout << GREY << std::setw(20) << std::left << instructionMemory[idx] << RESET;
        }

        if (i == 0) {
            displayRegisters();  // Print registers for the current instruction
        } else {
            std::cout << std::endl;
        }
    }
}

int main() {
    int instructionPointer = 0;  // Start executing from the 3rd instruction (index 2)

    while (true) {
        displayInstructions(instructionPointer);

        // Simulate execution step delay
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Update the instruction pointer
        instructionPointer++;
        if (instructionPointer >= instructionMemory.size()) break;
    }

    return 0;

    try {
        // Load the cartridge
        auto cartridge = std::make_unique<Cartridge>("../roms/Super Mario Bros.nes");

        // Create the BusInterface and pass the cartridge
        auto bus = std::make_shared<BusInterface>(std::move(cartridge));

        // Initialize the CPU with the BusInterface
        CPU6502 cpu(bus);

        // Reset the CPU
        cpu.reset();

        std::cout << "Emulator initialized successfully." << std::endl;

        // Main emulation loop (placeholder)
        while (true) {
            cpu.step(); // Execute a single CPU instruction
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
