#include "common.h"

int level;
int restart = 0;

int main(void)
{
	system("mode con cols=105 lines=36"); //콘솔창 크기조절: cols 가로길이,lines 세로길이
	title(33, 14); //타이틀화면 띄우기

	while (1) //1번 반복문-(탈출조건:menu 가 4, restart가 2)
	{
		int menu;

		if (restart == 1) // 재시작시 타이틀 띄우기
		{
			system("mode con cols=105 lines=36"); //콘솔창 크기조절: cols 가로길이,lines 세로길이
			title(33, 14); //타이틀화면 띄우기
			restart = 0; //restart 사용 후 값 초기화
		}

		show_menu(35, 13); // 메뉴 띄우기
		scanf("%d", &menu); // 사용자 입력받기
		getchar(); //엔터키 처리

		if (menu == 4) // 게임종료
		{
			ending_title(33, 14);
			break;
		}

		if (menu < 1 || menu>4)
			continue;

		switch (menu) {
		case 1: //낱말 연습
		{
			int mode;

			while (1) //2번 반복문 (탈출 mode가 3이거나 함수호출 후)
			{
				do {
					game1_mode(); //모드 메뉴 출력
					scanf("%d", &mode);//모드 입력받기
				} while (mode < 1 || mode>3);

				//게임모드에 따른 동작 수행
				if (mode == 3)  //뒤로가기
					break; //2번 반복문 탈출, 1번반복문으로

				else if (mode == 1) //낱말 일반모드
				{
					level = levelchoice_without_free();
					if (level == 4)
						continue; // 2번 반복문 반복

					else
					{
						game1_screen(level);
						waiting();
						wordgame_main();
						if (restart == 1)
							continue; //2번반복문, 모드메뉴 반복
						else
							break; //2번 반복문 탈출->1번 반복문(메뉴화면으로)
					}
				}
				else // 낱말 가위바위보
				{
					level = levelchoice_without_free();
					if (level == 4)
						continue;  // 2번 반복문 반복
					else
					{
						//함수호출
						game1_screen_sp(level);
						waiting();
						wordgame_main_rcp();
						//가위바위보 함수 호출
						if (restart == 1)
							continue; //2번 반복문, 모드메뉴 반복
						else
							break; // 2번 반복문 탈출->1번 반복문(메뉴화면으로)
					}
				}
			}
			break; //case1에 대한 break;
		}
		case 2: //짧은 글 연습
		{
			int mode;
			while (1) //2번 반복문 (탈출 mode가 3이거나 함수호출 후)
			{
				do {
					game2_mode(); //모드 메뉴 출력
					scanf("%d", &mode);//모드 입력받기
				} while (mode < 1 || mode>3);

				//모드에 따른 동작 수행
				if (mode == 3)  //뒤로가기하면 다시 메뉴화면으로
					break;

				else if (mode == 1) //짧은글 일반모드
				{
					level = levelchoice_with_free();
					if (level == 4)
						continue; //모드 메뉴 재출력
					else if (level == 0)
					{
						short_free();
					}
					else if (level == 1)
					{
						short_easy();
					}
					else if (level == 2)
					{
						short_normal();
					}
					else // (level == 3)
					{
						short_hard();
					}
				}
				else //폭탄모드
				{
					level = levelchoice_without_free();
					if (level == 4)
						continue; //모드메뉴 재출력
					else if (level == 1)
					{
						bomb_easy();//짧은글 폭탄 초급 호출
					}
					else if (level == 2)
					{
						bomb_normal();//짧은글 폭탄 중급 호출
					}
					else // (level == 3)
					{
						bomb_hard();//짧은글 폭탄 고급 호출
					}
				}

				// 재시작에 대한 조건문

				if (restart == 1)
					continue; //2번 반복문 재시작

				else
					break;  //모드 출력 반복문 탈출

			}
			break;  //case2에 대한 break;
		}
		case 3: //긴 글 연습
		{
			int mode;
			while (1) //2번 반복문 (탈출 mode가 3이거나 함수호출 후)
			{
				do {
					game3_mode(); //모드 메뉴 출력
					scanf("%d", &mode);//모드 입력받기
				} while (mode < 1 || mode>3);

				//모드에 따른 동작 수행
				if (mode == 3)  //뒤로가기하면 다시 메뉴화면으로
					break;

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
				if (restart == 2)
					break;  //모드 출력 반복문 탈출
			}
			break; //case3에 대한 break;
		}
		}
		system("cls"); //각 게임이 끝난 후에는 화면 리셋 후 다시 메뉴를 보여준다.

		if (restart == 2)
		{
			ending_title(33, 14);

			break;
		}
	}

	return 0;
}

void title(int x, int y)
{
	gotoxy(x, y); printf("타닥타닥 타자게임 ");
	gotoxy(x, y + 1); printf("<부제: 타닥타닥, 내 열정 불타는 소리> ");
	gotoxy(x, y + 2); printf("Press any key to start..");

	_getch(); //사용자가 아무 키값을 입력해야 타이틀에서 메뉴화면으로 이동한다.
}

void ending_title(int x, int y)
{
	system("cls");
	gotoxy(x, y); printf("타닥타닥 타자게임 ");
	gotoxy(x, y + 1); printf("<부제: 타닥타닥, 내 열정 불타는 소리> ");
	gotoxy(x, y + 2); printf("종료합니다..");
	printf("\n\n\n\n\n\n\n\n\n");
}

void show_menu(int x, int y)
{
	system("cls");
	gotoxy(x, y); printf("******메뉴******");
	gotoxy(x, y + 1); printf("1.낱말 연습");
	gotoxy(x, y + 2); printf("2.짧은 글 연습");
	gotoxy(x, y + 3); printf("3.긴 글 연습");
	gotoxy(x, y + 4); printf("4.종료");
	gotoxy(x, y + 5); printf("****************");
	gotoxy(x, y + 7); printf("메뉴를 선택하세요: ");
}

void waiting()
{
	gotoxy(25, 13); printf("준비되면 spacebar를 눌러주세요.");

	while (1)
	{
		if (_getch() == ' ')
		{
			gotoxy(25, 13); printf("                               ");// 스페이스바가 입력되면 설명문 지우기
			break;
		}
	}

	//입력창으로 이동
	gotoxy(5, 27);
	printf("");
}


//각 게임에 대한 게임창들
void game1_screen(int level)
{
	char info[] = { "제한 시간 내에 주어진 단어를 입력하세요. 시간 내에 입력하지 못하거나 오타가 발생할 경우 0점이 추가됩니다. 빠르게 입력할 수록 더 많은 점수가 추가됩니다." };
	int len, i, u = 1;
	len = strlen(info); //설명 문자열의 길이
	system("cls");
	//시스템창 
	printf("\n");
	printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃                      ┃ ┃\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	gotoxy(79, 3);
	{
		if (level == 1)
			printf("난이도: 초급");
		else if (level == 2)
			printf("난이도: 중급");
		else //level==3
			printf("난이도: 고급");
	}
	gotoxy(79, 5);
	printf("낱말 연습");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u) //이 조건이 만족되면 다음줄로 넘어가게 해주었다.
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 17);
	printf("▶일시정지키는 Esc");
	gotoxy(79, 18);
	printf(" 키를 눌러주세요.");

	gotoxy(5, 27);
	printf("");

}
void game1_screen_sp(int level)
{
	char info[] = { "제한 시간 내에 가위바위보 게임을 이길 수 있는 단어를 입력하세요. 단어를 입력 후 엔터키를 눌러주세요. 컴퓨터와 가위바위보 승부를 해 점수가 추가됩니다." };
	int len, i, u = 1;
	len = strlen(info); //설명 문자열의 길이
	system("cls");
	//시스템창 
	printf("\n");
	printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃                      ┃ ┃\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	gotoxy(79, 3);
	{
		if (level == 1)
			printf("난이도: 초급");
		else if (level == 2)
			printf("난이도: 중급");
		else //level==3
			printf("난이도: 고급");
	}
	gotoxy(79, 5);
	printf("가위바위보 게임");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u) //이 조건이 만족되면 다음줄로 넘어가게 해주었다.
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 17);
	printf("▶일시정지키는 Esc");
	gotoxy(79, 18);
	printf(" 키를 눌러주세요.");

	gotoxy(5, 27);
	printf("");
}
void game2_screen(int level)
{
	char info[] = { "제한 시간 내에 제시되는 문장을 입력하세요. 입력하는 빠르기에 따라 현재 타자속도와 최고 타자속도가 나타납니다. 처음에는 속도보다 정확하게 글자를 입력할 수 있도록 자유모드를 권장합니다." };
	int len, i, u = 1;
	len = strlen(info); //문자열의 길이 구하기
	system("cls");
	//시스템창 
	printf("\n");
	printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃                      ┃ ┃\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");


	gotoxy(79, 3);
	if (level == 0)
		printf("난이도 : 무제한");
	else if (level == 1)
		printf("난이도: 초급");
	else if (level == 2)
		printf("난이도: 중급");
	else //level==3
		printf("난이도: 고급");
	gotoxy(79, 5);
	printf("짧은 글 연습");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u)
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 8 + u);
	printf("▶일시정지키는 Esc");
	gotoxy(79, 9 + u);
	printf(" 키를 눌러주세요.");

}
void game2_screen_sp(int level)
{
	char info[] = { "일반모드와 진행방식은 같습니다. 불시에 폭탄문장이 나오면 해당 키위드를 3번 입력해 폭탄을 해체하세요. 해체하지 못하면 점수가 차감됩니다. 폭탄문장에서 폭탄이 제거된 후에는 일반 짧은 글 연습처럼 문장을 입력해주면 됩니다." };
	int len, i, u = 1;
	len = strlen(info); //문자열의 길이 구하기
	system("cls");
	//시스템창 
	printf("\n");
	printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃                      ┃ ┃\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	gotoxy(79, 3);
	if (level == 1)
		printf("난이도: 초급");
	else if (level == 2)
		printf("난이도: 중급");
	else //level==3
		printf("난이도: 고급");
	gotoxy(79, 5);
	printf("짧은 글 연습 - 폭탄");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u)
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 8 + u);
	printf("▶일시정지키는 Esc");
	gotoxy(79, 9 + u);
	printf(" 키를 눌러주세요.");

}
void game3_screen(int level)
{
	char info[] = { "제한 시간 내에 제시되는 문장을 입력하세요. 오타가 발생하는 경우, 오타 수가 좌측 하단에 표시되고, 정확도(%)가 떨어지게 됩니다. 난이도에 따라 원하는 글을 선택하여 긴 글 타자를 연습할 수 있습니다.." };
	int len, i, u = 1;
	len = strlen(info); //문자열의 길이 구하기
	system("cls");
	//시스템창 
	printf("\n");
	printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃                      ┃ ┃\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	gotoxy(79, 3);
	if (level == 0)
		printf("난이도 : 무제한");
	else if (level == 1)
		printf("난이도: 초급");
	else if (level == 2)
		printf("난이도: 중급");
	else //level==3
		printf("난이도: 고급");
	gotoxy(79, 5);
	printf("긴 글 연습");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u)
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 8 + u);
	printf("▶일시정지키는 Esc");
	gotoxy(79, 9 + u);
	printf(" 키를 눌러주세요.");

}
void game3_screen_sp(int level)
{
	char info[] = { "제한 시간 내에 주어진 긴 글을 입력하세요. 한 문장이 끝날 때마다 점수가 쌓입니다. 난이도 별로 자신이 원하는 글을 선택할 수 있으며, 선택한 글의 시대적, 문화적 특성에 따라 만들 수 있는 집의 모양이 달라집니다." };
	int len, i, u = 1;
	len = strlen(info); //문자열의 길이 구하기
	system("cls");
	//시스템창 
	printf("\n");
	printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┏━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃                      ┃ ┃\n");
	printf(" ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┨ ┃                      ┃ ┃\n");
	printf(" ┃ ┃                                                                       ┃ ┃                      ┃ ┃\n");
	printf(" ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┗━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");


	gotoxy(79, 3);
	if (level == 1)
		printf("난이도: 초급");
	else if (level == 2)
		printf("난이도: 중급");
	else //level==3
		printf("난이도: 고급");
	gotoxy(79, 5);
	printf("집 짓기 게임");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u)
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 8 + u);
	printf("▶일시정지키는 Esc");
	gotoxy(79, 9 + u);
	printf(" 키를 눌러주세요.");

}

// 낱말, 짧은글, 긴글에 대한 게임선택
void game1_mode()
{
	system("cls");
	gotoxy(33, 11); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
	gotoxy(33, 12); printf("▨        << 낱말 연습 >>           ▨");
	gotoxy(33, 13); printf("▨                                  ▨");
	gotoxy(33, 14); printf("▨         1. 일반 모드             ▨");
	gotoxy(33, 15); printf("▨       2. 가위바위보 게임         ▨");
	gotoxy(33, 16); printf("▨         3. 뒤로 가기             ▨");
	gotoxy(33, 17); printf("▨                                  ▨");
	gotoxy(33, 18); printf("▨    => 모드를 선택해주세요:       ▨");
	gotoxy(33, 19); printf("▨                                  ▨");
	gotoxy(33, 20); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
	gotoxy(63, 18);

}
void game2_mode()
{
	system("cls");
	gotoxy(33, 11); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
	gotoxy(33, 12); printf("▨       << 짧은 글 연습 >>         ▨");
	gotoxy(33, 13); printf("▨                                  ▨");
	gotoxy(33, 14); printf("▨         1. 일반 모드             ▨");
	gotoxy(33, 15); printf("▨         2. 폭탄 모드             ▨");
	gotoxy(33, 16); printf("▨         3. 뒤로 가기             ▨");
	gotoxy(33, 17); printf("▨                                  ▨");
	gotoxy(33, 18); printf("▨    => 모드를 선택해주세요:       ▨");
	gotoxy(33, 19); printf("▨                                  ▨");
	gotoxy(33, 20); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
	gotoxy(63, 18);

}
void game3_mode()
{
	system("cls");
	gotoxy(33, 11); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
	gotoxy(33, 12); printf("▨        << 긴 글 연습 >>          ▨");
	gotoxy(33, 13); printf("▨                                  ▨");
	gotoxy(33, 14); printf("▨         1. 일반 모드             ▨");
	gotoxy(33, 15); printf("▨         2. 집 짓기               ▨");
	gotoxy(33, 16); printf("▨         3. 뒤로 가기             ▨");
	gotoxy(33, 17); printf("▨                                  ▨");
	gotoxy(33, 18); printf("▨    => 모드를 선택해주세요:       ▨");
	gotoxy(33, 19); printf("▨                                  ▨");
	gotoxy(33, 20); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
	gotoxy(63, 18);

}

//난이도 선택(무제한이 있는 버전, 없는 버전)
int levelchoice_with_free() //무제한이 있는 레벨 메뉴
{
	int level;
	do {
		system("cls");
		gotoxy(33, 11); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
		gotoxy(33, 12); printf("▨        << 난이도 선택 >>         ▨");
		gotoxy(33, 13); printf("▨                                  ▨");
		gotoxy(33, 14); printf("▨            0. 무제한             ▨");
		gotoxy(33, 15); printf("▨            1. 초급               ▨");
		gotoxy(33, 16); printf("▨            2. 중급               ▨");
		gotoxy(33, 17); printf("▨            3. 고급               ▨");
		gotoxy(33, 18); printf("▨            4. 뒤로 가기          ▨");
		gotoxy(33, 19); printf("▨                                  ▨");
		gotoxy(33, 20); printf("▨    => 난이도를 선택해주세요:     ▨");
		gotoxy(33, 21); printf("▨                                  ▨");
		gotoxy(33, 22); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
		gotoxy(65, 20); //난이도를 선택해주세요 다음으로 커서이동
		scanf("%d", &level);//레벨 입력받기
	} while (level < 0 || level >4);
	return level;
}
int levelchoice_without_free()
{
	int level;
	do {
		system("cls");
		gotoxy(33, 11); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
		gotoxy(33, 12); printf("▨        << 난이도 선택 >>         ▨");
		gotoxy(33, 13); printf("▨                                  ▨");
		gotoxy(33, 14); printf("▨            1. 초급               ▨");
		gotoxy(33, 15); printf("▨            2. 중급               ▨");
		gotoxy(33, 16); printf("▨            3. 고급               ▨");
		gotoxy(33, 17); printf("▨            4. 뒤로 가기          ▨");
		gotoxy(33, 18); printf("▨                                  ▨");
		gotoxy(33, 19); printf("▨    => 난이도를 선택해주세요:     ▨");
		gotoxy(33, 20); printf("▨                                  ▨");
		gotoxy(33, 21); printf("▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨▨");
		gotoxy(65, 19);
		scanf("%d", &level);//레벨 입력받기
	} while (level < 1 || level >4);
	return level;
}

//일시정지
void pause(int* pt, int* resume, int* qe, int line) // 일시정지시간, 게임 재개 여부, 초기메뉴로 이동 여부, pause를 출력할 줄(게임창마다 크기가 달라서 맞추기 위해)
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
		}
		if (stop == 1)
			break; //일시정지 종료
	}
	et = time(0);
	*pt = et - st;
}


//이 cal함수는 각자의 타자연습에 맞춰서 변형되어 사용되었음.
void cal(int timespent, char* input, char* answer, int num, int* count, float* maxsp, int px, int py)
{
	int correct, error = 0;
	float speed, accuracy, processivity;
	int i;
	int len = strlen(input); // 문자열 길이

	(*count)++; //진행도 측정

	for (i = 0; i < len; i++) //오타수 측정:
	{
		if (input[i] != answer[i])// 사용자입력 각각의 알파벳과 정답 알파벳을 비교해서 같지 않으면
		{
			error += 1;
		}
	}
	//!만약 오타수 측정을 밖에서 한다면 인수 2개(포인터변수인 input과 answer)를 뺄 수 있다.

	//오타가 아닌 정타수
	correct = len - error;

	//타자속도 : (타자수/걸린시간)*60 = 분당 타자속도
	speed = ((len) / (float)(timespent)) * 60;
	/*speed=((correct)/(float)(timespent))*60 하면 (정타수/걸린시간)*60으로 = 분당 정타타자속도를 잴 수 있다*/

	//최고 타자 속도:
	if (speed > *maxsp)
	{
		*maxsp = speed;
	}
	//정확도= 타자수/문자열의 길이 *100
	accuracy = ((float)len / strlen(input)) * 100;

	//진행도
	processivity = ((float)(*count) / num) * 100;

	//출력
	gotoxy(79 + px, 22 + py);
	printf("타자속도: %.f (타)", speed);
	gotoxy(79 + px, 23 + py);
	printf("최고타자속도: %.f (타)", *maxsp);
	gotoxy(79 + px, 24 + py);
	printf("정확도 : %.f (%%)", accuracy);
	gotoxy(79 + px, 25 + py);
	printf("오타수: %d (개)", error);
	gotoxy(79 + px, 26 + py);
	printf("진행도: %.1f (%%)", processivity);

	Sleep(10000);// 확인용 waiting

}


//걸린시간, 문제수, 진행도카운트, 최대타자속도, 나머지는 0,0 (위치조절용)
void cal_timeover(int timespent, int num, int count, float* maxsp, int px, int py)
{
	float processivity;
	processivity = ((float)(count) / num) * 100;

	//기존 출력 지우기
	gotoxy(79 + px, 23 + py);
	printf("                    ");
	gotoxy(79 + px, 24 + py);
	printf("                    ");
	gotoxy(79 + px, 25 + py);
	printf("                    ");
	gotoxy(79 + px, 26 + py);
	printf("                    ");
	gotoxy(79 + px, 27 + py);
	printf("                    ");
	gotoxy(79 + px, 28 + py);
	printf("                    ");
	gotoxy(79 + px, 23 + py);
	printf("타자속도: ----- (타)");
	gotoxy(79 + px, 24 + py);
	printf("최고타자: %.f (타)", *maxsp);
	gotoxy(79 + px, 25 + py);
	printf("정확도 : ----- (%%)");
	gotoxy(79 + px, 26 + py);
	printf("오타수: ----- (개)");
	gotoxy(79 + px, 27 + py);
	printf("진행도: %.1f (%%)", processivity);
	gotoxy(79 + px, 28 + py);
	printf("걸린시간: timeover");
}

void score_short(int T, int limit_time, int* short_totalscore) //걸린시간과 제한시간
{
	int score;
	int num = 50; // 기본점수 50점
	float n, i; //구간길이
	n = limit_time / (float)10;

	if (T >= limit_time) //T가 제한시간이상일때 0점
		score = 0;

	else //T가 제한시간미만인 경우 10개의 구간으로 나누어 점수를 부여한다.
	{

		for (i = 0; i < limit_time; i += n)
		{
			if ((i <= T) && (T < i + n))
			{
				score = num;
			}
			num -= 5; //점수 5감소
		}
	}

	*short_totalscore += score; //누적 점수에 현재 score를 추가해 누적 점수를 갱신해준다.
}

void ask_restart()
{
	do {
		gotoxy(10, 15);
		printf("                                         ");
		gotoxy(10, 15);
		printf("재시작하시겠습니까? (1-네 2- 아니요): ");
		scanf("%d", &restart);
	} while (restart < 1 || restart>2);
}
