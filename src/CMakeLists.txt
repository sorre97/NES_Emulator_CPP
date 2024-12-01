# Add the ROM component as a library
add_library(rom rom/NESROM.cpp)
target_include_directories(rom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/rom)

# Add the Mapper component as a library
add_library(mapper mapper/mapper.cpp)
target_include_directories(mapper PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/mapper 
    ${CMAKE_CURRENT_SOURCE_DIR}/memory # Include memory for memory_ranges.h
)

# Add the PPU component as a library
add_library(ppu ppu/ppu.cpp) # Assuming ppu/ppu.cpp exists
target_include_directories(ppu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ppu)

# Add the Memory component as a library
add_library(memory memory/memory.cpp)
target_include_directories(memory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/memory)
target_link_libraries(memory PUBLIC rom mapper ppu) # Memory depends on ROM, Mapper, and PPU

# Add the CPU component as a library
add_library(cpu cpu/cpu.cpp)
target_include_directories(cpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cpu)
target_link_libraries(cpu PUBLIC memory) # CPU depends on Memory

# Main emulator executable
add_executable(nes-emulator main.cpp)

# Link libraries to the main executable
target_link_libraries(nes-emulator PRIVATE cpu memory rom mapper ppu)

# Include all library directories for the main executable
target_include_directories(nes-emulator PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/cpu 
    ${CMAKE_CURRENT_SOURCE_DIR}/memory 
    ${CMAKE_CURRENT_SOURCE_DIR}/rom
    ${CMAKE_CURRENT_SOURCE_DIR}/mapper
    ${CMAKE_CURRENT_SOURCE_DIR}/ppu
)
