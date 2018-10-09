#pragma warning (disable:4996)

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define BLACK 0
#define BLUE 9
#define RED 12
#define YELLOW 14
#define WHITE 15

#define NUMMAX 3

struct Num_save {
	int num;
	int s;
	int b;
};

void setColor(unsigned short color);  //각 사용자의 UI를 위해 컬러 지정을 해주는 함수
int Check_Input(int Input);  //사용자가 입력한 숫자의 자리를 확인하는 함수
void Input_arr(int Input, int arr[NUMMAX]);  //입력한 숫자를 각각의 배열방에 넣는 함수
int set_com(int *arr, int len);  //컴퓨터의 숫자 지정
void input_candidate(int *arr, int start, int num);  //후보키를 배열에 할당
int count_Candidate(int *save);  //처음 후보키의 개수 산출
void end(int *arr);  //메모리 동적할당 해제와 종료대기
int Check_num(int input, int check[NUMMAX], int *s_cnt, int*b_cnt);  //call-by-reference 형식으로 입력값과 비교값을 넣으면 strike, ball 값 반환
void print_arr(struct Num_save **s, int attack, int turn);
int checking(int arr, int input[NUMMAX], int s_cnt, int b_cnt, int turn);  //후보키와 입력키 비교

int main() {
	//처음 후보키들이 나올수 있는 경우의 수 계산  -> len, start
	int len = 1;
	int start = count_Candidate(&len);

	//메모리 동적할당을 사용하여 후보키들을 넣을 2차원 배열 선언
	int **NUM_candidate;
	NUM_candidate = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i<2; i++) {
		NUM_candidate[i] = (int*)malloc(sizeof(int) * len);
	}

	//후보키들을 배열방에 할당
	input_candidate(NUM_candidate[0], start, len);

	//com의 숫자를 NUMMAX에 맞게 랜덤으로 지정
	int NUM_com = set_com(NUM_candidate[0], len);
	
	//사용자의 숫자 입력
	unsigned int NUM_player;
	printf("당신의 시작 숫자를 입력해 주세요.\n");
	do {
		scanf_s("%d", &NUM_player);
	} while (Check_Input(NUM_player));
	system("cls");

	//사용자의 숫자와 com의 숫자를 2차원 배열에 할당
	int Start_Num[2][NUMMAX];
	Input_arr(NUM_player, Start_Num[0]);
	Input_arr(NUM_com, Start_Num[1]);

	//게임 시작

	struct Num_save save[2][100];
	//int NUM_play[2][100]; //player와 com이 부른 숫자를 저장하는 배열 - 상단에 누가 어떤 숫자를 불렀는지 출력하기 위해 사용
	int Flag = 0;  //게임이 종료됬는지 파악하는 변수
	int turn = 0;
	int player_turn = 0;  //player가 공격하는지, com이 공격하는지 구별하는 변수
	//------------------------------------------
	int count[2] = { 0 }; //필터링을 거친 후보키들의 개수가 저장
	count[0] = len;  //초기설정
	int com_turn = 0;  //2차원 배열의 0행, 1행이 토글 될 수 있도록 선언

	do
	{
		//player와 com의 공격숫자를 지정
		int num;
		int s = 0, b = 0;
		if (player_turn == 0)
		{
			setColor(WHITE);
			printf("Player가 공격하세요\n");
			do
			{
				scanf("%d", &num);
			} while (Check_Input(num));
		}
		else {
			num = NUM_candidate[com_turn][0];  //가장 첫번째 방을 공격숫자로 선언하는것은 일종의 전략...
		}
		//system("cls");

		Flag = Check_num(num, Start_Num[!player_turn], &s, &b);

		save[player_turn][turn].num = num;
		save[player_turn][turn].s = s;
		save[player_turn][turn].b = b;


		if (player_turn != 0)
		{
			int arr[NUMMAX];
			Input_arr(num, arr);
			//비교
			count[!com_turn] = 0;
			int j = 0;
			for (int i = 0; i < count[com_turn]; i++)
			{
				if (checking(NUM_candidate[com_turn][i], arr, s, b, com_turn) == 0) {
					NUM_candidate[!com_turn][j++] = NUM_candidate[com_turn][i];
					count[!com_turn]++;
				}
			}
			for (int i = 0; i < turn + 1; i++)
			{
				setColor(BLUE);
				printf("%d %dS %dB\t", save[0][i].num, save[0][i].s, save[0][i].b);
				setColor(RED);
				printf("%d %dS %dB\t", save[1][i].num, save[1][i].s, save[1][i].b);
				printf("\n");
			}
			//print_arr(save, player_turn, turn);  //좆같은거ㅅㅂ
		}

		//공격 내역을 구조체 배열에 저장하여 상단에 출력 할 수 있도로 함
		
		//system("cls");

		//printf("%d%d%d\n", Start_Num[1][0], Start_Num[1][1], Start_Num[1][2]);

		//printf("\n\n\n%d %d\n", s, b);
		//printf("\n\n\n%d %d\n", s, b);
		if (player_turn == 1) { turn++; }
		player_turn = !player_turn;
	} while (Flag == 0);

	//printf("%d", NUM_com);
	
	//end(NUM_candidate);
	system("PAUSE");
	return 0;
}

void setColor(unsigned short color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int set_com(int * arr, int len)
{
	srand(time(NULL));  //랜덤한 숫자를 만들기 위해 seed를 초기화
	int num;
	int random = rand() % len;
	num = arr[random];
	return num;
}

void end(int * arr)
{
	for (int i = 0; i < 2; i++) {
		free(arr[i]);
	}
	free(arr);
}

int Check_num(int input, int check[NUMMAX], int * s_cnt, int * b_cnt)
{
	int num[NUMMAX];
	Input_arr(input, num);

	int s = 0, b = 0;
	for (int i = 0; i < NUMMAX; i++)
	{
		for (int j = 0; j < NUMMAX; j++)
		{
			if (num[i] == check[j])
			{
				if (i == j) s++;
				else b++;
				break;
			}
		}
	}
	*s_cnt = s;
	*b_cnt = b;

	if (s == NUMMAX)
	{
		return 1;
	}
	else
		return 0;
}

void print_arr(struct Num_save **s, int attack, int turn)
{
	for (int i = 0; i < turn + 1; i++)
	{	
		setColor(BLUE);
		printf("%d %dS %dB\t", s[0][i].num, s[0][i].s, s[0][i].b);		
		setColor(RED);
		printf("%d %dS %dB\t", s[1][i].num, s[1][i].s, s[1][i].b);
		printf("\n");
	}
}

int Check_Input(int Input)
{
	int Cnt = 0;
	while (Input != 0)
	{
		Input /= 10;
		Cnt++;
	}
	if (Cnt == NUMMAX) {
		return 0;
	}
	else if (Cnt < NUMMAX)
	{
		printf("%d자리 늘려 다시 입력해 주세요.\n", NUMMAX - Cnt);
		return 1;
	}
	else printf("%d자리 줄여 다시 입력해 주세요.\n", Cnt - NUMMAX); return 1;
}

void Input_arr(int Input, int arr[NUMMAX])
{
	for (int i = NUMMAX - 1; i >= 0; i--)
	{
		arr[i] = Input % 10;
		Input = Input / 10;
	}
}

void input_candidate(int *arr, int start, int len)
{
	int cnt = 0;
	int digit = start;
	int i = 0;
	int temp;
	while (cnt != len) {
		int digit_Cnt[10] = { 0 };
		int flag = 0;
		temp = digit;
		for (int j = 0; j < NUMMAX; j++) {
			digit_Cnt[temp % 10]++;
			temp /= 10;
		}
		for (int c = 0; c < 10; c++)
		{
			if (digit_Cnt[c] > 1)
			{
				flag = 1;
				break;
			}
		}
		if (flag != 1)
		{
			arr[i++] = digit;
			cnt++;
		}
		digit++;
	}
}

int count_Candidate(int *save)
{
	int a = 10;
	for (int i = 0; i < NUMMAX; i++)
	{
		*save *= a--;
	}
	a = 10;
	int NUM_small = 1;
	for (int i = 0; i < NUMMAX - 1; i++)
	{
		NUM_small *= a--;
	}
	*save -= NUM_small;

	int start = 1;
	for (int i = 0; i < NUMMAX - 1; i++)
	{
		start *= 10;
	}
	return start;
}

int checking(int arr, int input[NUMMAX], int s_cnt, int b_cnt, int turn)
{
	int digit[NUMMAX];
	int i = 0;
	Input_arr(arr, digit);

	int s = 0, b = 0;
	for (int i = 0; i < NUMMAX; i++)
	{
		for (int j = 0; j < NUMMAX; j++)
		{
			if (input[i] == digit[j])
			{
				if (i == j) s++;
				else b++;
				break;
			}
		}
	}

	if (s_cnt == s && b_cnt == b)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}