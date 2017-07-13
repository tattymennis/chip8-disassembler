// nybbler.cpp
// implementation file for bit manipulation functions
#include "./nybbler.h"
// handle 2 byte opcode input for nybble manipulation
void Nybbler::assignNybbles(unsigned char b1, unsigned char b2){
    // assign high and low byte of opcode
    byte1 = b1;
    byte2 = b2;

    // assign full 16-bit word
    word = (byte1 << 8);    // xxxx xxxx 0000 0000
    word += (0xFF & byte2); // xxxx xxxx yyyy yyyy    

    // assign nybbles 1-4
    nybble1 = b1;           // xxxxxxxx
    nybble2_x = b1;         // xxxxxxxx
    nybble3_y = b2;         // xxxxxxxx
    nybble4 = b2;           // xxxxxxxx

    // bit manipulation for isolating nybbles
    nybble1 >>= 4;          // nybble1: 0000xxxx
    nybble2_x <<= 4;        // nybble2: xxxx0000 ->
    nybble2_x >>= 4;        // nybble2: 0000xxxx
    nybble3_y >>= 4;        // nybble3: 0000xxxx
    nybble4 <<= 4;          // nybble4: xxxx0000 ->
    nybble4 >>= 4;          // nybble4: 0000xxxx
}