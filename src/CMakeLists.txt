# CMake minimum version and project name
cmake_minimum_required(VERSION 3.16)
project(NES_Emulator)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate Raylib
find_package(raylib REQUIRED)

# Define source directory for convenience
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Cartridge Component (includes mapper)
add_library(cartridge 
    ${SRC_DIR}/Cartridge/cartridge.cpp
    ${SRC_DIR}/Cartridge/mapper.cpp
)
target_include_directories(cartridge PUBLIC 
    ${SRC_DIR}/Cartridge
)

# Bus (formerly Memory) Component
add_library(businterface 
    ${SRC_DIR}/Bus/businterface.cpp
)
target_include_directories(businterface PUBLIC 
    ${SRC_DIR}
)
target_link_libraries(businterface PUBLIC 
    cartridge # BusInterface depends on Cartridge
)

# CPU Component
add_library(cpu 
    ${SRC_DIR}/Cpu/cpu6502.cpp
    ${SRC_DIR}/Cpu/cpu6502_opcodes.cpp # Add opcode table implementation
)
target_include_directories(cpu PUBLIC 
    ${SRC_DIR}
)
target_link_libraries(cpu PUBLIC 
    businterface # CPU depends on BusInterface
)

# Disassembler Component
add_library(disassembler
    ${SRC_DIR}/Disassembler/disassembler.cpp
)
target_include_directories(disassembler PUBLIC
    ${SRC_DIR}/Disassembler # Correct path to the Disassembler folder
)
target_link_libraries(disassembler PUBLIC 
    cpu         # Disassembler depends on CPU
    businterface # Disassembler depends on BusInterface
)

# PPU Component
add_library(ppu
    ${SRC_DIR}/PPU/ppu.cpp
)
target_include_directories(ppu PUBLIC
    ${SRC_DIR}/PPU # Correct path to the PPU folder
)
target_link_libraries(ppu PUBLIC
    businterface # PPU depends on BusInterface
)

# Extend BusInterface to include PPU
target_link_libraries(businterface PUBLIC 
    ppu # BusInterface depends on PPU
)

# Main Emulator Executable
add_executable(nes-emulator 
    ${SRC_DIR}/main.cpp
)
target_include_directories(nes-emulator PUBLIC 
    ${SRC_DIR}
)
target_link_libraries(nes-emulator PRIVATE 
    disassembler # Main depends on Disassembler
    cpu 
    businterface 
    cartridge 
    ppu          # Main depends on PPU indirectly
    raylib       # Link Raylib here
)

# Link additional frameworks for macOS (important for Raylib)
if(APPLE)
    target_link_libraries(nes-emulator PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreAudio" "-framework AudioToolbox")
endif()
