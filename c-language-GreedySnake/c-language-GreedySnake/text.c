#define _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"
#include<stdio.h>

#include<locale.h>

int main()
{
	//���ó�����Ӧ���ػ���
	setlocale(LC_ALL, "");
	srand(time(NULL));
	Snake snake = { 0 };
	//1.��Ϸ��ʼ - ��ʼ����Ϸ
	GameStart(&snake);
	//2.��Ϸ���� 
	GameRun(&snake);
	//3.��Ϸ���� 
	GameEnd(&snake);
	return 0;
}

