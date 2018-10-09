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

void setColor(unsigned short color);  //�� ������� UI�� ���� �÷� ������ ���ִ� �Լ�
int Check_Input(int Input);  //����ڰ� �Է��� ������ �ڸ��� Ȯ���ϴ� �Լ�
void Input_arr(int Input, int arr[NUMMAX]);  //�Է��� ���ڸ� ������ �迭�濡 �ִ� �Լ�
int set_com(int *arr, int len);  //��ǻ���� ���� ����
void input_candidate(int *arr, int start, int num);  //�ĺ�Ű�� �迭�� �Ҵ�
int count_Candidate(int *save);  //ó�� �ĺ�Ű�� ���� ����
void end(int *arr);  //�޸� �����Ҵ� ������ ������
int Check_num(int input, int check[NUMMAX], int *s_cnt, int*b_cnt);  //call-by-reference �������� �Է°��� �񱳰��� ������ strike, ball �� ��ȯ
void print_arr(struct Num_save **s, int attack, int turn);
int checking(int arr, int input[NUMMAX], int s_cnt, int b_cnt, int turn);  //�ĺ�Ű�� �Է�Ű ��

int main() {
	//ó�� �ĺ�Ű���� ���ü� �ִ� ����� �� ���  -> len, start
	int len = 1;
	int start = count_Candidate(&len);

	//�޸� �����Ҵ��� ����Ͽ� �ĺ�Ű���� ���� 2���� �迭 ����
	int **NUM_candidate;
	NUM_candidate = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i<2; i++) {
		NUM_candidate[i] = (int*)malloc(sizeof(int) * len);
	}

	//�ĺ�Ű���� �迭�濡 �Ҵ�
	input_candidate(NUM_candidate[0], start, len);

	//com�� ���ڸ� NUMMAX�� �°� �������� ����
	int NUM_com = set_com(NUM_candidate[0], len);
	
	//������� ���� �Է�
	unsigned int NUM_player;
	printf("����� ���� ���ڸ� �Է��� �ּ���.\n");
	do {
		scanf_s("%d", &NUM_player);
	} while (Check_Input(NUM_player));
	system("cls");

	//������� ���ڿ� com�� ���ڸ� 2���� �迭�� �Ҵ�
	int Start_Num[2][NUMMAX];
	Input_arr(NUM_player, Start_Num[0]);
	Input_arr(NUM_com, Start_Num[1]);

	//���� ����

	struct Num_save save[2][100];
	//int NUM_play[2][100]; //player�� com�� �θ� ���ڸ� �����ϴ� �迭 - ��ܿ� ���� � ���ڸ� �ҷ����� ����ϱ� ���� ���
	int Flag = 0;  //������ �������� �ľ��ϴ� ����
	int turn = 0;
	int player_turn = 0;  //player�� �����ϴ���, com�� �����ϴ��� �����ϴ� ����
	//------------------------------------------
	int count[2] = { 0 }; //���͸��� ��ģ �ĺ�Ű���� ������ ����
	count[0] = len;  //�ʱ⼳��
	int com_turn = 0;  //2���� �迭�� 0��, 1���� ��� �� �� �ֵ��� ����

	do
	{
		//player�� com�� ���ݼ��ڸ� ����
		int num;
		int s = 0, b = 0;
		if (player_turn == 0)
		{
			setColor(WHITE);
			printf("Player�� �����ϼ���\n");
			do
			{
				scanf("%d", &num);
			} while (Check_Input(num));
		}
		else {
			num = NUM_candidate[com_turn][0];  //���� ù��° ���� ���ݼ��ڷ� �����ϴ°��� ������ ����...
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
			//��
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
			//print_arr(save, player_turn, turn);  //�������Ť���
		}

		//���� ������ ����ü �迭�� �����Ͽ� ��ܿ� ��� �� �� �ֵ��� ��
		
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
	srand(time(NULL));  //������ ���ڸ� ����� ���� seed�� �ʱ�ȭ
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
		printf("%d�ڸ� �÷� �ٽ� �Է��� �ּ���.\n", NUMMAX - Cnt);
		return 1;
	}
	else printf("%d�ڸ� �ٿ� �ٽ� �Է��� �ּ���.\n", Cnt - NUMMAX); return 1;
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