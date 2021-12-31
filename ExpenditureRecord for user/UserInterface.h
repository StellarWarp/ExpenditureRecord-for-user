#pragma once
#include <stdio.h>  
#include <windows.h>  
#include <conio.h>  
#include"LinkedList.h"
#include"Printer.h"
HANDLE handle_in;
HANDLE handle_out;
CONSOLE_SCREEN_BUFFER_INFO csbi;        //定义窗口缓冲区信息结构体  

//将光标移到坐标为(x,y)的位置  
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(handle_out, pos);
}
struct displaywindow
{
	COORD pos1;
	COORD pos2;
	char name[20];
	char top[4];
	char frame_v[4];
	char frame_h[4];
	char coner[4];
	WORD a_top;
	WORD a_frame_v;
	WORD a_frame_h;
	WORD baclground;
};
typedef struct displaywindow win_display;
win_display initial_window(int x1, int y1, int x2, int y2)
{
	struct displaywindow win;
	win.pos1.X = x1;
	win.pos1.Y = y1;
	win.pos2.X = x2;
	win.pos2.Y = y2;
	strcpy_s(win.name, 20, "");
	strcpy_s(win.top, 2, "-");
	strcpy_s(win.frame_h, 2, "-");
	strcpy_s(win.frame_v, 2, "|");
	strcpy_s(win.coner, 2, "+");
	win.a_top = NULL;
	win.a_frame_h = NULL;
	win.a_frame_v = NULL;
	win.baclground = NULL;
	return win;
}
void frame_window(win_display  win)
{
	COORD pos = win.pos1;
	DWORD written;
	int hight = win.pos2.Y - win.pos1.Y;
	int lenth = win.pos2.X - win.pos1.X + 1;
	GetConsoleScreenBufferInfo(handle_out, &csbi);
	WriteConsoleOutputCharacter(handle_out, win.coner, 1, pos, &written);
	pos.X++;
	for (int i = 2; i < lenth; i++)
	{
		WriteConsoleOutputCharacter(handle_out, win.frame_h, 1, pos, &written);
		pos.X++;
	}
	WriteConsoleOutputCharacter(handle_out, win.coner, 1, pos, &written);
	//FillConsoleOutputAttribute(handle_out, win.top, lenth, pos, &written);
	pos = win.pos1;
	pos.X += 2;
	WriteConsoleOutputCharacter(handle_out, win.name, strlen(win.name), pos, &written);
	pos = win.pos1;
	pos.Y++;
	for (int i = 1; i < hight; i++)
	{
		WriteConsoleOutputCharacter(handle_out, win.frame_v, 1, pos, &written);
		pos.X++;
		FillConsoleOutputAttribute(handle_out, win.baclground, lenth - 2, pos, &written);
		pos.X += lenth - 2;
		WriteConsoleOutputCharacter(handle_out, win.frame_v, 1, pos, &written);
		pos.X -= lenth - 1;
		pos.Y++;
	}
	WriteConsoleOutputCharacter(handle_out, win.coner, 1, pos, &written);
	pos.X++;
	for (int i = 2; i < lenth; i++)
	{
		WriteConsoleOutputCharacter(handle_out, win.frame_h, 1, pos, &written);
		pos.X++;
	}
	WriteConsoleOutputCharacter(handle_out, win.coner, 1, pos, &written);
}
void scroll_window(win_display  win, int dir, int top_modify)
{
	SMALL_RECT winarea;      //定义移动区域
	winarea.Left = win.pos1.X + 1 ;
	winarea.Top = win.pos1.Y + 1 + top_modify;
	winarea.Right = win.pos2.X - 1;
	winarea.Bottom = win.pos2.Y - 1;
	SMALL_RECT scroll;      //定义移动区域
	COORD pos;     //移动位置
	CHAR_INFO chFill;       //定义填充字符
	chFill.Char.AsciiChar = ' ';
	chFill.Attributes = csbi.wAttributes;
	if (dir == 1)
	{
		pos.X = winarea.Left;
		pos.Y = winarea.Top - 1;
	}
	else if (dir == -1)
	{
		pos.X = winarea.Left;
		pos.Y = winarea.Top + 1;
	}
	ScrollConsoleScreenBuffer(handle_out, &winarea, &winarea, pos, &chFill); //移动文本
}
struct display_info
{
	win_display win;
	struct displayArray_Record displayarray;
	SMALL_RECT winarea;
	int cup_display;//显示容量
	int top_display;
	int bottom_display;
};
struct display_info display_list_ini(win_display win, struct displayArray_Record displayarray)
{
	struct display_info info;
	info.win = win;
	info.displayarray = displayarray;
	info.winarea.Left = win.pos1.X + 1;
	info.winarea.Top = win.pos1.Y + 1;
	info.winarea.Right = win.pos2.X - 1;
	info.winarea.Bottom = win.pos2.Y - 1;
	info.cup_display = info.winarea.Bottom - info.winarea.Top;//显示容量
	info.top_display = 0;
	info.bottom_display = info.cup_display - 1;
	gotoxy(info.winarea.Left, info.winarea.Top);
	printf("     日期    名字	 额度      类型       方式      地点       细节");
	for (int i = 0; i < info.cup_display; i++)
	{
		gotoxy(info.winarea.Left, info.winarea.Top + i + 1);
		print_Record(*displayarray.Array[i]);
	}
	return  info;
}
void display_list(int dir, struct display_info* info)
{
	//显示区域
	SMALL_RECT winarea = info->winarea;
	win_display win = info->win;
	winarea.Left = info->winarea.Left;
	winarea.Top = info->winarea.Top;
	winarea.Right = info->winarea.Right;
	winarea.Bottom = info->winarea.Bottom;
	//首尾端控制
	int maxi = info->displayarray.num - 1;
	if (info->top_display == 0 && dir == -1) return;
	if (info->bottom_display == maxi && dir == 1) return;
	//滚动
	scroll_window(win, dir, 1);
	int i;
	if (dir == 1)
	{
		gotoxy(winarea.Left, winarea.Bottom);
		info->top_display++;
		info->bottom_display++;
		i = info->bottom_display;
	}
	else if (dir == -1)
	{
		gotoxy(winarea.Left, winarea.Top + 1);
		info->top_display--;
		info->bottom_display--;
		i = info->top_display;
	}
	int printform[6] = { 12,22,30,38,48,58 };
	//name,amount,type,method,site,detail
	print_Record(*info->displayarray.Array[i]);
}
//显示鼠标所在位置  
void DisplayMousePosition(COORD pos)
{
	COORD dis = { 0, 0 };        //显示鼠标位置  
	WORD att = FOREGROUND_BLUE | FOREGROUND_INTENSITY; //文本属性  
	DWORD w = NULL;
	GetConsoleScreenBufferInfo(handle_out, &csbi);  //获得窗口缓冲区信息  
	printf("X = %3d, Y = %3d", (int)pos.X, (int)pos.Y);
	FillConsoleOutputAttribute(handle_out, att, 16, dis, &w);  //填充文本属性  
}
int UI_initial()
{
	handle_in = GetStdHandle(STD_INPUT_HANDLE);      //获得标准输入设备句柄 
	//设置模式
	DWORD mode = NULL;
	GetConsoleMode(handle_in, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode |= ENABLE_MOUSE_INPUT;
	SetConsoleMode(handle_in, mode);
	COORD size = { 80, 25 };  //窗口缓冲区大小  
	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄  
	GetConsoleScreenBufferInfo(handle_out, &csbi);  //获得窗口缓冲区信息  
	SetConsoleScreenBufferSize(handle_out, size);   //设置窗口缓冲区大小  
}
int UI_off()
{
	CloseHandle(handle_out);
	CloseHandle(handle_in);
}

void MouseOP(struct display_info* info)
{
	for (;;)
	{
		INPUT_RECORD mouserec;      //定义输入事件结构体  
		DWORD res;      //用于存储读取记录  
		COORD pos;      //用于存储鼠标当前位置  
		ReadConsoleInput(handle_in, &mouserec, 1, &res);      //读取输入事件  
		pos = mouserec.Event.MouseEvent.dwMousePosition;    //获得当前鼠标位置  
		gotoxy(0, 0);  //设置鼠标位置  
		DisplayMousePosition(pos);      //显示鼠标位置  
		if (mouserec.EventType == MOUSE_EVENT)    //如果当前为鼠标事件  
		{
			gotoxy(pos.X, pos.Y);
			////单击鼠标左键，输出字符A  
			//if (mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			//{
			//	break;
			//}
			////单击鼠标右键，输出字符B  
			//if (mouserec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			//{
			//	break;
			//}
			//双击退出  
			if (mouserec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			{
				break;
			}
			if (mouserec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED && mouserec.Event.MouseEvent.dwButtonState == 0x00800000)
			{
				display_list(-1, info);
			}
			if (mouserec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED && mouserec.Event.MouseEvent.dwButtonState == 0xff800000)
			{
				display_list(1, info);
			}
		}
	}
}