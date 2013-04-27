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
    explicit DigitalOut(uint32_t pinnr, bool init=true) : bitmask_(1 << pinnr) { if (init) FIODIR |= bitmask_; }
    void low() const { FIOCLR = bitmask_;}
    void high() const { FIOSET = bitmask_;}
    force_inline void operator=(int value) const { if (value) FIOSET = bitmask_; else FIOCLR = bitmask_; }
    force_inline operator int() const { return FIOPIN & bitmask_; }
protected:
    const uint32_t bitmask_;
};

typedef enum {
    PullNone,
//    PullUp,   //Unsupported
//    PullDown, //Unsupported
    OpenDrain, //Emulated
    _Output = 0x80
} PinMode;
#warning "Incomplete DigitalInOut support!"
class DigitalInOut : public DigitalOut
{
public:
    explicit DigitalInOut(uint32_t pinnr) : DigitalOut(pinnr, false)
    {
        FIODIR &= ~bitmask_;
    }
    void operator=(int value) const;
    void mode(PinMode pull) const;
};

#endif // PIN_HPP
