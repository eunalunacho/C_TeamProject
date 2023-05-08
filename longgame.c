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
				game3_screen(level);
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
			//txt가 몇개의 라인 인지를 파악
			char ch;
			if (fgets(buf, sizeof(buf), fp) == NULL)  // 파일에서 문자열을 1줄씩 읽는다.
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
				for (int j = p * 10; j < (p + 1) * 10; j++) {//1페이지를 10줄로 정한다.
					if (j == linecount)
						break;
					printf("\t%s", texts[j]);
				}
				printf("\n\t\"%d페이지\"\n", p + 1);//10줄 읽을때마다 페이지 넘김

				gotoxy(z, w);
				printf("\t문장:%s\n", texts[k]);


				gotoxy(z, w + 2);
				printf("\t");

				gettext(input);

				ch = _getch();
				if (ch == 27) {
					//printf("성공");
					pauselong(&npt, &resume, &qe, tline);
					//Sleep(1000);
					getchar();
				}
				end = time(NULL);
				timespent = end - start;//걸린 시간
				alltime += timespent;//총 걸린 시간

				compare(texts[k], input, z, w, timespent, &maxsp, &comp_count, linecount, start, timelevel);
				Sleep(1000);//대기 시간
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
		free(texts);
		fclose(fp);
		system("cls");
		//점수 출력
		//break;

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

/// ////////////


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(unsigned int text) {//글자 색 바꾸는 함수
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
	texts = (char**)malloc(sizeof(char*) * linecount);  // 동적 메모리 할당

	for (int j = 0; j < linecount; j++)
	{
		// 파일에서 한 라인씩 읽어서 저장
		texts[j] = (char*)malloc(sizeof(char) * LSIZE); //texts 내 배열도 동적 메모리 할당
		/*  //texts안의 내용을 0으로 초기화하는 방법 1 for문
		for (int m = 0; m < SIZE; m++) {
			texts[m] = 0;
		}
		*/
		memset(texts[j], 0, LSIZE);		//->texts안의 내용을 0으로 초기화하는 방법 2 memset함수
		if (fgets(texts[j], LSIZE, fp) == NULL)
			break;
	}

}
void compare(char* texts, char* input, int z, int w, int timespent, float* maxsp, int* comp_count, int linecount, int start, int timelevel) {
	int end = 0, error = 0, correct = 0;
	int len = strlen(input);
	float speed = 0, accuracy = 0, process = 0;

	gotoxy(z, w);
	printf("\t문장:");
	textcolor(WHITE, 0);
	(*comp_count)++;
	for (int i = 0; i < LSIZE; i++)
	{
		if ((input[i] == '\0') || (texts[i] == '\n'))
			end = 1;

		// 문자의 끝이 오면 중지
		if ((texts[i] == '\0') || (texts[i] == '\n')) {
			printf("\n\n                                                                                            ");
			break;
		}
		if ((texts[i] == input[i]) && (end == 0))
		{
			// 맞는 문자는 초록색으로 출력
			textcolor(GREEN, 0);
			printf("%c", texts[i]);

		}
		else
		{
			// 틀린 문자는 붉은색으로 출력
			textcolor(RED);
			printf("%c", texts[i]);
			error++;
		}


	}
	//정타수
	correct = (strlen)(texts)-error;
	//타자속도->입력한 키보드 타수와 걸린 시간으로 계산
	if (timespent != 0) {
		speed = (len) / ((float)(timespent)) * 60;

		//최고타자속도
		if (speed > *maxsp) {
			*maxsp = speed;
		}
	}
	//정확도
	accuracy = ((float)correct / (strlen)(texts)) * 100;

	//전체 진행도
	process = (float)(*comp_count) / linecount * 100;
	if (time(0) == start + timelevel) {
		speed = 0;
	}

	//출력
	textcolor(WHITE);
	if (timespent == 0) {
		gotoxy(79, 22);
		printf("타자속도: too fast");
	}
	else {
		gotoxy(79, 22);
		printf("타자속도: %.f (타)", speed);
	}
	gotoxy(79, 23);
	printf("최고타자속도: %.f(타)", *maxsp);
	gotoxy(79, 24);
	printf("정확도 : %.f (%%)", accuracy);
	gotoxy(79, 25);
	printf("오타수: %d (개)", error);
	gotoxy(79, 26);
	printf("진행도: %.1f (%%)", process);
	gotoxy(79, 27);
	printf("걸린시간: %d (초)", timespent);

	correct = 0; //측정값들 초기화
	error = 0;
	accuracy = 0;
	speed = 0;
	printf("\n");
	//return e;
}
void gettext(char* input) {//사용자 입력 문장
	fgets(input, LSIZE, stdin);
	input[strlen(input) - 1] = '\n';

}
void pauselong(int* npt, int* resume, int* qe, int line) // 일시정지시간, 게임 재개 여부, 초기메뉴로 이동 여부, 출력할 줄
{
	int st, et, pause_choice;
	st = time(0);
	while (1)
	{
		*resume = 0; //값 초기화
		int stop = 0; //stop이 1로 변하면 일시정지 탈출
		while (1)// 일시 정지 메뉴 띄우기
		{
			gotoxy(4, line); printf("★일시정지★ 1. 게임 재개  2. 초기 메뉴로 이동  => 선택해주세요: ");
			Sleep(200);
			gotoxy(4, line); printf("☆일시정지☆ 1. 게임 재개  2. 초기 메뉴로 이동  => 선택해주세요: ");
			Sleep(200);
			if (_kbhit()) //키보드 히트가 발생하면 깜빡임 중지
				break;
		}
		do {
			gotoxy(69, line); // 선택해주세요 뒤로 이동
			printf("                                           "); // 기존의 거 지우고
			gotoxy(69, line); // 선택해주세요 뒤로 이동
			scanf("%d", &pause_choice);
		} while (pause_choice < 1 || pause_choice >2);

		switch (pause_choice)
		{
		case 1://게임재개 
			gotoxy(4, line); printf("                                                                                                     "); // 일시정지 글 지우기
			*resume = 1;
			stop = 1;
			break;

		default:
			gotoxy(4, line); printf("                                                                                                     "); // 일시정지 글 지우기
			*qe = 1;
			stop = 1;
			main();

		}
		if (stop == 1)
			break; //일시정지 종료
	}
	et = time(0);
	if (et != 0) {
		*npt = et - st;
	}
	else {
		*npt = 0;
	}
}
