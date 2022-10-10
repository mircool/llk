#include "framework.h"
#include "llk.h"
#include "llkDlg.h"
#include "afxdialogex.h"
#include "Cat.h"
#pragma comment(lib,"CAT.lib")

Cat* cat = BlackCat();

//QQ游戏 - 连连看角色版
const LPCTSTR game_caption = TEXT("QQ游戏 - 连连看角色版");
const int COUNT_DOWN = 10000; //倒计时时间
const int COUNT_DOWN_TIME_ID = 1; //倒计时事件id
HWND game_hwnd; //窗口句柄
RECT game_rect; //窗口坐标
DWORD process_id; //进程id
HANDLE process_hwnd; //进程句柄
BYTE chess_data[11][19]; //棋盘数组
POINT p1, p2; //两个点是否能消除

//初始化
void init()
{
	game_hwnd = cat->FindWindow(NULL, game_caption);
	if (game_hwnd == 0)
	{
		CatBox("请先打开游戏");
		return;
	}
	cat->GetClientRect(game_hwnd, &game_rect);
	process_id = cat->GetWindowProcessId(game_hwnd);
	process_hwnd = cat->OpenProcess(process_id);
	cat->ReadProcessMemory(process_hwnd, (LPVOID)0x00199F60, (LPVOID)&chess_data, 11 * 19);
}

// SetTimer回调函数
VOID CALLBACK countDownTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	cat->WriteInt(process_hwnd, (LPVOID)0x00186AAC, COUNT_DOWN, 4);
}

//点击两个棋子
//第一个棋子 29,243,46,257,宽高(17,14)
VOID clickTwoPoints(POINT p1, POINT p2)
{
	cat->GetClientRect(game_hwnd, &game_rect); //获取游戏坐标
	cat->MoveTo(29 + game_rect.left + p1.y * 39, 243 + game_rect.top + p1.x * 44);
	cat->Delay(1);
	cat->LeftClick();
	cat->Delay(1);
	cat->MoveTo(29 + game_rect.left + p2.y * 39, 243 + game_rect.top + p2.x * 44);
	cat->Delay(1);
	cat->LeftClick();
}
