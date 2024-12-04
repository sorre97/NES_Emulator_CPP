#include "raylib.h"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

// NES screen dimensions
constexpr int NES_WIDTH = 256;
constexpr int NES_HEIGHT = 240;

// Instruction memory
std::vector<std::string> instructionMemory = {
    "NOP", "LDA #$44", "STA $0200", "LDX #$02", "JMP $C000",
    "AND #$0F", "ASL", "BNE $FD", "BRK", "RTS"
};

// Function to get CPU register values as strings
std::vector<std::string> GetCPURegisters() {
    return {
        "A: 0x34",
        "X: 0x02",
        "Y: 0xFF",
        "PC: 0x8003",
        "SP: 0xFD"
    };
}

int main() {
    // Double NES resolution
    const int scaledNESWidth = NES_WIDTH * 2;
    const int scaledNESHeight = NES_HEIGHT * 2;

    // Right column for instructions and registers
    const int instructionColumnWidth = 200; // Wider column to accommodate instructions and registers
    const int windowWidth = scaledNESWidth + instructionColumnWidth;
    const int windowHeight = scaledNESHeight;

    InitWindow(windowWidth, windowHeight, "NES Emulator");
    SetTargetFPS(60);

    // Current instruction index
    int instructionPointer = 0;
    const int instructionsVisible = 2; // Number of instructions before and after

    while (!WindowShouldClose()) {
        // Check for spacebar press to advance the instruction
        if (IsKeyPressed(KEY_SPACE)) {
            instructionPointer++;
            if (instructionPointer >= instructionMemory.size()) {
                instructionPointer = 0; // Loop back to the start
            }
        }

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw NES screen on the left
        DrawRectangle(0, 0, scaledNESWidth, scaledNESHeight, DARKGRAY);
        DrawRectangleLinesEx({0, 0, (float)scaledNESWidth, (float)scaledNESHeight}, 2, BLACK);

        // Draw instruction and register column on the right
        int columnX = scaledNESWidth;
        DrawRectangle(columnX, 0, instructionColumnWidth, windowHeight, LIGHTGRAY);
        DrawRectangleLinesEx({(float)columnX, 0, (float)instructionColumnWidth, (float)windowHeight}, 2, BLACK);

        // Draw instructions
        int instructionsStartY = 20; // Starting Y position for instructions
        int lineHeight = 30; // Line height for instructions

        for (int i = -instructionsVisible; i <= instructionsVisible; ++i) {
            int idx = instructionPointer + i;
            if (idx < 0 || idx >= instructionMemory.size()) continue;

            // Highlight current instruction
            Color textColor = (i == 0) ? WHITE : DARKGRAY;
            DrawText(instructionMemory[idx].c_str(), columnX + 10, instructionsStartY + (i + instructionsVisible) * lineHeight, 20, textColor);
        }

        // Draw CPU registers below instructions
        int registersStartY = instructionsStartY + (instructionsVisible * 2 + 1) * lineHeight + 40; // Position below instructions
        DrawText("CPU Registers:", columnX + 10, registersStartY, 20, BLACK);

        std::vector<std::string> registers = GetCPURegisters();
        for (size_t i = 0; i < registers.size(); ++i) {
            DrawText(registers[i].c_str(), columnX + 10, registersStartY + 30 + (i * lineHeight), 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
