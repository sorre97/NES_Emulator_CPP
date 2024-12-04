#include "cartridge.h"
#include <fstream>
#include <iostream>

Cartridge::Cartridge(const std::string& filepath)
{
    /* 1, Open .nes file in binary mode */
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    /* 2. Read cartidge header (16 Bytes) */
    file.read(reinterpret_cast<char*>(&RomHeader), sizeof(RomHeaderType));
    if (!file) {
        throw std::runtime_error("Failed to read ROM header from file: " + filepath);
    }

    /* Verify the magic number */
    if (std::strncmp(RomHeader.magic, "NES\x1A", 4) != 0) {
        throw std::runtime_error("Invalid NES magic number.");
    }

    /* Check for NES 2.0 format */
    if (((RomHeader.flags7 >> 2) & 0x03) == 0x02) {
        throw std::runtime_error("NES 2.0 format is not supported.");
    }

    /* Assign specific flags */
    mapperID = (RomHeader.flags6 >> 4) | (RomHeader.flags7 & 0xF0);

    /* PRG-ROM size in bytes (16 KB units) */
    size_t PRGROM_size = RomHeader.PRGROM_size * 16 * 1024;
    PRGROM.resize(PRGROM_size);

    /* CHR-ROM size in bytes (8 KB units; if zero, CHR-RAM is used) */
    size_t CHRROM_size = RomHeader.CHRROM_size * 8 * 1024;
    if (CHRROM_size > 0) {
        CHRROM.resize(CHRROM_size);
    }

    /* 3. Read trainer data, if any */
    if(RomHeader.flags6 & (1 << 2))
    {
        trainer.resize(512);
        file.read(reinterpret_cast<char*>(trainer.data()), trainer.size());
        if (!file) {
            throw std::runtime_error("Failed to read trainer data.");
        }
    }

    /* 4. Rear PRG-ROM data */
    file.read(reinterpret_cast<char*>(PRGROM.data()), PRGROM.size());
    if (!file) {
        throw std::runtime_error("Failed to read PRG-ROM data.");
    }

    /* 5. Rear CHR-ROM data (if any) */
    if (CHRROM_size > 0) {
        file.read(reinterpret_cast<char*>(CHRROM.data()), CHRROM.size());
        if (!file) {
            throw std::runtime_error("Failed to read CHR-ROM data.");
        }
    }

    /* Close the file explicitly (destructor will handle it) */
    file.close();

    // Instantiate the appropriate mapper
    switch (mapperID) {
        case 0:
            mapper = std::make_unique<Mapper000>(RomHeader.PRGROM_size, RomHeader.CHRROM_size);
            break;
        default:
            throw std::runtime_error("Unsupported mapper: " + std::to_string(mapperID));
    }
}

uint8_t Cartridge::getMapperID() const
{
    return mapperID;
}

bool Cartridge::hasBatteryBackedRAM() const
{
    // TODO:
    
    return 1;
}

bool Cartridge::isFourScreenVRAM() const
{
    // TODO:
    
    return 1;
}

bool Cartridge::isVerticalMirroring() const
{
    // TODO:

    return 1;
}

uint8_t Cartridge::getPRGBankCount() const {
    return RomHeader.PRGROM_size; // Already in 16 KB units
}

uint8_t Cartridge::getCHRBankCount() const {
    return RomHeader.CHRROM_size; // Already in 8 KB units
}

uint8_t Cartridge::readPRGROM(uint16_t address) const {
    uint16_t translatedAddr = mapper->translatePRGaddr(address);
    if (translatedAddr >= PRGROM.size()) {
        throw std::out_of_range("PRG-ROM access out of bounds.");
    }
    return PRGROM[translatedAddr];
}

uint8_t Cartridge::readCHRROM(uint16_t address) const {
    uint16_t translatedAddr = mapper->translateCHRaddr(address);
    if (translatedAddr >= CHRROM.size()) {
        throw std::out_of_range("CHR-ROM access out of bounds.");
    }
    return CHRROM[translatedAddr];
}