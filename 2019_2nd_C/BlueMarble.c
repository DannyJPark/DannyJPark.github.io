
#include <stdio.h>

#include <windows.h>

#include <time.h>

#include <stdlib.h>

#pragma warning(disable : 4996)

 

void gotoxy(int x, int y);

void display(void);

void cpu_move(int *x, int *y, int dice);

void user_move(int *x, int *y, int dice);

 

int main() 

 

{

	   

	int x_cpu=1,y_cpu=23;  //컴퓨터의 좌표

	int x_user=3, y_user=23;   //사람의 좌표

	int cpu_dice, user_dice;   //주사위 값

	srand((unsigned)time(NULL));

	cpu_dice = rand() % 6 + 1;

	user_dice = rand() % 6 + 1;

	

	

	display();

	gotoxy(x_cpu, y_cpu);

	printf("c");

	gotoxy(x_user, y_user);

	printf("p");

 

	getch();

 

	while (1) 

	{

			srand((unsigned)time(NULL));

			cpu_dice = rand() % 6 + 1;

			user_dice = rand() % 6 + 1;

			display();

			cpu_move(&x_cpu, &y_cpu, cpu_dice);

			user_move(&x_user, &y_user, user_dice);

 

			gotoxy(x_cpu, y_cpu);

			printf("c");

			gotoxy(x_user, y_user);

			printf("p");

 

			getch();

	}

	

 

 

 

	getch();

	return 0;

}

 

 

 

void gotoxy(int x, int y)

{

 

	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

 

 

}

 

void display(void) {

	system("cls");

 

	printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ \n");

	printf("|      |      |      |      |      |      |      |\n");

	printf("|      |      |      |      |      |      |      |\n");

	printf("|      |      |      |      |      |      |      |\n");

	printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ \n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf(" ㅡㅡㅡ                                    ㅡㅡㅡ \n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf(" ㅡㅡㅡ                                    ㅡㅡㅡ \n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf(" ㅡㅡㅡ                                    ㅡㅡㅡ \n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf("|      |                                  |      |\n");

	printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ \n");

	printf("|      |      |      |      |      |      |      |\n");

	printf("|      |      |      |      |      |      |      |\n");

	printf("|      |      |      |      |      |      |      |\n");

	printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ \n");

 

 

 

	//시작 좌표

	gotoxy(1, 21);

	printf("시작");

 

 

	gotoxy(1, 17);

	printf("한국");

 

	gotoxy(1, 13);

	printf("벨기에");

 

	gotoxy(1, 9);

	printf("황금키");

 

	gotoxy(1, 5);

	printf("미국");

 

 

	gotoxy(1, 1);

	printf("프랑스");

 

	//=======================

	gotoxy(43, 21);

	printf("우주선");

		

	gotoxy(43, 17);

	printf("중국");

 

	gotoxy(43, 13);

	printf("인도");

 

	gotoxy(43, 9);

	printf("베트남");

 

	gotoxy(43, 5);

	printf("영국");

 

	gotoxy(43, 1);

	printf("무인도");

 

 

 

	//==========================

	gotoxy(8, 1);

	printf("캐나다");

 

	gotoxy(15, 1);

	printf("황금키");

 

	gotoxy(22, 1);

	printf("남아공");

 

	gotoxy(29, 1);

	printf("브라질");

 

	gotoxy(36, 1);

	printf("칠레");

 

	//==========================

 

	gotoxy(8, 21);

	printf("독일");

 

	gotoxy(15, 21);

	printf("스위스");

 

	gotoxy(22, 21);

	printf("사우디");

 

	gotoxy(29, 21);

	printf("몽골");

 

	gotoxy(36, 21);

	printf("황금키");

	

	

}

 

 

void cpu_move(int *x, int *y, int dice) {

 

	//시작부분에서 주사위 던지기

	if (*x == 1 && *y == 23) {

		if (dice == 1) {

			*x = 1;

			*y = 19;

		}

		else if (dice == 2) {

			*x = 1;

			*y = 15;

		}

		else if (dice == 3) {

			*x = 1;

			*y = 11;

		}

		else if (dice == 4) {

			*x = 1;

			*y = 7;

		}

		else if (dice == 5) {

			*x = 1;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 8;

			*y = 3;

		}

 

	}

 

	//한국에서 주사위 던지기

	else if (*x == 1 && *y == 19) {

		if (dice == 1) {

			*x = 1;

			*y = 15;

		}

		else if (dice == 2) {

			*x = 1;

			*y = 11;

		}

		else if (dice == 3) {

			*x = 1;

			*y = 7;

		}

		else if (dice == 4) {

			*x = 1;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 8;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 15;

			*y = 3;

		}

 

	}

 

	//벨기에에서 주사위 던지기

	else if (*x == 1 && *y == 15) {

		if (dice == 1) {

			*x = 1;

			*y = 11;

		}

		else if (dice == 2) {

			*x = 1;

			*y = 7;

		}

		else if (dice == 3) {

			*x = 1;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 8;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 15;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 22;

			*y = 3;

		}

 

	}

 

	//황금키(1,11)에서 주사위 던지기

	else if (*x == 1 && *y == 11) {

		if (dice == 1) {

			*x = 1;

			*y = 7;

		}

		else if (dice == 2) {

			*x = 1;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 8;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 15;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 22;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 29;

			*y = 3;

		}

 

	}

 

	//미국에서 주사위 던지기

	else if (*x == 1 && *y == 7) {

		if (dice == 1) {

			*x = 1;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 8;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 15;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 22;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 29;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 36;

			*y = 3;

		}

 

	}

 

	//프랑스에서 주사위 던지기

	else if (*x == 1 && *y == 3) {

		if (dice == 1) {

			*x = 8;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 15;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 22;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 29;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 36;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 43;

			*y = 3;

		}

 

	}

 

	//캐나다에서 주사위 던지기

	else if (*x == 8 && *y == 3) {

		if (dice == 1) {

			*x = 15;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 22;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 29;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 36;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 43;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 43;

			*y = 7;

		}

 

	}

 

	//황금키(15.3)에서 주사위 던지기

	else if (*x == 15 && *y == 3) {

		if (dice == 1) {

			*x = 22;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 29;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 36;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 43;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 43;

			*y = 7;

		}

		else if (dice == 6) {

			*x = 43;

			*y = 11;

		}

 

	}

 

	//남아공에서 주사위 던지기

	else if (*x == 22 && *y == 3) {

		if (dice == 1) {

			*x = 29;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 36;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 43;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 43;

			*y = 7;

		}

		else if (dice == 5) {

			*x = 43;

			*y = 11;

		}

		else if (dice == 6) {

			*x = 43;

			*y = 15;

		}

 

	}

 

	//브라질에서 주사위 던지기

	else if (*x == 29 && *y == 3) {

		if (dice == 1) {

			*x = 36;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 43;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 43;

			*y = 7;

		}

		else if (dice == 4) {

			*x = 43;

			*y = 11;

		}

		else if (dice == 5) {

			*x = 43;

			*y = 15;

		}

		else if (dice == 6) {

			*x = 43;

			*y = 19;

		}

 

	}

 

	//칠레에서 주사위 던지기

	else if (*x == 36 && *y == 3) {

		if (dice == 1) {

			*x = 43;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 43;

			*y = 7;

		}

		else if (dice == 3) {

			*x = 43;

			*y = 11;

		}

		else if (dice == 4) {

			*x = 43;

			*y = 15;

		}

		else if (dice == 5) {

			*x = 43;

			*y = 19;

		}

		else if (dice == 6) {

			*x = 43;

			*y = 23;

		}

 

	}

 

	//무인도에서 주사위 던지기

	else if (*x == 43 && *y == 3) {

		if (dice == 1) {

			*x = 43;

			*y = 7;

		}

		else if (dice == 2) {

			*x = 43;

			*y = 11;

		}

		else if (dice == 3) {

			*x = 43;

			*y = 15;

		}

		else if (dice == 4) {

			*x = 43;

			*y = 19;

		}

		else if (dice == 5) {

			*x = 43;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 36;

			*y = 23;

		}

 

	}

 

	//영국에서 주사위 던지기

	else if (*x == 43 && *y == 7) {

		if (dice == 1) {

			*x = 43;

			*y = 11;

		}

		else if (dice == 2) {

			*x = 43;

			*y = 15;

		}

		else if (dice == 3) {

			*x = 43;

			*y = 19;

		}

		else if (dice == 4) {

			*x = 43;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 36;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 29;

			*y = 23;

		}

 

	}

 

	//베트남에서 주사위 던지기

	else if (*x == 43 && *y == 11) {

		if (dice == 1) {

			*x = 43;

			*y = 15;

		}

		else if (dice == 2) {

			*x = 43;

			*y = 19;

		}

		else if (dice == 3) {

			*x = 43;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 36;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 29;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 22;

			*y = 23;

		}

 

	}

 

	//인도에서 주사위 던지기

	else if (*x == 43 && *y == 15) {

		if (dice == 1) {

			*x = 43;

			*y = 19;

		}

		else if (dice == 2) {

			*x = 43;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 36;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 29;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 22;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 15;

			*y = 23;

		}

 

	}

 

	//중국에서 주사위 던지기

	else if (*x == 43 && *y == 19) {

		if (dice == 1) {

			*x = 43;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 36;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 29;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 22;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 15;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 8;

			*y = 23;

		}

 

	}

 

	//우주선에서 주사위 던지기

	else if (*x == 43 && *y == 23) {

		if (dice == 1) {

			*x = 36;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 29;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 22;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 15;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 8;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 1;

			*y = 23;

		}

 

	}

 

	//황금키(36.23)에서 주사위 던지기

	else if (*x == 36 && *y == 23) {

		if (dice == 1) {

			*x = 29;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 22;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 15;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 8;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 1;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 1;

			*y = 19;

		}

 

	}

 

	//몽골에서 주사위 던지기

	else if (*x == 29 && *y == 23) {

		if (dice == 1) {

			*x = 22;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 15;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 8;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 1;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 1;

			*y = 19;

		}

		else if (dice == 6) {

			*x = 1;

			*y = 15;

		}

 

	}

 

	//사우디에서 주사위 던지기

	else if (*x == 22 && *y == 23) {

		if (dice == 1) {

			*x = 15;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 8;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 1;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 1;

			*y = 19;

		}

		else if (dice == 5) {

			*x = 1;

			*y = 15;

		}

		else if (dice == 6) {

			*x = 1;

			*y = 11;

		}

 

	}

 

	//스위스에서 주사위 던지기

	else if (*x == 15 && *y == 23) {

		if (dice == 1) {

			*x = 8;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 1;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 1;

			*y = 19;

		}

		else if (dice == 4) {

			*x = 1;

			*y = 15;

		}

		else if (dice == 5) {

			*x = 1;

			*y = 11;

		}

		else if (dice == 6) {

			*x = 1;

			*y = 7;

		}

 

	}

 

	//독일에서 주사위 던지기

	else if (*x == 8 && *y == 23) {

		if (dice == 1) {

			*x = 1;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 1;

			*y = 19;

		}

		else if (dice == 3) {

			*x = 1;

			*y = 15;

		}

		else if (dice == 4) {

			*x = 1;

			*y = 11;

		}

		else if (dice == 5) {

			*x = 1;

			*y = 7;

		}

		else if (dice == 6) {

			*x = 1;

			*y = 3;

		}

 

	}

 

 

 

}

 

void user_move(int *x, int *y, int dice) {

 

	//시작부분에서 주사위 던지기

	if (*x == 3 && *y == 23) {

		if (dice == 1) {

			*x = 3;

			*y = 19;

		}

		else if (dice == 2) {

			*x = 3;

			*y = 15;

		}

		else if (dice == 3) {

			*x = 3;

			*y = 11;

		}

		else if (dice == 4) {

			*x = 3;

			*y = 7;

		}

		else if (dice == 5) {

			*x = 3;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 10;

			*y = 3;

		}

 

	}

 

	//한국에서 주사위 던지기

	else if (*x == 3 && *y == 19) {

		if (dice == 1) {

			*x = 3;

			*y = 15;

		}

		else if (dice == 2) {

			*x = 3;

			*y = 11;

		}

		else if (dice == 3) {

			*x = 3;

			*y = 7;

		}

		else if (dice == 4) {

			*x = 3;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 10;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 17;

			*y = 3;

		}

 

	}

 

	//벨기에에서 주사위 던지기

	else if (*x == 3 && *y == 15) {

		if (dice == 1) {

			*x = 3;

			*y = 11;

		}

		else if (dice == 2) {

			*x = 3;

			*y = 7;

		}

		else if (dice == 3) {

			*x = 3;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 10;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 17;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 24;

			*y = 3;

		}

 

	}

 

	//황금키(3,11)에서 주사위 던지기

	else if (*x == 3 && *y == 11) {

		if (dice == 1) {

			*x = 3;

			*y = 7;

		}

		else if (dice == 2) {

			*x = 3;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 10;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 17;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 24;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 31;

			*y = 3;

		}

 

	}

 

	//미국에서 주사위 던지기

	else if (*x == 3 && *y == 7) {

		if (dice == 1) {

			*x = 3;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 10;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 17;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 24;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 31;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 38;

			*y = 3;

		}

 

	}

 

	//프랑스에서 주사위 던지기

	else if (*x == 3 && *y == 3) {

		if (dice == 1) {

			*x = 10;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 17;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 24;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 31;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 38;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 45;

			*y = 3;

		}

 

	}

 

	//캐나다에서 주사위 던지기

	else if (*x == 10 && *y == 3) {

		if (dice == 1) {

			*x = 17;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 24;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 31;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 38;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 45;

			*y = 3;

		}

		else if (dice == 6) {

			*x = 45;

			*y = 7;

		}

 

	}

 

	//황금키(17.3)에서 주사위 던지기

	else if (*x == 17 && *y == 3) {

		if (dice == 1) {

			*x = 24;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 31;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 38;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 45;

			*y = 3;

		}

		else if (dice == 5) {

			*x = 45;

			*y = 7;

		}

		else if (dice == 6) {

			*x = 45;

			*y = 11;

		}

 

	}

 

	//남아공에서 주사위 던지기

	else if (*x == 24 && *y == 3) {

		if (dice == 1) {

			*x = 31;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 38;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 45;

			*y = 3;

		}

		else if (dice == 4) {

			*x = 45;

			*y = 7;

		}

		else if (dice == 5) {

			*x = 45;

			*y = 11;

		}

		else if (dice == 6) {

			*x = 45;

			*y = 15;

		}

 

	}

 

	//브라질에서 주사위 던지기

	else if (*x == 31 && *y == 3) {

		if (dice == 1) {

			*x = 38;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 45;

			*y = 3;

		}

		else if (dice == 3) {

			*x = 45;

			*y = 7;

		}

		else if (dice == 4) {

			*x = 45;

			*y = 11;

		}

		else if (dice == 5) {

			*x = 45;

			*y = 15;

		}

		else if (dice == 6) {

			*x = 45;

			*y = 19;

		}

 

	}

 

	//칠레에서 주사위 던지기

	else if (*x == 38 && *y == 3) {

		if (dice == 1) {

			*x = 45;

			*y = 3;

		}

		else if (dice == 2) {

			*x = 45;

			*y = 7;

		}

		else if (dice == 3) {

			*x = 45;

			*y = 11;

		}

		else if (dice == 4) {

			*x = 45;

			*y = 15;

		}

		else if (dice == 5) {

			*x = 45;

			*y = 19;

		}

		else if (dice == 6) {

			*x = 45;

			*y = 23;

		}

 

	}

 

	//무인도에서 주사위 던지기

	else if (*x == 45 && *y == 3) {

		if (dice == 1) {

			*x = 45;

			*y = 7;

		}

		else if (dice == 2) {

			*x = 45;

			*y = 11;

		}

		else if (dice == 3) {

			*x = 45;

			*y = 15;

		}

		else if (dice == 4) {

			*x = 45;

			*y = 19;

		}

		else if (dice == 5) {

			*x = 45;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 38;

			*y = 23;

		}

 

	}

 

	//영국에서 주사위 던지기

	else if (*x == 45 && *y == 7) {

		if (dice == 1) {

			*x = 45;

			*y = 11;

		}

		else if (dice == 2) {

			*x = 45;

			*y = 15;

		}

		else if (dice == 3) {

			*x = 45;

			*y = 19;

		}

		else if (dice == 4) {

			*x = 45;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 38;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 31;

			*y = 23;

		}

 

	}

 

	//베트남에서 주사위 던지기

	else if (*x == 45 && *y == 11) {

		if (dice == 1) {

			*x = 45;

			*y = 15;

		}

		else if (dice == 2) {

			*x = 45;

			*y = 19;

		}

		else if (dice == 3) {

			*x = 45;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 38;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 31;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 24;

			*y = 23;

		}

 

	}

 

	//인도에서 주사위 던지기

	else if (*x == 45 && *y == 15) {

		if (dice == 1) {

			*x = 45;

			*y = 19;

		}

		else if (dice == 2) {

			*x = 45;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 38;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 31;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 24;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 17;

			*y = 23;

		}

 

	}

 

	//중국에서 주사위 던지기

	else if (*x == 45 && *y == 19) {

		if (dice == 1) {

			*x = 45;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 38;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 31;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 24;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 17;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 10;

			*y = 23;

		}

 

	}

 

	//우주선에서 주사위 던지기

	else if (*x == 45 && *y == 23) {

		if (dice == 1) {

			*x = 38;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 31;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 24;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 17;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 10;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 3;

			*y = 23;

		}

 

	}

 

	//황금키(38.23)에서 주사위 던지기

	else if (*x == 38 && *y == 23) {

		if (dice == 1) {

			*x = 31;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 24;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 17;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 10;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 3;

			*y = 23;

		}

		else if (dice == 6) {

			*x = 3;

			*y = 19;

		}

 

	}

 

	//몽골에서 주사위 던지기

	else if (*x == 31 && *y == 23) {

		if (dice == 1) {

			*x = 24;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 17;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 10;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 3;

			*y = 23;

		}

		else if (dice == 5) {

			*x = 3;

			*y = 19;

		}

		else if (dice == 6) {

			*x = 3;

			*y = 15;

		}

 

	}

 

	//사우디에서 주사위 던지기

	else if (*x == 24 && *y == 23) {

		if (dice == 1) {

			*x = 17;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 10;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 3;

			*y = 23;

		}

		else if (dice == 4) {

			*x = 3;

			*y = 19;

		}

		else if (dice == 5) {

			*x = 3;

			*y = 15;

		}

		else if (dice == 6) {

			*x = 3;

			*y = 11;

		}

 

	}

 

	//스위스에서 주사위 던지기

	else if (*x == 17 && *y == 23) {

		if (dice == 1) {

			*x = 10;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 3;

			*y = 23;

		}

		else if (dice == 3) {

			*x = 3;

			*y = 19;

		}

		else if (dice == 4) {

			*x = 3;

			*y = 15;

		}

		else if (dice == 5) {

			*x = 3;

			*y = 11;

		}

		else if (dice == 6) {

			*x = 3;

			*y = 7;

		}

 

	}

 

	//독일에서 주사위 던지기

	else if (*x == 10 && *y == 23) {

		if (dice == 1) {

			*x = 3;

			*y = 23;

		}

		else if (dice == 2) {

			*x = 3;

			*y = 19;

		}

		else if (dice == 3) {

			*x = 3;

			*y = 15;

		}

		else if (dice == 4) {

			*x = 3;

			*y = 11;

		}

		else if (dice == 5) {

			*x = 3;

			*y = 7;

		}

		else if (dice == 6) {

			*x = 3;

			*y = 3;

		}

 

	}

 

 

 

}
