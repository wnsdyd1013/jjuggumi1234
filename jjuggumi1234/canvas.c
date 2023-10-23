#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;

	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}


// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void display_m(void) {
	draw();
	if (tick >= 4000 && tick <= 7000) {
		gotoxy(6, 1);
		printf("@");
		gotoxy(7, 1);
		printf("@");
		gotoxy(8, 1);
		printf("@");
		gotoxy(6, 1);
	}
	else if (tick >= 0 && tick < 4000) {
		gotoxy(6, 1);
		printf("#");
		gotoxy(7, 1);
		printf("#");
		gotoxy(8, 1);
		printf("#");
	}
	gotoxy(N_ROW + 4, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d \n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");
	}
}



void dialog(char message[]) { //Ż�� ���� ���̾�α�
	int ii = DIALOG_DURATION_SEC;
	if (ii > 1) {
		for (int i = 4; i > 0; i--) {
			gotoxy(5, 7);
			printf("***************************\n");
			gotoxy(6, 7);
			printf("* %d %s *\n", i, message);
			gotoxy(7, 7);
			printf("***************************\n");
			Sleep(1000);
			ii--;
		}
		gotoxy(5, 7);
		printf("                           \n");
		gotoxy(6, 7);
		printf("                           \n");
		gotoxy(7, 7);
		printf("                           \n");
	}
}

void dialog_m(char massage[]) {//Ż�� ���� ���̾�α�
	int ii = DIALOG_DURATION_SEC;
	if (ii > 1) {
		for (int i = 3; i > 0; i--) {
			gotoxy(4, 5);
			printf("*****************************\n");
			gotoxy(5, 5);
			printf("*                           *\n");
			gotoxy(6, 5);
			printf("                             \n");
			gotoxy(7, 5);
			printf("*                           *\n");
			gotoxy(8, 5);
			printf("*****************************\n");
			gotoxy(6, 8);
			printf("%d %s", i, massage);


			Sleep(1000);

			display_m();

			Sleep(1000);
			ii--;
		}
		gotoxy(4, 5);
		printf("                             \n");
		gotoxy(5, 5);
		printf("                             \n");
		gotoxy(6, 5);
		printf("                                  \n");
		gotoxy(7, 5);
		printf("                             \n");
		gotoxy(8, 5);
		printf("                             \n");

		//display_m();
	}
}


