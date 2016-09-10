#ifndef SDLCLASS_H
#define SDLCLASS_H
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include <stdlib.h>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#pragma execution_character_set("utf-8")
using namespace std;

class SurfaceClass;//基本图像类
class MessageClass; //对话类
class Drawable;//绘制方法类
class CoinSurface;//硬笔类，是基本图像类的复合类
class StringSurface;//文本类
extern SDL_Surface* screen;//屏幕本体
extern Drawable drawable;//全局绘制类对象
extern SDL_Event event;//事件队列
stringstream stream;//格式转换流
inline void initScreen(int width, int height, const string &title, const string &icoPath);//屏幕初始化方法
inline void closeScreen();//屏幕关闭方法
inline void refreshScreen();//屏幕刷新方法
inline void stopScreen(unsigned int ms);//屏幕暂停方法
inline void waitToClick();//等待用户点击方法

class SurfaceClass
{
protected:
	SDL_Surface* pic;
	SDL_Rect offset;
	friend class CoinSurface;
public:
	SurfaceClass()
	{
		pic = nullptr;
	}
	SurfaceClass(const string &path, signed __int16 x = 0, signed __int16 y = 0) :pic(nullptr)
	{
		setNewPic(path);
		setOffset(x, y);
	}
	~SurfaceClass()
	{
		if (pic != nullptr) SDL_FreeSurface(pic);
	}
	void setNewPic(const string &path)//设置新图像
	{
		if (pic != nullptr) SDL_FreeSurface(pic);
		SDL_Surface* loadedImage = IMG_Load(path.c_str());
		if (loadedImage != NULL)
		{
			if (path.find(".png",0) != -1)
				pic = SDL_DisplayFormatAlpha(loadedImage);
			else pic = SDL_DisplayFormat(loadedImage);
			SDL_FreeSurface(loadedImage);
		}
	}
	void setOffset(signed __int16 x, signed __int16 y)//设置新位移
	{
		offset.x = x;
		offset.y = y;
	}
	void toScreen()//显示图像到屏幕
	{
		SDL_BlitSurface(pic, NULL, screen, &offset);
	}
	void gradient(SurfaceClass & aPic,int ms=1000)//过渡当前图像到下一个图像
	{
		int times = ms / 50;
		for (int i = 0; i <= times; i++)
		{
			SDL_SetAlpha(pic, SDL_SRCALPHA, 255 * (times - i) / (double)times);
			SDL_SetAlpha(aPic.pic, SDL_SRCALPHA, 255 * i / (double)times);
			toScreen();
			aPic.toScreen();
			SDL_Flip(screen);
			SDL_Delay(50);
		}
		SDL_SetAlpha(pic, SDL_SRCALPHA, 255);
		SDL_SetAlpha(aPic.pic, SDL_SRCALPHA, 255);
	}
	void copyScreen()//获取整个屏幕内容到该类对象
	{
		if (pic != nullptr) SDL_FreeSurface(pic);
		pic = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w,screen->h,screen->format->BitsPerPixel,
			screen->format->Rmask, screen->format->Gmask,
			screen->format->Bmask, screen->format->Amask);
		SDL_BlitSurface(screen, NULL, pic, NULL);
	}
	void setAlpha(int num)//设置透明度
	{
		SDL_SetAlpha(pic, SDL_SRCALPHA, num);
	}
};

class Drawable
{
private:
	vector<SurfaceClass*> allPic;
public:
	void push(SurfaceClass* aPic)
	{
		allPic.push_back(aPic);
	}
	void cleanAll()
	{
		allPic.clear();
	}
	void drawAll()
	{
		int size = allPic.size();
		for (auto &i : allPic)
		{
			i->toScreen();
		}
	}
};

class MessageClass
{
private:
	TTF_Font *font;
	SDL_Color textColor;
	int x, y;
	const int msPword=20;
	const int wPms = 20;
	int lineSpacing;
public:
	MessageClass(int x,int y,const string &fontName, int fontSize = 20,
		unsigned __int8 red = 0, unsigned __int8 green = 0, unsigned __int8 blue = 0)
	{
		this->x = x;
		this->y = y;
		setFont(fontName, fontSize);
		setColor(red, green, blue);
	}
	~MessageClass()
	{
		TTF_CloseFont(font);
	}
	void setFont(const string &fontName, int fontSize)
	{
		font = TTF_OpenFont(fontName.c_str(), fontSize);
		lineSpacing = fontSize / 2 + fontSize;
	}
	void setColor(unsigned __int8 red, unsigned __int8 green, unsigned __int8 blue)
	{
		textColor.r = red;
		textColor.g = green;
		textColor.b = blue;
	}
	void drawMessage(string* str, int lineNum)//绘制信息
	{
		SDL_Surface** message = new SDL_Surface*[lineNum];
		for (int i = 0; i < lineNum; i++)
		{
			message[i] = TTF_RenderUTF8_Solid(font, str[i].c_str(), textColor);
		}
		SDL_Rect offset;
		offset.x = x;
		for (int i = 0; i < lineNum; i++)
		{
			offset.y = y + i*lineSpacing;
			SDL_BlitSurface(message[i], NULL, screen, &offset);
		}
	}
	void readMessage(string* str,int lineNum)//按照一定的对话速度显示对话
	{
		SDL_Surface** message = new SDL_Surface*[lineNum];
		for (int i = 0; i < lineNum; i++)
		{
			message[i] = TTF_RenderUTF8_Solid(font, str[i].c_str(), textColor);
		}
		SDL_Rect offset;
		offset.x = x;
		SDL_Rect clip;
		clip.x = 0;
		clip.y = 0;
		for (int i = 0; i < lineNum; i++)
		{
			int w = message[i]->w;
			for (int j = 0; j < w; j += wPms)
			{
				drawable.drawAll();
				for (int k = 0; k < i; k++)
				{
					offset.y = y + k*lineSpacing;
					SDL_BlitSurface(message[k], NULL, screen, &offset);
				}
				offset.y = y + i*lineSpacing;
				clip.w = j + wPms;
				SDL_BlitSurface(message[i], &clip, screen, &offset);
				SDL_Flip(screen);
				SDL_Delay(msPword);
			}
		}
		for (int i = 0; i < lineNum; i++)
		{
			SDL_FreeSurface(message[i]);
		}
		delete[]message;
	}
};

class CoinSurface
{
private:
	SurfaceClass coins[7][7];
	int lineNum;
	int num[7];
	int nowNum[7];
public:
	CoinSurface(const string& path, signed __int16 x, signed __int16 y,int xspace,int yspace)
	{
		SDL_Surface* temp = IMG_Load(path.c_str());
		int w = temp->w;
		int h = temp->h;
		SDL_FreeSurface(temp);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				coins[i][j].setNewPic(path);
				coins[i][j].setOffset(x + j*(w+xspace), y + i*(h+yspace));
				SDL_SetAlpha(coins[i][j].pic, SDL_SRCALPHA, 0);
			}
		}
	}

	void setCoinsNum(int coinsNum[], int line)
	{
		lineNum = line;
		for (int i = 0; i < line; i++)
		{
			num[i] = coinsNum[i];
			nowNum[i] = num[i];
		}
		for (int i = 0; i < line; i++)
			for (int j = 0; j < num[i]; j++)
			{
				SDL_SetAlpha(coins[i][j].pic, SDL_SRCALPHA, 255);
			}
	}

	void reset()
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				SDL_SetAlpha(coins[i][j].pic, SDL_SRCALPHA, 0);
			}
		}
	}

	void destoryCoins(int lineNo, int coinsNum)//显示硬币消失的渐变动画
	{
		for (int i = 1; i <= 15; i++)
		{
			for (int j = 0; j < coinsNum; j++)
			{
				SDL_SetAlpha(coins[lineNo][nowNum[lineNo] - j - 1].pic, SDL_SRCALPHA, 255-i*17);
			}
			drawable.drawAll();
			SDL_Flip(screen);
			SDL_Delay(50);
		}
		nowNum[lineNo] -= coinsNum;
	}
	void pushToDrawable()//将所有硬币对象放置到绘图区
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				drawable.push(&coins[i][j]);
			}
		}
	}
};

class StringSurface :public SurfaceClass
{
private:
	TTF_Font *font;
	SDL_Color textColor;
public:
	StringSurface()
	{
		
	}
	StringSurface(const string &fontName, int fontSize = 20, signed __int16 x = 0, signed __int16 y = 0,
		unsigned __int8 red = 0, unsigned __int8 green = 0, unsigned __int8 blue = 0)
	{
		string str = " ";
		setFont(fontName, fontSize);
		setOffset(x, y);
		setColor(red, green, blue);
		pic = TTF_RenderUTF8_Solid(font, str.c_str(), textColor);
	}
	~StringSurface()
	{
		TTF_CloseFont(font);
	}
	void setFont(const string &fontName, int fontSize)
	{
		font = TTF_OpenFont(fontName.c_str(), fontSize);
	}
	void setColor(unsigned __int8 red, unsigned __int8 green, unsigned __int8 blue)
	{
		textColor.r = red;
		textColor.g = green;
		textColor.b = blue;
	}
	void setStr(const string& str)
	{
		if (pic != nullptr) SDL_FreeSurface(pic);
		pic = TTF_RenderUTF8_Solid(font, str.c_str(), textColor);
	}
};


inline void initScreen(int width, int height,const string &title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	TTF_Init();
	SDL_WM_SetCaption(title.c_str(), NULL);
}
inline void closeScreen()
{
	TTF_Quit();
	SDL_Quit();
}
inline void refreshScreen()
{
	SDL_Flip(screen);
}
inline void stopScreen(unsigned int ms)
{
	SDL_Delay(ms);
}

inline void cleanEvent()//清除事件队列
{
	while (SDL_PollEvent(&event)){}
}

inline void waitToClick()
{
	cleanEvent();
	
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				exit(0);
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_KP_ENTER) quit = true;
				else if (event.key.keysym.sym == SDLK_SPACE) quit = true;
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT) quit = true;
			}
		}
	}
}

void toString(string& str, int num)//将数组转换为字符串
{
	stream.clear();
	stream << num;
	stream >> str;
}
string getNumString(int num)//获取数字对应的字符串
{
	string str;
	toString(str, num);
	return str;
}
string getRoundString(int round)//获取回合数的字符串
{
	string str;
	if (round == 0) str = "【玩家】";
	else str = "【AI】";
	return str;
}
string getBinaryString(int num)//获取一个数的二进制字符串
{
	string str;
	switch (num)
	{
	case 0:str = "000"; break;
	case 1:str = "001"; break;
	case 2:str = "010"; break;
	case 3:str = "011"; break;
	case 4:str = "100"; break;
	case 5:str = "101"; break;
	case 6:str = "110"; break;
	case 7:str = "111"; break;
	}
	return str;
}

int getDecimalNum(const string& str)//获取一个字符串的二进制
{
	return (str[0] - '0') * 4 + (str[1] - '0') * 2 + str[2] - '0';
}


string getResultString(int num[],int lineNum)//获取二进制数组异或值
{
	string str;
	int result=0;
	for (int i = 0; i < lineNum; i++) result ^= num[i];
	str = getBinaryString(result);
	return str;
}

void calculate(int num[], int lineNum,int& il,int& in)//计算最佳策略
{
	string result = getResultString(num, lineNum);
	if (result == "000")
	{
		il = -1;
		in = -1;
	}
	else
	{
		int high;
		for (int i = 0; i < 3; i++)
		{
			if (result[i] == '1')
			{
				high = i;
				break;
			}
		}
		for (int i = 0; i < lineNum; i++)
		{
			string temp = getBinaryString(num[i]);
			if (temp[high] == '1')
			{
				il = i;
				int n1 = getDecimalNum(temp);
				int n2 = getDecimalNum(result);
				in = n1 - (n1^n2);
				break;
			}
		}
	}
}

string getPromptString(int num[], int lineNum)//获取最佳策略提示字符串
{
	int il, in;
	string str;
	calculate(num, lineNum, il, in);
	if (il == -1) str = "必败";
	else str = getNumString(il + 1) + "，" + getNumString(in);
	return str;
}

void readFileString(string* strArray, ifstream& inFile, int num)//读取文件流中的字符串
{
	for (int i = 0; i < num; i++)
	{
		getline(inFile, strArray[i]);
	}
}


#endif