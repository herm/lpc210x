#ifndef PIN_HPP
#define PIN_HPP

#include <inttypes.h>
#include "lpc2103.h"
#include "utils.h"

#define pin_mask(pin)  (1<<(pin))
#define pin_func(pin, function) ((function) << (((pin) & 0x0f)*2))
#define pin_func_mask(pin) (3 << (((pin) & 0x0f)*2))

class DigitalOut
{
public:
    explicit DigitalOut(uint32_t pinnr) : bitmask_(1 << pinnr) { FIODIR |= bitmask_; }
    void low() const { FIOCLR = bitmask_;}
    void high() const { FIOSET = bitmask_;}
    force_inline void operator=(int value) const { if (value) FIOSET = bitmask_; else FIOCLR = bitmask_; }
    force_inline operator int() const { return FIOPIN & bitmask_ ? 1 : 0; }
private:
    const uint32_t bitmask_;
};


#endif // PIN_HPP
