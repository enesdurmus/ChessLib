/*
 * chessLib.h
 *
 *  Created on: 12 Ara 2020
 *      Author: X550V
 */

#ifndef CHESSLIB_H_
#define CHESSLIB_H_

struct pos {
	short horizontal;
	char vertical;
};

int** createBoard();

void printMove(char, struct pos);

void printBoard(int**);

struct pos* moveKing(struct pos);

int movementNumberKing(int, int);

struct pos* moveQueen(struct pos);

int movementNumberQueen(int, int);

struct pos* moveBishop(struct pos);

int movementNumberBishop(int, int);

struct pos* moveKnight(struct pos);

int movementNumberKnight(int, int);

struct pos* moveRook(struct pos);

int movementNumberRook(int, int);

struct pos* movePawn(struct pos);

int movementNumberPawn(int, int);

int movementNumber(int, int);
#endif /* CHESSLIB_H_ */
