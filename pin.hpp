#ifndef PIN_HPP
#define PIN_HPP

class Pin
{
public:
    Pin(uint32_t bitmask) : bitmask_(bitmask) {}
    void low() { FIOCLR = bitmask_;}
    void high() { FIOSET = bitmask_;}
private:
    uint32_t bitmask_;
};


#endif // PIN_HPP
