#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<windows.h>
//#include<stdbool.h>

//int main()
//{
//	system("mode con cols=50 lines=20");//�����������ִ��ϵͳ����
//	printf("hehe\n");
//	return 0;
//}
//int main()
//{
//	system("title ̰����");
//	printf("hehe\n");
//	return 0;
//}
//int main()
//{
//	system("title ̰����");
//	printf("hehe\n");
//	COORD pos = { 3,5 };
//	return 0;
//}
//typedef struct _CONSOLE_CURSOR_INFO {
//	DWORD dwSize;
//	BOOL bVisible;
//}CONSOLE_CURSOR_INFO,*PCONSOLE_CURSOR_INFO;
//int main()
//{
//	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼����ľ��
//	//CONSOLE_CURSOR_INFO cursor_info;
//	//GetConsoleCursorInfo(handle,&cursor_info);
//	//SetConsoleCursorInfo(handle,&cursor_info);
//	//cursor_info.bVisible = false;
//	//int xh=getchar();
//	COORD pos = { 5,20 };
//	SetConsoleCursorPosition(handle, pos);
//	int ch = getchar();
//	COORD pos2 = { 20,5 };
//	SetConsoleCursorPosition(handle, pos2);
//	putchar(ch);
//	return 0;
//}

//void SetPos(int x, int y)
//{
//	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD pos = { x,y };
//	SetConsoleCursorPosition(handle, pos);
//}
//#define PRESS_KET(vk)(GetAsyncKeyState(vk)&0x1?1:0)//���vk��������ֵ��Ӧ�İ����Ƿ񱻰�������������1��û�з���0
//
//#include<locale.h>
//int main()
//{
//	setlocale(LC_ALL, "");
//	wchar_t ch1 = L'��';
//	wchar_t ch2 = L'��';
//
//	printf("ab\n");
//
//	wprintf(L"%lc\n", ch1);
//	wprintf(L"%lc\n", ch2);
//	wprintf(L"%lc\n", ch1);
//	wprintf(L"%lc\n", ch2);
//	return 0;
//}