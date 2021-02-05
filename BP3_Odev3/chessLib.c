#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessLib.h"

int** createBoard() {

	int **board = (int**) calloc(8, sizeof(int*));

	for (int i = 0; i < 8; i++) {
		*(board + i) = (int*) calloc(8, sizeof(int));
	}
	return board;
}

void printMove(char tas, struct pos firstPos) {

	struct pos* (*movementFunctions[])(struct pos) = {
		&moveKing,&moveQueen,&moveBishop,&moveKnight,&moveRook,&movePawn
	};

	struct pos *positions;
	int movement = 0;

	int posi = 8 - firstPos.horizontal;
	int posj = (int) firstPos.vertical - 65;

	switch (tas) {
	case 'S':
		positions = movementFunctions[0](firstPos);
		movement = movementNumberKing(posi, posj);
		break;
	case 'V':
		positions = movementFunctions[1](firstPos);
		movement = movementNumberQueen(posi, posj);
		break;

	case 'F':
		positions = movementFunctions[2](firstPos);
		movement = movementNumberBishop(posi, posj);
		break;

	case 'A':
		positions = movementFunctions[3](firstPos);
		movement = movementNumberKnight(posi, posj);
		break;

	case 'K':
		positions = movementFunctions[4](firstPos);
		movement = movementNumberRook(posi, posj);
		break;

	case 'P':
		positions = movementFunctions[5](firstPos);
		movement = movementNumberPawn(posi, posj);
		break;
	}

	int **board;
	board = createBoard();

	int temp_i = 0;
	int temp_j = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (i == posi && j == posj) {
				board[i][j] = 2;
			} else {

				for (int k = 0; k < movement; k++) {

					temp_i = 8 - positions[k].horizontal;
					temp_j = (int) positions[k].vertical - 65;
					if (i == temp_i && j == temp_j) {
						board[i][j] = 1;
						break;
					}
				}
			}
		}
	}
	printBoard(board);
}

void printBoard(int **board) {
	int count = 1;
	for (int i = 0; i < 8; i++) {
		printf("%d  |", count++);
		for (int j = 0; j < 8; j++) {
			printf("%d   ", board[i][j]);
		}
		puts("");
	}
	puts("    -----------------------------");
	puts("    A   B   C   D   E   F   G   H");
}

struct pos* moveKing(struct pos firstPos) {

	int posi = 8 - firstPos.horizontal;
	int posj = (int) firstPos.vertical - 65;

	int positionsIndex = 0;
	struct pos *positions = (struct pos*) calloc(
			movementNumberKing(posi, posj), sizeof(struct pos));

	for (int i = posi - 1; i <= posi + 1; i++) {

		for (int j = posj - 1; j <= posj + 1; j++) {

			if (!(i == posi && j == posj) && (i <= 7 && j <= 7)
					&& (0 <= i && 0 <= j)) {

				struct pos position;
				position.horizontal = 8 - i;
				position.vertical = (char) (j + 65);
				positions[positionsIndex] = position;

				positionsIndex++;
			}
		}
	}

	return positions;
}

int movementNumberKing(int posi, int posj) {
	int movement = 0;

	if ((posj == 0 && (posi == 0 || posi == 7))
			|| (posj == 7 && (posi == 0 || posi == 7))) {
		movement = 3;
	} else if ((posj == 0 && (posi != 0 && posi != 7))
			|| (posj == 7 && (posi != 0 && posi != 7))) {
		movement = 5;
	} else {
		movement = 8;
	}
	return movement;
}

struct pos* moveQueen(struct pos firstPos) {

	int posi = 8 - firstPos.horizontal;
	int posj = (int) firstPos.vertical - 65;

	int count = 0;
	struct pos *positions = (struct pos*) calloc(
			movementNumberQueen(posi, posj) , sizeof(struct pos));

	int temp_i = 0;
	int temp_j = 0;

	//To the left top corner
	temp_i = posi - 1;
	temp_j = posj - 1;

	while (temp_i >= 0 && temp_j >= 0) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i--;
		temp_j--;
	}

	//To the right bottom corner
	temp_i = posi + 1;
	temp_j = posj + 1;

	while (temp_i <= 7 && temp_j <= 7) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i++;
		temp_j++;
	}

	//To the left
	temp_i = posi;
	temp_j = posj - 1;

	while (temp_j >= 0) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_j--;
	}

	//To the right
	temp_i = posi;
	temp_j = posj + 1;

	while (temp_j <= 7) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_j++;
	}

	//To the top
	temp_i = posi - 1;
	temp_j = posj;

	while (temp_i >= 0) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i--;
	}

	//To the bottom
	temp_i = posi + 1;
	temp_j = posj;

	while (temp_i <= 7) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i++;
	}

	//To the left bottom corner
	temp_i = posi + 1;
	temp_j = posj - 1;

	while (temp_i <= 7 && temp_j >= 0) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i++;
		temp_j--;
	}

	//To the top right corner.
	temp_i = posi - 1;
	temp_j = posj + 1;

	while (temp_i >= 0 && temp_j <= 7) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i--;
		temp_j++;
	}

	return positions;

}

int movementNumberQueen(int posi, int posj) {

	int movement = 14;

	if (posi >= posj) {

		movement += posj;
		movement += 7 - posi;

	} else {

		movement += posi;
		movement += 7 - posj;

	}

	if ((posi + posj) >= 7) {

		movement += 7 - posi;
		movement += 7 - posj;

	} else {

		movement += posj;
		movement += posi;

	}

	return movement;

}

struct pos* moveBishop(struct pos firstPos) {

	int posi = 8 - firstPos.horizontal;
	int posj = (int) firstPos.vertical - 65;

	int count = 0;
	struct pos *positions = (struct pos*) calloc(
			movementNumberBishop(posi, posj) , sizeof(struct pos));

	int temp_i = 0;
	int temp_j = 0;

	//To the left top corner
	temp_i = posi - 1;
	temp_j = posj - 1;

	while (temp_i >= 0 && temp_j >= 0) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i--;
		temp_j--;
	}

	//To the right bottom corner
	temp_i = posi + 1;
	temp_j = posj + 1;

	while (temp_i <= 7 && temp_j <= 7) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i++;
		temp_j++;
	}

	//To the left bottom corner
	temp_i = posi + 1;
	temp_j = posj - 1;

	while (temp_i <= 7 && temp_j >= 0) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i++;
		temp_j--;
	}

	//To the top right corner.
	temp_i = posi - 1;
	temp_j = posj + 1;

	while (temp_i >= 0 && temp_j <= 7) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i--;
		temp_j++;
	}

	return positions;

}

int movementNumberBishop(int posi, int posj) {
	int movement = 0;

	if (posi >= posj) {

		movement += posj;
		movement += 7 - posi;

	} else {

		movement += posi;
		movement += 7 - posj;

	}

	if ((posi + posj) >= 7) {

		movement += 7 - posi;
		movement += 7 - posj;

	} else {

		movement += posj;
		movement += posi;

	}

	return movement;
}

struct pos* moveKnight(struct pos firstPos) {

	int posi = 8 - firstPos.horizontal;
	int posj = (int) firstPos.vertical - 65;

	int count = 0;
	struct pos *positions = (struct pos*) calloc(
			movementNumberKnight(posi, posj) , sizeof(struct pos));

	int temp_i = posi - 2;
	int temp_j = posj - 1;

	for (int i = 0; i < 4; i++) {

		if (i == 2) {
			temp_j = posj - 1;
			temp_i += 4;
		}

		if (temp_i >= 0 && temp_i <= 7 && temp_j >= 0 && temp_j <= 7) {

			struct pos position;
			position.horizontal = 8 - temp_i;
			position.vertical = (char) (temp_j + 65);
			positions[count] = position;
			count++;

		}

		temp_j += 2;
	}

	temp_i = posi - 1;
	temp_j = posj - 2;

	for (int i = 0; i < 4; i++) {

		if (i == 2) {
			temp_i = posi - 1;
			temp_j += 4;
		}

		if (temp_i >= 0 && temp_i <= 7 && temp_j >= 0 && temp_j <= 7) {

			struct pos position;
			position.horizontal = 8 - temp_i;
			position.vertical = (char) (temp_j + 65);
			positions[count] = position;
			count++;

		}

		temp_i += 2;
	}

	return positions;

}

int movementNumberKnight(int posi, int posj) {
	int movement = 0;

	if (((posi == 0 || posi == 7) && (posj == 0 || posj == 7))) {
		movement = 2;
	} else if ((posi == 0 && (posj == 1 || posj == 7))
			|| ((posi == 1 || posi == 6) && (posj == 0 || posj == 7))
			|| (posi == 7 && (posj == 1 || posj == 6))) {
		movement = 3;
	} else if (((posi == 0 || posi == 7) && (posj >= 2 && posj <= 5))
			|| (((posj == 0 || posj == 7) && (posi >= 2 && posi <= 5))
					|| ((posi == 6 || posi == 1) && (posj == 1 || posj == 6)))) {
		movement = 4;
	} else if (((posj == 1 || posj == 6) && (posi >= 2 && posi <= 5))
			|| ((posi == 1 || posi == 6) && (posj >= 2 && posj <= 5))) {
		movement = 6;
	} else {
		movement = 8;
	}

	return movement;
}

struct pos* moveRook(struct pos firstPos) {

	int posi = 8 - firstPos.horizontal;
	int posj = (int) firstPos.vertical - 65;

	int count = 0;
	struct pos *positions = (struct pos*) calloc(
			movementNumberRook(posi, posj) , sizeof(struct pos));

	int temp_i = 0;
	int temp_j = 0;

	//To the left
	temp_i = posi;
	temp_j = posj - 1;

	while (temp_j >= 0) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_j--;
	}

	//To the right
	temp_i = posi;
	temp_j = posj + 1;

	while (temp_j <= 7) {

		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_j++;
	}

	//To the Top
	temp_i = posi - 1;
	temp_j = posj;

	while (temp_i >= 0) {
		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i--;
	}

	//To the bottom
	temp_i = posi + 1;
	temp_j = posj;

	while (temp_i <= 7) {
		struct pos position;
		position.horizontal = 8 - temp_i;
		position.vertical = (char) (temp_j + 65);
		positions[count] = position;
		count++;

		temp_i++;
	}

	return positions;

}

int movementNumberRook(int posi, int posj) {
	return 14;
}

struct pos* movePawn(struct pos firstPos) {

	int posi = 8 - firstPos.horizontal;
	int posj = (int) firstPos.vertical - 65;

	int count = 0;
	struct pos *positions = (struct pos*) calloc(
			movementNumberPawn(posi, posj) , sizeof(struct pos));
	if (posi == 6) {
		for (int i = 0; i < 2; i++) {
			posi--;
			if ((posi >= 0 && posi <= 7) && (posj >= 0 && posj <= 7)) {
				struct pos position;
				position.horizontal = 8 - posi;
				position.vertical = (char) (posj + 65);
				positions[count] = position;
				count++;
			}
		}
	} else {
		posi--;
		if ((posi >= 0 && posi <= 7) && (posj >= 0 && posj <= 7)) {
			struct pos position;
			position.horizontal = 8 - posi;
			position.vertical = (char) (posj + 65);
			positions[count] = position;
			count++;
		}
	}
	return positions;
}

int movementNumberPawn(int posi, int posj) {
	int movement = 0;

	if (posi == 6) {
		movement = 2;
	} else if (posi == 0) {
		movement = 0;
	} else {
		movement = 1;
	}

	return movement;
}
