#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <Windows.h>
#include <process.h>
#include <mmsystem.h>
#include <time.h>

#pragma warning(disable:4996)
#pragma comment(lib, "wsock32.lib")

#define NAME_SIZE 30
#define sizeX 70
#define sizeY 45
#define delay1 100
#define delay2 200
#define delay3 500

typedef struct players
{
	int Save_number, Save_port;
	char Save_name[NAME_SIZE], Save_ip[NAME_SIZE];
	int Tanks, X, Y, Dir, Shot, Life, Energy, Score;
} Player;

typedef struct shots
{
	int shot_num, Shot[1010], X[1010], Y[1010], Dir[1010];
} Shot;

typedef struct stars
{
	int star, starX, starY;
} Star;

typedef struct blocks
{
	int blocks, X, Y, Dir, Length;
} Block;

int tanks = 1, key = 0, keyin = 0;
int game_start = 0, conn = 0;
int mouses = 0, m_buttons = 0, mouse_X = 0, mouse_Y = 0;
//int stars[10], starX[10], starY[10];
//int blocks[10], X[10], Y[10], Dir[10], Length[10];
int blockXY[80][50];

WSADATA wsaData;
SOCKET sock;
SOCKADDR_IN serverAddr;
HANDLE sendThread, recvThread;
HANDLE COUT, CIN1;

void Gotoxy(int x1, int y1);
void RemoveCurser();
void KeyboardController();
void TankMove(int tanks, int rX, int rY, int rDir, int rShot);
void DrawStar();
void RemoveScrollbar();
void DrawBorder();
void TextColor(int colors, int bcolors);
void Inits();
void Inputs();
void Connected();
int MouseInput(WORD* vkey, COORD* pos);
int IsMouseInput();
void CalcMouseDir();
void DrawBlocks();

unsigned WINAPI SendMsg(void* arg);//쓰레드 전송함수
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수

unsigned _stdcall Thread_Shot(void* arg);

void ErrorHandling(char* msg);

Player tank[5], sends, rcvs;
Shot shot[5];
Star star[10];
Block block[10];

int main() {

	system("cls");
	system("color f0");
	system("mode con cols=160 lines=45");

	Inits();
	Inputs();

	srand((unsigned)time(NULL));

	RemoveScrollbar();

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// 윈도우 소켓을 사용한다고 운영체제에 알림
		ErrorHandling("WSAStartup() error!");

	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(tank[tanks].Save_ip);
	serverAddr.sin_port = htons(1000);

	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//서버에 접속한다.
		ErrorHandling("connect() error");

	_beginthreadex(NULL, 0, Thread_Shot, 0, 0, NULL);

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//메시지 전송용 쓰레드가 실행된다.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//메시지 수신용 쓰레드가 실행된다.

	WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다./
	WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.
	WaitForSingleObject(Thread_Shot, INFINITE);
	//클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.

	printf("서버와의 접속이 종료되었습니다.\n");
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
	return 0;
}

unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
	SOCKET sock = *((SOCKET*)arg);///서버용 소켓을 전달한다.
	char message[NAME_SIZE];

	sprintf(message, "Connected..");
	send(sock, message, strlen(message), 0);

	DWORD mode;
	WORD keys;
	COORD pos;

	CIN1 = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);

	// 마우스 활성화
	GetConsoleMode(CIN1, &mode);
	SetConsoleMode(CIN1, mode | ENABLE_MOUSE_INPUT);

	while (1)
	{
		mouses = 0;
		keyin = 0;
		KeyboardController();

		strcpy(message, "...");

		if (keyin == 1) {
			if (key == 32) {
				//if ((key == 32) && game_start == 0) {
				//strcpy(msg, "...");
				Sleep(delay2);
				Gotoxy(20, 1);
				printf("                                                                                  ");

				sprintf(message, "[%d][%s][%d]", tank[tanks].Save_number, tank[tanks].Save_name, tank[tanks].Save_port);
				send(sock, message, strlen(message), 0);
				Sleep(delay2);

				if (tanks == 1) {
					Sleep(delay2);
					strcpy(message, "...");
					sprintf(message, "START!!");
					send(sock, message, strlen(message), 0);
					strcpy(message, "...");
					Sleep(delay2);
				}
				else {
					Sleep(delay2);
					strcpy(message, "...");
					Gotoxy(20, 1);
					printf(" 잠시만 기다리세요!! ");
					sprintf(message, "[%d][%s][%d]", tank[tanks].Save_number, tank[tanks].Save_name, tank[tanks].Save_port);
					send(sock, message, strlen(message), 0);
					strcpy(message, "...");
					Sleep(delay2);
				}
			}
			else if (game_start == 1) {
				strcpy(message, "...");
				//sprintf(message, "<%d><%s><%d><%d><%d><%d><%d><%d><%d>", 
				//	tanks, tank[tanks].X, tank[tanks].Y, tank[tanks].Dir, tank[tanks].Shot, tank[tanks].Life, tank[tanks].Energy, tank[tanks].Score);
				sprintf(message, "<%d><%d><%d><%d><%d>",
					tanks, sends.X, sends.Y, sends.Dir, sends.Shot);
				send(sock, message, strlen(message), 0);//message를 서버에게 전송한다.
				strcpy(message, "...");
				Sleep(delay1);
			}
		}

		if (IsMouseInput())
		{
			if (MouseInput(&keys, &pos) != 0)
			{
				MOUSE_EVENT;
				mouse_X = pos.X / 2;    // 마우스클릭값이 x,y변수에 저장되도록함
				mouse_Y = pos.Y;
				CalcMouseDir();
			}
		}

		if (mouses != 0) {

			if (game_start == 1) {
				sprintf(message, "<%d><%d><%d><%d><%d>",
					sends.Tanks, sends.X, sends.Y, sends.Dir, sends.Shot);
				send(sock, message, strlen(message), 0);
				strcpy(message, "...");
				Sleep(delay1);
			}
		}

		if (conn == 1) {
			Sleep(delay2);
			strcpy(message, "...");
			sprintf(message, "[%d][%s][%d]", tank[tanks].Save_number, tank[tanks].Save_name, tank[tanks].Save_port);
			send(sock, message, strlen(message), 0);
			strcpy(message, "...");
			Sleep(delay3);
			if (tanks == 1) {
				//Sleep(delay2);
				strcpy(message, "...");
				for (int i = 0; i < 10; i++) {
					sprintf(message, "(%d)(%d)(%d)(%d)(%d)(%d)", tanks, i, block[i].X, block[i].Y, block[i].Dir, block[i].Length);//message에 메시지를 전달한다.
					send(sock, message, strlen(message), 0);//
					Sleep(delay2);
					strcpy(message, "...");
				}
				Sleep(delay3);
				strcpy(message, "...");
				for (int i = 0; i < 10; i++) {
					sprintf(message, "{%d}{%d}{%d}{%d}", i, star[i].star, star[i].starX, star[i].starY);//message에 메시지를 전달한다.
					send(sock, message, strlen(message), 0);//
					Sleep(delay2);
					strcpy(message, "...");
				}
			}
			conn = 0;
		}
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {
	int nn = 0;

	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char message[NAME_SIZE];
	char temp[NAME_SIZE];
	char temp1[NAME_SIZE], temp2[NAME_SIZE], temp3[NAME_SIZE], temp4[NAME_SIZE], temp5[NAME_SIZE];
	int temp_num = 0;
	char tempMsg[20][NAME_SIZE];
	char* pt1;
	char* deli1 = "[] ";
	char* deli2 = "<> ";
	char* deli3 = "() ";
	char* deli4 = "{}";
	int ii = 0, j = 0;
	int strLen;
	while (1) {//반복
		strLen = recv(sock, message, NAME_SIZE - 1, 0);//서버로부터 메시지를 수신한다.
		if (strLen == -1) return -1;

		message[strLen] = '\0';//문자열의 끝을 알리기 위해 설정

		if (strcmp(message, "Connected..") == 0)
		{
			conn = 1;
			strcpy(message, "...");

		}
		else if (strcmp(message, "START!!") == 0)
		{
			game_start = 1;
			Gotoxy(20, 1);
			printf("게 임 시 작 !!!             ");
			Sleep(delay3);
			Gotoxy(20, 1);
			printf("                         ");
		}

		else if (message[0] == '[')
		{
			ii = 0;
			strcpy(temp, message);
			pt1 = strtok(temp, deli1);
			while (pt1) {
				strcpy(tempMsg[ii], pt1);
				pt1 = strtok(NULL, deli1);
				ii++;
			}

			for (int i = 0; i < ii; i++) {

				if ((i % 5) == 1) {
					nn = atoi(tempMsg[i]);
					tank[nn].Save_number = nn;
					strcpy(tank[nn].Save_ip, tempMsg[i - 1]);
					strcpy(tank[nn].Save_name, tempMsg[i + 1]);
				}
			}
			strcpy(message, "...");

			Connected();
		}

		else if (message[0] == '<') {
			//Sleep(delay1);
			strcpy(temp, message);
			pt1 = strtok(temp, deli2);
			strcpy(temp, pt1);
			rcvs.Tanks = atoi(temp);

			pt1 = strtok(NULL, deli2);
			strcpy(temp, pt1);
			rcvs.X = atoi(temp);

			pt1 = strtok(NULL, deli2);
			strcpy(temp, pt1);
			rcvs.Y = atoi(temp);

			pt1 = strtok(NULL, deli2);
			strcpy(temp, pt1);
			rcvs.Dir = atoi(temp);

			pt1 = strtok(NULL, deli2);
			strcpy(temp, pt1);
			rcvs.Shot = atoi(temp);

			TankMove(rcvs.Tanks, rcvs.X, rcvs.Y, rcvs.Dir, rcvs.Shot);
			strcpy(message, "...");

			for (int i = 1; i <= 4; i++)
				TankMove(i, tank[i].X, tank[i].Y, tank[i].Dir, tank[i].Shot);

			//Sleep(delay1);
		}

		else if (message[0] == '(') {

			strcpy(temp, message);
			pt1 = strtok(temp, deli3);
			pt1 = strtok(NULL, deli3);
			strcpy(temp1, pt1);
			temp_num = atoi(temp1);

			pt1 = strtok(NULL, deli3);
			strcpy(temp2, pt1);
			block[temp_num].X = atoi(temp2);

			pt1 = strtok(NULL, deli3);
			strcpy(temp3, pt1);
			block[temp_num].Y = atoi(temp3);

			pt1 = strtok(NULL, deli3);
			strcpy(temp4, pt1);
			block[temp_num].Dir = atoi(temp4);

			pt1 = strtok(NULL, deli3);
			strcpy(temp5, pt1);
			block[temp_num].Length = atoi(temp5);

			strcpy(message, "...");

			if (temp_num == 9) {
				DrawBlocks();
			}

		}
		else if (message[0] == '{') {

			strcpy(temp, message);
			pt1 = strtok(temp, deli4);
			//pt1 = strtok(NULL, deli4);
			strcpy(temp1, pt1);
			temp_num = atoi(temp1);

			pt1 = strtok(NULL, deli4);
			strcpy(temp2, pt1);
			star[temp_num].star = atoi(temp2);

			pt1 = strtok(NULL, deli4);
			strcpy(temp3, pt1);
			star[temp_num].starX = atoi(temp3);

			pt1 = strtok(NULL, deli4);
			strcpy(temp4, pt1);
			star[temp_num].starY = atoi(temp4);

			strcpy(message, "...");

			if (temp_num == 9) {
				DrawStar();
			}
		}

		else {
		}
	}
	return 0;
}



void CalcMouseDir() {
	mouses = 0;

	if ((mouse_X >= tank[tanks].X - 5) && (mouse_X <= tank[tanks].X + 5))
	{
		if (mouse_Y <= tank[tanks].Y) {
			sends.Dir = 2;
			mouses = 1;
		}
		else if (mouse_Y >= tank[tanks].Y) {
			sends.Dir = 4;
			mouses = 1;
		}
	}
	else {
		if (mouse_X >= tank[tanks].X) {
			sends.Dir = 1;
			mouses = 1;
		}
		else if (mouse_X <= tank[tanks].X) {
			sends.Dir = 3;
			mouses = 1;
		}
	}

	if (mouses == 1) {
		Sleep(delay2);

		sends.Tanks = tanks;
		sends.X = tank[tanks].X;
		sends.Y = tank[tanks].Y;

		if (m_buttons == 1) {
			sends.Shot = 1;
			Sleep(delay2);
		}
		else if (m_buttons == 2) {
			sends.Shot = 2;
			Sleep(delay3);
		}
	}

}

void KeyboardController()
{
	//int key;
	key = 0;
	keyin = 0;
	if (_kbhit()) // 키보드 입력을 받았다면
	{
		keyin = 1;
		key = _getch();
		if (key == 224) // 받은키가 방향키면
		{
			key = _getch(); // 한번 더 받는다.

			if (key == 77) { //오른쪽 1


				if (sends.X >= sizeX - 3) {
					//sends.X = sends.X - 1;
					keyin = 0;
				}
				else if ((blockXY[sends.X + 1][sends.Y - 1] != 0) || (blockXY[sends.X + 1][sends.Y] != 0) || (blockXY[sends.X + 1][sends.Y + 1] != 0)) {
					//sends.X = sends.X - 1;
					keyin = 0;
				}
				else {
					sends.X = tank[tanks].X + 1;
					sends.Y = tank[tanks].Y;
					sends.Dir = 1;
					sends.Shot = 0;
				}
			}
			else if (key == 72) {   //위2


				if (sends.Y < 3) {
					//sends.Y = sends.Y + 1;
					keyin = 0;
				}
				else	if ((blockXY[sends.X - 1][sends.Y - 1] != 0) || (blockXY[sends.X][sends.Y - 1] != 0) || (blockXY[sends.X + 1][sends.Y - 1] != 0)) {
					//sends.Y = sends.Y + 1;
					keyin = 0;
				}
				else {
					sends.X = tank[tanks].X;
					sends.Y = tank[tanks].Y - 1;
					sends.Dir = 2;
					sends.Shot = 0;
				}
			}
			else if (key == 75) {                  //왼쪽 3


				if (sends.X < 3) {
					//sends.X = sends.X + 1;
					keyin = 0;
				}
				else	if ((blockXY[sends.X - 1][sends.Y - 1] != 0) || (blockXY[sends.X - 1][sends.Y] != 0) || (blockXY[sends.X - 1][sends.Y + 1] != 0)) {
					//sends.X = sends.X + 1;
					keyin = 0;
				}
				else {
					sends.X = tank[tanks].X - 1;
					sends.Y = tank[tanks].Y;
					sends.Dir = 3;
					sends.Shot = 0;
				}
			}
			else if (key == 80) { //아래 4


				if (sends.Y >= sizeY - 3) {
					//sends.Y = sends.Y - 1;
					keyin = 0;
				}
				else if ((blockXY[sends.X - 1][sends.Y + 1] != 0) || (blockXY[sends.X][sends.Y + 1] != 0) || (blockXY[sends.X + 1][sends.Y + 1] != 0)) {
					//sends.Y = sends.Y - 1;
					keyin = 0;
				}
				else {
					sends.X = tank[tanks].X;
					sends.Y = tank[tanks].Y + 1;
					sends.Dir = 4;
					sends.Shot = 0;
				}
			}

		}
		else // 받은 키가 방향키가 아니라면
		{
			if (key == 44) {
				sends.X = tank[tanks].X;
				sends.Y = tank[tanks].Y;
				sends.Dir = tank[tanks].Dir;
				sends.Shot = 1;
			}
			else if (key == 46) {
				sends.X = tank[tanks].X;
				sends.Y = tank[tanks].Y;
				sends.Dir = tank[tanks].Dir;
				sends.Shot = 2;
			}
			else if (key == 32) {
				//sprintf(msg, "%d", key);
			}
		}

		if (key == 75 || key == 77 || key == 80 || key == 72 || key == 44 || key == 46 || key == 32) tanks = tanks;
		else keyin = 0;

		Sleep(delay2);
	}
	return;// 키보드 입력을 받지 않았다면 나감
}




void TankMove(int tanks, int rX, int rY, int rDir, int rShot)
{
	if (tank[tanks].Save_number == 0) return;

	int i;
	if (tanks == 1) {
		i = 1;
		TextColor(3, 15);
	}
	else if (tanks == 2) {
		i = 2;
		TextColor(5, 15);
	}
	else if (tanks == 3) {
		i = 3;
		TextColor(7, 15);
	}
	else {
		i = 4;
		TextColor(1, 15);
	}

	Gotoxy(tank[i].X - 1, tank[i].Y - 1);
	printf("      ");
	Gotoxy(tank[i].X - 1, tank[i].Y);
	printf("      ");
	Gotoxy(tank[i].X - 1, tank[i].Y + 1);
	printf("      ");

	tank[tanks].X = rX;
	tank[tanks].Y = rY;
	tank[tanks].Dir = rDir;
	tank[tanks].Shot = rShot;

	if (rShot != 0) {
		if (rShot == 1) {
			shot[tanks].Shot[shot[tanks].shot_num] = 1;
			shot[tanks].Dir[shot[tanks].shot_num] = tank[tanks].Dir;
			shot[tanks].X[shot[tanks].shot_num] = tank[tanks].X;
			shot[tanks].Y[shot[tanks].shot_num] = tank[tanks].Y;
			shot[tanks].shot_num++;
			if (shot[tanks].shot_num >= 1000) shot[tanks].shot_num = 1;
		}
		else if (rShot == 2) {
			shot[tanks].Shot[shot[tanks].shot_num] = 2;
			shot[tanks].Dir[shot[tanks].shot_num] = tank[tanks].Dir;
			shot[tanks].X[shot[tanks].shot_num] = tank[tanks].X;
			shot[tanks].Y[shot[tanks].shot_num] = tank[tanks].Y;
			shot[tanks].shot_num++;
			if (shot[tanks].shot_num >= 1000) shot[tanks].shot_num = 2;
		}
	}
	
		if (tank[tanks].Dir == 1) {
			if (tank[i].X >= sizeX - 3) tank[i].X = tank[i].X - 1;
			if ((blockXY[tank[i].X + 1][tank[i].Y - 1] != 0) || (blockXY[tank[i].X + 1][tank[i].Y] != 0) || (blockXY[tank[i].X + 1][tank[i].Y + 1] != 0)) {
				tank[i].X = tank[i].X - 1;
			}
		}
		else if (tank[i].Dir == 2) {
			if (tank[i].Y < 3) tank[i].Y = tank[i].Y + 1;
			if ((blockXY[tank[i].X - 1][tank[i].Y - 1] != 0) || (blockXY[tank[i].X][tank[i].Y - 1] != 0) || (blockXY[tank[i].X + 1][tank[i].Y - 1] != 0)) {
				tank[i].Y = tank[i].Y + 1;
			}
		}
		else if (tank[tanks].Dir == 3) {
			if (tank[i].X < 3) tank[i].X = tank[i].X + 1;
			if ((blockXY[tank[i].X - 1][tank[i].Y - 1] != 0) || (blockXY[tank[i].X - 1][tank[i].Y] != 0) || (blockXY[tank[i].X - 1][tank[i].Y + 1] != 0)) {
				tank[i].X = tank[i].X + 1;
			}
		}

		else if (tank[i].Dir == 4) {
			if (tank[i].Y >= sizeY - 3) tank[i].Y = tank[i].Y - 1;
			if ((blockXY[tank[i].X - 1][tank[i].Y + 1] != 0) || (blockXY[tank[i].X][tank[i].Y + 1] != 0) || (blockXY[tank[i].X + 1][tank[i].Y + 1] != 0)) {
				tank[i].Y = tank[i].Y - 1;
			}
		}
	
	switch (tank[i].Dir)
	{
	case 1: // 왼쪽 키

		Gotoxy(tank[i].X - 1, tank[i].Y - 1);
		printf("▣〓");
		Gotoxy(tank[i].X - 1, tank[i].Y);
		printf("▣▣▶");
		Gotoxy(tank[i].X - 1, tank[i].Y + 1);
		printf("●●●");
		Gotoxy(tank[i].X - 1, tank[i].Y - 1);
		printf("#%d", i);

		break;

	case 2: // 오른쪽 키

		Gotoxy(tank[i].X - 1, tank[i].Y - 1); // ⊂⊃∪∩
		printf("  ▲●");
		Gotoxy(tank[i].X - 1, tank[i].Y);
		printf("∥▣●");
		Gotoxy(tank[i].X - 1, tank[i].Y + 1);
		printf("▣▣●");
		Gotoxy(tank[i].X - 1, tank[i].Y + 1);
		printf("#%d", i);

		break;

	case 3: // 아래 키

		Gotoxy(tank[i].X - 1, tank[i].Y - 1);
		printf("  〓▣");
		Gotoxy(tank[i].X - 1, tank[i].Y);
		printf("◀▣▣");
		Gotoxy(tank[i].X - 1, tank[i].Y + 1);
		printf("●●●");
		Gotoxy(tank[i].X + 1, tank[i].Y - 1);
		printf("#%d", i);

		break;

	case 4: // 위쪽키

		Gotoxy(tank[i].X - 1, tank[i].Y - 1);
		printf("▣▣●");
		Gotoxy(tank[i].X - 1, tank[i].Y);
		printf("∥▣●");
		Gotoxy(tank[i].X - 1, tank[i].Y + 1);
		printf("  ▼●");
		Gotoxy(tank[i].X - 1, tank[i].Y - 1);
		printf("#%d", i);

		break;
	}
}

void Inits() {

	for (int i = 0; i <= 4; i++) {

		tank[i].Save_number = 0;
		strcpy(tank[i].Save_name, "...");
		strcpy(tank[i].Save_ip, "...");
		tank[i].Save_port = 1000;;
		tank[i].Tanks = i;
		tank[i].X = 0;
		tank[i].Y = 0;
		tank[i].Dir = 0;
		tank[i].Shot = 0;
		tank[i].Life = 3;
		tank[i].Energy = 100;
		tank[i].Score = 0;

	}

	for (int j = 0; j < 4; j++) {
		shot[j].shot_num = 0;
		for (int i = 0; i < 1000; i++) {
			shot[j].Shot[i] = 0;
			shot[j].Dir[i] = 0;
			shot[j].X[i] = 0;
			shot[j].Y[i] = 0;
		}

	}

	for (int i = 0; i < 75; i++) {
		for (int j = 0; j < 45; j++) {
			blockXY[i][j] = 0;
		}
	}


	tank[1].X = 5;
	tank[1].Y = 5;
	tank[1].Dir = 1;
	tank[2].X = 65;
	tank[2].Y = 35;
	tank[2].Dir = 2;
	tank[3].X = 5;
	tank[3].Y = 35;
	tank[3].Dir = 3;
	tank[4].X = 65;
	tank[4].Y = 5;
	tank[4].Dir = 4;


	conn = 0;
}

void Inputs() {
	char num[NAME_SIZE];
	char names[NAME_SIZE];
	char ips[NAME_SIZE];
	char port[NAME_SIZE];
	int ports;

	Gotoxy(2, 2);
	printf("게임시작을 위해 아래 항목을 입력해주세요... ");
	Gotoxy(2, 4);
	printf("번 호 ex) 1 ~ 4 : ");
	gets(num);
	if (strcmp(num, "") == 0) strcpy(num, "1");
	tanks = atoi(num);

	Gotoxy(2, 7);
	printf("이 름 ex) aaa : ");
	gets(names);
	if (strcmp(names, "") == 0) strcpy(names, "aaa");

	Gotoxy(2, 11);
	printf("ex) 172.30.1.150");
	Gotoxy(2, 10);
	printf("서버주소 (ip) : ");
	gets(ips);
	if (strcmp(ips, "") == 0) strcpy(ips, "127.0.0.1");
	Gotoxy(2, 14);
	printf("포트 ex) 1000 : ");
	gets(port);
	if (strcmp(port, "") == 0) strcpy(port, "1000");
	ports = atoi(port);

	tank[tanks].Save_number = tanks;
	strcpy(tank[tanks].Save_name, names);
	strcpy(tank[tanks].Save_ip, ips);
	tank[tanks].Save_port = ports;

	system("cls");

	RemoveCurser();

	Gotoxy(20, 1);
	printf("모든 접속이 완료되고 게임을 시작하려면 스페이스바를 눌러주세요!!!");

	if (tanks == 1) {
		srand((unsigned)time(NULL));

		for (int i = 0; i < 10; i++) {
			block[i].X = rand() % 50 + 10;
			block[i].Y = rand() % 35 + 2;
			block[i].Dir = rand() % 2;
			block[i].Length = rand() % 5 + 3;
		}

		for (int i = 0; i < 10; i++) {
			star[i].star = rand() % 4 + 1;
			star[i].starX = rand() % 50 + 10;
			star[i].starY = rand() % 35 + 3;
			if (blockXY[star[i].starX][star[i].starY] != 0) i--;
		}

	}
}

void Connected() {


	DrawBorder();
	//DrawStar();

	for (int i = 1; i <= 4; i++) {
		Gotoxy(71, (i - 1) * 10 + 2);
		printf("<%d>", tank[i].Save_number);
		Gotoxy(74, (i - 1) * 10 + 2);
		printf("[%s]", tank[i].Save_name);
		Gotoxy(71, (i - 1) * 10 + 3);
		printf("IP:[%s]", tank[i].Save_ip);
		//Gotoxy(71, (i - 1) * 10 + 4);
		//printf("PORT:(%d)", save_port[i]);
		Gotoxy(71, (i - 1) * 10 + 4);
		if (tank[i].Save_number == 0) {
			printf("대기중..\n");
		}
		else {
			printf("접속됨!!!\n");
			TankMove(i, tank[i].X, tank[i].Y, tank[i].Dir, tank[i].Shot);
		}
		//}
	}


}

void DrawBorder() {
	TextColor(6, 15);

	for (int y = 1; y <= sizeY - 2; y++)
	{
		Gotoxy(sizeX, y);
		printf("▩");
		Gotoxy(78, y);
		printf("▩");
	}

	for (int x = sizeX; x < 78; x++)
	{
		Gotoxy(x, 1);
		printf("▩");

		Gotoxy(x, sizeY - 2);
		printf("▩");
	}

	for (int i = 1; i <= 4; i++) {
		TankMove(i, tank[i].X, tank[i].Y, tank[i].Dir, tank[i].Shot);
	}
}

void DrawBlocks() {

	TextColor(1, 15);
	for (int i = 0; i < 10; i++) {
		switch (block[i].Dir) {
		case 0:
			for (int j = 0; j < block[i].Length; j++) {
				blockXY[block[i].X + j][block[i].Y] = 1;
				Gotoxy(block[i].X + j, block[i].Y);
				printf("▦");
				//printf("%d", blockXY[X + j][Y]);
			}
			break;
		case 1:
			for (int j = 0; j < block[i].Length; j++) {
				blockXY[block[i].X][block[i].Y + j] = 1;
				Gotoxy(block[i].X, block[i].Y + j);
				printf("▦");
				//printf("%d", blockXY[X][Y+j]);
			}
			break;
		}
	}
}

void DrawStar() {
	int ss;
	TextColor(9, 15);
	for (int i = 0; i < 10; i++) {

		Gotoxy(star[i].starX, star[i].starY);
		ss = star[i].star;
		switch (ss)
		{
		case 1:
			TextColor(9, 15);
			printf("♣");
			break;
		case 2:
			TextColor(9, 15);
			printf("◆");
			break;
		case 3:
			TextColor(4, 15);
			printf("♠");
			break;
		case 4:
			TextColor(4, 15);
			printf("♥");
			break;
		}
	}

}

unsigned _stdcall Thread_Shot(void* arg)
{
	int i = 0, j = 0, dir1 = 0, shots = 0;
	while (1) {
		Sleep(delay1);
		TextColor(3, 15);
		//for (int i = 1; i <= 4; i++)
		//	TankMove(i, tank[i].X, tank[i].Y, tank[i].Dir, tank[i].Shot);

		for (j = 1; j <= 4; j++) {

			for (i = 1; i < 1000; i++)
			{
				shots = shot[j].Shot[i];
				if (shots == 1 || shots == 2) {
					dir1 = shot[j].Dir[i];

					switch (dir1)
					{
					case 1: // 오른쪽
						shot[j].X[i]++;
						switch (shots)
						{
						case 1:
							if (blockXY[shot[j].X[i] + 2][shot[j].Y[i] - 1] != 0) {
								Gotoxy(shot[j].X[i] + 1, shot[j].Y[i] - 1);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else if (shot[j].X[i] >= sizeX - 4) {
								Gotoxy(shot[j].X[i] + 1, shot[j].Y[i] - 1);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {

								Gotoxy(shot[j].X[i] + 1, shot[j].Y[i] - 1);
								printf("  ");
								Gotoxy(shot[j].X[i] + 2, shot[j].Y[i] - 1);
								printf("→");
							}
							break;

						case 2:
							if (blockXY[shot[j].X[i] + 2][shot[j].Y[i]] != 0) {
								Gotoxy(shot[j].X[i] + 1, shot[j].Y[i]);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else if (shot[j].X[i] >= sizeX - 4) {
								Gotoxy(shot[j].X[i] + 1, shot[j].Y[i]);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {

								Gotoxy(shot[j].X[i] + 1, shot[j].Y[i]);
								printf("  ");
								Gotoxy(shot[j].X[i] + 2, shot[j].Y[i]);
								printf("▷");
							}
							break;


						}
						//shot[j].X[i]++;
						break;

					case 2: //윗쪽

						shot[j].Y[i]--;


						switch (shots)
						{
						case 2:
							if (blockXY[shot[j].X[i]][shot[j].Y[i] - 3] != 0) {
								shot[j].Shot[i] = 0;
								Gotoxy(shot[j].X[i], shot[j].Y[i] - 2);
								printf("  ");
								//redraw_block = 1;
							}
							else if (shot[j].Y[i] <= 5) {
								Gotoxy(shot[j].X[i], shot[j].Y[i] - 3);
								printf("  ");
								Gotoxy(shot[j].X[i], shot[j].Y[i] - 2);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {
								Gotoxy(shot[j].X[i], shot[j].Y[i] - 2);
								printf("  ");
								Gotoxy(shot[j].X[i], shot[j].Y[i] - 3);
								printf("△");
							}
							break;
						case 1:
							if (blockXY[shot[j].X[i] - 1][shot[j].Y[i] - 3] != 0) {
								shot[j].Shot[i] = 0;
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] - 2);
								printf("  ");
								//redraw_block = 1;
							}
							else if (shot[j].Y[i] <= 5) {
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] - 3);
								printf("  ");
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] - 2);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] - 2);
								printf("  ");
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] - 3);
								printf("↑");
							}
							break;

						}

						break;

					case 3: //왼쪽

						shot[j].X[i]--;

						switch (shots)
						{

						case 2:
							if (blockXY[shot[j].X[i] - 3][shot[j].Y[i]] == 1) {
								shot[j].Shot[i] = 0;
								Gotoxy(shot[j].X[i] - 2, shot[j].Y[i]);
								printf("  ");
								//redraw_block = 1;
							}
							else if (shot[j].X[i] <= 4) {
								Gotoxy(shot[j].X[i] - 2, shot[j].Y[i]);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {

								Gotoxy(shot[j].X[i] - 2, shot[j].Y[i]);
								printf("  ");
								Gotoxy(shot[j].X[i] - 3, shot[j].Y[i]);
								printf("◁");
							}
							break;
						case 1:
							if (blockXY[shot[j].X[i] - 3][shot[j].Y[i] - 1] == 1) {
								shot[j].Shot[i] = 0;
								Gotoxy(shot[j].X[i] - 2, shot[j].Y[i] - 1);
								printf("  ");
								//redraw_block = 1;
							}
							else if (shot[j].X[i] <= 4) {
								Gotoxy(shot[j].X[i] - 2, shot[j].Y[i] - 1);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {
								Gotoxy(shot[j].X[i] - 2, shot[j].Y[i] - 1);
								printf("  ");
								Gotoxy(shot[j].X[i] - 3, shot[j].Y[i] - 1);
								printf("←");
							}
							break;

						}

						break;

					case 4: //아래쪽

						shot[j].Y[i]++;



						switch (shots)
						{
						case 2:
							if (blockXY[shot[j].X[i]][shot[j].Y[i] + 2] == 1) {
								shot[j].Shot[i] = 0;
								Gotoxy(shot[j].X[i], shot[j].Y[i] + 1);
								printf("  ");
								//redraw_block = 1;
							}
							else if (shot[j].Y[i] >= sizeY - 4) {
								Gotoxy(shot[j].X[i], shot[j].Y[i] + 1);
								printf("  ");
								Gotoxy(shot[j].X[i], shot[j].Y[i] + 2);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {
								Gotoxy(shot[j].X[i], shot[j].Y[i] + 1);
								printf("  ");
								Gotoxy(shot[j].X[i], shot[j].Y[i] + 2);
								printf("▽");
							}
							break;
						case 1:
							if (blockXY[shot[j].X[i] - 1][shot[j].Y[i] + 2] == 1) {
								shot[j].Shot[i] = 0;
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] + 1);
								printf("  ");
								//redraw_block = 1;
							}
							else if (shot[j].Y[i] >= sizeY - 4) {
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] + 1);
								printf("  ");
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] + 2);
								printf("  ");
								shot[j].Shot[i] = 0;
							}
							else {
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] + 1);
								printf("  ");
								Gotoxy(shot[j].X[i] - 1, shot[j].Y[i] + 2);
								printf("↓");
							}
							break;

						}

						break;
					}
				}
			}
		}
	}
}


void RemoveScrollbar() // 콘솔창의 스크롤바를 삭제합니다.
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
	 info.srWindow.Right - info.srWindow.Left + 1,
	 info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void Gotoxy(int x1, int y1) // 좌표로 커서를 이동합니다.
{
	COORD pos = { x1 * 2, y1 }; // 좌표값을 넣습니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCurser() // 커서를 표시하지 않습니다.
{
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void TextColor(int colors, int bcolors) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors | bcolors << 4);
}
/*
void gotoXY(int x2, int y2) // 좌표로 커서를 이동합니다.
{
	COORD pos = { x2 * 2, y2 }; // 좌표값을 넣습니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
*/
void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int IsMouseInput()
{
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CIN1, &input_record, 1, &input_count);
	return input_count;
}

int MouseInput(WORD* vkey, COORD* pos)
{
	INPUT_RECORD input_record;
	DWORD input_count;

	ReadConsoleInput(CIN1, &input_record, 1, &input_count);
	m_buttons = 0;
	switch (input_record.EventType)
	{
	case MOUSE_EVENT:
		if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			GetConsoleScreenBufferInfo(COUT, &csbi);
			*pos = input_record.Event.MouseEvent.dwMousePosition;

			m_buttons = 1;

			return MOUSE_EVENT;
		}

		else if (pos && (input_record.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED))
		{ // 우측 버튼이 클릭되었을 경우
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			GetConsoleScreenBufferInfo(COUT, &csbi);

			*pos = input_record.Event.MouseEvent.dwMousePosition;

			m_buttons = 2;
			return MOUSE_EVENT;
			//break;
		}
		break;
	}
	return 0;
}