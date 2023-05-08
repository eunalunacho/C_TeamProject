#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WORD_SIZE 15 //��������- ��(����)�� ���� 15
#define WORDMAX 120 //��������-���� ����=�ܾ��� ����-> �� 120��
#define TIME_LIMIT 7 //��������-�Ѱ� �ð� 7��
#define TIME_LIMIT_RCP 5//���������� �Ѱ� �ð� 5��

#define GREEN 10 //�ʷϻ� ��Ʈ
#define WHITE 15 //��� ''
#define RED 12 //������ ''
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

//����â��� �޴� ����
void title(int, int); //Ÿ��Ʋ ���
void ending_title(int x, int y);
void show_menu(int, int); //���θ޴� ���
void game1_screen(int); // ���� ���� ȭ��
void game2_screen(int); // ª�� �� ���� ȭ��
void game3_screen(int); // �� �� ���� ȭ��
void game1_screen_sp(int); // ���������� ���� ȭ��
void game2_screen_sp(int); // ��ź��� ȭ��
void game3_screen_sp(int); // �� ���� ���� ȭ��
void game1_mode();// �������� ���޴� ���
void game2_mode();// ª�� �� ���� ���޴� ���
void game3_mode();//�� �� ���� ���޴� ���
int levelchoice_with_free(); // �������� �ִ� ���̵� ����
int levelchoice_without_free(); // �������� ���� ���̵� ����
void waiting();  // ����â �����ϱ��� ���ȭ��
void score_short(int T, int limit_time, int* short_totalscore); //�������
void ask_restart();//����� ���� ����
void pause(int* pt, int* resume, int* qe, int line); //�Ͻ����� ���� ����

//�������� �Լ���
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

//ª���ۿ��� �Լ���
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