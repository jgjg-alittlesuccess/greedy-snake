#define _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"
#include<stdio.h>

#include<locale.h>

int main()
{
	//设置程序适应本地环境
	setlocale(LC_ALL, "");
	srand(time(NULL));
	Snake snake = { 0 };
	//1.游戏开始 - 初始化游戏
	GameStart(&snake);
	//2.游戏运行 
	GameRun(&snake);
	//3.游戏结束 
	GameEnd(&snake);
	return 0;
}

