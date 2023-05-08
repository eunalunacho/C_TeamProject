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
			printf("3.뒤로 가기");
			gotoxy(10, 8);
			printf("입력창:");
			scanf("%d", &i);

			switch (i) {//파일 선택
			case 1:
				fopen_s(&fp, "adele.txt", "r");//test.txt파일 open
				re = 0;//반복문이 종료되도 ok라는 신호
				break;
			case 2:
				fopen_s(&fp, "maroon.txt", "r");
				re = 0;
				break;
			case 3:
				//main();
				main();
			default:
				//뒤로 가기->타이틀화면 출력
				break;
			}
			if (i < 1 || i>3) {
				gotoxy(10, 9);
				printf("1-3사이의 값을 입력해주세요\n");
				Sleep(1000);
				system("cls");
				game3_screen_sp(level);
				//waiting();
				gotoxy(5, 27);
				printf("일반모드 실행");
			}

			else {
				switch (num) {
				case 1:
					startScore = 5000;
					timelevel = LEASYTIME;//난이도 쉬움
					loseScore = 100;
					//printf("\n초급:제한 5분");
					break;
				case 2:
					startScore = 7000;
					timelevel = LMIDTIME;//난이도 중간
					loseScore = 300;
					//printf("\n중급:제한 3분");
					break;
				case 3:
					startScore = 10000;
					timelevel = LHARDTIME;//난이도 어려움
					loseScore = 500;
					//printf("\n고급:제한 2분");
					break;
				case 4:
					system("cls");
					re = 1;//반복문을 다시 시작해야겠다는 신호
					continue;
					//파일 선택으로 이동
				}
			}
		}

		Sleep(1000);
		system("cls");

		while (1) {
			char ch;
			//txt가 몇개의 라인 인지를 파악
			if (fgets(buf, sizeof(buf), fp) == NULL)  // 파일에서 문자열을 1줄씩 읽는다.
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
				printf("\n\t\"%d페이지\"\n", p + 1);//10줄 읽을때마다 페이지 넘김

				gotoxy(z, w);
				printf("\t문장:%s\n", btexts[k]);
				gotoxy(z, w + 2);
				printf("\t");
				
				gettext(input);

				ch = _getch();
				if (ch == 27) {
					//printf("성공");
					pauselong(&pt, &resume, &qe, tline);
					//Sleep(1000);
					getchar();
				}

				end = time(NULL);
				timespent = end - start;//걸린 시간
				alltime += timespent;//총 걸린 시간
				//compare_house(btexts[k], input, z, w, timespent, &maxsp, &comp_count, linecount);

				build = compare_house(btexts[k], input, z, w, timespent, &maxsp, &comp_count, linecount, start, timelevel);
				if (i == 1) {
					adele_house(&right, build);//adele
				}
				if (i == 2) {
					maroon_house(&right, build);//maroon
				}

				Sleep(1000);//대기 시간
				gotoxy(z, w);
				printf("                                                                                                                ");//창 지우기

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
			printf("제한시간이 초과되었으므로 최종점수  %d점입니다.", finalScore);
		}
		else {
			printf("최종점수: %d점입니다", finalScore);
		}
		Sleep(1000);
		if (num == 3) {
			gotoxy(10, 16);
			printf("종료하시려면 q를, 처음부터 재시작하려면 r를 눌러주세요:");
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
		//점수 출력
		break;
	}
	system("cls");
	if (check == 1) {
		return 2;
	}
	if (check == 2) {
		while (1) {
			do {
				game3_mode(); //모드 메뉴 출력
				scanf("%d", &mode);//모드 입력받기
			} while (mode < 1 || mode>3);

			//모드에 따른 동작 수행
			if (mode == 3) {  //뒤로가기하면 다시 메뉴화면으로
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
				break;  //모드 출력 반복문 탈출
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
	btexts = (char**)malloc(sizeof(char*) * linecount);  // 동적 메모리 할당

	for (int j = 0; j < linecount; j++)
	{
		// 파일에서 한 라인씩 읽어서 저장
		btexts[j] = (char*)malloc(sizeof(char) * LSIZE); //texts 내 배열도 동적 메모리 할당
		/*  //texts안의 내용을 0으로 초기화하는 방법 1 for문
		for (int m = 0; m < SIZE; m++) {
			texts[m] = 0;
		}
		*/
		memset(btexts[j], 0, LSIZE);		//->texts안의 내용을 0으로 초기화하는 방법 2 memset함수
		if (fgets(btexts[j], LSIZE, fp) == NULL)
			break;
	}

}

int compare_house(char* btexts, char* input, int z, int w, int timespent, float* maxsp, int* comp_count, int linecount, int start, int timelevel) {
	int end = 0, error = 0, correct = 0;
	int len = strlen(input);
	float speed = 0, accuracy = 0, process = 0;

	gotoxy(z, w);
	printf("\t문장:");
	textcolor(WHITE, 0);
	(*comp_count)++;
	for (int i = 0; i < LSIZE; i++)
	{
		if ((input[i] == '\0') || (btexts[i] == '\n'))
			end = 1;

		// 문자의 끝이 오면 중지
		if ((btexts[i] == '\0') || (btexts[i] == '\n')) {
			printf("\n\n                                                                                            ");
			break;
		}
		if ((btexts[i] == input[i]) && (end == 0))
		{
			// 맞는 문자는 초록색으로 출력
			textcolor(GREEN, 0);
			printf("%c", btexts[i]);

		}
		else
		{
			// 틀린 문자는 붉은색으로 출력
			textcolor(RED);
			printf("%c", btexts[i]);
			error++;
		}


	}
	correct = (strlen)(btexts)-error;//-->이 경우 맞는 문자마다 correct를 늘려주는 것이 맞다
//타자속도->입력한 키보드 타수와 걸린 시간으로 계산
	if (timespent != 0) {
		speed = (len) / ((float)(timespent)) * 60;
		//speed = ((correct) / (float)(timespent)) * 60;
		//speed = len / (float)(timespent) * 60;
		//최고타자속도
		if (speed > *maxsp) {
			*maxsp = speed;
		}
	}
	//정확도
	accuracy = ((float)correct / (strlen)(btexts)) * 100;

	//전체 진행도
	process = (float)(*comp_count) / linecount * 100;
	if (time(0) == start + timelevel) {
		speed = 0;
	}

	//Sleep(1000);// 확인용 waiting
	//출력
	textcolor(WHITE);
	if (timespent == 0) {
		gotoxy(79, 23);
		printf("타자속도: too fast");
	}
	else {
		gotoxy(79, 23);
		printf("타자속도: %.f (타)", speed);
	}
	gotoxy(79, 24);
	printf("최고타자속도: %.f(타)", *maxsp);
	gotoxy(79, 25);
	printf("정확도 : %.f (%%)", accuracy);
	gotoxy(79, 26);
	printf("오타수: %d (개)", error);
	gotoxy(79, 27);
	printf("진행도: %.1f (%%)", process);
	gotoxy(79, 28);
	printf("걸린시간: %d (초)", timespent);

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
		printf("축하합니다!");
		Sleep(1000);
		// break;
	case 17:
		gotoxy(57, 13);
		printf("□□□");
		gotoxy(59, 11);
		printf("□");
		gotoxy(59, 12);
		printf("□");

	case 16:
		gotoxy(57, 21);
		printf("▩▩▩▩");

	case 15:
		gotoxy(57, 22);
		printf("▩▩▩▩");

	case 14:
		gotoxy(57, 23);
		printf("▩▩▩▩");

	case 13:
		gotoxy(57, 24);
		printf("▩▩▩▩");

	case 12:
		gotoxy(55, 13);
		printf("□□");
		gotoxy(63, 13);
		printf("□□");

	case 11:
		gotoxy(53, 14);
		printf("□□");
		gotoxy(65, 14);
		printf("□□");

	case 10:
		gotoxy(51, 15);
		printf("□□");
		gotoxy(67, 15);
		printf("□□");

	case 9:
		gotoxy(49, 16);
		printf("□□");
		gotoxy(69, 16);
		printf("□□");

	case 8:
		gotoxy(49, 17);
		printf("□□");
		gotoxy(69, 17);
		printf("□□");

	case 7:
		gotoxy(49, 18);
		printf("□□");
		gotoxy(69, 18);
		printf("□□");

	case 6:
		gotoxy(49, 19);
		printf("□□");
		gotoxy(69, 19);
		printf("□□");

	case 5:
		gotoxy(49, 20);
		printf("□□");
		gotoxy(69, 20);
		printf("□□");

	case 4:
		gotoxy(49, 21);
		printf("□□");
		gotoxy(69, 21);
		printf("□□");

	case 3:
		gotoxy(49, 22);
		printf("□□");
		gotoxy(69, 22);
		printf("□□");

	case 2:
		gotoxy(49, 23);
		printf("□□");
		gotoxy(69, 23);
		printf("□□");

	case 1:
		gotoxy(49, 24);
		printf("□□");
		gotoxy(69, 24);
		printf("□□");

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
		printf("축하합니다!");
		Sleep(1000);
		// break;
	case 17:
		gotoxy(57, 13);
		printf("□□□");
		gotoxy(59, 11);
		printf("□");
		gotoxy(59, 12);
		printf("□");

	case 16:
		gotoxy(57, 21);
		printf("▩▩▩▩");

	case 15:
		gotoxy(57, 22);
		printf("▩▩▩▩");

	case 14:
		gotoxy(57, 23);
		printf("▩▩▩▩");

	case 13:
		gotoxy(57, 24);
		printf("▩▩▩▩");

	case 12:
		gotoxy(55, 13);
		printf("□□");
		gotoxy(63, 13);
		printf("□□");

	case 11:
		gotoxy(53, 14);
		printf("□□");
		gotoxy(65, 14);
		printf("□□");

	case 10:
		gotoxy(51, 15);
		printf("□□");
		gotoxy(67, 15);
		printf("□□");

	case 9:
		gotoxy(49, 16);
		printf("□□");
		gotoxy(69, 16);
		printf("□□");

	case 8:
		gotoxy(49, 17);
		printf("□□");
		gotoxy(69, 17);
		printf("□□");

	case 7:
		gotoxy(49, 18);
		printf("□□");
		gotoxy(69, 18);
		printf("□□");

	case 6:
		gotoxy(49, 19);
		printf("□□");
		gotoxy(69, 19);
		printf("□□");

	case 5:
		gotoxy(49, 20);
		printf("□□");
		gotoxy(69, 20);
		printf("□□");

	case 4:
		gotoxy(49, 21);
		printf("□□");
		gotoxy(69, 21);
		printf("□□");

	case 3:
		gotoxy(49, 22);
		printf("□□");
		gotoxy(69, 22);
		printf("□□");

	case 2:
		gotoxy(49, 23);
		printf("□□");
		gotoxy(69, 23);
		printf("□□");

	case 1:
		gotoxy(49, 24);
		printf("□□");
		gotoxy(69, 24);
		printf("□□");

	default:
		break;
	}
}