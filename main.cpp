#include <stdio.h>
#include <iostream>
#include <fstream>
#include "./parser.h"
#include "./parser.cpp"
#include "./nybbler.h"
#include "./nybbler.cpp"

//++++++++++++++++++++++++++++++++++++//
//   A disassembler for CHIP-8 ROMs   //
//    Written by Matthew W. Tennis    //
//     matthewtennisypr@gmail.com     //
//++++++++++++++++++++++++++++++++++++//

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 2)
        cout << "Error: requires 1 arg :: file path" << endl;
    else { // TODO: Add multiple file args functionality
        void printBanner(string nameStr, string sizeStr);
        void parse(char b[], int fsize); // forward decl of parse function
        
        // define input stream variable from CLI input
        ifstream ifile (argv[1], ios::in | ios::binary | ios::ate);

        if (!ifile.is_open())
            cout << "Error reading file " << argv[1] << endl;
        else {
            int fsize = ifile.tellg(); // determine filesize in bytes
            string name = "File name: " + (string)argv[1];
            string size = "File size: " + to_string(fsize) + " bytes";

            printBanner(name,size);

            // move 200 bytes into file, skipping interpreter
            //ifile.seekg(512, ios::beg);

            // move to beginning of file
            ifile.seekg(0, ios::beg);

            char buf[fsize];
            ifile.read(buf, fsize);

            if (ifile.fail())
                cout << "File read error." << endl;

            ifile.close();
            parse(buf, fsize);
        }
    }
    return 0;
}
