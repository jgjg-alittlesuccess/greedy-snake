#pragma once
#include<locale.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>

#define WALL L'��'
#define BODY L'��'
#define FOOD L'��'

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

//̰���ߵĽڵ�
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode,*pSnakeNode;

//̰���ߵĽṹ
typedef struct Snake
{
	pSnakeNode _psnake;//ָ��̰����ͷ�ڵ��ָ��
	pSnakeNode _pFood;//ָ��ʳ��ڵ��ָ��
	int _Score;//̰���߻��۵��ܷ�
	int _FoodWeight;//һ��ʳ��ķ���
	int _SleepTime;//ÿ��һ����Ϣ��ʱ�䣬ʱ��Խ���ٶ�Խ��
	enum DIRECTION _Dir;//�����ߵķ���
	enum GAME_STATUS _Status;//��Ϸ��״̬���������˳���ײǽ��ײ���Լ�
}Snake,*pSnake;

//1.��Ϸ��ʼ - ��ʼ����Ϸ
void GameStart(pSnake ps);
void WelcomeToGame();//��Ϸ��ʼ�Ļ�ӭ����
void CreateMap();//��ӡ��ͼ
void InitSnake(pSnake ps);//��ʼ����
void CreateFood(pSnake ps);//����ʳ��
//2.��Ϸ���� 
void GameRun(pSnake ps);
void PrintHelpInfo();//��ӡ������Ϣ
void SnakeMove(pSnake ps);//�ߵ��ƶ�
int NextIsFood(pSnake ps, pSnakeNode pNext);//�ж���һ��λ���Ƿ���ʳ��
void KillByWall(pSnake ps);//���Ƿ�ײǽ
void  KillBySelf(pSnake ps);//���Ƿ���ɱ
//3.��Ϸ���� 
void GameEnd(pSnake ps);