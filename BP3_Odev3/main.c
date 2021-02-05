/*
 * main.c
 *
 *  Created on: 12 Ara 2020
 *      Author: X550V
 */
#include "conio.h"
#include <stdlib.h>
#include <stdio.h>
#include "chessLib.h"

int main(int argc, char **argv) {
	struct pos firstPos;
	firstPos.vertical = 'D';
	firstPos.horizontal = 4;
	char tas = 'S';
	printMove(tas, firstPos);


	puts("Press something to start... ");
	char c = 's';
	while (c != 'q') {
		printf("Tasi giriniz.\n-S V F A K P\n");
		scanf("%c", &tas);
		struct pos Pos;
		puts("Yatay harfi giriniz.");
		scanf(" %c", &Pos.vertical);

		puts("Dusey sayiyi giriniz.");
	    scanf("%hu",&Pos.horizontal);

		printMove(tas, Pos);

		printf("\nTasi giriniz veya cikmak icin q'ya basiniz.\n");

		c = getch();
	}
	return EXIT_SUCCESS;

}
