# NES Emulator in C++

A C++ NES emulator implementation featuring a modular and well-structured design. The project emulates the NES hardware and includes a CPU implementation, memory mapping, and a basic disassembler for debugging purposes.

## Table of Contents
- Overview
- Project Structure
- Features
- Building and Running
- Instruction Implementation Status
- Contributing
- License

## Overview

This NES emulator is written in modern C++ and aims to faithfully emulate the Nintendo Entertainment System (NES) with a focus on modularity and extensibility. The emulator leverages a component-based design to make the codebase easy to navigate and modify.

## Project Structure

- src/
  - Cartridge/: Handles loading and parsing of NES ROMs.
  - Cpu/: Implements the 6502 CPU, including opcodes and addressing modes.
  - Bus/: Manages memory and communication between the CPU and peripherals.
  - Disassembler/: Provides a disassembler for debugging purposes.
- CMakeLists.txt: Build configuration for the project.

## Features

- Emulates the 6502 CPU core of the NES.
- Supports loading `.nes` ROM files.
- Modular design for easy debugging and extension.
- Basic disassembler to inspect ROM instructions.

## Building and Running

### Prerequisites
- CMake (version 3.16 or higher)
- A C++17-compatible compiler
- Raylib for rendering (automatically linked via CMake on macOS)

### Build Instructions
1. Clone the repository: `git clone <repository-url>`
2. Navigate to the project directory: `cd NES_Emulator_CPP`
3. Create a build directory: `mkdir build && cd build`
4. Run CMake: `cmake ..`
5. Build the project: `make`
6. Run the emulator: `./output/bin/nes-emulator`

## Instruction Implementation Status

| Instruction | Addressing Modes Implemented | Status |
|-------------|-------------------------------|--------|
| LDA         | Immediate, Absolute           | Done   |
| STA         | Absolute                      | Done   |
| LDY         | Immediate                     | Not Done |
| SEI         | Implied                       | Done   |
| BPL         | Relative                      | Done   |
| CLD         | Implied                       | Done   |
| BRK         | None                          | Not Done |
| ...         | ...                           | ...    |

## Contributing

Contributions are welcome! Please submit issues or pull requests for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
