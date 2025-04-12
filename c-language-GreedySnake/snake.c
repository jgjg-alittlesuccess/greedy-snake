#define _CRT_SECURE_NO_WARNINGS 1
#include"snake.h"

//1.��Ϸ��ʼ - ��ʼ����Ϸ
void SetPos(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(handle, pos);
}

void WelcomeToGame()
{
	//��λ���
	SetPos(40, 15);
	printf("��ӭ����̰����С��Ϸ��");
	SetPos(40, 25);
	system("pause");
	system("cls");
	SetPos(25, 15);
	printf("ʹ�á�.��.��.�������ߵ��ƶ���F3�Ǽ��٣�F4�Ǽ���");
	SetPos(40, 25);
	system("pause");
	system("cls");
}

void CreateMap()
{
	//��
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//��
	SetPos(0, 26);
	for (i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//��
	for (i = 1; i <= 25; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	//��
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

		//ͷ�巨
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
	//��ӡ����
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

	//���겻�ܺ��ߵ������ͻ
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

	//��ӡʳ��
	SetPos(x, y);
	wprintf(L"%lc", FOOD);
}

void GameStart(pSnake ps)
{
	//����̨���ڵ�����
	system("mode con cols=100 lines=30");
	system("title ̰����");
	
	//�������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼����ľ��
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(handle, &cursor_info);
	cursor_info.bVisible = false;
	SetConsoleCursorInfo(handle, &cursor_info);
	
	//��ӡ��ӭ����
	WelcomeToGame();
	//������ͼ
	CreateMap();	
	//��ʼ��̰����
	InitSnake(ps);
	//����ʳ��
	CreateFood(ps);
}

//2.��Ϸ���� 

void PrintHelpInfo()//��ӡ������Ϣ
{
	SetPos(64, 15);
	printf("1.����ײǽ������ҧ�Լ���");
	SetPos(64, 16);
	printf("2.ʹ�á������������������ߵ��ƶ���");
	SetPos(64, 17);
	printf("3.F3���٣�F4���١�");
	SetPos(64, 18);
	printf("4.ESC�˳����ո���ͣ��");
	SetPos(64, 20);
	printf("��������@��Ȩ");
}

int NextIsFood(pSnake ps, pSnakeNode pNext)//�ж���һ��λ���Ƿ���ʳ��
{
	if (ps->_pFood->x == pNext->x && ps->_pFood->y == pNext->y)
		return 1;
	else return 0;
}

void KillByWall(pSnake ps)//���Ƿ�ײǽ
{
	if (ps->_psnake->x == 0 || ps->_psnake->x == 56 || ps->_psnake->y == 0 || ps->_psnake->y == 26)
	{
		ps->_Status = KILL_BY_WALL;
	}
}
void  KillBySelf(pSnake ps)//���Ƿ���ɱ
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

void SnakeMove(pSnake ps)//�ߵ��ƶ�
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

	//�ж���һ��λ���Ƿ���ʳ��
	if (NextIsFood(ps, pNext))//��
	{
		//ͷ��
		pNext->next = ps->_psnake;
		ps->_psnake = pNext;
		//��ӡ����
		SetPos(ps->_psnake->x, ps->_psnake->y);
		wprintf(L"%lc", BODY);
		//����ʳ��
		free(ps->_pFood);
		ps->_Score += ps->_FoodWeight;
		CreateFood(ps);
	}
	else//����
	{
		//ͷ��
		pNext->next = ps->_psnake;
		ps->_psnake = pNext;
		//ɾ�����ڵ㲢��ӡ����
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

	//���Ƿ�ײǽ
	KillByWall(ps);
	//���Ƿ���ɱ
	KillBySelf(ps);
}

void GameRun(pSnake ps)
{
	PrintHelpInfo();
	do
	{
		//��ӡ�����÷�
		SetPos(64, 10);
		printf("�÷֣�%05d", ps->_Score);
		SetPos(64, 11);
		printf("ÿ��ʳ��ķ�����%2d", ps->_FoodWeight);

		//�жϰ������
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
		else if (PRESS_KET(VK_F3))//����
		{
			if (ps->_SleepTime >= 80)
			{
				ps->_SleepTime -= 30;
				ps->_FoodWeight += 2;
			}
		}		
		else if (PRESS_KET(VK_F4))//����
		{
			if (ps->_SleepTime <= 320)
			{
				ps->_SleepTime += 30;
				ps->_FoodWeight -= 2;
			}
		}

		//�ߵ��ƶ�
		Sleep(ps->_SleepTime);
		SnakeMove(ps);

	} while (ps->_Status == OK);
}

//3.��Ϸ���� 
void GameEnd(pSnake ps)
{
	SetPos(20, 12);
	switch (ps->_Status)
	{
	case END_NORMAL:
		printf("�˳���Ϸ\n");
		break;	
	case KILL_BY_SELF:
		printf("ײ�Լ��ˣ���Ϸ������\n");
		break;	
	case KILL_BY_WALL:
		printf("ײǽ�ˣ���Ϸ������\n");
		break;
	}
	SetPos(0, 27);
	//�ͷ�����ڵ�
	pSnakeNode cur = ps->_psnake;
	while (cur)
	{
		pSnakeNode del = cur;
		cur = cur->next;
		free(del);
	}
	ps->_psnake = NULL;
}