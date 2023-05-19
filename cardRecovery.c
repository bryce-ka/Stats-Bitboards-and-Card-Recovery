/* Function reading bytes from raw file and producing seqOne files.
 *
 * Time spent: 9 hours
 *
 * Authors: Paige Johnson, Bryce Anthony
*/
//importing neccerasy libraries and files
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <bits/types/FILE.h>

 FILE* infile;

int fileSize(FILE* infile){
    /* Returns size of file and checks if file is valid
    Parameters:
       infile - file being used
    Returns:
       length - the number of bytes in the file
    */

    if (infile == NULL) {
        printf("Error: unable to open file %s\n", "input.txt");
        exit(1);
    }

    //gets number of bytes in file
    fseek(infile, 0, SEEK_END);
    int length =  ftell(infile);

    fclose(infile);
    return length;
}

int recoverFiles(){

    unsigned char seqOne[4] = {0xff,0xd8,0xff,0xe0};
    unsigned char seqTwo[4] = {0xff,0xd8,0xff,0xe1};
    FILE* outfile;
    infile = fopen("card.raw", "rb");
    int sizeOfFile = 0;
    sizeOfFile = fileSize(infile);

    if(sizeOfFile != 0){
        int falsecounter = 0;
        falsecounter ++;
    }

    infile = fopen("card.raw", "rb");

    // counter of bytes
    int counter = 0;
    // counter of real jpegs
    int num = 0;
    // failed bytes
    int byteNot = 0;

    // pattern indicator
    int pat = 0;
    //while loop to look at bytes and write jpegs
    while (feof(infile) != !feof(infile)) {
        // read the next byte
        unsigned char byte = readByte(infile);

        if (feof(infile)){
            // close the outfile
            fclose(outfile);
            break;
        }

        //check byte patterns
        if((byte == seqOne[counter] || byte == seqTwo[counter])){
            counter = counter + 1;
            if (counter == 4){
                if (pat == 1){
                    fclose(outfile);
                }
                //same
                pat = 1;
                num ++;

                char jpegslot[10];

                snprintf(jpegslot, 10, "%d.%s", num, "jpg");

                outfile = fopen(jpegslot, "wb");

                writeByte(outfile, seqOne[0]);
                writeByte(outfile, seqOne[1]);
                writeByte(outfile, seqOne[2]);
                //reset counters
                counter = 0;
                byteNot = 0;
            }
        }

        else{
            counter = 0;
            if(pat == 1){
                for(int i = 0; i < byteNot; i++){
                    writeByte(outfile,seqOne[i]);
                }
                //reset failed counter
                byteNot = 0;
            }
        }

        if(!feof(infile) && pat == 1 && counter == 0){
            writeByte(outfile, byte);
        }
        else if (pat == 1){
            byteNot++;
        }
    }
    //finished reading file
    fclose(infile);
    return num;
}

//to run function
int main(){
    recoverFiles();
    return 0;
}