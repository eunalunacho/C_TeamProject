#include "common.h"

char word_begin[WORDMAX][WORD_SIZE] = { "apple", "ant", "lake","social","allow","correct","custom","order","fair","pain", //줄과 행으로 나머지 공간 자동 초기화 /0으로 채워짐
"link","aloud","price","stamp","rotate","turtle","wonder","ocean","shore","awake",
"however","item","raise","actual","direct","mean","trend","connect","scale","range",
"brick","uniform","earn","cartoon","dig","law","rub","period","even","respect",
"dialog","cotton","manner","expect","actor","loyal","attend","except","lift","receive",
"shake","bark","recent","crazy","future","hit","hope","most","report","sour",
"era","fight","moment","thick","history","cage","climb","intend","cheek","harm",
"smooth","shelf","image","silver","before","decide","such","along","return","century",
"common","guess","divide","rough","daily","luck","capital","insect","include","proper",
"audio","band","hide","still","issue","curve","stupid","booth","castle","contest",
"speech","garden","admire","mind","root","seed","army","local","final","loaf",
"blink","sink","gate","empty","swan","calm","bill","bow","avoid","nation" };

char word_medium[WORDMAX][WORD_SIZE] = { "between","anxious","toilet","project","method","article","valley","equal","commercial","attention",
"auditory","benefit","mushroom","belong","dessert","against","swallow","therefore","basement","decorate",
"departure","dozen","exchange","experience","difficult","straight","gesture","dictionary","hospital","request",
"example","chopstick","comfortable","cabbage","develop","advance","exercise","popular","relogion","already",
"kingdom","forward","although","culture","emperor","journey","anymore","challenge","believe","patient",
"principle","regular","movement","various","medicine","medical","pracice","escape","supply","amount",
"command","climate","succeed","abroad","ceramic","toward","compare","downtown","ground","handle",
"espouse","disdain","despise","sanction","disown","refute","ratify","appease","placate","adulate",
"advocate","revere","repulse","endorse","negate","affirm","justify","detest","loathe","vilify",
"champion","rebuff","interdict","object","renounce","allege","warrant","hosility","execrate","asperse",
"defender","inhibit","assent","demur","gainsay","assert","controvert","confirm","enmity","slander",
"flatter","consent","disapprove","except","dissent","disavow","confute","verify","validate","obloquy" };

char word_high[WORDMAX][WORD_SIZE] = { "delicious","acceptance", "according","photograph","mathematics","convenience","international","aggrandize","excoriate", "chastise",
"lambaste", "countenance", "vindicator", "advocator", "blandish", "ingratiate", "calumniate", "impassioned", "covetous", "analgesia",
"asperse", "opprobrium", "billingsgate", "vituperate", "traduce", "idolize", "abominate", "conciliate", "propitiate", "antipathy",
"antagonism", "animosity", "implacable", "relentless", "inexorable", "unrelenting", "corroborate", "authenticate", "vindicate", "controvert",
"disconfirm", "countenance", "scornful", "authentic", "fallacious", "specious", "stratagem", "subterfuge", "sequester", "eclipse",
"contradict", "disparage", "disdainful", "verifiable", "heterodox", "erroneous", "disingenuous", "ensconce", "comprehend", "comprehensive",
"disaffirm", "blaspheme", "contemptuous", "canonical", "factitious", "inconvincible", "equivocate", "apprehensive", "fathomable", "understandable",
"abnegate", "prodigious", "burlesque", "orthodox", "integrity", "rectitude", "prevaricate", "quibble", "puissant", "effervescent",
"approbate", "despicable", "travesty", "infallible", "truthfulness", "faithfulness", "inveigle", "disillusion", "promulgate", "obscure",
"validate", "contemptible", "opprobrious", "flawless", "veracity", "uprightness", "disenchant", "propagate", "disseminate", "acquaint",
"redoubtable", "ipprobrious", "ignominious", "faultless", "chicanery", "finesse", "reassured", "skeptical", "credulous", "demonstrate",
"macerate","emasculate","enfeeble","effeminate","strengthen","buttress","lackadaisical","incompetent","feckless","puissance" };

int start_time, end_time;
int i_word; //인덱스 값 
int l;//문자열 길이

int pt_word = 0; //일시정지 시간

int word_total_score = 0; //낱말 연습 총 점수
int word_each_score; //각 단어 별로 얻은 점수

int T;//각 단어 입력하는 데 걸린 시간
int wn = 0; //출력된 단어 갯수

char overlap_word[WORDMAX] = { "|0" }; //중복 없애는 배열 (0이면 출력, 이미 나온배열은 1로 설정해 출력 x)

extern int level; //사용자가 선택한 난이도
extern int restart; //사용자로부터 입력받은 재시작 여부 값

void wordgame_main() {

	srand(time(0));

	if (level == 1) {
		printword();
		scanword(word_begin);
	}
	else if (level == 2) {
		printword();
		scanword(word_medium);
	}
	else if (level == 3) {
		printword();
		scanword(word_high);
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

void printword() {
	int check = WORDMAX;

	while (1) {
		i_word = rand() % WORDMAX;
		if (overlap_word[i_word] != 1) {
			overlap_word[i_word] = 1;
			break;
		}
	}

	gotoxy(35, 27);
	printf("                           ");
	gotoxy(35, 13);
	printf("                        ");

	start_time = time(0);

	if (level == 1) {
		gotoxy(35, 13);
		l = strlen(word_begin[i_word]);
		printf("%s ", word_begin[i_word]);
	}
	if (level == 2) {
		gotoxy(35, 13);
		l = strlen(word_medium[i_word]);
		printf("%s ", word_medium[i_word]);
	}
	if (level == 3) {
		gotoxy(35, 13);
		l = strlen(word_high[i_word]);
		printf("%s ", word_high[i_word]);
	}
}

void scanword(const char wordlevel[][WORD_SIZE]) {
	// 매 게임마다 30개 단어 출력
	int word_num = 30;
	int j = 0;
	char  ch, word_input[WORD_SIZE]; //사용자 입력 배열
	int resume = 0, qe = 0;

	while (1) {
		if (time(0) >= start_time) {    //잔여 시간 출력
			CursorView(FALSE);
			gotoxy(6, 4);
			printf("남은 시간 : %d초  ", TIME_LIMIT - (time(0) - start_time - pt_word));
		}
		if (wn >= word_num) {
			gotoxy(6, 4);
			printf("                      ");
			gotoxy(35, 13);
			printf("                                  ");

			gotoxy(31, 10);
			printf("---게 임 종 료---");
			gotoxy(32, 12);
			textcolor(14);
			printf("최종 점수: %d점", word_total_score);
			textcolor(15);
			if (level < 3) {
				gotoxy(20, 16);
				printf("*아무키나 누르시면 다음레벨로 넘어갑니다*");
			}
			else if (level == 3) {
				gotoxy(30, 16);
				printf("*아무키나 눌러주세요*");
			}

			word_total_score = 0;
			wn = 0;
			pt_word = 0;
			for (int m = 0; m < WORDMAX; m++) {
				overlap_word[m] = 0;
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
				game1_screen(level);
				waiting();
			}
			wordgame_main();
			return 0;
		}
		if (time(0) == start_time + TIME_LIMIT + pt_word) {

			end_time = time(0);
			T = end_time - start_time - pt_word;
			j = 0;
			wn++;
			cal_word(T, word_input, wordlevel, word_num);

			printword();
			gotoxy(35, 27);
			pt_word = 0;
		}
		if (_kbhit()) {
			gotoxy(35 + j, 27);
			ch = _getch();
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				printf("%c", ch);
				word_input[j] = ch;
				j++;
			}
			if ((ch == 8) && (j != 0)) {
				printf("\b");
				j--;
				printf(" ");
				printf("\b");
			}
			if (ch == 27) {
				int pt_word_each = 0;
				pause(&pt_word_each, &resume, &qe, 32);
				pt_word += pt_word_each;

				if (resume == 1) {
					gotoxy(35, 27);
					continue;
				}
				if (qe == 1) {
					word_total_score = 0;
					wn = 0;
					pt_word = 0;
					CursorView(TRUE);
					break;
				}
			}

		}
		if (j >= l) {
			end_time = time(0);
			T = end_time - start_time - pt_word;
			if (!strncmp(wordlevel[i_word], word_input, l)) {
				wordscore(T);    //점수 계산
				word_total_score += word_each_score;     //단어게임 총점수 초기화					
			}
			wn++;
			cal_word(T, word_input, wordlevel, word_num);
			printword();
			gotoxy(35, 27);

			pt_word = 0;
			j = 0;
		}

	}
}

void wordscore(double n) {
	if (n < 1)
		word_each_score = 50;
	else if ((n >= 1) && (n < 2))
		word_each_score = 40;
	else if ((n >= 2) && (n < 3))
		word_each_score = 30;
	else if ((n >= 3) && (n < 4))
		word_each_score = 20;
	else if ((n >= 4) && (n < 7))
		word_each_score = 10;
}

void cal_word(int timespent, char* word_input, char answer[][WORD_SIZE], int num)
{
	int correct = 0;
	int error = 0;
	float speed, accuracy, processivity;
	int s;
	int len = strlen(answer[i_word]); // 문자열 길이

	for (s = 0; s < len; s++) //오타수 측정:
	{
		if (word_input[s] != answer[i_word][s])// 사용자입력 각각의 알파벳과 정답 알파벳을 비교해서 같지 않으면
		{
			error += 1;
		}
	}

	//오타가 아닌 정타수
	correct = len - error;

	//타자속도 : (타자수/걸린시간)*60 = 분당 타자속도
	speed = (len / (float)(timespent)) * 60;

	//정확도= 정타수/문자열의 길이 *100
	accuracy = ((float)correct / strlen(answer[i_word])) * 100;

	//진행도
	processivity = ((float)(wn) / num) * 100;

	if (time(0) == start_time + TIME_LIMIT + pt_word) {
		speed = 0;
	}

	//기존 출력 지우기
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

	//출력
	if (timespent <= 0)//걸린시간이 0이면
	{
		gotoxy(79, 22);
		printf("타자속도: too fast");
		gotoxy(79, 24);
		printf("정확도 : %.f (%%)", accuracy);
		gotoxy(79, 25);
		printf("오타수: %d (개)", error);
		gotoxy(79, 26);
		printf("진행도: %.1f (%%)", processivity);
		gotoxy(79, 28);
		printf("SCORE: %d ", word_total_score);
	}

	else {
		gotoxy(79, 22);
		printf("타자속도: %.f (타)", speed);
		gotoxy(79, 24);
		printf("정확도 : %.f (%%)", accuracy);
		gotoxy(79, 25);
		printf("오타수: %d (개)", error);
		gotoxy(79, 26);
		printf("진행도: %.1f (%%)", processivity);
		gotoxy(79, 28);
		printf("SCORE: %d ", word_total_score);
	}

	correct = 0;
	error = 0;
	accuracy = 0;
	speed = 0;

}

void CursorView(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}