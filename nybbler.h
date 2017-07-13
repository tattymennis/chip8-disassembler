// nybbler.h
// header file for bit manipulation functions
#ifndef __NYBBLER_H_INCLUDED__
#define __NYBBLER_H_INCLUDED__

// handle 2 byte opcode input for nybble manipulation
class Nybbler {
    public:
        void assignNybbles(unsigned char b1, unsigned char b2);
        char16_t word;
        unsigned char byte1;
        unsigned char byte2;
        unsigned char nybble1;
        unsigned char nybble2_x;
        unsigned char nybble3_y;
        unsigned char nybble4; 
};

#endif