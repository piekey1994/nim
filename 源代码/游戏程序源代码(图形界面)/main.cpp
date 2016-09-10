#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include"sdlClass.h"
#include<stdlib.h>
#include<time.h>
#include<string>
#include<vector>
#include<iostream>
#include<vector>
#include<fstream>
#pragma execution_character_set("utf-8")
using namespace std;

SDL_Surface* screen;
Drawable drawable;
SDL_Event event;

void teachGameEntrance(SurfaceClass& begin);//教学模式入口
void battleGameEntrance(SurfaceClass& begin);//对战模式入口

int main(int argc, char* args[])
{
	initScreen(800, 600, "NIM_GAME");
	//起始界面
	{
		SurfaceClass begin("begin/begin.jpg");
		SurfaceClass button1("begin/button1.png");
		SurfaceClass button2("begin/button2.png");
		SurfaceClass button3("begin/button3.png");
		begin.toScreen();
		refreshScreen();
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) quit = true;
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						int x = event.button.x;
						int y = event.button.y;
						if (x > 335 && x < 452)
						{
							if (y>300 && y < 340)
							{
								begin.toScreen();
								button1.toScreen();
								refreshScreen();
							}
							else if (y>362 && y < 402)
							{
								begin.toScreen();
								button2.toScreen();
								refreshScreen();
							}
							else if (y>424 && y < 464)
							{
								begin.toScreen();
								button3.toScreen();
								refreshScreen();
							}
						}
					}
				}
				else if (event.type == SDL_MOUSEBUTTONUP)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						int x = event.button.x;
						int y = event.button.y;
						if (x > 335 && x < 452)
						{
							if (y>300 && y < 340)
							{
								begin.toScreen();
								refreshScreen();
								stopScreen(500);
								teachGameEntrance(begin);
								quit = true;
							}
							else if (y>362 && y < 402)
							{
								begin.toScreen();
								refreshScreen();
								stopScreen(500);
								battleGameEntrance(begin);
								quit = true;
							}
							else if (y>424 && y < 464)
							{
								begin.toScreen();
								refreshScreen();
								stopScreen(500);
								quit = true;
							}
						}
					}
				}
			}
		}
	}
	closeScreen();
	return 0;
}

void teachGameEntrance(SurfaceClass& begin)
{
	string sayArray[5];
	//序章
	{
		ifstream inFile("say/input1.say");
		SurfaceClass title1("title/1.jpg");
		SurfaceClass bg1("bg/1.jpg");
		SurfaceClass fg1("visual/me.png");
		SurfaceClass face1("face/me.png");
		SurfaceClass dialogueBox("say/say.png");
		MessageClass say(250, 425, "font/fzltzh.ttf");
		drawable.cleanAll();
		drawable.push(&bg1);
		drawable.push(&fg1);
		drawable.push(&dialogueBox);
		drawable.push(&face1);
		begin.gradient(title1, 1000);
		title1.toScreen();
		refreshScreen();
		stopScreen(2500);
		title1.gradient(bg1, 1000);
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		fg1.setNewPic("visual/me2.png");
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		fg1.setNewPic("visual/they.png");
		bg1.setNewPic("bg/2.jpg");
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		fg1.setNewPic("visual/they2.png");
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		fg1.setNewPic("visual/me.png");
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		fg1.setNewPic("visual/me2.png");
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		SurfaceClass temp;
		temp.copyScreen();
		SurfaceClass title2("title/2.jpg");
		temp.gradient(title2, 1000);
		inFile.close();
	}
	//教学
	{
		ifstream inFile("say/input2.say");
		SurfaceClass title2("title/2.jpg");
		SurfaceClass bg("bg/3.jpg");
		SurfaceClass fg("visual/me.png");
		SurfaceClass dialogue1("other/empty.png");
		SurfaceClass dialogue2("other/empty.png");
		CoinSurface coins("other/coin.jpg",227,124,6,8);
		SurfaceClass face("face/me.png");
		SurfaceClass dialogueBox("say/say.png");
		MessageClass say(250, 425, "font/fzltzh.ttf");
		MessageClass leftSay(73, 52, "font/fzltzh.ttf",18);
		MessageClass rightSay(653, 52, "font/fzltzh.ttf", 18);
		StringSurface* strArray[5];
		for (int i = 0; i < 5; i++)
		{
			strArray[i] = new StringSurface("font/fzltzh.ttf",20,250,425+i*30,0,0,0);
		}
		drawable.cleanAll();
		drawable.push(&bg);
		drawable.push(&fg);
		drawable.push(&dialogue1);
		drawable.push(&dialogue2);
		drawable.push(&dialogueBox);
		drawable.push(&face);
		for (int i = 0; i < 5; i++) drawable.push(strArray[i]);
		coins.pushToDrawable();

		title2.toScreen();
		refreshScreen();
		stopScreen(1500);
		title2.gradient(bg,1000);
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		int cn[3] = { 3, 4, 5 };
		coins.setCoinsNum(cn, 3);
		fg.setNewPic("visual/battle.png");
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 3);
		say.readMessage(sayArray, 3);
		readFileString(sayArray, inFile, 5);
		waitToClick();
		strArray[0]->setStr(sayArray[0]);
		drawable.drawAll();
		stopScreen(200);
		dialogue2.setNewPic("other/right.png");
		string temp[2];
		temp[0] = "第1行1枚";
		temp[1] = "消失吧";
		rightSay.readMessage(temp, 2);
		stopScreen(2000);
		coins.destoryCoins(0, 1);
		strArray[1]->setStr(sayArray[1]);
		drawable.drawAll();
		stopScreen(200);
		dialogue2.setNewPic("other/empty.png");
		dialogue1.setNewPic("other/left.png");
		temp[0] = "第2行4枚";
		temp[1] = "我拿下了";
		leftSay.readMessage(temp, 2);
		stopScreen(2000);
		coins.destoryCoins(1, 4);
		strArray[2]->setStr(sayArray[2]);
		drawable.drawAll();
		stopScreen(200);
		dialogue1.setNewPic("other/empty.png");
		dialogue2.setNewPic("other/right.png");
		temp[0] = "第3行3枚";
		temp[1] = "消失吧";
		rightSay.readMessage(temp, 2);
		stopScreen(2000);
		coins.destoryCoins(2, 3);
		strArray[3]->setStr(sayArray[3]);
		drawable.drawAll();
		stopScreen(200);
		dialogue2.setNewPic("other/empty.png");
		dialogue1.setNewPic("other/left.png");
		temp[0] = "第1行第2枚";
		temp[1] = "我拿下了";
		leftSay.readMessage(temp, 2);
		stopScreen(2000);
		coins.destoryCoins(0, 2);
		strArray[4]->setStr(sayArray[4]);
		drawable.drawAll();
		stopScreen(200);
		dialogue1.setNewPic("other/empty.png");
		dialogue2.setNewPic("other/right.png");
		temp[0] = "第3行第2枚";
		temp[1] = "消失吧";
		rightSay.readMessage(temp, 2);
		stopScreen(2000);
		coins.destoryCoins(2, 2);
		stopScreen(500);
		fg.setNewPic("visual/battleend.png");
		temp[0] = "想战胜我";
		temp[1] = "还早100年呢";
		rightSay.readMessage(temp, 2);
		waitToClick();
		for (int i = 0; i < 5; i++) strArray[i]->setStr(" ");
		dialogue2.setNewPic("other/empty.png");
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 4);
		say.readMessage(sayArray, 4);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();

		drawable.cleanAll();
		SurfaceClass fg2("other/empty.png");
		SurfaceClass coin30("other/num.png");
		StringSurface coinNum("font/fzltzh.ttf", 48, 433, 175, 0, 0, 0);
		coinNum.setStr("30");
		fg.setNewPic("visual/battle.png");
		dialogue1.setNewPic("other/empty.png");
		dialogue2.setNewPic("other/empty.png");
		drawable.push(&bg);
		drawable.push(&fg);
		drawable.push(&coin30);
		drawable.push(&coinNum);
		drawable.push(&fg2);
		drawable.push(&dialogue1);
		drawable.push(&dialogue2);
		drawable.push(&dialogueBox);
		drawable.push(&face);
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();

		int takenNum;
		int sum = 30;
		sayArray[0] = "轮到你了";
		sayArray[1] = "（请按键盘的1~7，其他按键无效）";
		while (true)
		{
			takenNum = sum % 8;
			sum -= takenNum;
			dialogue1.setNewPic("other/empty.png");
			dialogue2.setNewPic("other/right.png");
			temp[0] = "那我就拿";
			temp[1] = getNumString(takenNum)+"枚好了";
			rightSay.readMessage(temp, 2);
			stopScreen(1500);
			coinNum.setStr(getNumString(sum));
			drawable.drawAll();
			if (sum == 0)
			{
				fg.setNewPic("visual/battleend.png");
				temp[0] = "想战胜我";
				temp[1] = "还早100年呢";
				rightSay.readMessage(temp, 2);
				waitToClick();
				break;
			}
			else
			{
				dialogue2.setNewPic("other/empty.png");
				say.readMessage(sayArray, 2);
				
				bool inputQuit = false;
				while (!inputQuit)
				{
					while (SDL_PollEvent(&event))
					{
						if (event.type == SDL_QUIT)
						{
							exit(0);
						}
						else if (event.type == SDL_KEYUP)
						{
							if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP1)
							{
								takenNum = 1;
								inputQuit = true;
							}
							else if (event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP2)
							{
								takenNum = 2;
								inputQuit = true;
							}
							else if (event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP3)
							{
								takenNum = 3;
								inputQuit = true;
							}
							else if (event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_KP4)
							{
								takenNum = 4;
								inputQuit = true;
							}
							else if (event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_KP5)
							{
								takenNum = 5;
								inputQuit = true;
							}
							else if (event.key.keysym.sym == SDLK_6 || event.key.keysym.sym == SDLK_KP6)
							{
								takenNum = 6;
								inputQuit = true;
							}
							else if (event.key.keysym.sym == SDLK_7 || event.key.keysym.sym == SDLK_KP7)
							{
								takenNum = 7;
								inputQuit = true;
							}
						}
					}
				}
				sum -= takenNum;
				dialogue1.setNewPic("other/left.png");
				temp[0] = "这" + getNumString(takenNum) + "枚";
				temp[1] = "在下取走了";
				leftSay.readMessage(temp, 2);
				stopScreen(1500);
				coinNum.setStr(getNumString(sum));
				drawable.drawAll();
			}
		}
		dialogue2.setNewPic("other/empty.png");
		fg2.setNewPic("visual/me.png");
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 1);
		say.setColor(232,0,0);
		say.readMessage(sayArray, 1);
		waitToClick();
		say.setColor(0, 0, 0);
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 3);
		say.readMessage(sayArray, 3);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.setColor(232, 0, 0);
		say.readMessage(sayArray, 2);
		say.setColor(0, 0, 0);
		waitToClick();
		fg2.setNewPic("visual/me2.png");
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 3);
		say.setColor(232, 0, 0);
		say.readMessage(sayArray, 3);
		say.setColor(0, 0, 0);
		waitToClick();
		fg.setNewPic("other/leftcoin.png");
		fg2.setNewPic("other/empty.png");
		coin30.setNewPic("other/empty.png");
		coinNum.setStr("");
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.setColor(232, 0, 0);
		say.readMessage(sayArray, 2);
		say.setColor(0, 0, 0);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		fg.setNewPic("other/leftcoin2.png");
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		fg.setNewPic("other/leftcoin3.png");
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		fg2.setNewPic("visual/me.png");
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 1);
		say.readMessage(sayArray, 1);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		readFileString(sayArray, inFile, 2);
		say.readMessage(sayArray, 2);
		waitToClick();
		SurfaceClass endtemp;
		endtemp.copyScreen();
		battleGameEntrance(endtemp);
	}
}

void battleGameEntrance(SurfaceClass& begin)
{
	srand((unsigned int)time(0));
	SurfaceClass title("title/3.jpg");
	SurfaceClass bg("bg/4.jpg");
	SurfaceClass button1("battle/button1.png");
	SurfaceClass button2("battle/button2.png");
	SurfaceClass face1("face/player.png");
	SurfaceClass face2("face/ai.png");
	begin.gradient(title, 1000);
	title.toScreen();
	refreshScreen();
	waitToClick();
	title.gradient(bg,500);

	//七个矩形初始化
	SurfaceClass rect[7];
	for (int i = 0; i < 7; i++)
	{
		rect[i].setNewPic("battle/rect.jpg");
		rect[i].setOffset(149,108+i*58);
		rect[i].setAlpha(0);
	} 

	//七行硬币初始化
	CoinSurface coin("battle/coin2.jpg", 159, 114, 6, 17);

	//文字部分
	StringSurface barrier("font/fzhy.ttf", 25, 14, 10, 239, 239, 239);//回合+关卡
	StringSurface* coinsNum[7];//行数个数
	for (int i = 0; i < 7; i++)
	{
		coinsNum[i] = new StringSurface("font/fzhy.ttf", 40, 39, 115 + i * 57, 118, 118, 118);
	}
	StringSurface playerName("font/fzhy.ttf", 20, 640, 60, 180, 180, 180);//玩家姓名
	StringSurface playerLineNum("font/fzhy.ttf", 20, 648, 107, 180, 180, 180);//玩家行数
	StringSurface playerNum("font/fzhy.ttf", 20, 648, 136, 180, 180, 180);//玩家个数
	StringSurface* binary[7];//二进制数组
	for (int i = 0; i < 7; i++)
	{
		binary[i] = new StringSurface("font/fzhy.ttf", 20,576,207+i*23,8,8,8);
	}
	StringSurface result("font/fzhy.ttf", 20, 576,379,8,8,8);//异或结果
	StringSurface tips("font/fzhy.ttf", 20, 676, 213, 255, 255, 255);//提示数
	StringSurface prompt("font/fzhy.ttf", 20, 678, 300, 8, 8, 8);//提示内容
	StringSurface aiName("font/fzhy.ttf", 20, 640, 452, 180, 180, 180);//Ai名
	StringSurface aiLine("font/fzhy.ttf", 20, 648, 496, 180, 180, 180);//AI行数
	StringSurface aiNum("font/fzhy.ttf", 20, 648, 523, 180, 180, 180);//AI个数
	
	//绘画区开始记录
	drawable.cleanAll();
	drawable.push(&bg);
	drawable.push(&face1);
	drawable.push(&face2);
	drawable.push(&button1);
	drawable.push(&button2);
	for (int i = 0; i < 7; i++) drawable.push(&rect[i]);
	coin.pushToDrawable();
	drawable.push(&barrier);
	for (int i = 0; i < 7; i++) drawable.push(coinsNum[i]);
	drawable.push(&playerName);
	drawable.push(&playerLineNum);
	drawable.push(&playerNum);
	for (int i = 0; i < 7; i++) drawable.push(binary[i]);
	drawable.push(&result);
	drawable.push(&tips);
	drawable.push(&prompt);
	drawable.push(&aiName);
	drawable.push(&aiLine);
	drawable.push(&aiNum);

	//从配置文件中读取提示个数
	ifstream inFile("battle/config.txt");
	int tipsNum;
	inFile >> tipsNum;
	int tipsNumBack = tipsNum;

	//胜者初始化决定第一轮的先手
	int winner;
	if (rand() % 2 == 0) winner = 0;
	else winner = 1;

	//回合
	int round = winner;

	//每行个数
	int cn[7];
	for (int i = 0; i < 7; i++) cn[i] = 0;

	//行数个数
	int il, in;

	//积分
	int score = 0;

	//游戏开始
	for (int i = 0; i < 6; i++)
	{
		//初始化各类信息
		tipsNum = tipsNumBack;
		barrier.setStr("关卡" + getNumString(i+1) + ":" + getRoundString(winner) + "回合");
		for (int j = 0; j < i + 2; j++)
		{
			cn[j] = rand() % 7 + 1;
			coinsNum[j]->setStr(getNumString(j + 1) + ":" + getNumString(cn[j]) + "$");
			rect[j].setAlpha(255);
		}
		coin.setCoinsNum(cn, i + 2);
		playerName.setStr("【玩家】");
		playerLineNum.setStr("行数：");
		playerNum.setStr("个数：");
		for (int j = 0; j < 7; j++)
		{
			binary[j]->setStr(getBinaryString(cn[j]));
		}
		result.setStr(getResultString(cn, i + 2));
		tips.setStr("提示"+getNumString(tipsNum));
		aiName.setStr("【AI】(IQ"+getNumString(i*20)+"%)");
		aiLine.setStr("行数：");
		aiNum.setStr("个数：");
		drawable.drawAll();
		refreshScreen();
		bool isover = false;//对战结束标志
		//对战开始
		while (!isover)
		{
			bool beclick = false;
			if (round == 0)
			{
				bool quit=false;
				while (!quit)
				{
					while (SDL_PollEvent(&event))
					{
						if (event.type == SDL_QUIT)
						{
							exit(0);
						}
						else if (event.type == SDL_MOUSEBUTTONDOWN)
						{
							if (event.button.button == SDL_BUTTON_LEFT)
							{
								int x = event.button.x;
								int y = event.button.y;
								if (x > 665 && x < 737 && y>212 && y < 238)
								{
									button2.setNewPic("battle/button2down.png");
									drawable.drawAll();
									refreshScreen();
								}
								else if (x > 251 && x < 369 && y>524 && y < 550)
								{
									button1.setNewPic("battle/button1down.png");
									drawable.drawAll();
									refreshScreen();
								}
							}
						}
						else if (event.type == SDL_MOUSEBUTTONUP)
						{
							if (event.button.button == SDL_BUTTON_LEFT)
							{
								int x = event.button.x;
								int y = event.button.y;
								if (x > 665 && x < 737 && y>212 && y < 238)
								{
									button2.setNewPic("battle/button2.png");
									drawable.drawAll();
									refreshScreen();
									if (tipsNum > 0 && beclick == false)
									{
										tipsNum--;
										beclick = true;
										tips.setStr("提示" + getNumString(tipsNum));
										prompt.setStr(getPromptString(cn, i + 2));
										drawable.drawAll();
										refreshScreen();
									}
								}
								else if (x > 251 && x < 369 && y>524 && y < 550)
								{
									button1.setNewPic("battle/button1.png");
									drawable.drawAll();
									refreshScreen();
									std::cin >> il >> in;
									cleanEvent();
									if (il <= i + 2 && il>0 && in <= cn[il - 1] && in>0)
									{
										aiLine.setStr("行数：");
										aiNum.setStr("个数：");
										playerLineNum.setStr("行数：" + getNumString(il));
										playerNum.setStr("个数：" + getNumString(in));
										drawable.drawAll();
										refreshScreen();
										stopScreen(1000);
										coin.destoryCoins(il - 1, in);
										cn[il - 1] -= in;
										coinsNum[il - 1]->setStr(getNumString(il) + ":" + getNumString(cn[il-1]) + "$");
										binary[il - 1]->setStr(getBinaryString(cn[il - 1]));
										result.setStr(getResultString(cn, i + 2));
										prompt.setStr(" ");
										drawable.drawAll();
										refreshScreen();
										stopScreen(200);
										//判断胜负
										bool iswin = true;
										for (int j = 0; j < i + 2; j++)
										{
											if (cn[j] != 0)
											{
												iswin = false;
												break;
											}
										}
										if (iswin == true)
										{
											face1.setNewPic("face/playerwin.png");
											face2.setNewPic("face/ailose.png");
											drawable.drawAll();
											refreshScreen();
											face1.setNewPic("face/player.png");
											face2.setNewPic("face/ai.png");
											stopScreen(2000);
											isover = true;
											winner = 0;
											round = 0;
											score += (i + 1) * 10;
											quit = true;
										}
										else
										{
											round = 1;
											barrier.setStr("关卡" + getNumString(i + 1) + ":" + getRoundString(round) + "回合");
											drawable.drawAll();
											refreshScreen();
											quit = true;
										}
									}
									else
									{
										prompt.setStr("有误");
										drawable.drawAll();
										refreshScreen();
										prompt.setStr(" ");
									}
								}
							}
						}
					}
				}
			}
			else
			{
				calculate(cn, i + 2, il, in);
				if (il == -1 || rand()%5>=i)
				{
					do
					{
						il = rand() % (i + 2);
					} while (cn[il] == 0);
					in = rand() % cn[il] + 1;
				}
				cn[il] -= in;
				coinsNum[il]->setStr(getNumString(il+1) + ":" + getNumString(cn[il]) + "$");
				playerLineNum.setStr("行数：");
				playerNum.setStr("个数：");
				aiLine.setStr("行数：" + getNumString(il + 1));
				aiNum.setStr("个数：" + getNumString(in));
				drawable.drawAll();
				refreshScreen();
				stopScreen(2000);
				coin.destoryCoins(il, in);
				binary[il]->setStr(getBinaryString(cn[il]));
				result.setStr(getResultString(cn, i + 2));
				prompt.setStr(" ");
				drawable.drawAll();
				refreshScreen();
				stopScreen(200);
				//判断胜负
				bool iswin = true;
				for (int j = 0; j < i + 2; j++)
				{
					if (cn[j] != 0)
					{
						iswin = false;
						break;
					}
				}
				if (iswin == true)
				{
					face1.setNewPic("face/playerlose.png");
					face2.setNewPic("face/aiwin.png");
					drawable.drawAll();
					refreshScreen();
					face1.setNewPic("face/player.png");
					face2.setNewPic("face/ai.png");
					stopScreen(2000);
					isover = true;
					winner = 1;
					round = 1;
				}
				else
				{
					round = 0;
					barrier.setStr("关卡" + getNumString(i + 1) + ":" + getRoundString(round) + "回合");
					drawable.drawAll();
					refreshScreen();
				}
			}
		}
	}
	SurfaceClass temp;
	temp.copyScreen();
	SurfaceClass end("bg/5.jpg");
	temp.gradient(end);
	StringSurface endScore("font/fzhy.ttf", 48, 241, 451, 255, 255, 255);
	endScore.setStr("得分：" + getNumString(score)+"/210");
	end.toScreen();
	endScore.toScreen();
	refreshScreen();
	waitToClick();
	for (int i = 0; i < 7; i++)
	{
		delete coinsNum[i];
		delete binary[i];
	}
}
