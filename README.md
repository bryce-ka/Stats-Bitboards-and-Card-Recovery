# Chess Bitboard Library

This repository contains a C library for working with chess bitboards. It provides functions for generating pawn moves based on the placement of other chess pieces on the board.

## Files

### `bitboard.c`

This file contains the implementation of the chess bitboard library. It includes the following functions:

#### `unsigned long forwardHelper(unsigned long pawns, unsigned long color, unsigned long color2)`

This helper function returns the pawns for the next row. It takes three parameters: `pawns` (placement of white pawns on the board), `color` and `color2` (placement of colored pieces on the board). It returns an unsigned integer with the value showing where pawns from the current move can move forward.

#### `unsigned long diagonalHelper(unsigned long pawns, unsigned long black)`

This function returns diagonal pawn moves. It takes two parameters: `pawns` (placement of white pawns on the board) and `black` (placement of black pieces on the board). It returns an unsigned integer with the value showing where pawns from the current move can move diagonally.

#### `unsigned long computePawnMoves(unsigned long pawnPositions, unsigned long whitePieces, unsigned long blackPieces)`

This function computes all possible pawn moves based on the given pawn positions, white pieces, and black pieces. It takes three parameters: `pawnPositions` (placement of pawns on the board), `whitePieces` (placement of white pieces on the board), and `blackPieces` (placement of black pieces on the board). It returns an unsigned integer representing the combined final pawn moves.

#### `int main()`

This is the main function of the program, which demonstrates the usage of the chess bitboard library. It initializes the pawn positions, white pieces, and black pieces, calls the `computePawnMoves` function, and prints the computed solution.

### `cardrecovery.c`

This file contains a program for reading bytes from a raw file and producing sequence one files. It includes the following functions:

#### `int fileSize(FILE* infile)`

This function returns the size of the file and checks if the file is valid. It takes a file pointer `infile` as a parameter. It returns the number of bytes in the file.

#### `int recoverFiles()`

This function reads bytes from the input file (`card.raw`) and writes JPEG files based on the byte patterns. It uses two sequences: `seqOne` and `seqTwo`. It returns the number of JPEG files recovered.

#### `int main()`

This is the main function of the program, which calls the `recoverFiles` function to recover JPEG files from the `card.raw` file.

## Authors

This code was written by Paige Johnson and Bryce Anthony.
