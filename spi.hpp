#ifndef SPI_HPP
#define SPI_HPP
#include <inttypes.h>
#include "inline.hpp"

class SPI
{
public:
    SPI()
    {
        PINSEL0 = (PINSEL0 & ~(pin_func_mask(spi_miso)|pin_func_mask(spi_mosi)|pin_func_mask(spi_sck))) |
                  pin_func(spi_miso, 1) | pin_func(spi_mosi, 1) | pin_func(spi_sck, 1);
        FIODIR = (FIODIR & ~pin_mask(spi_miso)) | pin_mask(spi_mosi) | pin_mask(spi_sck);
        format();
        frequency();
    }
    inline void format(uint_fast8_t bits = 8, uint_fast8_t mode = 0)
    {
        uint16_t bits_value = SPI0_BITS_8;
        if (bits == 16) {
            bits_value = SPI0_BITS_16;
        } else {
            bits_value = SPI0_BITS_8 + bits - 8;
        }

        uint16_t mode_bits = 0;
        if (mode == 1)
        {
            //TODO
        }
        S0SPCR = SPI0_BitEnable | SPI0_Master | bits_value | mode_bits;
    }

    force_inline void frequency(uint32_t freq = 1000000)
    {
        uint32_t tmp = PCLK / freq;
        if (tmp & 1) tmp++;
        if (tmp < 8) tmp = 8;
        S0SPCCR = tmp;
    }

    /* Status is shifted out while command is shifted in */
    uint_fast8_t write(uint_fast8_t data)
    {
        S0SPDR = data;
        while (!(S0SPSR&SPIF)); //Wait for data
        return S0SPDR;
    }
};
#endif // SPI_HPP
