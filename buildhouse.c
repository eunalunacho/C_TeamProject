#include "common.h"
char** btexts = 0;

int buildhouse(int level) {
	int check = 0, mode, restart = 0;
	while (1) {
		game3_screen_sp(level);
		char buf[LSIZE], line[LSIZE], ch, input[LSIZE], count, quit;
		srand(time(NULL));
		int re = 1, i, linecount = 0, page, p = 0, x = 2, y = 2, z = 5, w = 27, cnt = 0, k = 0, choice;
		int* num_count = 0, * comp_count = 0, * right = 0;
		int start, end, timelevel = 0, alltime = 0, startScore=0, finalScore=0, loseScore=0;
		int pt = 0, * resume = 0, * qe = 0, tline = 32;
		float* maxsp = 0;
		int num = level;
		int* npt = &pt;
		FILE* fp = 0;
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
				game3_screen_sp(level);
				//waiting();
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
			char ch;
			//txt�� ��� ���� ������ �ľ�
			if (fgets(buf, sizeof(buf), fp) == NULL)  // ���Ͽ��� ���ڿ��� 1�پ� �д´�.
				break;
			linecount++;
		}
		fclose(fp);
		//select_num_long(&fp, i);
		if (linecount > 10) {
			page = linecount / 10;
		}

		buildreadfile(linecount, i);
		while (getchar() != '\n');
		while (p != page) {

			textcolor(WHITE);
			//printf(" ");
			for (int k = 0; k < linecount; k++) {

				int timespent = 0, build;
				start = time(NULL);

				if (k % 10 == 0 && k != 0) {
					++p;
				}
				//system("cls");
				game3_screen_sp(level);
				if (i = 1) {
					if (build = '\0') {
						adele_house(&right, 0);
					}
					else {
						adele_house(&right, build);
					}
				}
				else {
					if (build = '\0') {
						maroon_house(&right, 0);
					}
					else {
						maroon_house(&right, build);
					}
				}
				count = 0;
				gotoxy(x, y + 1);
				for (int j = p * 10; j < (p + 1) * 10; j++) {
					if (j == linecount)
						break;
					printf("\t%s", btexts[j]);
				}
				printf("\n\t\"%d������\"\n", p + 1);//10�� ���������� ������ �ѱ�

				gotoxy(z, w);
				printf("\t����:%s\n", btexts[k]);
				gotoxy(z, w + 2);
				printf("\t");
				
				gettext(input);

				ch = _getch();
				if (ch == 27) {
					//printf("����");
					pauselong(&pt, &resume, &qe, tline);
					//Sleep(1000);
					getchar();
				}

				end = time(NULL);
				timespent = end - start;//�ɸ� �ð�
				alltime += timespent;//�� �ɸ� �ð�
				//compare_house(btexts[k], input, z, w, timespent, &maxsp, &comp_count, linecount);

				build = compare_house(btexts[k], input, z, w, timespent, &maxsp, &comp_count, linecount, start, timelevel);
				if (i == 1) {
					adele_house(&right, build);//adele
				}
				if (i == 2) {
					maroon_house(&right, build);//maroon
				}

				Sleep(1000);//��� �ð�
				gotoxy(z, w);
				printf("                                                                                                                ");//â �����

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
		free(btexts);
		fclose(fp);
		system("cls");
		//���� ���
		break;
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

void buildreadfile(int linecount, int i) {
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
	btexts = (char**)malloc(sizeof(char*) * linecount);  // ���� �޸� �Ҵ�

	for (int j = 0; j < linecount; j++)
	{
		// ���Ͽ��� �� ���ξ� �о ����
		btexts[j] = (char*)malloc(sizeof(char) * LSIZE); //texts �� �迭�� ���� �޸� �Ҵ�
		/*  //texts���� ������ 0���� �ʱ�ȭ�ϴ� ��� 1 for��
		for (int m = 0; m < SIZE; m++) {
			texts[m] = 0;
		}
		*/
		memset(btexts[j], 0, LSIZE);		//->texts���� ������ 0���� �ʱ�ȭ�ϴ� ��� 2 memset�Լ�
		if (fgets(btexts[j], LSIZE, fp) == NULL)
			break;
	}

}

int compare_house(char* btexts, char* input, int z, int w, int timespent, float* maxsp, int* comp_count, int linecount, int start, int timelevel) {
	int end = 0, error = 0, correct = 0;
	int len = strlen(input);
	float speed = 0, accuracy = 0, process = 0;

	gotoxy(z, w);
	printf("\t����:");
	textcolor(WHITE, 0);
	(*comp_count)++;
	for (int i = 0; i < LSIZE; i++)
	{
		if ((input[i] == '\0') || (btexts[i] == '\n'))
			end = 1;

		// ������ ���� ���� ����
		if ((btexts[i] == '\0') || (btexts[i] == '\n')) {
			printf("\n\n                                                                                            ");
			break;
		}
		if ((btexts[i] == input[i]) && (end == 0))
		{
			// �´� ���ڴ� �ʷϻ����� ���
			textcolor(GREEN, 0);
			printf("%c", btexts[i]);

		}
		else
		{
			// Ʋ�� ���ڴ� ���������� ���
			textcolor(RED);
			printf("%c", btexts[i]);
			error++;
		}


	}
	correct = (strlen)(btexts)-error;//-->�� ��� �´� ���ڸ��� correct�� �÷��ִ� ���� �´�
//Ÿ�ڼӵ�->�Է��� Ű���� Ÿ���� �ɸ� �ð����� ���
	if (timespent != 0) {
		speed = (len) / ((float)(timespent)) * 60;
		//speed = ((correct) / (float)(timespent)) * 60;
		//speed = len / (float)(timespent) * 60;
		//�ְ�Ÿ�ڼӵ�
		if (speed > *maxsp) {
			*maxsp = speed;
		}
	}
	//��Ȯ��
	accuracy = ((float)correct / (strlen)(btexts)) * 100;

	//��ü ���൵
	process = (float)(*comp_count) / linecount * 100;
	if (time(0) == start + timelevel) {
		speed = 0;
	}

	//Sleep(1000);// Ȯ�ο� waiting
	//���
	textcolor(WHITE);
	if (timespent == 0) {
		gotoxy(79, 23);
		printf("Ÿ�ڼӵ�: too fast");
	}
	else {
		gotoxy(79, 23);
		printf("Ÿ�ڼӵ�: %.f (Ÿ)", speed);
	}
	gotoxy(79, 24);
	printf("�ְ�Ÿ�ڼӵ�: %.f(Ÿ)", *maxsp);
	gotoxy(79, 25);
	printf("��Ȯ�� : %.f (%%)", accuracy);
	gotoxy(79, 26);
	printf("��Ÿ��: %d (��)", error);
	gotoxy(79, 27);
	printf("���൵: %.1f (%%)", process);
	gotoxy(79, 28);
	printf("�ɸ��ð�: %d (��)", timespent);

	printf("\n");
	//return e;
	if (accuracy == 100.0) {
		correct = 0;
		error = 0;
		accuracy = 0;
		speed = 0;
		return 1;
	}
	else {
		correct = 0;
		error = 0;
		accuracy = 0;
		speed = 0;
		return 0;
	}
}


void adele_house(int* right, int build) {
	if (build == 1) {
		*right = *right + 1;
	}
	switch (*right) {
	case 18:
		gotoxy(40, 25);
		printf("�����մϴ�!");
		Sleep(1000);
		// break;
	case 17:
		gotoxy(57, 13);
		printf("����");
		gotoxy(59, 11);
		printf("��");
		gotoxy(59, 12);
		printf("��");

	case 16:
		gotoxy(57, 21);
		printf("�̢̢̢�");

	case 15:
		gotoxy(57, 22);
		printf("�̢̢̢�");

	case 14:
		gotoxy(57, 23);
		printf("�̢̢̢�");

	case 13:
		gotoxy(57, 24);
		printf("�̢̢̢�");

	case 12:
		gotoxy(55, 13);
		printf("���");
		gotoxy(63, 13);
		printf("���");

	case 11:
		gotoxy(53, 14);
		printf("���");
		gotoxy(65, 14);
		printf("���");

	case 10:
		gotoxy(51, 15);
		printf("���");
		gotoxy(67, 15);
		printf("���");

	case 9:
		gotoxy(49, 16);
		printf("���");
		gotoxy(69, 16);
		printf("���");

	case 8:
		gotoxy(49, 17);
		printf("���");
		gotoxy(69, 17);
		printf("���");

	case 7:
		gotoxy(49, 18);
		printf("���");
		gotoxy(69, 18);
		printf("���");

	case 6:
		gotoxy(49, 19);
		printf("���");
		gotoxy(69, 19);
		printf("���");

	case 5:
		gotoxy(49, 20);
		printf("���");
		gotoxy(69, 20);
		printf("���");

	case 4:
		gotoxy(49, 21);
		printf("���");
		gotoxy(69, 21);
		printf("���");

	case 3:
		gotoxy(49, 22);
		printf("���");
		gotoxy(69, 22);
		printf("���");

	case 2:
		gotoxy(49, 23);
		printf("���");
		gotoxy(69, 23);
		printf("���");

	case 1:
		gotoxy(49, 24);
		printf("���");
		gotoxy(69, 24);
		printf("���");

	default:
		break;
	}
}
void maroon_house(int* right, int build) {
	if (build == 1) {
		*right = *right + 1;
	}
	switch (*right) {
	case 18:
		gotoxy(40, 25);
		printf("�����մϴ�!");
		Sleep(1000);
		// break;
	case 17:
		gotoxy(57, 13);
		printf("����");
		gotoxy(59, 11);
		printf("��");
		gotoxy(59, 12);
		printf("��");

	case 16:
		gotoxy(57, 21);
		printf("�̢̢̢�");

	case 15:
		gotoxy(57, 22);
		printf("�̢̢̢�");

	case 14:
		gotoxy(57, 23);
		printf("�̢̢̢�");

	case 13:
		gotoxy(57, 24);
		printf("�̢̢̢�");

	case 12:
		gotoxy(55, 13);
		printf("���");
		gotoxy(63, 13);
		printf("���");

	case 11:
		gotoxy(53, 14);
		printf("���");
		gotoxy(65, 14);
		printf("���");

	case 10:
		gotoxy(51, 15);
		printf("���");
		gotoxy(67, 15);
		printf("���");

	case 9:
		gotoxy(49, 16);
		printf("���");
		gotoxy(69, 16);
		printf("���");

	case 8:
		gotoxy(49, 17);
		printf("���");
		gotoxy(69, 17);
		printf("���");

	case 7:
		gotoxy(49, 18);
		printf("���");
		gotoxy(69, 18);
		printf("���");

	case 6:
		gotoxy(49, 19);
		printf("���");
		gotoxy(69, 19);
		printf("���");

	case 5:
		gotoxy(49, 20);
		printf("���");
		gotoxy(69, 20);
		printf("���");

	case 4:
		gotoxy(49, 21);
		printf("���");
		gotoxy(69, 21);
		printf("���");

	case 3:
		gotoxy(49, 22);
		printf("���");
		gotoxy(69, 22);
		printf("���");

	case 2:
		gotoxy(49, 23);
		printf("���");
		gotoxy(69, 23);
		printf("���");

	case 1:
		gotoxy(49, 24);
		printf("���");
		gotoxy(69, 24);
		printf("���");

	default:
		break;
	}
}