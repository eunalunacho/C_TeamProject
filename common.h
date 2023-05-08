#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WORD_SIZE 15 //낱말연습- 행(가로)의 길이 15
#define WORDMAX 120 //낱말연습-열의 갯수=단어의 갯수-> 다 120개
#define TIME_LIMIT 7 //낱말연습-한계 시간 7초
#define TIME_LIMIT_RCP 5//가위바위보 한계 시간 5초

#define GREEN 10 //초록색 폰트
#define WHITE 15 //흰색 ''
#define RED 12 //붉은색 ''
#define LSIZE 100
#define LEASYTIME 300
#define LMIDTIME 180
#define LHARDTIME 120

#define SHORT_MAX_E 31
#define SHORT_MAX_N 51
#define SHORT_MAX_H 71
#define SHORT_LINE 20
#define SEASYTIME 35
#define SNORMALTIME 25
#define SHARDTIME 15
#define BOMBEASY 20
#define BOMBNORMAL 15
#define BOMBHARD 10

//void txt(void);

void gotoxy(int x, int y);
void textcolor(unsigned int);
void readfile(int linecount, int i);
void buildreadfile(int linecount, int i);
void gettext(char*);
void cal(int timespent, char* input, char* answer, int num, int* count, float* maxsp, int px, int py);
void compare(char*, char*, int, int, int, float*, int*, int, int, int);
int compare_house(char* texts, char* input, int z, int w, int timespent, float* maxsp, int* comp_count, int linecount, int, int);
void gettext(char*);
void adele_house(int*, int);
void maroon_house(int*, int);
 int longgame(int);
int buildhouse(int);
void pauselong(int* pt, int* resume, int* qe, int line);

//게임창들과 메뉴 관련
void title(int, int); //타이틀 출력
void ending_title(int x, int y);
void show_menu(int, int); //메인메뉴 출력
void game1_screen(int); // 낱말 연습 화면
void game2_screen(int); // 짧은 글 연습 화면
void game3_screen(int); // 긴 글 연습 화면
void game1_screen_sp(int); // 가위바위보 게임 화면
void game2_screen_sp(int); // 폭탄모드 화면
void game3_screen_sp(int); // 집 짓기 게임 화면
void game1_mode();// 낱말연습 모드메뉴 출력
void game2_mode();// 짧은 글 연습 모드메뉴 출력
void game3_mode();//긴 글 연습 모드메뉴 출력
int levelchoice_with_free(); // 무제한이 있는 난이도 선택
int levelchoice_without_free(); // 무제한이 없는 난이도 선택
void waiting();  // 게임창 시작하기전 대기화면
void score_short(int T, int limit_time, int* short_totalscore); //점수계산
void ask_restart();//재시작 여부 묻기
void pause(int* pt, int* resume, int* qe, int line); //일시정지 간단 버전

//낱말연습 함수들
void printword();
void wordgame_main();
void scanword(const char wordlevel[][WORD_SIZE]);
void wordscore(double n);
void cal_word(int timespent, char* input, char answer[][WORD_SIZE], int num);
void CursorView(char show);

void wordgame_main_rcp();
void printword_rcp();
void scanword_rcp(const char wordlevel[][WORD_SIZE]);
void wordscore_rcp(int);
int decision(int ascomputer, int asuser);
void rock_rcp(int, int);
void scissors_rcp(int, int);
void paper_rcp(int, int);
void cal_word_rcp(int timespent, char* word_input, char answer[][WORD_SIZE], int num);

//짧은글연습 함수들
void short_free();
void short_easy();
void short_normal();
void short_hard();
void bomb_easy();
void bomb_normal();
void bomb_hard();
int rand_print(char* ran, int* len);
int short_compare(const char easy[], const char input[], int len);
int bomb_cmp(char*, char*, int, int*, int*);
void clear_cnt(int* cnt, int* error);
void sent_clear(void);
void score_short(int T, int limit_time, int* short_totalscore);
void cal_short(int timespent, int error, int num, int count, float* maxsp, int len, int px, int py);
void cal_timeover(int timespent, int num, int count, float* maxsp, int px, int py);
int timeattack(int start, int ppt, int limit);
void serror_cnt(int a, char input[], int len, int* error);
void swrite(char ch, int a, int* cnt, char input[]);