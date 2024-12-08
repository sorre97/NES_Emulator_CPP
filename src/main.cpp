#include "Cpu/cpu6502.h"
#include "Bus/businterface.h"
#include "Cartridge/cartridge.h"
#include "disassembler.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "ppu.h"

int main() {
    try {
        // Load the cartridge
        //auto cartridge = std::make_shared<Cartridge>("../roms/Super Mario Bros.nes");
        auto cartridge = std::make_shared<Cartridge>("../roms/Donkey Kong.nes");

        // Create the CPU and link it to the bus
        auto ppu = std::make_shared<PPU>();

        // Create the BusInterface and attach the cartridge
        auto bus = std::make_shared<BusInterface>(cartridge, ppu);

        // Create the CPU and link it to the bus
        auto cpu = std::make_shared<CPU6502>(bus);

        // Set IRQ callback
        ppu->setIRQCallback([cpu]() {
            cpu->triggerIRQ();
        });

        // Register the NMI callback from the PPU to the CPU
        ppu->setNMICallback([cpu] {
            cpu->triggerNMI();
        });

        // Create the Disassembler, passing the CPU and bus
        Disassembler disassembler(cpu, bus);

        // Reset the CPU and PPU
        cpu->reset();
        ppu->reset();
        std::cout << "CPU and PPU reset complete.\n";

        // Print initial state
        std::cout << "Initial instruction view:\n";
        disassembler.print();

        // Main emulation loop
        while (true) {
            // Print the current disassembled instruction view
            disassembler.print();

            // Wait for 1 second
            //if(cpu->getPC() > 0x90D0)
            //    std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            // Simulate instruction execution
            // std::cout << "\nExecuting instruction...\n";
            cpu->step(); // Simulate one CPU instruction execution

            // Execute 3 PPU steps for each CPU step
            for (int i = 0; i < 3; ++i) {
                ppu->step();
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
