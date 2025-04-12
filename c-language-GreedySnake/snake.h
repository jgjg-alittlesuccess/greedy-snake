#pragma once
#include<locale.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>

#define WALL L'□'
#define BODY L'●'
#define FOOD L'★'

#define POS_X 24
#define POS_Y 5

#define PRESS_KET(vk)(GetAsyncKeyState(vk)&0x1?1:0)

enum DIRECTION
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

enum GAME_STATUS
{
	OK,
	END_NORMAL,
	KILL_BY_WALL,
	KILL_BY_SELF
};

//贪吃蛇的节点
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode,*pSnakeNode;

//贪吃蛇的结构
typedef struct Snake
{
	pSnakeNode _psnake;//指向贪吃蛇头节点的指针
	pSnakeNode _pFood;//指向食物节点的指针
	int _Score;//贪吃蛇积累的总分
	int _FoodWeight;//一个食物的分数
	int _SleepTime;//每走一步休息的时间，时间越短速度越快
	enum DIRECTION _Dir;//描述蛇的方向
	enum GAME_STATUS _Status;//游戏的状态：正常，退出，撞墙，撞到自己
}Snake,*pSnake;

//1.游戏开始 - 初始化游戏
void GameStart(pSnake ps);
void WelcomeToGame();//游戏开始的欢迎界面
void CreateMap();//打印地图
void InitSnake(pSnake ps);//初始化蛇
void CreateFood(pSnake ps);//创建食物
//2.游戏运行 
void GameRun(pSnake ps);
void PrintHelpInfo();//打印辅助信息
void SnakeMove(pSnake ps);//蛇的移动
int NextIsFood(pSnake ps, pSnakeNode pNext);//判断下一个位置是否是食物
void KillByWall(pSnake ps);//蛇是否撞墙
void  KillBySelf(pSnake ps);//蛇是否自杀
//3.游戏结束 
void GameEnd(pSnake ps);