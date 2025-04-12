#define _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"

//1.游戏开始 - 初始化游戏
void SetPos(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(handle, pos);
}

void WelcomeToGame()
{
	//定位光标
	SetPos(40, 15);
	printf("欢迎来到贪吃蛇小游戏！");
	SetPos(40, 25);
	system("pause");
	system("cls");
	SetPos(25, 15);
	printf("使用↑.↓.←.→控制蛇的移动，F3是加速，F4是减速");
	SetPos(40, 25);
	system("pause");
	system("cls");
}

void CreateMap()
{
	//上
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//下
	SetPos(0, 26);
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//左
	for (i = 1; i <= 25; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	//右
	for (i = 1; i <= 25; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}
}

void InitSnake(pSnake ps)
{
	pSnakeNode cur = NULL;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		cur = (pSnakeNode)malloc(sizeof(SnakeNode));
		if (cur == NULL)
		{
			perror("InitSnake()::malloc()");
			return;
		}
		cur->x = POS_X + 2 * i;
		cur->y = POS_Y;
		cur->next = NULL;

		//头插法
		if (ps->_psnake == NULL)
		{
			ps->_psnake = cur;
		}
		else
		{
			cur->next = ps->_psnake;
			ps->_psnake = cur;
		}
	}
	//打印蛇身
	cur = ps->_psnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	ps->_Status = OK;
	ps->_Score = 0;
	ps->_pFood = NULL;
	ps->_SleepTime = 200;
	ps->_FoodWeight = 10;
	ps->_Dir = RIGHT;
}

void CreateFood(pSnake ps)
{
	int x;
	int y;
	again:
	do
	{
		x = rand() % 53 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);

	//坐标不能和蛇的身体冲突
	pSnakeNode cur = ps->_psnake;
	if (cur->x == x && cur->y == y)
	{
		goto again;
	}
	pSnakeNode pFood = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pFood == NULL)
	{
		perror("CreateFood()::malloc()");
		return;
	}
	pFood->x = x;
	pFood->y = y;
	ps->_pFood = pFood;

	//打印食物
	SetPos(x, y);
	wprintf(L"%lc", FOOD);
}

void GameStart(pSnake ps)
{
	//控制台窗口的设置
	system("mode con cols=100 lines=30");
	system("title 贪吃蛇");
	
	//光标隐藏
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出的句柄
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(handle, &cursor_info);
	cursor_info.bVisible = false;
	SetConsoleCursorInfo(handle, &cursor_info);
	
	//打印欢迎界面
	WelcomeToGame();
	//创建地图
	CreateMap();	
	//初始化贪吃蛇
	InitSnake(ps);
	//创建食物
	CreateFood(ps);
}

//2.游戏运行 

void PrintHelpInfo()//打印辅助信息
{
	SetPos(64, 15);
	printf("1.不能撞墙，不能咬自己。");
	SetPos(64, 16);
	printf("2.使用↑、↓、←、→控制蛇的移动。");
	SetPos(64, 17);
	printf("3.F3加速，F4减速。");
	SetPos(64, 18);
	printf("4.ESC退出，空格暂停。");
	SetPos(64, 20);
	printf("几个几个@版权");
}

int NextIsFood(pSnake ps, pSnakeNode pNext)//判断下一个位置是否是食物
{
	if (ps->_pFood->x == pNext->x && ps->_pFood->y == pNext->y)
		return 1;
	else return 0;
}

void KillByWall(pSnake ps)//蛇是否撞墙
{
	if (ps->_psnake->x == 0 || ps->_psnake->x == 56 || ps->_psnake->y == 0 || ps->_psnake->y == 26)
	{
		ps->_Status = KILL_BY_WALL;
	}
}
void  KillBySelf(pSnake ps)//蛇是否自杀
{
	pSnakeNode cur = ps->_psnake->next;
	while (cur)
	{
		if (ps->_psnake->x == cur->x && ps->_psnake->y == cur->y)
		{
			ps->_Status = KILL_BY_SELF;
		}
		cur = cur->next;
	}
}

void SnakeMove(pSnake ps)//蛇的移动
{
	pSnakeNode pNext = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pNext == NULL)
	{
		perror("SnakeMove()::malloc()");
		return;
	}
	pNext->next = NULL;
	switch (ps->_Dir)
	{
	case UP:
		pNext->x = ps->_psnake->x;
		pNext->y = ps->_psnake->y - 1;
		break;
	case DOWN:
		pNext->x = ps->_psnake->x;
		pNext->y = ps->_psnake->y + 1;
		break;	
	case LEFT:	
		pNext->x = ps->_psnake->x - 2;
		pNext->y = ps->_psnake->y;
		break;
	case RIGHT:
		pNext->x = ps->_psnake->x + 2;
		pNext->y = ps->_psnake->y;
		break;
	}

	//判断下一个位置是否是食物
	if (NextIsFood(ps, pNext))//是
	{
		//头插
		pNext->next = ps->_psnake;
		ps->_psnake = pNext;
		//打印蛇身
		SetPos(ps->_psnake->x, ps->_psnake->y);
		wprintf(L"%lc", BODY);
		//处理食物
		free(ps->_pFood);
		ps->_Score += ps->_FoodWeight;
		CreateFood(ps);
	}
	else//不是
	{
		//头插
		pNext->next = ps->_psnake;
		ps->_psnake = pNext;
		//删除最后节点并打印蛇身
		SetPos(ps->_psnake->x, ps->_psnake->y);
		wprintf(L"%lc", BODY);
		pSnakeNode cur = ps->_psnake;
		while (cur->next->next)
		{
			cur = cur->next;
		}
		SetPos(cur->next->x, cur->next->y);
		printf("  ");
		free(cur->next);
		cur->next = NULL;
	}

	//蛇是否撞墙
	KillByWall(ps);
	//蛇是否自杀
	KillBySelf(ps);
}

void GameRun(pSnake ps)
{
	PrintHelpInfo();
	do
	{
		//打印按键得分
		SetPos(64, 10);
		printf("得分：%05d", ps->_Score);
		SetPos(64, 11);
		printf("每个食物的分数：%2d", ps->_FoodWeight);

		//判断按键情况
		if (PRESS_KET(VK_UP) && ps->_Dir != DOWN)
		{
			ps->_Dir = UP;
		}		
		else if (PRESS_KET(VK_DOWN) && ps->_Dir != UP)
		{
			ps->_Dir = DOWN;
		}		
		else if (PRESS_KET(VK_LEFT) && ps->_Dir != RIGHT)
		{
			ps->_Dir = LEFT;
		}		
		else if (PRESS_KET(VK_RIGHT) && ps->_Dir != LEFT)
		{
			ps->_Dir = RIGHT;
		}		
		else if (PRESS_KET(VK_ESCAPE))
		{
			ps->_Status = END_NORMAL;
		}		
		else if (PRESS_KET(VK_SPACE))
		{
			while (1)
			{
				Sleep(100);
				if (PRESS_KET(VK_SPACE))
				{
					break;
				}
			}
		}		
		else if (PRESS_KET(VK_F3))//加速
		{
			if (ps->_SleepTime >= 80)
			{
				ps->_SleepTime -= 30;
				ps->_FoodWeight += 2;
			}
		}		
		else if (PRESS_KET(VK_F4))//减速
		{
			if (ps->_SleepTime <= 320)
			{
				ps->_SleepTime += 30;
				ps->_FoodWeight -= 2;
			}
		}

		//蛇的移动
		Sleep(ps->_SleepTime);
		SnakeMove(ps);

	} while (ps->_Status == OK);
}

//3.游戏结束 
void GameEnd(pSnake ps)
{
	SetPos(20, 12);
	switch (ps->_Status)
	{
	case END_NORMAL:
		printf("退出游戏\n");
		break;	
	case KILL_BY_SELF:
		printf("撞自己了，游戏结束。\n");
		break;	
	case KILL_BY_WALL:
		printf("撞墙了，游戏结束。\n");
		break;
	}
	SetPos(0, 27);
	//释放蛇身节点
	pSnakeNode cur = ps->_psnake;
	while (cur)
	{
		pSnakeNode del = cur;
		cur = cur->next;
		free(del);
	}
	ps->_psnake = NULL;
}