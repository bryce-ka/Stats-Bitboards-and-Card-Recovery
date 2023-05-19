/* Function producing a chess board of pawn moves given placement of other pieces
 *
 * Time spent: 5 hours
 *
 * Authors: Paige Johnson, Bryce Anthony
*/
#include "io.h"
#include <stdio.h>

unsigned long forwardHelper(unsigned long pawns, unsigned long color, unsigned long color2){
/* Helper function that returns pawns for the next row.
   Parameters:
       pawns - placement of white pawns on the board
       color & color2 - placement of colored pieces on the board
       currentRow - integer value representing row of pawns being looked at
   Returns:
       PawnsNext - unsigned int with value showing where pawns from current move can move forward
*/
    //int shift = (currentRow-1) * 8;

    //get pawns of current row
    //pawns = pawns >> shift;
    unsigned long pawnShift = (pawns << 8);

    //match  pieces to check forward move (need to shift)
    //unsigned long colorRow = color >> (shift + 8);
    //unsigned long colorRow2 = color2 >> (shift + 8);
    unsigned long pawnBlock = pawns;

    // calculation of next row
    unsigned long PawnsNext  =  (~color) & pawnShift;

    //unsigned int pawnPrint;
    unsigned long PawnsNext2  =  (~color2) & pawnShift;
    PawnsNext2 = PawnsNext2 & (~pawnBlock);

    //find moves for black and white pieces
    PawnsNext = PawnsNext & PawnsNext2;

    printf("forward helper: %lx\n", PawnsNext);
    return PawnsNext;
}

unsigned long diagonalHelper(unsigned long pawns, unsigned long black){
    /* Returns diagonal pawn moves
    Parameters:
        pawns - placement of white pawns on the board
        black - placement of black pieces on board
        currentRow - integer value representing row of pawns being looked at
    Returns:
        finalDiagonal - unsigned int with value showing where pawns from current move can move diagonally
    */
    //get pawns of current row
    pawns = (pawns << 8);
    prettyPrint(pawns);
    printf("\n");
    prettyPrint(black);
    printf("\n");
    // calculation of next row
    //left
    unsigned long blackRowLeft = black << 1;
    unsigned long PawnsLeft  =  pawns & blackRowLeft;
    //shift back to original position
    PawnsLeft = (PawnsLeft >> 1);
    prettyPrint(PawnsLeft);
    printf("\n");

    //right
    unsigned long blackRowRight = black >> 1;
    prettyPrint(blackRowRight);
    printf("\n");
    //printf("br right: %lx\n", blackRowRight);
    //printf("pawns: %lx\n", pawns);
    unsigned long PawnsRight  =  pawns & blackRowRight;
    //printf("pawns right: %lx\n", PawnsRight);
    //shift back to original position
    PawnsRight = (PawnsRight << 1);
    prettyPrint(PawnsRight);
    //printf("pawns right 2: %lx\n", PawnsRight);

    //combine
    unsigned long finalDiagonal = PawnsRight | PawnsLeft;

    printf("diag helper: %lx\n", finalDiagonal);
    return finalDiagonal;
}

unsigned long computePawnMoves(unsigned long pawnPositions, unsigned long whitePieces, unsigned long blackPieces){
    unsigned long forwardFinal = 0x0000000000000000;
    unsigned long diagonalFinal = 0x0000000000000000;
    unsigned long tempRow = 0x0000000000000000;
    unsigned long tempRow2 = 0x0000000000000000;

    unsigned long allWhite = pawnPositions | whitePieces;


    //finding paws that move forward twice
    unsigned long row3Pawns = forwardHelper(pawnPositions, allWhite, blackPieces);
    row3Pawns = row3Pawns & 0x0000000000ff0000;
    tempRow = forwardHelper(row3Pawns, allWhite, blackPieces);
    tempRow = tempRow & 0x00000000ff000000;
    forwardFinal = forwardFinal | tempRow;
    //printf("forward final: %lx\n", forwardFinal);

    //testing row 2 to produce row 3
    tempRow = forwardHelper(pawnPositions, allWhite, blackPieces);
    unsigned long maskThird = 0x0000000000ff0000;
    tempRow = tempRow & maskThird;
    forwardFinal = forwardFinal | tempRow;

    tempRow = pawnPositions & 0x000000000000ff00;
    tempRow2 = diagonalHelper(tempRow, blackPieces);
    tempRow2 = tempRow2 & maskThird;
    diagonalFinal = diagonalFinal | tempRow2;

    //testing row 3 to produce row 4
    tempRow = forwardHelper(pawnPositions, allWhite, blackPieces);
    unsigned long maskFourth = 0x00000000ff000000;
    tempRow = tempRow & maskFourth;
    forwardFinal = forwardFinal | tempRow;

    tempRow = pawnPositions & maskThird;
    tempRow2 = diagonalHelper(tempRow, blackPieces);
    tempRow2 = tempRow2 & maskFourth;
    diagonalFinal = diagonalFinal | tempRow2;

    //testing row 4 to produce row 5
    tempRow = forwardHelper(pawnPositions, allWhite, blackPieces);
    unsigned long maskFifth = 0x000000ff00000000;
    tempRow = tempRow & maskFifth;
    forwardFinal = forwardFinal | tempRow;

    tempRow = pawnPositions & maskFourth;
    tempRow2 = diagonalHelper(tempRow, blackPieces);
    tempRow2 = tempRow2 & maskFifth;
    diagonalFinal = diagonalFinal | tempRow2;

    //testing row 5 to produce row 6
    tempRow = forwardHelper(pawnPositions, allWhite, blackPieces);
    unsigned long maskSixth = 0x0000ff0000000000;
    tempRow = tempRow & maskSixth;
    forwardFinal = forwardFinal | tempRow;

    tempRow = pawnPositions & maskFifth;
    tempRow2 = diagonalHelper(tempRow, blackPieces);
    tempRow2 = tempRow2 & 0x0000ff0000000000;
    diagonalFinal = diagonalFinal | tempRow2;

    //testing row 6 to produce row 7
    tempRow = forwardHelper(pawnPositions, allWhite, blackPieces);
    unsigned long maskSeventh = 0x00ff000000000000;
    tempRow = tempRow & maskSeventh;
    forwardFinal = forwardFinal | tempRow;

    tempRow = pawnPositions & maskSixth;
    tempRow2 = diagonalHelper(tempRow, blackPieces);
    tempRow2 = tempRow2 & maskSeventh;
    diagonalFinal = diagonalFinal | tempRow2;

    //testing row 7 to produce row 8
    tempRow = forwardHelper(pawnPositions, allWhite, blackPieces);
    unsigned long maskEighth = 0xff00000000000000;
    tempRow = tempRow & maskEighth;
    forwardFinal = forwardFinal | tempRow;

    tempRow = pawnPositions & maskSeventh;
    tempRow2 = diagonalHelper(pawnPositions, blackPieces);
    tempRow2 = tempRow2 & maskEighth;
    diagonalFinal = diagonalFinal | tempRow2;

    unsigned long combinedFinal = 0x0000000000000000;
    combinedFinal = forwardFinal | diagonalFinal;
    return combinedFinal;
}


int main(){
    unsigned long whitePieces = 0x200000000;
    unsigned long blackPieces  = 0x2800000000;
    unsigned long pawnPositions = 0x14000000;
    unsigned long solution = computePawnMoves(pawnPositions, whitePieces, blackPieces);
    printf("solution: %lx\n", solution);
    printf("goal: 3c00000000\n");
    return 0;
}