#include "Cpu/cpu6502.h"
#include "Bus/businterface.h"
#include "Cartridge/cartridge.h"
#include "disassembler.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

int main() {
    try {
        // Load the cartridge
        auto cartridge = std::make_shared<Cartridge>("../roms/Super Mario Bros.nes");

        // Create the BusInterface and attach the cartridge
        auto bus = std::make_shared<BusInterface>(cartridge);

        // Create the CPU and link it to the bus
        auto cpu = std::make_shared<CPU6502>(bus);

        // Create the Disassembler, passing the CPU and bus
        Disassembler disassembler(cpu, bus);

        // Reset the CPU
        cpu->reset();
        std::cout << "CPU reset complete.\n";

        // Print initial state
        std::cout << "Initial instruction view:\n";
        disassembler.print();

        // Main emulation loop
        while (true) {
            // Print the current disassembled instruction view
            disassembler.print();

            // Wait for 1 second
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // Simulate instruction execution
            // std::cout << "\nExecuting instruction...\n";
            cpu->step(); // Simulate one CPU instruction execution
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
