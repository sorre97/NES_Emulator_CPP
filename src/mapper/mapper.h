#ifndef MAPPER_H
#define MAPPER_H

#include <cstdint>

class Mapper {

    public:
        Mapper() = delete;
        explicit Mapper(uint8_t nPRGBanks, uint8_t nCHRBanks);
        virtual ~Mapper() = default;

        virtual uint16_t translatePRGaddr(uint16_t address) const = 0;  // Translate PRG-ROM address
        virtual uint16_t translateCHRaddr(uint16_t address) const = 0;  // Translate CHR-ROM address
    
    protected:
        uint8_t nPRGBanks;
        uint8_t nCHRBanks;
};

class Mapper000 : public Mapper 
{
    public:
        Mapper000(uint8_t nPRGBanks, uint8_t nCHRBanks);
        uint16_t translatePRGaddr(uint16_t address) const override;  // Translate PRG-ROM address
        uint16_t translateCHRaddr(uint16_t address) const override;  // Translate CHR-ROM address
};

#endif