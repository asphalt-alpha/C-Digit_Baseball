#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


#define NUMMAX 3 // 7�ڸ� �� ���� �Է°���

int count_Candidate(int *save);  //ó�� �ĺ�Ű�� ���� ����
void input_Arr(int *arr, int start, int num);  //�ĺ�Ű�� �迭�� �Ҵ�
int Check_Input(int strike, int ball);  //��Ʈ����ũ,�� ī��Ʈ�� ����� �Է���� Ȯ�� 
int checking(int arr, int input[NUMMAX], int s_cnt, int b_cnt, int turn);  //�ĺ�Ű�� �Է�Ű ��
void change_Arr(int arr, int output[NUMMAX]);  //���ڸ� ������ n�ڸ��� �迭�濡 �Ҵ�
int change_digit(int input[NUMMAX]);  //������ �迭���� ���ڸ� �ϳ��� ���ڷ� ��ȯ


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
	input_Arr(NUM_candidate[0], start, len);

	//����
	int input[NUMMAX];  //������� ���ڰ� ����Ǵ� �迭
	int strike, ball;  //������� ī��Ʈ�� ����Ǵ� ����
	int count[2] = { 0 }; //���͸��� ��ģ �ĺ�Ű���� ������ ����
	count[0] = len;  //�ʱ⼳��
	int turn = 0;  //2���� �迭�� 0��, 1���� ��� �� �� �ֵ��� ����

	while (count[(turn + 1) % 2] != 1) {

		//������� �Է�
		printf("�����Ͻ� ���� %d �ڸ��� Strike, Ball ī��Ʈ�� ���ʴ�� �Է��ϼ���\n", NUMMAX);
		for (int i = 0; i < NUMMAX; i++)
		{
			scanf_s("%01d", &input[i]);
		}
		do {
			scanf_s("%d %d", &strike, &ball);
		} while (Check_Input(strike, ball));
		system("cls");

		//��
		count[(turn + 1) % 2] = 0;
		int j = 0;
		for (int i = 0; i < count[turn]; i++)
		{
			if (checking(NUM_candidate[turn][i], input, strike, ball, turn) == 0) {
				NUM_candidate[(turn + 1) % 2][j++] = NUM_candidate[turn][i];
				count[(turn + 1) % 2]++;
			}
		}

		for (int i = 0; i < count[(turn + 1) % 2]; i++) {
			printf("%03d\n", NUM_candidate[(turn + 1) % 2][i]);
		}

		turn = (turn + 1) % 2;
	}

	//�޸� �����Ҵ� ����
	for (int i = 0; i < 2; i++) {
		free(NUM_candidate[i]);
	}
	free(NUM_candidate);
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

void input_Arr(int *arr, int start, int len)
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

int checking(int arr, int input[NUMMAX], int s_cnt, int b_cnt, int turn)
{
	int digit[NUMMAX];
	int i = 0;
	change_Arr(arr, digit);

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

void change_Arr(int arr, int output[NUMMAX])
{
	int num = arr;
	for (int i = NUMMAX - 1; i >= 0; i--) {
		output[i] = num % 10;
		num /= 10;
	}
}

int change_digit(int input[NUMMAX])
{
	int num = 0;
	int j = 1;
	for (int i = NUMMAX - 1; i >= 0; i--) {
		num += input[i] * j;
		j *= 10;
	}
	return num;
}

int Check_Input(int strike, int ball)
{
	if (strike + ball <= NUMMAX) {
		return 0;
	}
	else printf("�ٽ� �Է��� �ּ���.\n"); return 1;
}