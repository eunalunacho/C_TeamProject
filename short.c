#include "common.h"

extern int level;
extern int restart;

char* easy[SHORT_LINE] = { "No news is good news.","No pain, no gain.","Sleep is better than medicine.", "Speak of the devil.",
		"If there is no wind, row.","Never judge by appearances.", "Asking costs nothing.", "The longest night must end.","Love begets love.",
		"Pride will have a fall.","Honesty is the best policy.","Practice makes perfect.","Look before you leap.","Rome wasn't built in a day.",
	"It takes two to tango.","First things first.","It's the tip of the iceberg.","Out of sight, out of mind.","Easy come, easy go.", "Walls have ears." };
char* ebomb[20] = { "good", "pain", "better", "devil","wind","judge","costs","night","begets", "Pride","best","perfect","before","built",
	"tango","first","iceberg","sight", "come","ears" };

char* normal[SHORT_LINE] = { "Empty vessels make the most sound.", "Don't judge a book by its cover.","When in Rome, do as the Romans do.",
	"Where there's a will, there's a way.", "Don't make a mountain out of an anthill.", "The early bird catches the worm.", "Always put your best foot forward.",
	"Actions speak louder than words.", "It's no use crying over spilled milk.","A rolling stone gathers no moss.","Every cloud has a silver lining.",
	"Hold a true friend with both your hands.","A trouble shared is a trouble halved.", "Live as if you were to die tomorrow.", "Times change, and we change with them.",
	"We live, not as we wish, but as we can.", "Love must be fostered with soft words.","There is no royal road to learning.", "You can't eat your cake and have it.",
	"Put yourself in other people's shoes." };
char* nbomb[20] = { "sound", "cover", "Rome", "will","anthill","bird","forward","speak","milk", "stone","cloud","friend","trouble","Live",
	"change","wish","soft","royal", "cake","shoes" };

char* hard[SHORT_LINE] = { "Just because you can doesn't mean you should.", "Power is dangerous unless you have humility.",
"Don't cross the bridge until you come to it.","Don't count your chickens before they hatch.","Never put off till tomorrow what you can do today.",
"Failure is but a stepping stone to success.","The sparrow near a school sings the primer.","An eye for an eye, a tooth for a tooth.",
"Good things can come from bad situation.","Opportunity did not knock until I built a door.","Be slow in choosing, but slower in changing.",
"One man's trash is another man's treasure.","A little knowledge is a dangerous thing.","A bad workman always blames his tools.",
"God helps those who help themselves.","Everybody's business is nobody's business.","The darkest hour is just before the dawn.",
"The mind makes heaven of hell and hell of heaven.","Kind words are worth much and they cost little.","A life of leisure and life of laziness are two things." };
char* hbomb[20] = { "should", "unless", "bridge", "hatch","tomorrow","success","school","tooth","things", "knock","slow","trash","little","blames",
	"those","business","dawn","heaven", "worth","leisure" };

void short_free() {
	int i = 0, start, end, gap = 0, len; //문장 진행도, 시간 측정 시작, 끝, 문장 당 소요 시간, 멈춘 시간, 문자열 길이
	int pt, resume = 0, qe = 0;
	int short_totalscore = 0, stop = 1;        //짧은글 게임 점수 누적, 시간 출력 스위치
	float max_spd = 0;               //최고 타자 속도
	unsigned int cnt = 0;
	int error = 0;          //문자열 인덱스, 문자열 비교시 오류 갯수
	char input[SHORT_MAX_E], ch;     //입력 받는 배열, 입력 받는 문자 저장
	char ran[SHORT_LINE] = { 0 };    //출력 여부 확인용 배열 (한 번 출력된 것은 1로 변경, 0인 경우만 출력한다)

	game2_screen(level);
	waiting();
	sent_clear();
	srand((unsigned)time(NULL));
	while (i < SHORT_LINE) {
		int a;
		CursorView(FALSE);
		a = rand_print(ran, &len);  //랜덤 숫자 선택 및 문제 출력 함수
		if (ran[a] != 1) {
			start = time(NULL);
			while (1) {
				if (time(0) >= start) {
					if (!stop) {
						pause(&pt, &resume, &qe, 32);
						if (resume == 1) {
							start = time(0);
							stop = 1;
						}
						else
							break;
					}
					gotoxy(8, 28);
				}
				if (_kbhit()) {
					gotoxy(8 + cnt, 28);
					ch = _getch();
					swrite(ch, a, &cnt, input);
					if (ch == 27) {  //esc 키
						end = time(NULL);
						gap += end - start;
						stop = 0;
					}
				}
				textcolor(15);
				if (cnt >= len) {
					end = time(0);
					gap += end - start;
					serror_cnt(a, input, len, &error);  //오타 수 세기
					short_compare(easy[a], input, len);
					cal_short(gap, ferror, SHORT_LINE, i + 1, &max_spd, len, 0, 1);
					sent_clear();
					clear_cnt(&cnt, &ferror);
					gap = 0;
					break;
				}
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) {  // 일시정지
					end = time(0);
					gap += end - start;
					pause(&pt, &resume, &qe, 32);
					if (resume == 1)
						stop = 1;
					else
						break;
				}
			}
			ran[a] = 1;
			i++;
		}
		else
			continue;
		if (qe == 1)
			break;
	}
	if (qe != 1)
	{
		sent_clear();
		gotoxy(10, 14);
		printf("자유 모드가 종료되었습니다.");
		gotoxy(10, 15);
		printf("잠시 후 자동으로 다음 레벨로 이동합니다.");
		Sleep(5000);
		clear_cnt(&cnt, &error);
		level += 1;
		short_easy();
	}
}

void short_easy() {
	int i = 0, sstart, start, end, gap = 0, len; //문장 진행도, 시간 측정 시작, 끝, 문장 당 소요 시간, 멈춘 시간, 문자열 길이
	int pt, ppt = 0, resume = 0, qe = 0;
	int short_totalscore = 0, stop = 1;        //짧은글 게임 점수 누적, 시간 출력 스위치
	float max_spd = 0;               //최고 타자 속도
	unsigned int cnt = 0;
	int error = 0;          //문자열 인덱스, 문자열 비교시 오류 갯수
	char input[SHORT_MAX_E], ch;     //입력 받는 배열, 입력 받는 문자 저장
	char ran[SHORT_LINE] = { 0 };    //출력 여부 확인용 배열 (한 번 출력된 것은 1로 변경, 0인 경우만 출력한다)

	game2_screen(level);
	waiting();
	sent_clear();
	srand((unsigned)time(NULL));
	while (i < SHORT_LINE) {
		int a;
		a = rand_print(ran, &len);  //랜덤 숫자 선택 및 문제 출력 함수
		if (ran[a] != 1) {
			sstart = start = time(NULL);
			while (1) {
				if (time(0) >= sstart) {
					if (stop) {
						gotoxy(6, 4);
						CursorView(FALSE);
						printf("남은 시간 : %d초  ", SEASYTIME - (time(0) - sstart) + ppt);      //잔여 시간 출력
						if (timeattack(sstart, ppt, SEASYTIME) == 1) {
							cal_timeover(SEASYTIME, SHORT_LINE, i + 1, &max_spd, 0, 0);
							sent_clear();
							clear_cnt(&cnt, &error);
							gap = 0;
							break;
						}
					}
					else {
						pause(&pt, &resume, &qe, 32);
						ppt += pt;
						if (resume == 1) {
							start = time(0);
							stop = 1;
						}
						else
							break;
					}
					gotoxy(8, 28);
				}
				if (_kbhit()) {
					gotoxy(8 + cnt, 28);
					ch = _getch();
					swrite(ch, a, &cnt, input);
					if (ch == 27) {  //esc 키
						end = time(NULL);
						gap += end - start;
						stop = 0;
					}
				}
				textcolor(15);
				if (cnt >= len) {
					end = time(0);
					gap += end - start;
					serror_cnt(a, input, len, &error);  //오타 수 세기
					if (short_compare(easy[a], input, len)) {
						score_short(gap, SEASYTIME, &short_totalscore);
					}
					else {
						score_short(SEASYTIME, SEASYTIME, &short_totalscore);  //오타 있으면 점수 0 위해 소요 시간 제한시간으로 초기화
					}
					cal_short(gap, error, SHORT_LINE, i + 1, &max_spd, len, 0, 1);
					sent_clear();
					clear_cnt(&cnt, &error);
					gap = 0;
					break;
				}
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) {  // 일시정지
					stop = 0;
					end = time(0);
					gap += end - start;
					pause(&pt, &resume, &qe, 32);
					ppt += pt;
					if (resume == 1) {
						start = time(0);
						stop = 1;
					}
					else
						break;
				}
			}
			ran[a] = 1;
			ppt = 0;
			i++;
		}
		else
			continue;
		if (qe == 1)
			break;
	}
	if (qe != 1)
	{
		sent_clear();
		gotoxy(10, 14);
		printf("이번 게임 점수는 %d점 입니다.", short_totalscore);
		gotoxy(10, 15);
		printf("잠시 후 자동으로 다음 레벨로 이동합니다.");
		Sleep(5000);
		clear_cnt(&cnt, &error);
		CursorView(TRUE);
		level += 1;
		short_normal();
	}
}

void short_normal() {
	int i = 0, sstart, start, end, gap = 0, len; //문장 진행도, 시간 측정 시작, 끝, 문장 당 소요 시간, 멈춘 시간, 문자열 길이
	int pt, ppt = 0, resume = 0, qe = 0;
	int short_totalscore = 0, stop = 1;        //짧은글 게임 점수 누적, 시간 출력 스위치
	float max_spd = 0;               //최고 타자 속도
	unsigned int cnt = 0;
	int error = 0;          //문자열 인덱스, 문자열 비교시 오류 갯수
	char input[SHORT_MAX_N], ch;     //입력 받는 배열, 입력 받는 문자 저장
	char ran[SHORT_LINE] = { 0 };    //출력 여부 확인용 배열 (한 번 출력된 것은 1로 변경, 0인 경우만 출력한다)

	game2_screen(level);
	waiting();
	sent_clear();
	srand((unsigned)time(NULL));
	while (i < SHORT_LINE) {
		int a;
		a = rand_print(ran, &len);  //랜덤 숫자 선택 및 문제 출력 함수
		if (ran[a] != 1) {
			sstart = start = time(NULL);
			while (1) {
				if (time(0) >= sstart) {
					if (stop) {
						gotoxy(6, 4);
						CursorView(FALSE);
						printf("남은 시간 : %d초  ", SNORMALTIME - (time(0) - sstart) + ppt);      //잔여 시간 출력
						if (timeattack(sstart, ppt, SNORMALTIME) == 1) {
							cal_timeover(SNORMALTIME, SHORT_LINE, i + 1, &max_spd, 0, 0);
							sent_clear();
							clear_cnt(&cnt, &error);
							gap = 0;
							break;
						}
					}
					else {
						pause(&pt, &resume, &qe, 32);
						ppt += pt;
						if (resume == 1) {
							start = time(0);
							stop = 1;
						}
						else
							break;
					}
					gotoxy(8, 28);
				}
				if (_kbhit()) {
					gotoxy(8 + cnt, 28);
					ch = _getch();
					swrite(ch, a, &cnt, input);
					if (ch == 27) {  //esc 키
						end = time(NULL);
						gap += end - start;
						stop = 0;
					}
				}
				textcolor(15);
				if (cnt >= len) {
					end = time(0);
					gap += end - start;
					serror_cnt(a, input, len, &error);  //오타 수 세기
					if (short_compare(normal[a], input, len)) {
						score_short(gap, SNORMALTIME, &short_totalscore);
					}
					else {
						score_short(SNORMALTIME, SNORMALTIME, &short_totalscore);  //오타 있으면 점수 0 위해 소요 시간 제한시간으로 초기화
					}
					cal_short(gap, error, SHORT_LINE, i + 1, &max_spd, len, 0, 1);
					sent_clear();
					clear_cnt(&cnt, &error);
					gap = 0;
					break;
				}
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) {  // 일시정지
					stop = 0;
					end = time(0);
					gap += end - start;
					pause(&pt, &resume, &qe, 32);
					ppt += pt;
					if (resume == 1) {
						start = time(0);
						stop = 1;
					}
					else
						break;
				}
			}
			ran[a] = 1;
			ppt = 0;
			i++;
		}
		else
			continue;
		if (qe == 1)
			break;
	}
	if (qe != 1)
	{
		sent_clear();
		gotoxy(10, 14);
		printf("이번 게임 점수는 %d점 입니다.", short_totalscore);
		gotoxy(10, 15);
		printf("잠시 후 자동으로 다음 레벨로 이동합니다.");
		Sleep(5000);
		clear_cnt(&cnt, &error);
		CursorView(TRUE);
		level += 1;
		short_hard();
	}
}

void short_hard() {
	int i = 0, sstart, start, end, gap = 0, len; //문장 진행도, 시간 측정 시작, 끝, 문장 당 소요 시간, 멈춘 시간, 문자열 길이
	int pt, ppt = 0, resume = 0, qe = 0;
	int short_totalscore = 0, stop = 1;        //짧은글 게임 점수 누적, 시간 출력 스위치
	float max_spd = 0;               //최고 타자 속도
	unsigned int cnt = 0;
	int error = 0;          //문자열 인덱스, 문자열 비교시 오류 갯수
	char input[SHORT_MAX_H], ch;     //입력 받는 배열, 입력 받는 문자 저장
	char ran[SHORT_LINE] = { 0 };    //출력 여부 확인용 배열 (한 번 출력된 것은 1로 변경, 0인 경우만 출력한다)

	game2_screen(level);
	waiting();
	sent_clear();
	srand((unsigned)time(NULL));
	while (i < SHORT_LINE) {
		int a;
		a = rand_print(ran, &len);  //랜덤 숫자 선택 및 문제 출력 함수
		if (ran[a] != 1) {
			sstart = start = time(NULL);
			while (1) {
				if (time(0) >= sstart) {
					if (stop) {
						gotoxy(6, 4);
						CursorView(FALSE);
						printf("남은 시간 : %d초  ", SHARDTIME - (time(0) - sstart) + ppt);      //잔여 시간 출력
						if (timeattack(sstart, ppt, SHARDTIME) == 1) {
							cal_timeover(SHARDTIME, SHORT_LINE, i + 1, &max_spd, 0, 0);
							sent_clear();
							clear_cnt(&cnt, &error);
							gap = 0;
							break;
						}
					}
					else {
						pause(&pt, &resume, &qe, 32);
						ppt += pt;
						if (resume == 1) {
							start = time(0);
							stop = 1;
						}
						else
							break;
					}
					gotoxy(8, 28);
				}
				if (_kbhit()) {
					gotoxy(8 + cnt, 28);
					ch = _getch();
					swrite(ch, a, &cnt, input);
					if (ch == 27) {  //esc 키
						end = time(NULL);
						gap += end - start;
						stop = 0;
					}
				}
				textcolor(15);
				if (cnt >= len) {
					end = time(0);
					gap += end - start;
					serror_cnt(a, input, len, &error);  //오타 수 세기
					if (short_compare(hard[a], input, len)) {
						score_short(gap, SHARDTIME, &short_totalscore);
					}
					else {
						score_short(SHARDTIME, SHARDTIME, &short_totalscore);  //오타 있으면 점수 0 위해 소요 시간 제한시간으로 초기화
					}
					cal_short(gap, error, SHORT_LINE, i + 1, &max_spd, len, 0, 1);
					sent_clear();
					clear_cnt(&cnt, &error);
					gap = 0;
					break;
				}
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) {  // 일시정지
					stop = 0;
					end = time(0);
					gap += end - start;
					pause(&pt, &resume, &qe, 32);
					ppt += pt;
					if (resume == 1) {
						start = time(0);
						stop = 1;
					}
					else
						break;
				}
			}
			ran[a] = 1;
			ppt = 0;
			i++;
		}
		else
			continue;
		if (qe == 1)
			break;
	}
	if (qe != 1)
	{
		sent_clear();
		gotoxy(10, 14);
		printf("이번 게임 점수는 %d점 입니다.", short_totalscore);
		CursorView(TRUE);
		ask_restart();
	}
}

void bomb_easy() {
	int i = 0, sstart, start, end, gap = 0, len;     // 문장 진행도  /  시간 측정 시작, 끝, 문장 당 소요 시간  /  문자열 길이
	int pt, ppt = 0, resume = 0, qe = 0, stop = 1;    // 일시정지 변수
	int short_totalscore = 0;                // 짧은글 게임 점수 누적
	float max_spd = 0;                       // 최고 타자 속도
	int cnt = 0, bomb_cnt = 0, error = 0;    // 문자열 인덱스  /  폭탄 출력 개수  /  입력 값 중 오류 갯수

	char input[SHORT_MAX_E], ch;             // 입력값 저장 배열  /  입력 받는 문자 저장
	char ran[SHORT_LINE] = { 0 };            // 출력 여부 확인 (랜덤출력에 활용, 출력됨 = 1)
	char bombbuf[25], bombinp[25];           // 폭탄 문자열 배열  /  폭탄 입력값 저장 배열

	game2_screen_sp(level);                  // 난이도별 화면 출력
	waiting();
	sent_clear();
	srand((unsigned)time(NULL));

	while (i < SHORT_LINE) {
		int a, j, k = 0;                     // 랜덤 숫자  /  반복문 카운트  /  폭탄 위치 찾기용 변수, 
		a = rand() % SHORT_LINE;
		len = strlen(easy[a]);

		if (ran[a] != 1) {                   // 출력 안된 문장들만 출력
			if (rand() % 2 == 1 && bomb_cnt < 5) {         // 폭탄 5개만 출력
				gotoxy(8, 14);
				puts(easy[a]);
				for (j = 0; j < len; j++) {                // 폭탄 위치 찾기
					if (easy[a][j] == ebomb[a][k] && easy[a][j + 1] == ebomb[a][k + 1]) {
						k += 1;
					}
					if (k == 3) {
						strcpy(bombbuf, ebomb[a]);         // 폭탄 문자열 만들기
						strcat(bombbuf, ebomb[a]);
						strcat(bombbuf, ebomb[a]);
						gotoxy(8 + j - 2, 14);             // 폭탄 문자열 출력
						textcolor(RED);
						puts(ebomb[a]);
						textcolor(WHITE);
						gotoxy(8, 28);
						printf("해체 키워드를 입력하세요(띄어쓰기없이3번): ");
						sstart = time(0);
						while (1) {
							if (time(0) >= sstart) {        // 잔여 시간 출력 & 일시정지
								if (stop) {
									gotoxy(6, 4);
									CursorView(FALSE);
									printf("폭탄 제거 남은 시간 : %d초  ", BOMBEASY - (time(0) - sstart) + ppt);
									if (timeattack(sstart, ppt, BOMBEASY) == 1) {
										short_totalscore -= 10;
										sent_clear();
										clear_cnt(&cnt, &error);
										bomb_cnt++;
										k = 4;
										break;
									}
								}
								else {
									pause(&pt, &resume, &qe, 32);
									ppt += pt;
									if (resume == 1) {
										stop = 1;
									}
									else {
										k = 4;
										break;
									}
								}
								gotoxy(8, 28);
							}
							if (_kbhit()) {                // 키보드 입력이 생기면 비교 및 입력
								gotoxy(50 + cnt, 28);
								ch = _getch();
								if (ch == 27) {            //일시정지 키
									stop = 0;
								}
								if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
									|| ch == ' ' || ch == '.' || ch == ',' || ch == '\'') {
									if (ch == bombbuf[cnt]) {     // 맞으면 초록색 출력
										textcolor(10);
										printf("%c", ch);
										bombinp[cnt] = ch;
										cnt++;
									}
									else {                        // 틀리면 빨강색 출력
										textcolor(12);
										printf("%c", ch);
										bombinp[cnt] = ch;
										cnt++;
									}
								}
								if (ch == 13) {
									bombinp[cnt] = '\0';
									cnt++;
								}
								if (ch == 8) {
									if (cnt > 0) {
										cnt--;
										printf("\b \b");
									}
								}
							}
							textcolor(15);
							for (int j = 0; j < strlen(bombbuf); j++) {      // 오타 수 세기
								if (bombbuf[j] != bombinp[j])
									error++;
							}
							if (cnt >= strlen(bombbuf) + 1) {
								if (bomb_cmp(bombbuf, bombinp, a, &cnt, &error) == 1) {
									bomb_cnt++;
									gotoxy(40, 4);
									printf("폭탄 : %d%/5   ", bomb_cnt);
									gotoxy(8, 28);
									printf("                                                                  ");
									gotoxy(8, 29);
									printf("           ");
									gotoxy(8, 28);
									k = 4;
									break;
								}
								else {
									gotoxy(8, 28);
									printf("해체 키워드를 입력하세요(띄어쓰기없이3번):                        ");
									gotoxy(8, 29);
									printf("           ");
								}
								clear_cnt(&cnt, &error);
								continue;
							}
						}
					}
					else
						continue;
				}
				if (qe == 1)
					break;
			}
			gotoxy(8, 14);                   // 폭탄 제거 후 일반 모드
			puts(easy[a]);
			sstart = start = time(NULL);

			while (1) {
				if (time(0) >= sstart) {
					if (stop) {
						gotoxy(6, 4);
						CursorView(FALSE);
						printf("남은 시간 : %d초           ", SEASYTIME - (time(0) - sstart) + ppt);      //잔여 시간 출력
						if (timeattack(sstart, ppt, SEASYTIME) == 1) {
							cal_timeover(SEASYTIME, SHORT_LINE, i + 1, &max_spd, 0, 0);
							sent_clear();
							clear_cnt(&cnt, &error);
							gap = 0;
							break;
						}
					}
					else {
						pause(&pt, &resume, &qe, 32);
						ppt += pt;
						if (resume == 1) {
							start = time(0);
							stop = 1;
						}
						else
							break;
					}
					gotoxy(8, 28);
				}
				if (_kbhit()) {
					gotoxy(8 + cnt, 28);
					ch = _getch();
					swrite(ch, a, &cnt, input);
					if (ch == 27) {          // 일시정지
						end = time(NULL);
						gap += end - start;
						stop = 0;
					}
				}
				textcolor(15);
				if (cnt >= len) {
					end = time(0);
					gap += end - start;
					serror_cnt(a, input, len, &error);  //오타 수 세기
					if (short_compare(easy[a], input, len)) {
						score_short(gap, SEASYTIME, &short_totalscore);
					}
					else {
						score_short(SEASYTIME, SEASYTIME, &short_totalscore);
					}
					cal_short(gap, error, SHORT_LINE, i + 1, &max_spd, len, 0, 1);
					sent_clear();
					clear_cnt(&cnt, &error);
					gap = 0;
					break;
				}
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) {              // 일시정지
					end = time(0);
					gap += end - start;
					stop = 0;
					pause(&pt, &resume, &qe, 32);
					ppt += pt;
					if (resume == 1) {
						start = time(0);
						stop = 1;
					}
					else
						break;
				}
			}
			ran[a] = 1;
			ppt = 0;
			i++;
		}
		else
			continue;
		if (qe == 1)
			break;
	}
	if (qe != 1) {	// 점수 출력 후 다음 레벨 자동 이동
		sent_clear();
		gotoxy(10, 14);
		printf("이번 게임 점수는 %d점 입니다.", short_totalscore);
		gotoxy(10, 15);
		printf("잠시 후 자동으로 다음 레벨로 이동합니다.");
		Sleep(5000);
		clear_cnt(&cnt, &error);
		level += 1;
		bomb_normal();
	}
}

void bomb_normal() {
	int i = 0, sstart, start, end, gap = 0, len;     // 문장 진행도  /  시간 측정 시작, 끝, 문장 당 소요 시간  /  문자열 길이
	int pt, ppt = 0, resume = 0, qe = 0, stop = 1;    // 일시정지 변수
	int short_totalscore = 0;                // 짧은글 게임 점수 누적
	float max_spd = 0;                       // 최고 타자 속도
	int cnt = 0, bomb_cnt = 0, error = 0;    // 문자열 인덱스  /  폭탄 출력 개수  /  입력 값 중 오류 갯수

	char input[SHORT_MAX_N], ch;             // 입력값 저장 배열  /  입력 받는 문자 저장
	char ran[SHORT_LINE] = { 0 };            // 출력 여부 확인 (랜덤출력에 활용, 출력됨 = 1)
	char bombbuf[25], bombinp[25];           // 폭탄 문자열 배열  /  폭탄 입력값 저장 배열

	game2_screen_sp(level);                  // 난이도별 화면 출력
	waiting();
	sent_clear();
	srand((unsigned)time(NULL));

	while (i < SHORT_LINE) {
		int a, j, k = 0;                     // 랜덤 숫자  /  반복문 카운트  /  폭탄 위치 찾기용 변수, 
		a = rand() % SHORT_LINE;
		len = strlen(normal[a]);

		if (ran[a] != 1) {                   // 출력 안된 문장들만 출력
			if (rand() % 2 == 1 && bomb_cnt < 5) {         // 폭탄 5개만 출력
				gotoxy(8, 14);
				puts(normal[a]);
				for (j = 0; j < len; j++) {                // 폭탄 위치 찾기
					if (normal[a][j] == nbomb[a][k] && normal[a][j + 1] == nbomb[a][k + 1]) {
						k += 1;
					}
					if (k == 3) {
						strcpy(bombbuf, nbomb[a]);    // 폭탄 문자열 만들기
						strcat(bombbuf, nbomb[a]);
						strcat(bombbuf, nbomb[a]);
						gotoxy(8 + j - 2, 14);        // 폭탄 문자열 출력
						textcolor(RED);
						puts(nbomb[a]);
						textcolor(WHITE);
						gotoxy(8, 28);
						printf("해체 키워드를 입력하세요(띄어쓰기없이3번): ");
						sstart = time(0);
						while (1) {
							if (time(0) >= sstart) {    // 잔여 시간 출력 & 일시정지
								if (stop) {
									gotoxy(6, 4);
									CursorView(FALSE);
									printf("폭탄 제거 남은 시간 : %d초  ", BOMBNORMAL - (time(0) - sstart) + ppt);
									if (timeattack(sstart, ppt, BOMBNORMAL) == 1) {
										short_totalscore -= 10;
										sent_clear();
										clear_cnt(&cnt, &error);
										bomb_cnt++;
										gap = 0;
										k = 4;
										break;
									}
								}
								else {
									pause(&pt, &resume, &qe, 32);
									ppt += pt;
									if (resume == 1) {
										stop = 1;
									}
									else {
										k = 4;
										break;
									}
								}
								gotoxy(8, 28);
							}
							if (_kbhit()) {             // 키보드 입력이 생기면 비교 및 입력
								gotoxy(50 + cnt, 28);
								ch = _getch();
								if (ch == 27) {         //일시정지 키
									stop = 0;
								}
								if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
									|| ch == ' ' || ch == '.' || ch == ',' || ch == '\'') {
									if (ch == bombbuf[cnt]) {     // 맞으면 초록색 출력
										textcolor(10);
										printf("%c", ch);
										bombinp[cnt] = ch;
										cnt++;
									}
									else {                        // 틀리면 빨강색 출력
										textcolor(12);
										printf("%c", ch);
										bombinp[cnt] = ch;
										cnt++;
									}
								}
								if (ch == 13) {
									bombinp[cnt] = '\0';
									cnt++;
								}
								if (ch == 8) {
									if (cnt > 0) {
										cnt--;
										printf("\b \b");
									}
								}
							}
							textcolor(15);
							for (int j = 0; j < strlen(bombbuf); j++) {      //오타 수 세기
								if (bombbuf[j] != bombinp[j])
									error++;
							}
							if (cnt >= strlen(bombbuf) + 1) {
								if (bomb_cmp(bombbuf, bombinp, a, &cnt, &error) == 1) {
									bomb_cnt++;
									gotoxy(40, 4);
									printf("폭탄 : %d%/5   ", bomb_cnt);
									gotoxy(8, 28);
									printf("                                                                  ");
									gotoxy(8, 29);
									printf("           ");
									gotoxy(8, 28);
									k = 4;
									break;
								}
								else {
									gotoxy(8, 28);
									printf("해체 키워드를 입력하세요(띄어쓰기없이3번):                        ");
									gotoxy(8, 29);
									printf("           ");
								}
								clear_cnt(&cnt, &error);
								continue;
							}
						}
					}
					else
						continue;
				}
				if (qe == 1)
					break;
			}
			gotoxy(8, 14);                   // 폭탄 제거 후 일반 모드
			puts(normal[a]);
			sstart = start = time(NULL);

			while (1) {
				if (time(0) >= sstart) {
					if (stop) {
						gotoxy(6, 4);
						CursorView(FALSE);
						printf("남은 시간 : %d초           ", SNORMALTIME - (time(0) - sstart) + ppt);      //잔여 시간 출력
						if (timeattack(sstart, ppt, SNORMALTIME) == 1) {
							cal_timeover(SNORMALTIME, SHORT_LINE, i + 1, &max_spd, 0, 0);
							sent_clear();
							clear_cnt(&cnt, &error);
							gap = 0;
							break;
						}
					}
					else {
						pause(&pt, &resume, &qe, 32);
						ppt += pt;
						if (resume == 1) {
							start = time(0);
							stop = 1;
						}
						else
							break;
					}
					gotoxy(8, 28);
				}
				if (_kbhit()) {
					gotoxy(8 + cnt, 28);
					ch = _getch();
					swrite(ch, a, &cnt, input);
					if (ch == 27) {          // 일시정지
						end = time(NULL);
						gap += end - start;
						stop = 0;
					}
				}
				textcolor(15);
				if (cnt >= len) {
					end = time(0);
					gap += end - start;
					serror_cnt(a, input, len, &error);  // 오타 수 세기
					if (short_compare(normal[a], input, len)) {
						score_short(gap, SNORMALTIME, &short_totalscore);
					}
					else {
						score_short(SNORMALTIME, SNORMALTIME, &short_totalscore);
					}
					cal_short(gap, error, SHORT_LINE, i + 1, &max_spd, len, 0, 1);
					sent_clear();
					clear_cnt(&cnt, &error);
					gap = 0;
					break;
				}
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) {              // 일시정지
					end = time(0);
					gap += end - start;
					stop = 0;
					pause(&pt, &resume, &qe, 32);
					ppt += pt;
					if (resume == 1) {
						start = time(0);
						stop = 1;
					}
					else
						break;
				}
			}
			ran[a] = 1;
			ppt = 0;
			i++;
		}
		else
			continue;
		if (qe == 1)
			break;
	}
	if (qe != 1) {	// 점수 출력 후 다음 레벨 자동 이동
		sent_clear();
		gotoxy(10, 14);
		printf("이번 게임 점수는 %d점 입니다.", short_totalscore);
		gotoxy(10, 15);
		printf("잠시 후 자동으로 다음 레벨로 이동합니다.");
		Sleep(5000);
		clear_cnt(&cnt, &error);
		level += 1;
		bomb_hard();
	}
}

void bomb_hard() {
	int i = 0, sstart, start, end, gap = 0, len;     // 문장 진행도  /  시간 측정 시작, 끝, 문장 당 소요 시간  /  문자열 길이
	int pt, ppt = 0, resume = 0, qe = 0, stop = 1;    // 일시정지 변수
	int short_totalscore = 0;                // 짧은글 게임 점수 누적
	float max_spd = 0;                       // 최고 타자 속도
	int cnt = 0, bomb_cnt = 0, error = 0;    // 문자열 인덱스  /  폭탄 출력 개수  /  입력 값 중 오류 갯수

	char input[SHORT_MAX_H], ch;             // 입력값 저장 배열  /  입력 받는 문자 저장
	char ran[SHORT_LINE] = { 0 };            // 출력 여부 확인 (랜덤출력에 활용, 출력됨 = 1)
	char bombbuf[25], bombinp[25];           // 폭탄 문자열 배열  /  폭탄 입력값 저장 배열

	game2_screen_sp(level);
	waiting();
	sent_clear();
	srand((unsigned)time(NULL));

	while (i < SHORT_LINE) {
		int a, j, k = 0;                     // 랜덤 숫자  /  반복문 카운트  /  폭탄 위치 찾기용 변수, 
		a = rand() % SHORT_LINE;
		len = strlen(hard[a]);

		if (ran[a] != 1) {                   // 출력 안된 문장들만 출력
			if (rand() % 2 == 1 && bomb_cnt < 5) {         // 폭탄 5개만 출력
				gotoxy(8, 14);
				puts(hard[a]);
				for (j = 0; j < len; j++) {                // 폭탄 위치 찾기
					if (hard[a][j] == hbomb[a][k] && hard[a][j + 1] == hbomb[a][k + 1]) {
						k += 1;
					}
					if (k == 3) {
						strcpy(bombbuf, hbomb[a]);    // 폭탄 문자열 만들기
						strcat(bombbuf, hbomb[a]);
						strcat(bombbuf, hbomb[a]);
						gotoxy(8 + j - 2, 14);        // 폭탄 문자열 출력
						textcolor(RED);
						puts(hbomb[a]);
						textcolor(WHITE);
						gotoxy(8, 28);
						printf("해체 키워드를 입력하세요(띄어쓰기없이3번): ");
						sstart = time(0);
						while (1) {
							if (time(0) >= sstart) {    // 잔여 시간 출력 & 일시정지
								if (stop) {
									gotoxy(6, 4);
									CursorView(FALSE);
									printf("폭탄 제거 남은 시간 : %d초  ", BOMBHARD - (time(0) - sstart) + ppt);
									if (timeattack(sstart, ppt, BOMBHARD) == 1) {
										short_totalscore -= 10;
										sent_clear();
										clear_cnt(&cnt, &error);
										bomb_cnt++;
										gap = 0;
										k = 4;
										break;
									}
								}
								else {
									pause(&pt, &resume, &qe, 32);
									ppt += pt;
									if (resume == 1) {
										stop = 1;
									}
									else {
										k = 4;
										break;
									}
								}
								gotoxy(8, 28);
							}
							if (_kbhit()) {             // 키보드 입력이 생기면 비교 및 입력
								gotoxy(50 + cnt, 28);
								ch = _getch();
								if (ch == 27) {         //일시정지 키
									stop = 0;
								}
								if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
									|| ch == ' ' || ch == '.' || ch == ',' || ch == '\'') {
									if (ch == bombbuf[cnt]) {     // 맞으면 초록색 출력
										textcolor(10);
										printf("%c", ch);
										bombinp[cnt] = ch;
										cnt++;
									}
									else {                        // 틀리면 빨강색 출력
										textcolor(12);
										printf("%c", ch);
										bombinp[cnt] = ch;
										cnt++;
									}
								}
								if (ch == 13) {
									bombinp[cnt] = '\0';
									cnt++;
								}
								if (ch == 8) {
									if (cnt > 0) {
										cnt--;
										printf("\b \b");
									}
								}
							}
							textcolor(15);
							for (int j = 0; j < strlen(bombbuf); j++) {      //오타 수 세기
								if (bombbuf[j] != bombinp[j])
									error++;
							}
							if (cnt >= strlen(bombbuf) + 1) {
								if (bomb_cmp(bombbuf, bombinp, a, &cnt, &error) == 1) {
									bomb_cnt++;
									gotoxy(40, 4);
									printf("폭탄 : %d%/5   ", bomb_cnt);
									gotoxy(8, 28);
									printf("                                                                  ");
									gotoxy(8, 29);
									printf("           ");
									gotoxy(8, 28);
									k = 4;
									break;
								}
								else {
									gotoxy(8, 28);
									printf("해체 키워드를 입력하세요(띄어쓰기없이3번):                        ");
									gotoxy(8, 29);
									printf("           ");
								}
								clear_cnt(&cnt, &error);
								continue;
							}
						}
					}
					else
						continue;
				}
				if (qe == 1)
					break;
			}
			gotoxy(8, 14);                   // 폭탄 제거 후 일반 모드
			puts(hard[a]);
			sstart = start = time(NULL);

			while (1) {
				if (time(0) >= sstart) {
					if (stop) {
						gotoxy(6, 4);
						CursorView(FALSE);
						printf("남은 시간 : %d초           ", SHARDTIME - (time(0) - sstart) + ppt);      //잔여 시간 출력
						if (timeattack(sstart, ppt, SHARDTIME) == 1) {
							cal_timeover(SHARDTIME, SHORT_LINE, i + 1, &max_spd, 0, 0);
							sent_clear();
							clear_cnt(&cnt, &error);
							gap = 0;
							break;
						}
					}
					else {
						pause(&pt, &resume, &qe, 32);
						ppt += pt;
						if (resume == 1) {
							start = time(0);
							stop = 1;
						}
						else
							break;
					}
					gotoxy(8, 28);
				}
				if (_kbhit()) {
					gotoxy(8 + cnt, 28);
					ch = _getch();
					swrite(ch, a, &cnt, input);
					if (ch == 27) {          // 일시정지
						end = time(NULL);
						gap += end - start;
						stop = 0;
					}
				}
				textcolor(15);
				if (cnt >= len) {
					end = time(0);
					gap += end - start;
					serror_cnt(a, input, len, &error);  //오타 수 세기
					if (short_compare(hard[a], input, len)) {
						score_short(gap, SHARDTIME, &short_totalscore);
					}
					else {
						score_short(SHARDTIME, SHARDTIME, &short_totalscore);
					}
					cal_short(gap, error, SHORT_LINE, i + 1, &max_spd, len, 0, 1);
					sent_clear();
					clear_cnt(&cnt, &error);
					gap = 0;
					break;
				}
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) {              // 일시정지
					end = time(0);
					gap += end - start;
					stop = 0;
					pause(&pt, &resume, &qe, 32);
					ppt += pt;
					if (resume == 1) {
						start = time(0);
						stop = 1;
					}
					else
						break;
				}
			}
			ran[a] = 1;
			ppt = 0;
			i++;
		}
		else
			continue;
		if (qe == 1)
			break;
	}
	if (qe != 1) {
		sent_clear();
		gotoxy(10, 14);
		printf("이번 게임 점수는 %d점 입니다.", short_totalscore);
		CursorView(TRUE);
		ask_restart();
	}
}

int rand_print(char* ran, int* len) {
	int r;
	while (1) {
		r = rand() % SHORT_LINE;     // 랜덤 숫자 선택
		if (ran[r] != 1) {           // 나왔던 문장(1)이면 다시 선택, 아니면(0) 출력 및 게임 시작
			if (level == 0 || level == 1) {
				*len = strlen(easy[r]);
				gotoxy(8, 14);
				puts(easy[r]);
			}
			else if (level == 2) {
				*len = strlen(normal[r]);
				gotoxy(8, 14);
				puts(normal[r]);
			}
			else {
				*len = strlen(hard[r]);
				gotoxy(8, 14);
				puts(hard[r]);
			}
			gotoxy(8, 28);
			return r;
		}
		else
			continue;
	}
}
void serror_cnt(int a, char input[], int len, int* error) {
	if (level == 0 || level == 1) {
		for (int j = 0; j < len; j++) {
			if (easy[a][j] != input[j])
				(*error)++;
		}
	}
	else if (level == 2) {
		for (int j = 0; j < len; j++) {
			if (normal[a][j] != input[j])
				(*error)++;
		}
	}
	else {
		for (int j = 0; j < len; j++) {
			if (hard[a][j] != input[j])
				(*error)++;
		}
	}
}
void swrite(char ch, int a, int* cnt, char input[]) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
		|| ch == ' ' || ch == '.' || ch == ',' || ch == '\'') {
		if (level == 0 || level == 1) {
			if (ch == easy[a][*cnt]) {
				textcolor(10);
				printf("%c", ch);
				input[*cnt] = ch;
				(*cnt)++;
			}
			else {
				textcolor(12);
				printf("%c", ch);
				input[*cnt] = ch;
				(*cnt)++;
			}
		}
		if (level == 2) {
			if (ch == normal[a][*cnt]) {
				textcolor(10);
				printf("%c", ch);
				input[*cnt] = ch;
				(*cnt)++;
			}
			else {
				textcolor(12);
				printf("%c", ch);
				input[*cnt] = ch;
				(*cnt)++;
			}
		}
		if (level == 3) {
			if (ch == hard[a][*cnt]) {
				textcolor(10);
				printf("%c", ch);
				input[*cnt] = ch;
				(*cnt)++;
			}
			else {
				textcolor(12);
				printf("%c", ch);
				input[*cnt] = ch;
				(*cnt)++;
			}
		}
	}                         // 엔터는 아예 인식 안하도록 설정
	if (ch == 8) {
		if (*cnt > 0) {
			(*cnt)--;
			printf("\b \b");
		}

	}
}
int short_compare(const char buffer[], const char input[], int len) {
	if (!strncmp(buffer, input, len)) {
		gotoxy(8, 29);
		printf("Good");
		return 1;
	}
	else {
		gotoxy(8, 29);
		printf("Bad");
		return 0;
	}
}
int bomb_cmp(char* bombbuf, char* bombinp, int a, int* cnt, int* error) {
	if (!strncmp(bombbuf, bombinp, strlen(bombbuf) + 1)) {
		gotoxy(8, 29);
		textcolor(15);
		printf("Good!");
		Sleep(500);
		*cnt = 0;
		*error = 0;
		return 1;
	}
	else {
		gotoxy(8, 29);
		textcolor(15);
		printf("Try again!");
		Sleep(500);
		*cnt = 0;
		*error = 0;
		return 0;
	}
}
int timeattack(int start, int ppt, int limit) {
	if (time(NULL) >= start + limit + ppt) {
		gotoxy(8, 18);
		printf("TIME OVER!");
		gotoxy(8, 28);
		printf("                                                                  ");
		gotoxy(8, 28);
		Sleep(1000);
		return 1;
	}
}
void clear_cnt(int* cnt, int* error) {
	*cnt = 0;
	*error = 0;
}
void cal_short(int timespent, int error, int num, int count, float* maxsp, int len, int px, int py)
{
	int correct;
	float speed, accuracy, processivity;

	correct = len - error;

	if (timespent != 0) {//걸린시간이 0이 아닐때만 계산
		speed = ((len) / (float)(timespent)) * 60;
		/*speed=((correct)/(float)(timespent))*60 하면 (정타수/걸린시간)*60으로 = 분당 정타타자속도를 잴 수 있다*/

		if (speed > *maxsp) {
			*maxsp = speed;
		}
	}

	accuracy = ((float)correct / len) * 100;
	processivity = ((float)(count) / num) * 100;

	gotoxy(79 + px, 22 + py);
	printf("                     ");
	gotoxy(79 + px, 23 + py);
	printf("                   ");
	gotoxy(79 + px, 24 + py);
	printf("                     ");
	gotoxy(79 + px, 25 + py);
	printf("                     ");
	gotoxy(79 + px, 26 + py);
	printf("                     ");
	gotoxy(79 + px, 27 + py);
	printf("                     ");

	if (timespent == 0) {
		gotoxy(79 + px, 22 + py);
		printf("타자속도: too fast");
	}
	else {
		gotoxy(79 + px, 22 + py);
		printf("타자속도: %.f (타)", speed);
	}
	gotoxy(79 + px, 23 + py);
	printf("최고타자: %.f (타)", *maxsp);
	gotoxy(79 + px, 24 + py);
	printf("정확도 : %.f (%%)", accuracy);
	gotoxy(79 + px, 25 + py);
	printf("오타수: %d (개)", error);
	gotoxy(79 + px, 26 + py);
	printf("진행도: %.1f (%%)", processivity);
	gotoxy(79 + px, 27 + py);
	printf("걸린시간: %d (초)", timespent);
	gotoxy(79 + px, 28 + py);
	Sleep(1000);
}
void sent_clear(void)
{
	gotoxy(6, 4);
	printf("                                                                  ");
	gotoxy(8, 14);
	printf("                                                                  ");
	gotoxy(8, 15);
	printf("                                                                  ");
	gotoxy(8, 16);
	printf("                                                                  ");
	gotoxy(8, 18);
	printf("                                                                  ");
	gotoxy(5, 27);
	printf("                                                                  ");
	gotoxy(5, 28);
	printf("                                                                  ");
	gotoxy(5, 29);
	printf("                                                                  ");
	gotoxy(8, 28);
}
