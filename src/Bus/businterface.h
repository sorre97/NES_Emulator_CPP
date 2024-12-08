/**
 * @file businterface.h
 * @brief Defines the BusInterface class for managing CPU and PPU bus communication.
 */

#ifndef BUSINTERFACE_H
#define BUSINTERFACE_H

#include <cstdint>
#include "cartridge.h"
#include <memory>
#include "ppu.h"


/**
 * @class BusInterface
 * @brief Manages communication between the CPU, PPU, and memory-mapped devices.
 */
class BusInterface {
public:
    /**
     * @brief Destructor.
     */
    ~BusInterface() = default;

    /**
     * @brief Deleted default constructor.
     */
    BusInterface() = delete;

    /**
     * @brief Constructs the BusInterface with a Cartridge instance.
     * @param cartridge Unique pointer to the Cartridge instance.
     */
    explicit BusInterface(std::shared_ptr<Cartridge> cartridge, std::shared_ptr<PPU> ppu);

    /**
     * @brief Reads a byte from the CPU bus at the specified address.
     * @param address Memory address to read from.
     * @return The byte read from the address.
     */
    uint8_t cpuBusRead(uint16_t address) const;

    /**
     * @brief Writes a byte to the CPU bus at the specified address.
     * @param address Memory address to write to.
     * @param data The byte to write to the address.
     */
    void cpuBusWrite(uint16_t address, uint8_t data);

    /**
     * @brief Reads a byte from the PPU bus at the specified address.
     * @param address Memory address to read from.
     * @return The byte read from the address.
     */
    uint8_t ppuBusRead(uint16_t address) const;

    /**
     * @brief Writes a byte to the PPU bus at the specified address.
     * @param address Memory address to write to.
     * @param data The byte to write to the address.
     */
    void ppuBusWrite(uint16_t address, uint8_t data);

private:
    std::shared_ptr<Cartridge> cartridge; /**< Pointer to the loaded NES cartridge. */
    std::shared_ptr<PPU> ppu;
};

#endif // BUSINTERFACE_H
