#include "common.h"

int level;
int restart = 0;

int main(void)
{
	system("mode con cols=105 lines=36"); //夔樂璽 觼晦褻瞰: cols 陛煎望檜,lines 撮煎望檜
	title(33, 14); //顫檜ぎ�飛� 嗥辦晦

	while (1) //1廓 奩犒僥-(驍轎褻勒:menu 陛 4, restart陛 2)
	{
		int menu;

		if (restart == 1) // 營衛濛衛 顫檜ぎ 嗥辦晦
		{
			system("mode con cols=105 lines=36"); //夔樂璽 觼晦褻瞰: cols 陛煎望檜,lines 撮煎望檜
			title(33, 14); //顫檜ぎ�飛� 嗥辦晦
			restart = 0; //restart 餌辨 �� 高 蟾晦��
		}

		show_menu(35, 13); // 詭景 嗥辦晦
		scanf("%d", &menu); // 餌辨濠 殮溘嫡晦
		getchar(); //縛攪酈 籀葬

		if (menu == 4) // 啪歜謙猿
		{
			ending_title(33, 14);
			break;
		}

		if (menu < 1 || menu>4)
			continue;

		switch (menu) {
		case 1: //章蜓 翱蝗
		{
			int mode;

			while (1) //2廓 奩犒僥 (驍轎 mode陛 3檜剪釭 л熱��轎 ��)
			{
				do {
					game1_mode(); //賅萄 詭景 轎溘
					scanf("%d", &mode);//賅萄 殮溘嫡晦
				} while (mode < 1 || mode>3);

				//啪歜賅萄縑 評艇 翕濛 熱ч
				if (mode == 3)  //菴煎陛晦
					break; //2廓 奩犒僥 驍轎, 1廓奩犒僥戲煎

				else if (mode == 1) //章蜓 橾奩賅萄
				{
					level = levelchoice_without_free();
					if (level == 4)
						continue; // 2廓 奩犒僥 奩犒

					else
					{
						game1_screen(level);
						waiting();
						wordgame_main();
						if (restart == 1)
							continue; //2廓奩犒僥, 賅萄詭景 奩犒
						else
							break; //2廓 奩犒僥 驍轎->1廓 奩犒僥(詭景�飛橉虞�)
					}
				}
				else // 章蜓 陛嬪夥嬪爾
				{
					level = levelchoice_without_free();
					if (level == 4)
						continue;  // 2廓 奩犒僥 奩犒
					else
					{
						//л熱��轎
						game1_screen_sp(level);
						waiting();
						wordgame_main_rcp();
						//陛嬪夥嬪爾 л熱 ��轎
						if (restart == 1)
							continue; //2廓 奩犒僥, 賅萄詭景 奩犒
						else
							break; // 2廓 奩犒僥 驍轎->1廓 奩犒僥(詭景�飛橉虞�)
					}
				}
			}
			break; //case1縑 渠и break;
		}
		case 2: //穠擎 旋 翱蝗
		{
			int mode;
			while (1) //2廓 奩犒僥 (驍轎 mode陛 3檜剪釭 л熱��轎 ��)
			{
				do {
					game2_mode(); //賅萄 詭景 轎溘
					scanf("%d", &mode);//賅萄 殮溘嫡晦
				} while (mode < 1 || mode>3);

				//賅萄縑 評艇 翕濛 熱ч
				if (mode == 3)  //菴煎陛晦ж賊 棻衛 詭景�飛橉虞�
					break;

				else if (mode == 1) //穠擎旋 橾奩賅萄
				{
					level = levelchoice_with_free();
					if (level == 4)
						continue; //賅萄 詭景 營轎溘
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
				else //ァ驕賅萄
				{
					level = levelchoice_without_free();
					if (level == 4)
						continue; //賅萄詭景 營轎溘
					else if (level == 1)
					{
						bomb_easy();//穠擎旋 ァ驕 蟾晝 ��轎
					}
					else if (level == 2)
					{
						bomb_normal();//穠擎旋 ァ驕 醞晝 ��轎
					}
					else // (level == 3)
					{
						bomb_hard();//穠擎旋 ァ驕 堅晝 ��轎
					}
				}

				// 營衛濛縑 渠и 褻勒僥

				if (restart == 1)
					continue; //2廓 奩犒僥 營衛濛

				else
					break;  //賅萄 轎溘 奩犒僥 驍轎

			}
			break;  //case2縑 渠и break;
		}
		case 3: //曹 旋 翱蝗
		{
			int mode;
			while (1) //2廓 奩犒僥 (驍轎 mode陛 3檜剪釭 л熱��轎 ��)
			{
				do {
					game3_mode(); //賅萄 詭景 轎溘
					scanf("%d", &mode);//賅萄 殮溘嫡晦
				} while (mode < 1 || mode>3);

				//賅萄縑 評艇 翕濛 熱ч
				if (mode == 3)  //菴煎陛晦ж賊 棻衛 詭景�飛橉虞�
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
					break;  //賅萄 轎溘 奩犒僥 驍轎
			}
			break; //case3縑 渠и break;
		}
		}
		system("cls"); //陝 啪歜檜 部陪 �醴●� �飛� 葬撢 �� 棻衛 詭景蒂 爾罹遽棻.

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
	gotoxy(x, y); printf("顫款顫款 顫濠啪歜 ");
	gotoxy(x, y + 1); printf("<睡薯: 顫款顫款, 頂 翮薑 碳顫朝 模葬> ");
	gotoxy(x, y + 2); printf("Press any key to start..");

	_getch(); //餌辨濠陛 嬴鼠 酈高擊 殮溘п撿 顫檜ぎ縑憮 詭景�飛橉虞� 檜翕и棻.
}

void ending_title(int x, int y)
{
	system("cls");
	gotoxy(x, y); printf("顫款顫款 顫濠啪歜 ");
	gotoxy(x, y + 1); printf("<睡薯: 顫款顫款, 頂 翮薑 碳顫朝 模葬> ");
	gotoxy(x, y + 2); printf("謙猿м棲棻..");
	printf("\n\n\n\n\n\n\n\n\n");
}

void show_menu(int x, int y)
{
	system("cls");
	gotoxy(x, y); printf("******詭景******");
	gotoxy(x, y + 1); printf("1.章蜓 翱蝗");
	gotoxy(x, y + 2); printf("2.穠擎 旋 翱蝗");
	gotoxy(x, y + 3); printf("3.曹 旋 翱蝗");
	gotoxy(x, y + 4); printf("4.謙猿");
	gotoxy(x, y + 5); printf("****************");
	gotoxy(x, y + 7); printf("詭景蒂 摹鷗ж撮蹂: ");
}

void waiting()
{
	gotoxy(25, 13); printf("遽綠腎賊 spacebar蒂 揚楝輿撮蹂.");

	while (1)
	{
		if (_getch() == ' ')
		{
			gotoxy(25, 13); printf("                               ");// 蝶む檜蝶夥陛 殮溘腎賊 撲貲僥 雖辦晦
			break;
		}
	}

	//殮溘璽戲煎 檜翕
	gotoxy(5, 27);
	printf("");
}


//陝 啪歜縑 渠и 啪歜璽菟
void game1_screen(int level)
{
	char info[] = { "薯и 衛除 頂縑 輿橫霞 欽橫蒂 殮溘ж撮蹂. 衛除 頂縑 殮溘ж雖 跤ж剪釭 螃顫陛 嫦儅й 唳辦 0薄檜 蹺陛腌棲棻. 緒腦啪 殮溘й 熱煙 渦 號擎 薄熱陛 蹺陛腌棲棻." };
	int len, i, u = 1;
	len = strlen(info); //撲貲 僥濠翮曖 望檜
	system("cls");
	//衛蝶蠱璽 
	printf("\n");
	printf(" 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 早 早                                                                       早 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早                      早 早\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");

	gotoxy(79, 3);
	{
		if (level == 1)
			printf("陪檜紫: 蟾晝");
		else if (level == 2)
			printf("陪檜紫: 醞晝");
		else //level==3
			printf("陪檜紫: 堅晝");
	}
	gotoxy(79, 5);
	printf("章蜓 翱蝗");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u) //檜 褻勒檜 虜褶腎賊 棻擠還煎 剩橫陛啪 п輿歷棻.
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 17);
	printf("Ⅱ橾衛薑雖酈朝 Esc");
	gotoxy(79, 18);
	printf(" 酈蒂 揚楝輿撮蹂.");

	gotoxy(5, 27);
	printf("");

}
void game1_screen_sp(int level)
{
	char info[] = { "薯и 衛除 頂縑 陛嬪夥嬪爾 啪歜擊 檜望 熱 氈朝 欽橫蒂 殮溘ж撮蹂. 欽橫蒂 殮溘 �� 縛攪酈蒂 揚楝輿撮蹂. 闡У攪諦 陛嬪夥嬪爾 蝓睡蒂 п 薄熱陛 蹺陛腌棲棻." };
	int len, i, u = 1;
	len = strlen(info); //撲貲 僥濠翮曖 望檜
	system("cls");
	//衛蝶蠱璽 
	printf("\n");
	printf(" 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 早 早                                                                       早 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早                      早 早\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");

	gotoxy(79, 3);
	{
		if (level == 1)
			printf("陪檜紫: 蟾晝");
		else if (level == 2)
			printf("陪檜紫: 醞晝");
		else //level==3
			printf("陪檜紫: 堅晝");
	}
	gotoxy(79, 5);
	printf("陛嬪夥嬪爾 啪歜");
	gotoxy(79, 7);
	for (i = 0; i < len; i++)
	{
		if (i + 1 == 20 * u) //檜 褻勒檜 虜褶腎賊 棻擠還煎 剩橫陛啪 п輿歷棻.
		{
			gotoxy(79, 7 + u);
			u++;
		}
		printf("%c", info[i]);
	}

	gotoxy(79, 17);
	printf("Ⅱ橾衛薑雖酈朝 Esc");
	gotoxy(79, 18);
	printf(" 酈蒂 揚楝輿撮蹂.");

	gotoxy(5, 27);
	printf("");
}
void game2_screen(int level)
{
	char info[] = { "薯и 衛除 頂縑 薯衛腎朝 僥濰擊 殮溘ж撮蹂. 殮溘ж朝 緒腦晦縑 評塭 ⑷營 顫濠樓紫諦 譆堅 顫濠樓紫陛 釭顫陶棲棻. 籀擠縑朝 樓紫爾棻 薑�旁炾� 旋濠蒂 殮溘й 熱 氈紫煙 濠嶸賅萄蒂 掏濰м棲棻." };
	int len, i, u = 1;
	len = strlen(info); //僥濠翮曖 望檜 掘ж晦
	system("cls");
	//衛蝶蠱璽 
	printf("\n");
	printf(" 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 早 早                                                                       早 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早                      早 早\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");


	gotoxy(79, 3);
	if (level == 0)
		printf("陪檜紫 : 鼠薯и");
	else if (level == 1)
		printf("陪檜紫: 蟾晝");
	else if (level == 2)
		printf("陪檜紫: 醞晝");
	else //level==3
		printf("陪檜紫: 堅晝");
	gotoxy(79, 5);
	printf("穠擎 旋 翱蝗");
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
	printf("Ⅱ橾衛薑雖酈朝 Esc");
	gotoxy(79, 9 + u);
	printf(" 酈蒂 揚楝輿撮蹂.");

}
void game2_screen_sp(int level)
{
	char info[] = { "橾奩賅萄諦 霞ч寞衝擎 偽蝗棲棻. 碳衛縑 ァ驕僥濰檜 釭螃賊 п渡 酈嬪萄蒂 3廓 殮溘п ァ驕擊 п羹ж撮蹂. п羹ж雖 跤ж賊 薄熱陛 離馬腌棲棻. ァ驕僥濰縑憮 ァ驕檜 薯剪脹 �醴●� 橾奩 穠擎 旋 翱蝗籀歲 僥濰擊 殮溘п輿賊 腌棲棻." };
	int len, i, u = 1;
	len = strlen(info); //僥濠翮曖 望檜 掘ж晦
	system("cls");
	//衛蝶蠱璽 
	printf("\n");
	printf(" 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 早 早                                                                       早 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早                      早 早\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");

	gotoxy(79, 3);
	if (level == 1)
		printf("陪檜紫: 蟾晝");
	else if (level == 2)
		printf("陪檜紫: 醞晝");
	else //level==3
		printf("陪檜紫: 堅晝");
	gotoxy(79, 5);
	printf("穠擎 旋 翱蝗 - ァ驕");
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
	printf("Ⅱ橾衛薑雖酈朝 Esc");
	gotoxy(79, 9 + u);
	printf(" 酈蒂 揚楝輿撮蹂.");

}
void game3_screen(int level)
{
	char info[] = { "薯и 衛除 頂縑 薯衛腎朝 僥濰擊 殮溘ж撮蹂. 螃顫陛 嫦儅ж朝 唳辦, 螃顫 熱陛 謝難 ж欽縑 ル衛腎堅, 薑�挾�(%)陛 雲橫雖啪 腌棲棻. 陪檜紫縑 評塭 錳ж朝 旋擊 摹鷗ж罹 曹 旋 顫濠蒂 翱蝗й 熱 氈蝗棲棻.." };
	int len, i, u = 1;
	len = strlen(info); //僥濠翮曖 望檜 掘ж晦
	system("cls");
	//衛蝶蠱璽 
	printf("\n");
	printf(" 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 早 早                                                                       早 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早                      早 早\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 朵收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收此 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");

	gotoxy(79, 3);
	if (level == 0)
		printf("陪檜紫 : 鼠薯и");
	else if (level == 1)
		printf("陪檜紫: 蟾晝");
	else if (level == 2)
		printf("陪檜紫: 醞晝");
	else //level==3
		printf("陪檜紫: 堅晝");
	gotoxy(79, 5);
	printf("曹 旋 翱蝗");
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
	printf("Ⅱ橾衛薑雖酈朝 Esc");
	gotoxy(79, 9 + u);
	printf(" 酈蒂 揚楝輿撮蹂.");

}
void game3_screen_sp(int level)
{
	char info[] = { "薯и 衛除 頂縑 輿橫霞 曹 旋擊 殮溘ж撮蹂. и 僥濰檜 部陳 陽葆棻 薄熱陛 論殮棲棻. 陪檜紫 滌煎 濠褐檜 錳ж朝 旋擊 摹鷗й 熱 氈戲貊, 摹鷗и 旋曖 衛渠瞳, 僥�倣� か撩縑 評塭 虜菟 熱 氈朝 餵曖 賅曄檜 殖塭餵棲棻." };
	int len, i, u = 1;
	len = strlen(info); //僥濠翮曖 望檜 掘ж晦
	system("cls");
	//衛蝶蠱璽 
	printf("\n");
	printf(" 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 早 早                                                                       早 旨收收收收收收收收收收收收收收收收收收收收收收旬 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早                      早 早\n");
	printf(" 早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 朵收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收此 早                      早 早\n");
	printf(" 早 早                                                                       早 早                      早 早\n");
	printf(" 早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 曲收收收收收收收收收收收收收收收收收收收收收收旭 早\n");
	printf(" 曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭\n");


	gotoxy(79, 3);
	if (level == 1)
		printf("陪檜紫: 蟾晝");
	else if (level == 2)
		printf("陪檜紫: 醞晝");
	else //level==3
		printf("陪檜紫: 堅晝");
	gotoxy(79, 5);
	printf("餵 騁晦 啪歜");
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
	printf("Ⅱ橾衛薑雖酈朝 Esc");
	gotoxy(79, 9 + u);
	printf(" 酈蒂 揚楝輿撮蹂.");

}

// 章蜓, 穠擎旋, 曹旋縑 渠и 啪歜摹鷗
void game1_mode()
{
	system("cls");
	gotoxy(33, 11); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
	gotoxy(33, 12); printf("〧        << 章蜓 翱蝗 >>           〧");
	gotoxy(33, 13); printf("〧                                  〧");
	gotoxy(33, 14); printf("〧         1. 橾奩 賅萄             〧");
	gotoxy(33, 15); printf("〧       2. 陛嬪夥嬪爾 啪歜         〧");
	gotoxy(33, 16); printf("〧         3. 菴煎 陛晦             〧");
	gotoxy(33, 17); printf("〧                                  〧");
	gotoxy(33, 18); printf("〧    => 賅萄蒂 摹鷗п輿撮蹂:       〧");
	gotoxy(33, 19); printf("〧                                  〧");
	gotoxy(33, 20); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
	gotoxy(63, 18);

}
void game2_mode()
{
	system("cls");
	gotoxy(33, 11); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
	gotoxy(33, 12); printf("〧       << 穠擎 旋 翱蝗 >>         〧");
	gotoxy(33, 13); printf("〧                                  〧");
	gotoxy(33, 14); printf("〧         1. 橾奩 賅萄             〧");
	gotoxy(33, 15); printf("〧         2. ァ驕 賅萄             〧");
	gotoxy(33, 16); printf("〧         3. 菴煎 陛晦             〧");
	gotoxy(33, 17); printf("〧                                  〧");
	gotoxy(33, 18); printf("〧    => 賅萄蒂 摹鷗п輿撮蹂:       〧");
	gotoxy(33, 19); printf("〧                                  〧");
	gotoxy(33, 20); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
	gotoxy(63, 18);

}
void game3_mode()
{
	system("cls");
	gotoxy(33, 11); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
	gotoxy(33, 12); printf("〧        << 曹 旋 翱蝗 >>          〧");
	gotoxy(33, 13); printf("〧                                  〧");
	gotoxy(33, 14); printf("〧         1. 橾奩 賅萄             〧");
	gotoxy(33, 15); printf("〧         2. 餵 騁晦               〧");
	gotoxy(33, 16); printf("〧         3. 菴煎 陛晦             〧");
	gotoxy(33, 17); printf("〧                                  〧");
	gotoxy(33, 18); printf("〧    => 賅萄蒂 摹鷗п輿撮蹂:       〧");
	gotoxy(33, 19); printf("〧                                  〧");
	gotoxy(33, 20); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
	gotoxy(63, 18);

}

//陪檜紫 摹鷗(鼠薯и檜 氈朝 幗瞪, 橈朝 幗瞪)
int levelchoice_with_free() //鼠薯и檜 氈朝 溯漣 詭景
{
	int level;
	do {
		system("cls");
		gotoxy(33, 11); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
		gotoxy(33, 12); printf("〧        << 陪檜紫 摹鷗 >>         〧");
		gotoxy(33, 13); printf("〧                                  〧");
		gotoxy(33, 14); printf("〧            0. 鼠薯и             〧");
		gotoxy(33, 15); printf("〧            1. 蟾晝               〧");
		gotoxy(33, 16); printf("〧            2. 醞晝               〧");
		gotoxy(33, 17); printf("〧            3. 堅晝               〧");
		gotoxy(33, 18); printf("〧            4. 菴煎 陛晦          〧");
		gotoxy(33, 19); printf("〧                                  〧");
		gotoxy(33, 20); printf("〧    => 陪檜紫蒂 摹鷗п輿撮蹂:     〧");
		gotoxy(33, 21); printf("〧                                  〧");
		gotoxy(33, 22); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
		gotoxy(65, 20); //陪檜紫蒂 摹鷗п輿撮蹂 棻擠戲煎 醴憮檜翕
		scanf("%d", &level);//溯漣 殮溘嫡晦
	} while (level < 0 || level >4);
	return level;
}
int levelchoice_without_free()
{
	int level;
	do {
		system("cls");
		gotoxy(33, 11); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
		gotoxy(33, 12); printf("〧        << 陪檜紫 摹鷗 >>         〧");
		gotoxy(33, 13); printf("〧                                  〧");
		gotoxy(33, 14); printf("〧            1. 蟾晝               〧");
		gotoxy(33, 15); printf("〧            2. 醞晝               〧");
		gotoxy(33, 16); printf("〧            3. 堅晝               〧");
		gotoxy(33, 17); printf("〧            4. 菴煎 陛晦          〧");
		gotoxy(33, 18); printf("〧                                  〧");
		gotoxy(33, 19); printf("〧    => 陪檜紫蒂 摹鷗п輿撮蹂:     〧");
		gotoxy(33, 20); printf("〧                                  〧");
		gotoxy(33, 21); printf("〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧〧");
		gotoxy(65, 19);
		scanf("%d", &level);//溯漣 殮溘嫡晦
	} while (level < 1 || level >4);
	return level;
}

//橾衛薑雖
void pause(int* pt, int* resume, int* qe, int line) // 橾衛薑雖衛除, 啪歜 營偃 罹睡, 蟾晦詭景煎 檜翕 罹睡, pause蒂 轎溘й 還(啪歜璽葆棻 觼晦陛 殖塭憮 蜃蹺晦 嬪п)
{
	int st, et, pause_choice;
	st = time(0);
	while (1)
	{
		*resume = 0; //高 蟾晦��
		int stop = 0; //stop檜 1煎 滲ж賊 橾衛薑雖 驍轎
		while (1)// 橾衛 薑雖 詭景 嗥辦晦
		{
			gotoxy(4, line); printf("≠橾衛薑雖≠ 1. 啪歜 營偃  2. 蟾晦 詭景煎 檜翕  => 摹鷗п輿撮蹂: ");
			Sleep(200);
			gotoxy(4, line); printf("≧橾衛薑雖≧ 1. 啪歜 營偃  2. 蟾晦 詭景煎 檜翕  => 摹鷗п輿撮蹂: ");
			Sleep(200);
			if (_kbhit()) //酈爾萄 �鷝扇� 嫦儅ж賊 梭緇歜 醞雖
				break;
		}
		do {
			gotoxy(69, line); // 摹鷗п輿撮蹂 菴煎 檜翕
			printf("                                           "); // 晦襄曖 剪 雖辦堅
			gotoxy(69, line); // 摹鷗п輿撮蹂 菴煎 檜翕
			scanf("%d", &pause_choice);
		} while (pause_choice < 1 || pause_choice >2);

		switch (pause_choice)
		{
		case 1://啪歜營偃 
			gotoxy(4, line); printf("                                                                                                     "); // 橾衛薑雖 旋 雖辦晦
			*resume = 1;
			stop = 1;
			break;

		default:
			gotoxy(4, line); printf("                                                                                                     "); // 橾衛薑雖 旋 雖辦晦
			*qe = 1;
			stop = 1;
		}
		if (stop == 1)
			break; //橾衛薑雖 謙猿
	}
	et = time(0);
	*pt = et - st;
}


//檜 calл熱朝 陝濠曖 顫濠翱蝗縑 蜃醮憮 滲⑽腎橫 餌辨腎歷擠.
void cal(int timespent, char* input, char* answer, int num, int* count, float* maxsp, int px, int py)
{
	int correct, error = 0;
	float speed, accuracy, processivity;
	int i;
	int len = strlen(input); // 僥濠翮 望檜

	(*count)++; //霞ч紫 難薑

	for (i = 0; i < len; i++) //螃顫熱 難薑:
	{
		if (input[i] != answer[i])// 餌辨濠殮溘 陝陝曖 憲だ漯婁 薑港 憲だ漯擊 綠掖п憮 偽雖 彊戲賊
		{
			error += 1;
		}
	}
	//!虜擒 螃顫熱 難薑擊 夤縑憮 и棻賊 檣熱 2偃(ん檣攪滲熱檣 input婁 answer)蒂 賑 熱 氈棻.

	//螃顫陛 嬴棋 薑顫熱
	correct = len - error;

	//顫濠樓紫 : (顫濠熱/勘萼衛除)*60 = 碟渡 顫濠樓紫
	speed = ((len) / (float)(timespent)) * 60;
	/*speed=((correct)/(float)(timespent))*60 ж賊 (薑顫熱/勘萼衛除)*60戲煎 = 碟渡 薑顫顫濠樓紫蒂 燥 熱 氈棻*/

	//譆堅 顫濠 樓紫:
	if (speed > *maxsp)
	{
		*maxsp = speed;
	}
	//薑�挾�= 顫濠熱/僥濠翮曖 望檜 *100
	accuracy = ((float)len / strlen(input)) * 100;

	//霞ч紫
	processivity = ((float)(*count) / num) * 100;

	//轎溘
	gotoxy(79 + px, 22 + py);
	printf("顫濠樓紫: %.f (顫)", speed);
	gotoxy(79 + px, 23 + py);
	printf("譆堅顫濠樓紫: %.f (顫)", *maxsp);
	gotoxy(79 + px, 24 + py);
	printf("薑�挾� : %.f (%%)", accuracy);
	gotoxy(79 + px, 25 + py);
	printf("螃顫熱: %d (偃)", error);
	gotoxy(79 + px, 26 + py);
	printf("霞ч紫: %.1f (%%)", processivity);

	Sleep(10000);// �挫怷� waiting

}


//勘萼衛除, 僥薯熱, 霞ч紫蘋遴お, 譆渠顫濠樓紫, 釭該雖朝 0,0 (嬪纂褻瞰辨)
void cal_timeover(int timespent, int num, int count, float* maxsp, int px, int py)
{
	float processivity;
	processivity = ((float)(count) / num) * 100;

	//晦襄 轎溘 雖辦晦
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
	printf("顫濠樓紫: ----- (顫)");
	gotoxy(79 + px, 24 + py);
	printf("譆堅顫濠: %.f (顫)", *maxsp);
	gotoxy(79 + px, 25 + py);
	printf("薑�挾� : ----- (%%)");
	gotoxy(79 + px, 26 + py);
	printf("螃顫熱: ----- (偃)");
	gotoxy(79 + px, 27 + py);
	printf("霞ч紫: %.1f (%%)", processivity);
	gotoxy(79 + px, 28 + py);
	printf("勘萼衛除: timeover");
}

void score_short(int T, int limit_time, int* short_totalscore) //勘萼衛除婁 薯и衛除
{
	int score;
	int num = 50; // 晦獄薄熱 50薄
	float n, i; //掘除望檜
	n = limit_time / (float)10;

	if (T >= limit_time) //T陛 薯и衛除檜鼻橾陽 0薄
		score = 0;

	else //T陛 薯и衛除嘐虜檣 唳辦 10偃曖 掘除戲煎 釭援橫 薄熱蒂 睡罹и棻.
	{

		for (i = 0; i < limit_time; i += n)
		{
			if ((i <= T) && (T < i + n))
			{
				score = num;
			}
			num -= 5; //薄熱 5馬模
		}
	}

	*short_totalscore += score; //援瞳 薄熱縑 ⑷營 score蒂 蹺陛п 援瞳 薄熱蒂 偵褐п遽棻.
}

void ask_restart()
{
	do {
		gotoxy(10, 15);
		printf("                                         ");
		gotoxy(10, 15);
		printf("營衛濛ж衛啊蝗棲梱? (1-啻 2- 嬴棲蹂): ");
		scanf("%d", &restart);
	} while (restart < 1 || restart>2);
}
