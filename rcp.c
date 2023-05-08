#include "common.h"

extern char word_begin[WORDMAX][WORD_SIZE];
extern char word_medium[WORDMAX][WORD_SIZE];
extern char word_high[WORDMAX][WORD_SIZE];

extern int restart; //����ڷκ��� ���ع��� ����� ���� ��
extern int level; //����ڰ� ������ ���̵�

int word_total_score_rcp; //���� ���� �� ����
int word_each_score_rcp; //�� �ܾ� ���� ���� ����

int start_time_rcp, end_time_rcp;
int i_word_rcp1; //���� �ε��� ��
int i_word_rcp2; //���� �ε��� ��
int i_word_rcp3; //�� �ε��� ��

int true_rcp = 0; //���� ��

int l_rcp_1;//���� ���ڿ� ����
int l_rcp_2;//���� ���ڿ� ����
int l_rcp_3;//�� ���ڿ� ����

int computer; //��ǻ�� ���� �ε��� ��
char overlap[WORDMAX] = { "|0" }; //�ߺ� ���ִ� �迭!!

int pt_rcp = 0;  // �Ͻ������� �ɸ� �ð�

int T_rcp;//�� �ܾ� �Է��ϴ� �� �ɸ� �ð�
int wn_rcp = 0; //��µ� �ܾ� ����

void wordgame_main_rcp() {

	srand(time(0));

	if (level == 1) {
		printword_rcp();
		scanword_rcp(word_begin);
	}
	else if (level == 2) {
		printword_rcp();
		scanword_rcp(word_medium);
	}
	else if (level == 3) {
		printword_rcp();
		scanword_rcp(word_high);
	}
	else if (level == 4) {
		ask_restart();
		if (restart == 1) {

		}
		else {
			ending_title(33, 14);
			Sleep(1000);
			exit(0);
		}
	}
}

void printword_rcp() {
	int check = WORDMAX;

	computer = rand() % 3;

	while (1) {
		i_word_rcp1 = rand() % WORDMAX;
		if (overlap[i_word_rcp1] != 1) {
			overlap[i_word_rcp1] = 1;
			break;
		}
	}

	while (1) {
		i_word_rcp2 = rand() % WORDMAX;
		if (overlap[i_word_rcp2] != 1) {
			overlap[i_word_rcp2] = 1;
			break;
		}
	}
	while (1) {
		i_word_rcp3 = rand() % WORDMAX;
		if (overlap[i_word_rcp3] != 1) {
			overlap[i_word_rcp3] = 1;
			break;
		}
	}

	gotoxy(35, 27);
	printf("                           ");

	gotoxy(17, 23);
	printf("                        ");
	gotoxy(35, 23);
	printf("                        ");
	gotoxy(55, 23);
	printf("               ");

	gotoxy(10, 6);
	printf("                                                    ");
	gotoxy(10, 7);
	printf("                                                    ");
	gotoxy(10, 8);
	printf("                                                    ");
	gotoxy(10, 9);
	printf("                                                    ");
	gotoxy(10, 10);
	printf("                                                    ");
	gotoxy(10, 11);
	printf("                                                    ");
	gotoxy(10, 12);
	printf("                                                    ");
	gotoxy(10, 13);
	printf("                                                    ");

	start_time_rcp = time(0);

	textcolor(10);
	gotoxy(38, 13);
	printf("VS");
	textcolor(15);

	rock_rcp(0, 0);
	scissors_rcp(0, 0);
	paper_rcp(0, 0);

	if (level == 1) {
		gotoxy(17, 23);
		l_rcp_1 = strlen(word_begin[i_word_rcp1]);
		printf("%s ", word_begin[i_word_rcp1]);
		gotoxy(35, 23);
		l_rcp_2 = strlen(word_begin[i_word_rcp2]);
		printf("%s ", word_begin[i_word_rcp2]);
		gotoxy(55, 23);
		l_rcp_3 = strlen(word_begin[i_word_rcp3]);
		printf("%s ", word_begin[i_word_rcp3]);
	}
	if (level == 2) {
		gotoxy(17, 23);
		l_rcp_1 = strlen(word_medium[i_word_rcp1]);
		printf("%s ", word_medium[i_word_rcp1]);
		gotoxy(35, 23);
		l_rcp_2 = strlen(word_medium[i_word_rcp2]);
		printf("%s ", word_medium[i_word_rcp2]);
		gotoxy(55, 23);
		l_rcp_3 = strlen(word_medium[i_word_rcp3]);
		printf("%s ", word_medium[i_word_rcp3]);
	}
	if (level == 3) {
		gotoxy(17, 23);
		l_rcp_1 = strlen(word_high[i_word_rcp1]);
		printf("%s ", word_high[i_word_rcp1]);
		gotoxy(35, 23);
		l_rcp_2 = strlen(word_high[i_word_rcp2]);
		printf("%s ", word_high[i_word_rcp2]);
		gotoxy(55, 23);
		l_rcp_3 = strlen(word_high[i_word_rcp3]);
		printf("%s ", word_high[i_word_rcp3]);
	}
}

void scanword_rcp(const char wordlevel[][WORD_SIZE]) {
	// �� ���Ӹ��� 30�� �ܾ� ���
	int j = 0;
	int result_rcp;
	int resume = 0, qe = 0;
	int word_num_rcp = 10; //���������� : 10��
	char  ch_rcp, word_input_rcp[WORD_SIZE]; //����� �Է� �� ���� ��, �迭

	while (1) {
		if (time(0) >= start_time_rcp) {    //�ܿ� �ð� ���
			CursorView(FALSE);
			gotoxy(6, 4);
			printf("���� �ð� : %d��  ", TIME_LIMIT_RCP - (time(0) - start_time_rcp - pt_rcp));
		}
		if (wn_rcp >= word_num_rcp) {
			gotoxy(6, 4);
			printf("                                  ");
			gotoxy(35, 13);
			printf("                                  ");

			gotoxy(17, 23);
			printf("                        ");
			gotoxy(35, 23);
			printf("                        ");
			gotoxy(55, 23);
			printf("              ");

			gotoxy(10, 6);
			printf("                                                    ");
			gotoxy(10, 7);
			printf("                                                    ");
			gotoxy(10, 8);
			printf("                                                    ");
			gotoxy(10, 9);
			printf("                                                    ");
			gotoxy(10, 10);
			printf("                                                    ");
			gotoxy(10, 11);
			printf("                                                    ");
			gotoxy(10, 12);
			printf("                                                    ");
			gotoxy(10, 13);
			printf("                                                    ");
			gotoxy(10, 14);
			printf("                                                    ");
			gotoxy(10, 15);
			printf("                                                    ");
			gotoxy(10, 16);
			printf("                                                    ");
			gotoxy(10, 17);
			printf("                                                                ");
			gotoxy(10, 18);
			printf("                                                                ");
			gotoxy(10, 19);
			printf("                                                                ");
			gotoxy(10, 20);
			printf("                                                                ");
			gotoxy(10, 21);
			printf("                                                    ");
			gotoxy(10, 22);
			printf("                                                    ");
			gotoxy(10, 23);
			printf("                                                    ");

			gotoxy(31, 10);
			printf("---�� �� �� ��---");
			gotoxy(32, 12);
			textcolor(14);
			printf("���� ����: %d��", word_total_score_rcp);
			textcolor(15);
			if (level < 3) {
				gotoxy(20, 16);
				printf("*�ƹ�Ű�� �����ø� ���������� �Ѿ�ϴ�*");
			}
			else if (level == 3) {
				gotoxy(30, 16);
				printf("*�ƹ�Ű�� �����ּ���*");
			}

			word_total_score_rcp = 0;
			wn_rcp = 0;
			for (int m = 0; m < WORDMAX; m++) {
				overlap[m] = 0;
			}

			_getch();

			gotoxy(31, 10);
			printf("                                  ");
			gotoxy(32, 12);
			printf("                                  ");
			gotoxy(20, 16);
			printf("                                           ");

			CursorView(TRUE);
			level++;
			if (level < 4) {
				game1_screen_sp(level);
				waiting();
			}
			wordgame_main_rcp();
		}
		if (time(0) == start_time_rcp + TIME_LIMIT_RCP + pt_rcp) {

			if (!strncmp(wordlevel[i_word_rcp1], word_input_rcp, l_rcp_1)) {
				if (j > l_rcp_1)
				{
					true_rcp = 3;
				}
				else {
					true_rcp = 0; //����� �Է°� ����
					scissors_rcp(27, -9);//���� �Լ� ���/gotoxy	
				}
			}
			else if (!strncmp(wordlevel[i_word_rcp2], word_input_rcp, l_rcp_2)) {
				if (j > l_rcp_2)
				{
					true_rcp = 3;
				}
				else {
					true_rcp = 1;// ����� �Է°� ����
					rock_rcp(13, -9);//���� �Լ� ���/gotoxy
				}
			}
			else if (!strncmp(wordlevel[i_word_rcp3], word_input_rcp, l_rcp_3)) {
				if (j > l_rcp_3)
				{
					true_rcp = 3;
				}
				else {
					true_rcp = 2; //����� �Է°� ��
					paper_rcp(-7, -8);//�� �Լ� ���/gotoxy
				}
			}
			else {
				true_rcp = 3; // �׳� ��Ÿ�� ���ó��
			}

			switch (computer)
			{
			case 0:
				scissors_rcp(8, -9);//���� �׸� ���/gotoxy
				break;
			case 1:
				rock_rcp(-8, -9);//���� �׸� ���/gotoxy
				break;
			case 2:
				paper_rcp(-32, -8);//�� �׸� ���(�Լ�)
				break;
			}
			wn_rcp++;
			result_rcp = decision(computer, true_rcp);

			wordscore_rcp(result_rcp);    //���� ���
			textcolor(15);

			Sleep(2000);
			gotoxy(36, 4);
			printf("          ");

			word_total_score_rcp += word_each_score_rcp;     //�ܾ���� ������ �ʱ�ȭ
			cal_word_rcp(T_rcp, word_input_rcp, wordlevel, word_num_rcp);

			j = 0;

			printword_rcp();
			gotoxy(35, 27);

			pt_rcp = 0;
		}
		if (_kbhit()) {
			gotoxy(35 + j, 27);
			ch_rcp = _getch();
			if ((ch_rcp >= 'a' && ch_rcp <= 'z') || (ch_rcp >= 'A' && ch_rcp <= 'Z')) {
				printf("%c", ch_rcp);
				word_input_rcp[j] = ch_rcp;
				j++;
			}
			if ((ch_rcp == 8) && (j != 0)) {
				printf("\b");
				j--;
				printf(" ");
				printf("\b");
			}
			if (ch_rcp == 27) {
				int pt_rcp_each = 0;
				pause(&pt_rcp_each, &resume, &qe, 32);
				pt_rcp += pt_rcp_each;
				if (resume == 1) {
					gotoxy(35, 27);
					continue;
				}
				if (qe == 1) {
					word_total_score_rcp = 0;
					wn_rcp = 0;
					pt_rcp = 0;
					CursorView(TRUE);
					break;
				}
			}
			if (ch_rcp == 13) {
				end_time_rcp = time(0);
				T_rcp = end_time_rcp - start_time_rcp - pt_rcp;
			}

		}
		if (j > WORD_SIZE) {
			j = 0;
			gotoxy(35, 27);
			printf("                    ");
			gotoxy(35, 27);

		}

	}
}

void wordscore_rcp(int n) {
	switch (n)
	{
	case 0: //���º�
		word_each_score_rcp = 6;
		gotoxy(36, 4);
		textcolor(11);
		printf("���º�");
		break;

	case 1: //�¸�
		word_each_score_rcp = 10;
		gotoxy(37, 4);
		textcolor(14);
		printf("�¸�");
		break;

	case 2://�й�
		word_each_score_rcp = 2;
		gotoxy(37, 4);
		textcolor(12);
		printf("�й�");
		break;

	case 3://���
		word_each_score_rcp = 0;
		gotoxy(37, 4);
		textcolor(13);
		printf("���");
		break;
	}
}


int decision(int ascomputer, int asuser)
{
	if (asuser == 3) {
		return 3; //���
	}
	else if (ascomputer == asuser) {
		return 0; //���º�
	}
	else if ((ascomputer == 0 && asuser == 1) || (ascomputer == 1 && asuser == 2) || (ascomputer == 2 && asuser == 0)) {
		return 1; //�̱�
	}
	else {
		return 2; //��
	}
}

void scissors_rcp(int a, int b) {
	gotoxy(10 + a, 15 + b);
	printf("       ��     ��");
	gotoxy(10 + a, 16 + b);
	printf("        ��   ��");
	gotoxy(10 + a, 17 + b);
	printf("         �� ��");
	gotoxy(10 + a, 18 + b);
	printf("       �����");
	gotoxy(10 + a, 19 + b);
	printf("      ������");
	gotoxy(10 + a, 20 + b);
	printf("       �����");
	gotoxy(10 + a, 21 + b);
	printf("         ���");
}
void rock_rcp(int a, int b) {
	gotoxy(26 + a, 17 + b);
	printf("         ����");
	gotoxy(26 + a, 18 + b);
	printf("       ������");
	gotoxy(26 + a, 19 + b);
	printf("      �������");
	gotoxy(26 + a, 20 + b);
	printf("       ������");
	gotoxy(26 + a, 21 + b);
	printf("         ���� ");
}
void paper_rcp(int a, int b) {
	gotoxy(47 + a, 14 + b);
	printf("          �� ");
	gotoxy(47 + a, 15 + b);
	printf("        ����");
	gotoxy(47 + a, 16 + b);
	printf("     �� ����");
	gotoxy(47 + a, 17 + b);
	printf("     �� ����   ��");
	gotoxy(47 + a, 18 + b);
	printf("     ������ ��");
	gotoxy(47 + a, 19 + b);
	printf("     �������");
	gotoxy(47 + a, 20 + b);
	printf("      ������");
	gotoxy(47 + a, 21 + b);
	printf("        ����");
}

void cal_word_rcp(int timespent, char* word_input, char answer[][WORD_SIZE], int num)
{
	int correct = 0;
	int error = 0;
	float speed, accuracy, processivity;
	int s;
	int len;
	int i_cal = 0;

	if (true_rcp == 0) {
		i_cal = i_word_rcp1;
	}
	else if (true_rcp == 1) {
		i_cal = i_word_rcp2;
	}
	else if (true_rcp == 2) {
		i_cal = i_word_rcp3;
	}
	len = strlen(answer[i_cal]);

	for (s = 0; s < len; s++) //��Ÿ�� ����:
	{
		if (word_input[s] != answer[i_cal][s])// ������Է� ������ ���ĺ��� ���� ���ĺ��� ���ؼ� ���� ������
		{
			error += 1;
		}
	}

	//��Ÿ�� �ƴ� ��Ÿ��
	correct = len - error;

	//Ÿ�ڼӵ� : (Ÿ�ڼ�/�ɸ��ð�)*60 = �д� Ÿ�ڼӵ�
	speed = (len / (float)(timespent)) * 60;

	//��Ȯ��= ��Ÿ��/���ڿ��� ���� *100
	accuracy = ((float)correct / strlen(answer[i_cal])) * 100;

	//���൵
	processivity = ((float)(wn_rcp) / num) * 100;

	if (time(0) == start_time_rcp + TIME_LIMIT_RCP + pt_rcp) {
		speed = 0;
	}

	if (true_rcp == 3) {
		error = 0;
		accuracy = 0;
	}

	//���� ��� �����
	gotoxy(79, 22);
	printf("                   ");
	gotoxy(79, 23);
	printf("                 ");
	gotoxy(79, 24);
	printf("                   ");
	gotoxy(79, 25);
	printf("                   ");
	gotoxy(79, 26);
	printf("                   ");
	gotoxy(79, 27);
	printf("                   ");

	//���
	if (timespent <= 0)//�ɸ��ð��� 0�̸�
	{
		gotoxy(79, 22);
		printf("Ÿ�ڼӵ�: too fast");
		gotoxy(79, 24);
		printf("��Ȯ�� : %.f (%%)", accuracy);
		gotoxy(79, 25);
		printf("��Ÿ��: %d (��)", error);
		gotoxy(79, 26);
		printf("���൵: %.1f (%%)", processivity);
		gotoxy(79, 28);
		printf("SCORE: %d ", word_total_score_rcp);
	}

	else {
		gotoxy(79, 22);
		printf("Ÿ�ڼӵ�: %.f (Ÿ)", speed);
		gotoxy(79, 24);
		printf("��Ȯ�� : %.f (%%)", accuracy);
		gotoxy(79, 25);
		printf("��Ÿ��: %d (��)", error);
		gotoxy(79, 26);
		printf("���൵: %.1f (%%)", processivity);
		gotoxy(79, 28);
		printf("SCORE: %d ", word_total_score_rcp);
	}

	correct = 0;
	error = 0;
	accuracy = 0;
	speed = 0;
}