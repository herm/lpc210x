#include "../lpc2103.h"
#include "config.h"
#include <inttypes.h>
#include "nrf24l01.hpp"
#include "spi.hpp"

NRF24L01::NRF24L01(SPI &spi_) : spi(spi_)
{
    status = read_reg(0x0f);
}

void NRF24L01::write_reg(uint8_t reg_nr, uint8_t data)
{
    cs_low();
    status = spi.rw(WRITE_REG | reg_nr);
    spi.rw(data);
    cs_high();
}

uint8_t NRF24L01::read_reg(uint8_t reg_nr)
{
    cs_low();
    status = spi.rw(READ_REG | reg_nr);
    uint8_t result = spi.rw(0);
    cs_high();
    return result;
}

