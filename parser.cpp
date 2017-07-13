// parser.cpp
// implementation file for parsing functions
#include <iomanip>
#include "./parser.h"
#include "./nybbler.h"

void prettyPrinter(char16_t word, unsigned char numNybbles) {
    if (numNybbles > 4)
        std::cout << "Error" << std::endl; // TODO: error
    else {
        switch(numNybbles) {
            case 2: // print lowest 2 nybbles, lowest byte
                word = word & 0x00FF; // bit-mask for lowest byte
                std::cout << std::showbase << std::internal
                << std::setfill('0') << std::setw(4)
                << std::hex << word << std::noshowbase 
                << std::endl;
                break;
            case 3: // print lowest 3 nybbles, 12 bits
                word <<= 4;
                word >>= 4;
                // format for 12-bit addresses
                std::cout << std::showbase << std::internal
                          << std::setfill('0') << std::setw(5) 
                          << std::hex << word << std::noshowbase;
                break;
            case 4: 
                std::cout << std::showbase << std::internal
                          << std::setfill('0') << std::setw(6) 
                          << std::hex << word << std::noshowbase;
                break;
            default:
                std::cout << "Invalid length applied to printer.\n";
                break;
        }     
    }
}

void parseOpcode(Nybbler &n){
    unsigned char byte1 = n.byte1;
    unsigned char byte2 = n.byte2;
    unsigned char nybble1 = n.nybble1;
    unsigned char nybble2_x = n.nybble2_x;
    unsigned char nybble3_y = n.nybble3_y;
    unsigned char nybble4 = n.nybble4;
    char16_t word = n.word;

    // case split on first nybble or most significant 4 bits
    switch (nybble1){
        case 0x0 : // possible parsing ambiguity w/ 0x0nnn
            switch (byte1) {
                case 0x00:
                    switch (byte2){
                        case 0xE0: std::cout << "CLS" << std::endl; break;
                        case 0xEE: std::cout << "RET" << std::endl; break;
                        // Super CHIP-48 Instructions
                        case 0xFB: // SCR   0x00FB
                            std::cout << "SCR\t\n";
                            break;
                        case 0xFC: // SCL   0x00FC
                            std::cout << "SCL\t\n";
                            break;
                        case 0xFD: // EXIT  0x00FD
                            std::cout << "EXIT\t\n";
                            break;
                        case 0xFE: // LOW   0x00FE
                            std::cout << "LOW\t\n";
                            break;
                        case 0xFF: // HIGH  0x00FF
                            std::cout << "HIGH\t\n";
                            break;                                                        
                        default:
                            if (nybble3_y == 0xC) {// Super CHIP-48, 0x00Cn
                                // SCD nibble   // 0x00Cn     
                                std::cout << "SCD\t" << (uint16_t)nybble4
                                          << std::endl;
                            }
                            else if(word > 0x0000) { // 0x00nn, one case for 0x0nnn
                                std::cout << "SYS\t";
                                prettyPrinter(word, 3); // get 12-bit addr
                                std::cout << "\tdeprecated op 0x0nnn\n";
                            }
                            else {
                                std::cout << "SYS\t";
                                prettyPrinter(word, 3); // get 12-bit addr (0x0000)
                                std::cout << "\tdeprecated op 0x0nnn\n";
                            }
                            break;
                    }
                default: // catch-all for 0x0nnn
                    if (((uint16_t)nybble2_x > 0)){
                        std::cout << "SYS\t";
                        prettyPrinter(word, 3); // print 12-bit addr
                        std::cout << "\tdeprecated op 0x0nnn\n";
                    }
                    break;
            } break;
        case 0x1 : // JP    0x0nnn
            std::cout << "JP\t";
            prettyPrinter(word, 3); // print 12-bit addr
            std::cout << std::endl;
            break;

        case 0x2 : 
            std::cout << "CALL\t"; 
            prettyPrinter(word, 3); // print 12-bit addr
            std::cout << std::endl;
            break;

        case 0x3 : // SE    Vx, Vy  // 3xkk 
            std::cout << "SE\tV" << (uint16_t)nybble2_x << ", ";
            prettyPrinter(word, 2); // print kk or lowest byte
            break;

        case 0x4 : // SNE  Vx, Vy   // 4xkk 
            std::cout << "SNE\tV" << (uint16_t)nybble2_x << ", ";
            prettyPrinter(word, 2); // print kk or lowest byte
            break;

        case 0x5 : // SE Vx, Vy     // 5xy0
            if (nybble4 != 0) {
                std::cout << "---\tERROR: Invalid opcode: ";
                prettyPrinter(word, 4); // print full 16-bit opcode
                std::cout << " ---\n";
            }
            else {
                std::cout << "SE\tV" << (uint16_t)nybble2_x << ", V" 
                          << (uint16_t)nybble3_y << std::endl;
            } break;
            
        case 0x6 : // LD Vx, kk     // 6xkk 
            std::cout << "LD\tV" << std::hex << (uint16_t)nybble2_x << ", ";
            prettyPrinter(word, 2); // print kk or lowest byte
            break;

        case 0x7 : // ADD Vx, kk    // 7xkk
            std::cout << "ADD\tV" << std::hex << (uint16_t)nybble2_x << ", ";
            prettyPrinter(word, 2); // print kk or lowest byte
            break;

        case 0x8 : // logical operators
            switch (nybble4) { // compare on least significant nybble
                case 0x0: // LD Vx, Vy  // 8xy0
                    std::cout << "LD\tV" << std::hex << (uint16_t)nybble2_x 
                              << ", V" << (uint16_t)nybble3_y << std::endl; 
                    break;
                case 0x1: // OR Vx, Vy  // 8xy1
                    std::cout << "OR\tV" << std::hex << (uint16_t)nybble2_x 
                              << ", V" << (uint16_t)nybble3_y << std::endl; 
                    break;
                case 0x2: // AND Vx, Vy // 8xy2     
                    std::cout << "AND\tV" << std::hex << (uint16_t)nybble2_x 
                              << ", V" << (uint16_t)nybble3_y << std::endl; 
                    break;
                case 0x3: // XOR Vx, Vy // 8xy3
                    std::cout << "XOR\tV" << std::hex << (uint16_t)nybble2_x 
                              << ", V" << (uint16_t)nybble3_y << std::endl;                 
                    break;
                case 0x4: // ADD Vx, Vy // 8xy4
                    std::cout << "ADD\tV" << std::hex << (uint16_t)nybble2_x 
                              << ", V" << (uint16_t)nybble3_y << std::endl;                 
                    break;
                case 0x5: // SUB Vx, Vy // 8xy5
                    std::cout << "SUB\tV" << std::hex << (uint16_t)nybble2_x 
                              << ", V" << (uint16_t)nybble3_y << std::endl;                 
                    break;
                case 0x6: // SHR Vx {, Vy} // 8xy6
                    std::cout << "SHR\tV" << std::hex << (uint16_t)nybble2_x 
                              << " {, V" << (uint16_t)nybble3_y << "}\n";                 
                    break;
                case 0x7: // SUBN Vx, Vy // 8xy7
                    std::cout << "SUBN\tV" << std::hex << (uint16_t)nybble2_x 
                              << ", V" << (uint16_t)nybble3_y << std::endl; 
                    break;
                case 0xE: // SHL Vx {, Vy} // 8xyE
                    std::cout << "SHL\tV" << std::hex << (uint16_t)nybble2_x 
                              << " {, V" << (uint16_t)nybble3_y << "}\n";                    
                    break;
                default:
                    std::cout << "---\tERROR: Invalid opcode: ";
                    prettyPrinter(word, 4); // print full 16-bit opcode
                    std::cout << " ---\n";
            } break;


        case 0x9 : // SNE Vx, Vy    // 9xy0
            if (nybble4 != 0) { 
                std::cout << "---\tERROR: Invalid opcode: "; // TODO
                prettyPrinter(word, 4);
                std::cout << " ---\n";
            }
            else { // SNE Vx, Vy    // 9xy0
                std::cout << "SNE\tV" << std::hex << (uint16_t)nybble2_x 
                          << ", V" << (uint16_t)nybble3_y << std::endl;                 
            } break;

        case 0xA : // LD I, addr    // Annn
            std::cout << "LD\tI, ";
            prettyPrinter(word, 3); // print 12-bit addr
            std::cout << std::endl;
            break;

        case 0xB : // JP V0, addr   // Bnnn
            std::cout << "JP\tV0, ";
            prettyPrinter(word, 3); // print 12-bit addr
            std::cout << std::endl;
            break;

        case 0xC : // RND Vx, byte  // Cxkk
            std::cout << "RND\tV" << std::hex << (uint16_t)nybble2_x
                      << ", ";
            prettyPrinter(word, 2); // print kk or lowest byte
            break;

        case 0xD : // DRW Vx, Vy, nibble // Dxyn
            if (((uint16_t)nybble4) > 0) {
                std::cout << "DRW \tV" << std::hex << (uint16_t)nybble2_x
                          << ", V" << (uint16_t)nybble3_y << ", "
                          << std::showbase << std::setw(6) << (uint16_t)nybble4 
                          << std::noshowbase << std::endl;
            }
            else { // Super CHIP-48, DRW Vx, Vy, 0
                std::cout << "DRW \tV" << std::hex << (uint16_t)nybble2_x
                          << ", V" << (uint16_t)nybble3_y << ", 0\n";              
            }
            break;

        case 0xE : // SKIP opcode
            switch (byte2) {
                case 0x9E: // SKP Vx    // Ex9E
                    std::cout << "SKP\tV" << std::hex << int(nybble2_x)
                              << std::endl;
                    break;
                case 0xA1: // SKPN Vx   // ExA1
                    std::cout << "SKPN\tV" << std::hex << int(nybble2_x)
                              << std::endl;               
                    break;
                default:
                    std::cout << "---\tERROR: Invalid opcode: ";
                    prettyPrinter(word, 4); // print entire opcode
                    std::cout << " ---\n";
            } break;
            break;

        case 0xF :
            switch (byte2) {
                case 0x07: // LD Vx, DT // Fx07
                    std::cout << "LD\tV" << (uint16_t)nybble2_x 
                              << ", DT\n";
                    break;
                case 0x0A: // LD Vx, K // Fx0A
                    std::cout << "LD\tV" << (uint16_t)nybble2_x
                              << ", K\n"; 
                    break;
                case 0x15: // LD DT, Vx // Fx15
                    std::cout << "LD\tDT, V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x18: // LD ST, Vx // Fx18
                    std::cout << "LD\tST, V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x1E: // ADD I, Vx // Fx1E
                    std::cout << "ADD\tI, V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x29: // LD F, Vx  // Fx29
                    std::cout << "LD\tF, V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x33: // LD B, Vx  // Fx33
                    std::cout << "LD\tB, V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x55: // LD [I], Vx // Fx55
                    std::cout << "LD\t[I], V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x65: // LD Vx, [I] // Fx65
                    std::cout << "LD\tV" << (uint16_t)nybble2_x
                              << ", [I]\n";
                    break;
                // Super CHIP-48 opcodes
                case 0x30: // LD HF, Vx // 0xFx30
                    std::cout << "LD\tHF, V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x75: // LD R, Vx  // 0xFx75
                    std::cout << "LD\tR, V" << (uint16_t)nybble2_x
                              << std::endl;
                    break;
                case 0x85: // LD Vx, R  // 0xFx85
                    std::cout << "LD\tV" << (uint16_t)nybble2_x
                              << ", R\t"; 
                    break;
                default:
                    std::cout << "---\tERROR: invalid opcode: ";
                    prettyPrinter(word, 4);
                    std::cout << " ---\n";
                    break;
            }
            break;
        default:
            // implicity impossible case
            std::cout << "---\tERROR: opcode case not covered! "
                      << std::hex << std::showbase << std::setfill('0');
            prettyPrinter(word, 4);
            std::cout << std::noshowbase << " ---\n";
            
            break;
    }
}

// function to parse CHIP-8 ROM binaries
void parse(char buf[], int fsize){ 
    char16_t memory;
    char16_t word;
    unsigned char byte1;
    unsigned char byte2;
    std::cout << "Memory\t" << "Opcode\t   " << "Instruction\n"; 
    std::cout << "======================================\n";

    for (int i = 0; i < fsize; i+=2) {
        Nybbler nybbler; // declaring variable in this scope?
        memory = static_cast<char16_t>(i);
        byte1 = static_cast<unsigned char>(buf[i]);
        byte2 = static_cast<unsigned char>(buf[i+1]);
        
        // call constructor for object handling nybble manipulation
        nybbler.assignNybbles(byte1, byte2);
        word = nybbler.word;

        // display/increment program memory
        std::cout << std::hex << std::showbase
                  << std::setw(6) << std::setfill('0')
                  << memory << "\t";

        // display opcode 
        std::cout  << "[" << std::hex << std::showbase
                  << std::setw(6) << std::setfill('0')
                  << word << "]" << std::noshowbase << ":  ";
        parseOpcode(nybbler);
    }
}

// print filename, filesize for banner. TODO: formatting
void printBanner(std::string nameStr, std::string sizeStr) {
    size_t width = 0;

    // for long filenames
    if ((nameStr.length() > 128) || (sizeStr.length() > 128))
        width = 128;

    else { // leave room for "+ " and " +"
        if (nameStr.length() > sizeStr.length())
            width = nameStr.length() + 4;
        else
            width = sizeStr.length() + 4;
    }

    // print head "+++...+++"
    for (size_t i = 0; i < width; i++)
        std::cout << "+";

    // nameStr is longer
    if ((width - 4 ) == nameStr.length())
    {
        std::cout << "\n+ " << nameStr << " +\n";
        std::cout << "+ " << sizeStr;
        for (size_t i = 0; i < width-(sizeStr.length()+3); i++)
            std::cout << " ";
        std::cout << "+\n";
    }

    // sizeStr is longer
    else if ((width - 4) == sizeStr.length())
    {
        std::cout << "\n+ " << nameStr;
        for (size_t i = 0; i < width-(nameStr.length()+3); i++)
            std::cout << " ";
        std::cout << "+\n+ " << sizeStr << " +\n";
    }

    // print tail "+++...+++"
    for (size_t i = 0; i < width; i++)
        std::cout << "+";
    std::cout << "\n\n";
}