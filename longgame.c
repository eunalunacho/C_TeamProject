#include "common.h"
char** texts = 0;

int longgame(int level) {
	int check = 0, mode, restart = 0;

	while (1) {
		game3_screen(level);
		char buf[LSIZE], line[LSIZE], ch, input[LSIZE], count, quit;
		srand(time(NULL));
		int re = 1, i, linecount = 0, page = 0, p = 0, x = 2, y = 2, z = 5, w = 26, cnt = 0, k = 0, choice;
		int* num_count = 0, * comp_count = 0;
		int start, end, timelevel = 0, alltime = 0, startScore = 0, finalScore = 0, loseScore = 0;
		int pt = 0, * resume = 0, * qe = 0, tline = 32;
		int* npt = &pt;
		float* maxsp = 0;
		FILE* fp = 0;
		int num = level;

		while (re) {
			gotoxy(10, 5);
			printf("1.Adele - Someone like you");
			gotoxy(10, 6);
			printf("2.Maroon 5 - sugar");
			gotoxy(10, 7);
			printf("3.�ڷ� ����");
			gotoxy(10, 8);
			printf("�Է�â:");
			scanf("%d", &i);

			switch (i) {//���� ����
			case 1:
				fopen_s(&fp, "adele.txt", "r");//test.txt���� open
				re = 0;//�ݺ����� ����ǵ� ok��� ��ȣ
				break;
			case 2:
				fopen_s(&fp, "maroon.txt", "r");
				re = 0;
				break;
			case 3:
				//main();
				main();
			default:
				//�ڷ� ����->Ÿ��Ʋȭ�� ���
				break;
			}
			if (i < 1 || i>3) {
				gotoxy(10, 9);
				printf("1-3������ ���� �Է����ּ���\n");
				Sleep(1000);
				system("cls");
				game3_screen(level);
				gotoxy(5, 27);
				printf("�Ϲݸ�� ����");
			}

			else {
				switch (num) {
				case 1:
					startScore = 5000;
					timelevel = LEASYTIME;//���̵� ����
					loseScore = 100;
					//printf("\n�ʱ�:���� 5��");
					break;
				case 2:
					startScore = 7000;
					timelevel = LMIDTIME;//���̵� �߰�
					loseScore = 300;
					//printf("\n�߱�:���� 3��");
					break;
				case 3:
					startScore = 10000;
					timelevel = LHARDTIME;//���̵� �����
					loseScore = 500;
					//printf("\n���:���� 2��");
					break;
				case 4:
					system("cls");
					re = 1;//�ݺ����� �ٽ� �����ؾ߰ڴٴ� ��ȣ
					continue;
					//���� �������� �̵�
				}
			}
		}

		Sleep(1000);
		system("cls");
		while (1) {
			//txt�� ��� ���� ������ �ľ�
			char ch;
			if (fgets(buf, sizeof(buf), fp) == NULL)  // ���Ͽ��� ���ڿ��� 1�پ� �д´�.
				break;
			linecount++;
		}
		fclose(fp);
		//select_level_long(&fp, i);
		if (linecount > 10) {
			page = linecount / 10;
		}

		readfile(linecount, i);
		while (getchar() != '\n');
		while (p != page) {

			textcolor(WHITE);
			//printf(" ");
			for (int k = 0; k < linecount; k++) {

				int timespent = 0;
				start = time(NULL);

				if (k % 10 == 0 && k != 0) {
					++p;
				}
				system("cls");
				game3_screen(level);
				count = 0;
				gotoxy(x, y + 1);
				for (int j = p * 10; j < (p + 1) * 10; j++) {//1�������� 10�ٷ� ���Ѵ�.
					if (j == linecount)
						break;
					printf("\t%s", texts[j]);
				}
				printf("\n\t\"%d������\"\n", p + 1);//10�� ���������� ������ �ѱ�

				gotoxy(z, w);
				printf("\t����:%s\n", texts[k]);


				gotoxy(z, w + 2);
				printf("\t");

				gettext(input);

				ch = _getch();
				if (ch == 27) {
					//printf("����");
					pauselong(&npt, &resume, &qe, tline);
					//Sleep(1000);
					getchar();
				}
				end = time(NULL);
				timespent = end - start;//�ɸ� �ð�
				alltime += timespent;//�� �ɸ� �ð�

				compare(texts[k], input, z, w, timespent, &maxsp, &comp_count, linecount, start, timelevel);
				Sleep(1000);//��� �ð�
				gotoxy(z, w);
				printf("                                                                                                     ");
				//system("cls");
			}

		}
		if (timelevel < alltime) {
			finalScore = 0;
		}
		else {
			if (NULL != *npt) {
				finalScore = startScore - (alltime - (*npt)) * loseScore;
			}
			else {
				finalScore = startScore - alltime * loseScore;
			}
		}
		system("cls");
		game3_screen_sp(level);
		gotoxy(10, 15);
		if (finalScore == 0) {
			printf("���ѽð��� �ʰ��Ǿ����Ƿ� ��������  %d���Դϴ�.", finalScore);
		}
		else {
			printf("��������: %d���Դϴ�", finalScore);
		}
		Sleep(1000);
		if (num == 3) {
			gotoxy(10, 16);
			printf("�����Ͻ÷��� q��, ó������ ������Ϸ��� r�� �����ּ���:");
			scanf(" %c", &quit);
			if (quit == 'q') {
				check = 1;
				break;
			}
			if (quit == 'r') {
				//level = 1;
				check = 2;
				break;
			}
		}
		else {
			++level;
		}
		free(texts);
		fclose(fp);
		system("cls");
		//���� ���
		//break;

	}
	system("cls");
	if (check == 1) {
		return 2;
	}
	if (check == 2) {
		while (1) {
			do {
				game3_mode(); //��� �޴� ���
				scanf("%d", &mode);//��� �Է¹ޱ�
			} while (mode < 1 || mode>3);

			//��忡 ���� ���� ����
			if (mode == 3) {  //�ڷΰ����ϸ� �ٽ� �޴�ȭ������
				system("cls");
				//main();
				break;
			}
			else if (mode == 1)
			{
				level = levelchoice_without_free();
				if (level == 4)
					continue;
				else
				{
					game3_screen(level);
					waiting();

					restart = longgame(level);
					break;
				}
			}
			else
			{
				level = levelchoice_without_free();
				if (level == 4)
					continue;
				else
				{
					game3_screen_sp(level);
					waiting();

					restart = buildhouse(level);
					break;
				}
			}
			if (restart == 1 || restart == 2)
				break;  //��� ��� �ݺ��� Ż��
		}

	}
}

/// ////////////


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(unsigned int text) {//���� �� �ٲٴ� �Լ�
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void readfile(int linecount, int i) {
	FILE* fp = 0;
	switch (i) {
	case 1:
		fp = fopen("adele.txt", "r");
		break;
	case 2:
		fp = fopen("maroon.txt", "r");
		break;
	default:
		break;
	}
	texts = (char**)malloc(sizeof(char*) * linecount);  // ���� �޸� �Ҵ�

	for (int j = 0; j < linecount; j++)
	{
		// ���Ͽ��� �� ���ξ� �о ����
		texts[j] = (char*)malloc(sizeof(char) * LSIZE); //texts �� �迭�� ���� �޸� �Ҵ�
		/*  //texts���� ������ 0���� �ʱ�ȭ�ϴ� ��� 1 for��
		for (int m = 0; m < SIZE; m++) {
			texts[m] = 0;
		}
		*/
		memset(texts[j], 0, LSIZE);		//->texts���� ������ 0���� �ʱ�ȭ�ϴ� ��� 2 memset�Լ�
		if (fgets(texts[j], LSIZE, fp) == NULL)
			break;
	}

}
void compare(char* texts, char* input, int z, int w, int timespent, float* maxsp, int* comp_count, int linecount, int start, int timelevel) {
	int end = 0, error = 0, correct = 0;
	int len = strlen(input);
	float speed = 0, accuracy = 0, process = 0;

	gotoxy(z, w);
	printf("\t����:");
	textcolor(WHITE, 0);
	(*comp_count)++;
	for (int i = 0; i < LSIZE; i++)
	{
		if ((input[i] == '\0') || (texts[i] == '\n'))
			end = 1;

		// ������ ���� ���� ����
		if ((texts[i] == '\0') || (texts[i] == '\n')) {
			printf("\n\n                                                                                            ");
			break;
		}
		if ((texts[i] == input[i]) && (end == 0))
		{
			// �´� ���ڴ� �ʷϻ����� ���
			textcolor(GREEN, 0);
			printf("%c", texts[i]);

		}
		else
		{
			// Ʋ�� ���ڴ� ���������� ���
			textcolor(RED);
			printf("%c", texts[i]);
			error++;
		}


	}
	//��Ÿ��
	correct = (strlen)(texts)-error;
	//Ÿ�ڼӵ�->�Է��� Ű���� Ÿ���� �ɸ� �ð����� ���
	if (timespent != 0) {
		speed = (len) / ((float)(timespent)) * 60;

		//�ְ�Ÿ�ڼӵ�
		if (speed > *maxsp) {
			*maxsp = speed;
		}
	}
	//��Ȯ��
	accuracy = ((float)correct / (strlen)(texts)) * 100;

	//��ü ���൵
	process = (float)(*comp_count) / linecount * 100;
	if (time(0) == start + timelevel) {
		speed = 0;
	}

	//���
	textcolor(WHITE);
	if (timespent == 0) {
		gotoxy(79, 22);
		printf("Ÿ�ڼӵ�: too fast");
	}
	else {
		gotoxy(79, 22);
		printf("Ÿ�ڼӵ�: %.f (Ÿ)", speed);
	}
	gotoxy(79, 23);
	printf("�ְ�Ÿ�ڼӵ�: %.f(Ÿ)", *maxsp);
	gotoxy(79, 24);
	printf("��Ȯ�� : %.f (%%)", accuracy);
	gotoxy(79, 25);
	printf("��Ÿ��: %d (��)", error);
	gotoxy(79, 26);
	printf("���൵: %.1f (%%)", process);
	gotoxy(79, 27);
	printf("�ɸ��ð�: %d (��)", timespent);

	correct = 0; //�������� �ʱ�ȭ
	error = 0;
	accuracy = 0;
	speed = 0;
	printf("\n");
	//return e;
}
void gettext(char* input) {//����� �Է� ����
	fgets(input, LSIZE, stdin);
	input[strlen(input) - 1] = '\n';

}
void pauselong(int* npt, int* resume, int* qe, int line) // �Ͻ������ð�, ���� �簳 ����, �ʱ�޴��� �̵� ����, ����� ��
{
	int st, et, pause_choice;
	st = time(0);
	while (1)
	{
		*resume = 0; //�� �ʱ�ȭ
		int stop = 0; //stop�� 1�� ���ϸ� �Ͻ����� Ż��
		while (1)// �Ͻ� ���� �޴� ����
		{
			gotoxy(4, line); printf("���Ͻ������� 1. ���� �簳  2. �ʱ� �޴��� �̵�  => �������ּ���: ");
			Sleep(200);
			gotoxy(4, line); printf("���Ͻ������� 1. ���� �簳  2. �ʱ� �޴��� �̵�  => �������ּ���: ");
			Sleep(200);
			if (_kbhit()) //Ű���� ��Ʈ�� �߻��ϸ� ������ ����
				break;
		}
		do {
			gotoxy(69, line); // �������ּ��� �ڷ� �̵�
			printf("                                           "); // ������ �� �����
			gotoxy(69, line); // �������ּ��� �ڷ� �̵�
			scanf("%d", &pause_choice);
		} while (pause_choice < 1 || pause_choice >2);

		switch (pause_choice)
		{
		case 1://�����簳 
			gotoxy(4, line); printf("                                                                                                     "); // �Ͻ����� �� �����
			*resume = 1;
			stop = 1;
			break;

		default:
			gotoxy(4, line); printf("                                                                                                     "); // �Ͻ����� �� �����
			*qe = 1;
			stop = 1;
			main();

		}
		if (stop == 1)
			break; //�Ͻ����� ����
	}
	et = time(0);
	if (et != 0) {
		*npt = et - st;
	}
	else {
		*npt = 0;
	}
}
