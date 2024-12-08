#include "ppu.h"
#include <iostream>
#include <unwind.h>
#include <dlfcn.h>
#include <sstream>
#include <cxxabi.h>

constexpr int TOTAL_CYCLES_PER_SCANLINE = 341;
constexpr int VISIBLE_SCANLINES = 240;
constexpr int TOTAL_SCANLINES = 261;
constexpr int VBLANK_START_SCANLINE = 241;
constexpr int VBLANK_END_SCANLINE = 260;

PPU::PPU() 
    : PPUCTRL(0), PPUMASK(0), PPUSTATUS(0), OAMADDR(0), PPUSCROLL(0), PPUADDR(0), PPUDATA(0), triggerNMI(nullptr) {
    VRAM.resize(2048, 0); // Initialize 2 KB of VRAM
    OAM.resize(256, 0);   // Initialize 256 bytes of OAM
}

void PPU::setNMICallback(const std::function<void()>& callback) {
    triggerNMI = callback;
}

void PPU::setIRQCallback(const std::function<void()>& callback) {
        triggerIRQ = callback;
    }

void PPU::reset() {
    PPUCTRL = 0;
    PPUMASK = 0;
    PPUSTATUS = 0;
    OAMADDR = 0;
    PPUSCROLL = 0;
    PPUADDR = 0;
    PPUDATA = 0;
}

/*
VBlank, or Vertical Blanking Interval, is a period during the NES rendering cycle when the PPU is not actively drawing the screen. It's a crucial part of the NES rendering system that allows the CPU to update graphical data without disrupting the display.

Key Points About VBlank:
Duration: VBlank lasts for about 2273 PPU cycles (from scanlines 241 to 260 inclusive in the NTSC NES).
Significance:
During VBlank, the VBlank flag (bit 7 of the $2002 register) is set.
The CPU uses this period to modify graphical data like background tiles and sprites safely.
End of VBlank: The flag is cleared at the end of VBlank, and rendering for the next frame begins.

+----------------------+-------------------------+---------------------------+---------------------------------+
|      Category        | Horizontal (Pixels)     | Vertical (Scanlines)      | Vertical Range (Scanlines)     |
+----------------------+-------------------------+---------------------------+---------------------------------+
| Visible Area         | 256 pixels             | 240 scanlines             | 0–239                          |
| Post-Render Line     | 256 pixels             | 1 scanline                | 240                            |
| VBlank Period        | 256 pixels             | 20 scanlines              | 241–260                        |
| Pre-Render Line      | 256 pixels             | 1 scanline                | 261                            |
| Total Frame          | 256 pixels             | 261 scanlines             | 0–261                          |
+----------------------+-------------------------+---------------------------+---------------------------------+

Notes:
- Visible Area: Spans from scanline 0 to 239 and contains the on-screen graphics.
- Post-Render Line: Scanline 240, where the PPU enters an idle state after completing visible rendering.
- VBlank Period: Starts at scanline 241 and ends at 260, during which no pixels are rendered, and VRAM updates can occur.
- Pre-Render Line: The last scanline (261) is used to prepare the PPU for the next frame's rendering cycle.
*/
void PPU::step() {
    // Increment the cycle counter
    currentCycle++;

    // Check if we've completed a scanline
    if (currentCycle >= TOTAL_CYCLES_PER_SCANLINE) {
        currentCycle = 0;
        currentScanline++;

        // Wrap back to the start of the frame
        if (currentScanline >= TOTAL_SCANLINES) {
            currentScanline = 0;
        }
    }

    // Handle VBlank period
    if (currentScanline == VBLANK_START_SCANLINE && currentCycle == 0) {
        // Enter VBlank
        PPUSTATUS |= (1<<7); // Set VBlank flag
        if (triggerNMI) {
            triggerNMI(); // Trigger NMI via callback
        }
    }

    if (currentScanline == VBLANK_END_SCANLINE && currentCycle == 0) {
        // Exit VBlank
        PPUSTATUS &= ~(1<<7); // Clear VBlank flag
    }

    // Rendering logic
    if (currentScanline < VISIBLE_SCANLINES) {
        // Calculate pixel output based on scrollX and scrollY
        int pixelX = (currentCycle + scrollX) % 256; // Adjust for horizontal scroll
        int pixelY = (currentScanline + scrollY) % 240; // Adjust for vertical scroll

        // Fetch and render the pixel from VRAM based on pixelX and pixelY
        // Example: Fetch tile data and attributes here
    }
}


uint8_t PPU::readRegister(uint16_t address) {
    uint16_t reg = address & 0x2007; // Handle mirroring within $2000-$2007
    switch (reg) {
        case 0x2002: // PPUSTATUS
            {
                uint8_t status = PPUSTATUS;
                PPUSTATUS &= 0x7F; // Clear the vertical blank flag (bit 7)
                return status;
            }
        case 0x2004: // OAMDATA
            return OAM[OAMADDR]; // Read from OAM at current OAMADDR
        case 0x2007: // PPUDATA
            {
                uint8_t data = VRAM[PPUADDR % 2048]; // Read from VRAM
                PPUADDR += (PPUCTRL & 0x04) ? 32 : 1; // Increment PPUADDR by 1 or 32
                return data;
            }
        default:
            // Stack trace collection
            void* callstack[128];
            int frames = 0;

            struct StackFrame {
                void** callstack;
                int maxFrames;
                int numFrames;
            } frame = {callstack, 128, 0};

            _Unwind_Backtrace([](struct _Unwind_Context* context, void* arg) -> _Unwind_Reason_Code {
                StackFrame* frame = static_cast<StackFrame*>(arg);
                if (frame->numFrames >= frame->maxFrames) return _URC_END_OF_STACK;
                frame->callstack[frame->numFrames++] = (void*)_Unwind_GetIP(context);
                return _URC_NO_REASON;
            }, &frame);

            frames = frame.numFrames;

            // Format the stack trace
            std::ostringstream oss;
            oss << "Unsupported PPU register read at address: 0x" << std::hex << address << "\n";
            oss << "Call stack:\n";

            for (int i = 0; i < frames; ++i) {
                Dl_info info;
                if (dladdr(callstack[i], &info)) {
                    const char* demangled = abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, nullptr);
                    if (demangled) {
                        oss << "Frame " << i << ": " << demangled
                            << " (" << info.dli_fname << ")\n";
                    } else {
                        oss << "Frame " << i << ": " << info.dli_sname
                            << " (" << info.dli_fname << ")\n";
                    }
                } else {
                    oss << "Frame " << i << ": " << callstack[i] << " (unknown)\n";
                }
            }

            throw std::runtime_error(oss.str());
            //throw std::runtime_error("Unsupported PPU register read.");
    }
}

void PPU::writeRegister(uint16_t address, uint8_t value) {
    uint16_t reg = address & 0x2007; // Handle mirroring within $2000-$2007
    switch (reg) {
        case 0x2000: // PPUCTRL
            PPUCTRL = value;
            break;
        case 0x2001: // PPUMASK
            PPUMASK = value;
            break;
        case 0x2003: // OAMADDR
            OAMADDR = value;
            break;
        case 0x2004: // OAMDATA
            OAM[OAMADDR++] = value; // Write to OAM and increment OAMADDR
            break;
        case 0x2005: // PPUSCROLL
            if (!writeToggle) {
                scrollX = value; // First write: Fine X scroll
            } else {
                scrollY = value; // Second write: Fine Y scroll
            }
            writeToggle = !writeToggle; // Toggle latch
            break;
        case 0x2007: // PPUDATA
            VRAM[PPUADDR % 2048] = value; // Write to VRAM
            PPUADDR += (PPUCTRL & 0x04) ? 32 : 1; // Increment PPUADDR
            break;
        default:
            std::ostringstream oss;
            oss << "Unsupported PPU register write at address: 0x" << std::hex << address;
            throw std::runtime_error(oss.str());
    }
}

