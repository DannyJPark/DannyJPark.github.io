#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <winsock2.h>

#pragma comment(lib, "wsock32.lib")

#define BUF_SIZE 30
#define MAX_CLNT 256

unsigned WINAPI HandleClient(void* arg);//������ �Լ�
void SendMsg(char* msg, int len);//�޽��� ������ �Լ�
void ErrorHandling(char* msg);

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];//Ŭ���̾�Ʈ ���� ������ �迭
SOCKET serverSock, clientSock;
SOCKADDR_IN serverAddr, clientAddr;
HANDLE hMutex;//���ؽ�
HANDLE hThread;
WSADATA wsaData;
int clientAddrSize;

int main() {
	//	int main(int argc, char* argv[]) {

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //������ ������ ����ϰڴٴ� ����� �ü���� ����
		ErrorHandling("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);//�ϳ��� ���ؽ��� �����Ѵ�.
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //�ϳ��� ������ �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(1000);

	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //������ ������ ��ġ�Ѵ�.
		ErrorHandling("bind() error");
	if (listen(serverSock, 5) == SOCKET_ERROR)//������ �غ���¿� �д�.
		ErrorHandling("listen() error");

	printf("Waiting Client Connect....\n");

	while (1) {
		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
		WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
		clientSocks[clientCount++] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
		ReleaseMutex(hMutex);//���ؽ� ����
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
		//sprintf(addrs[clientCount], "%s", inet_ntoa(clientAddr.sin_addr));
		printf("Connected Client IP  : %s\n", inet_ntoa(clientAddr.sin_addr));
	}
	closesocket(serverSock);//������ ������ ����.
	WSACleanup();//������ ������ �����ϰڴٴ� ����� �ü���� ����
	return 0;
}

unsigned WINAPI HandleClient(void* arg) {

	SOCKET clientSock = *((SOCKET*)arg); //�Ű������ι��� Ŭ���̾�Ʈ ������ ����

	int strLen = 0, i;
	char msg[BUF_SIZE];
	char msg1[BUF_SIZE];

	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) { //Ŭ���̾�Ʈ�κ��� �޽����� ���������� ��ٸ���.

		if (msg[0] == '[')
		{
			strcpy(msg1, "...");
			sprintf(msg1, "[%s]%s", inet_ntoa(clientAddr.sin_addr), msg);
			SendMsg(msg1, strlen(msg1));//SendMsg�� ���� �޽����� �����Ѵ�.
			printf("\n%s\n", msg1);
			//Sleep(100);
			strcpy(msg, "...");
		}

		else if (msg[0] != '.')
		{
			SendMsg(msg, strLen);
			printf("%s\n", msg);
			//Sleep(100);
			strcpy(msg, "...");
		}
	}

	//�� ���� �����Ѵٴ� ���� �ش� Ŭ���̾�Ʈ�� �����ٴ� ����� ���� �ش� Ŭ���̾�Ʈ�� �迭���� �����������
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i < clientCount; i++) {//�迭�� ������ŭ
		if (clientSock == clientSocks[i]) {//���� ���� clientSock���� �迭�� ���� ���ٸ�
			while (i++ < clientCount - 1)//Ŭ���̾�Ʈ ���� ��ŭ
				clientSocks[i] = clientSocks[i + 1];//������ �����.
			break;
		}
	}
	clientCount--;//Ŭ���̾�Ʈ ���� �ϳ� ����
	ReleaseMutex(hMutex);//���ؽ� ����
	closesocket(clientSock);//������ �����Ѵ�.
	return 0;
}

void SendMsg(char* msg, int len) {//�޽����� ��� Ŭ���̾�Ʈ���� ������.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i < clientCount; i++)//Ŭ���̾�Ʈ ������ŭ
		send(clientSocks[i], msg, len, 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
	ReleaseMutex(hMutex);//���ؽ� ����
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
