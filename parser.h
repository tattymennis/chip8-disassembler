// parser.h
// header file for parsing functions
#ifndef __PARSE_H_INCLUDED__
#define __PARSE_H_INCLUDED__

class Nybbler;

void parse(char buf[], int fsize);
void parseOpcode(Nybbler *n);
void prettyPrinter(char16_t word, unsigned char numNybbles);
void printBanner(std::string nameStr, std::string sizeStr);

#endif