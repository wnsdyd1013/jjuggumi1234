#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3
#define DIR_ZERO	4

void safe(void);
void map_start(void);
void player_move(int player);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
int px_next[PLAYER_MAX], py_next[PLAYER_MAX];
int winner[20];
int younghi;
int random_player_move;
char out;
int is;

void mugung(int count) {
	//char massage[100] = "무 궁 화 꽃 이 피 었 습 니 다";
	if (count == 100) {
		gotoxy(N_ROW, 0);
		printf("무");
	}
	if (count == 500) {
		gotoxy(N_ROW, 0);
		printf("무 궁");
	}
	if (count == 900) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화");
	}
	if (count == 1400) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화 꽃");
	}
	if (count == 1900) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화 꽃 이");
	}
	if (count == 2100) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화 꽃 이 피");
	}
	if (count == 2300) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화 꽃 이 피 었");
	}
	if (count == 2500) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화 꽃 이 피 었 습");
	}
	if (count == 2800) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화 꽃 이 피 었 습 니");
	}
	if (count == 3000) {
		gotoxy(N_ROW, 0);
		printf("무 궁 화 꽃 이 피 었 습 니 다");
		younghi = 1;
	}
	if (count == 6000) {
		gotoxy(N_ROW, 0);
		printf("                                   ");

	}
}

void map_start() {
	map_init(15, 40);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			x = 3 + i;
			y = (N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 300);
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	tick = 0;
}

void player_move(int player, int dir) {
	// 랜덤 시드 초기화 (한 번만 호출)
	static bool srandInitialized = false;
	if (!srandInitialized) {
		srand((unsigned)time(NULL));
		srandInitialized = true;
	}

	int p = player;
	int nx = px[p];
	int ny = py[p];

	// 랜덤 방향 설정 (왼쪽 70% 확률)
	int ran = rand() % 10;
	if (ran >= 1 && ran <= 7) {
		ny -= 1; // 왼쪽 이동
	}
	else if (ran == 8) {
		nx -= 1; // 위로 이동
	}
	else if (ran == 9) {
		nx += 1; // 아래로 이동
	}

	// 이동 가능한지 확인 후 이동
	if (placable(nx, ny)) {
		safe(p, nx, ny);
	}
}


void safe(int player, int nx, int ny) {
	int p = player;
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;

	if ((nx == 5 && ny == 1) || (nx == 9 && ny == 1) || (nx >= 6 && nx <= 8 && ny == 2)) {
		winner[p] = 777;
		back_buf[px[p]][py[p]] = ' ';
	}
}

void mugunghwa(void) {
	int aa = 4;
	int dead_players = 0;
	int ii = 0;
	char out[100] = "player  dead!";
	int is = 6;
	int a;
	map_start();
	system("cls");
	display_m();
	while (1) {
		//player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			int prev_x = px[0];
			int prev_y = py[0];
			move_manual(key);
			if (younghi == 1) {
				int state = 0;
				for (int j = 0; j < n_player; j++) {
					if (px[j] == px[0] && py[j] < py[0]) {
						state = 1;
						break;
					}
				}
				if (player[0] == true) {
					if (px[0] != prev_x || py[0] != prev_y) {
						if (state == 0) {
							player[0] = false;
							if (player[0] == false) n_alive--; dead_players++;
							back_buf[px[0]][py[0]] = ' ';
							int length = strlen(out);
							for (int j = length; j >= is; j--) {
								out[j + 1] = out[j];
							}
							out[is] = ',';
							is++;
							for (int j = length; j >= is; j--) {
								out[j + 1] = out[j];
							}
							out[is] = '0';
							is++;
							gotoxy(N_ROW + 3, 0);
							printf("%d", dead_players);
						}

					}
				}
				if (px[0] != prev_x || py[0] != prev_y) {
					if (state == 0) {
						player[0] = false;
						back_buf[px[0]][py[0]] = ' ';
					}
				}
			}
		}

		// player 1 부터는 랜덤으로 움직임(4방향)
		for (int i = 1; i < n_player; i++) {

			if (tick % period[i] == 0) {//period[i] = randint(100, 500);
				if (younghi == 1) {
					random_player_move = randint(1, 10); // 1/10 확률로 player move
					if (random_player_move == 1) {
						if (winner[i] != 777) {
							player_move(i, -1);
						}
						if (player[i] == true) {
							if (px[i] != px_next[i] || py[i] != py_next[i]) {
								int length = strlen(out);
								for (int j = length; j >= is; j--) {
									out[j + 1] = out[j];
								}
								out[is] = ',';
								is++;
								for (int j = length; j >= is; j--) {
									out[j + 1] = out[j];
								}
								out[is] = i + '0';
								is++;
								dead_players++;
								gotoxy(N_ROW + 3, 0);
								printf("%d", dead_players);
								player[i] = false;
								back_buf[px[i]][py[i]] = ' ';
								n_alive--;
								ii++;
							}
						}
					}
					else {
						int state = false;
						for (int j = 0; j < n_player; j++) {
							if (px[j] == px[i] && py[j] < py[i]) {
								state = true;
								break; // 다른 플레이어가 앞에 가려서 탈락 안하도록 패스하기
							}
						}
						if (state == true) {
							continue;
						}
					}


					px_next[i] = px[i]; //저장된 x, y좌표 다시 바꿈
					py_next[i] = py[i];
				}
				else {
					player_move(i, -1);

				}
			}
		}
		if (tick == 6000) {
			younghi = 0;
			if (dead_players != 0) {
				dialog_m(out);
				dead_players = 0;
				for (int i = 0; i < 23; i++) {
					out[i] = ' ';
				}
				out[0] = 'p';
				out[1] = 'l';
				out[2] = 'a';
				out[3] = 'y';
				out[4] = 'e';
				out[5] = 'r';
				out[6] = ' ';
				out[7] = ' ';
				out[8] = 'd';
				out[9] = 'e';
				out[10] = 'a';
				out[11] = 'd';
				out[12] = '!';
				is = 6;
			}
		}
		if (tick >= 6010) {
			tick = 0;
		}
		mugung(tick);
		display_m();
		Sleep(10);
		tick += 10;
		gotoxy(N_ROW + 2, 0);
		printf("%d", tick);
		int a = 0;
		for (int i = 0; i < 10; i++) {
			if (player[i] == true && winner[i] == 777) {
				a++;
			}
		}
		if (a == n_alive) {
			break;
		}
		if (n_alive == 1) {
			break;
		}
	}
}

