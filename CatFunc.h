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
DWORD process_id;
HANDLE process_hwnd;

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
}

// SetTimer回调函数
VOID CALLBACK countDownTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	cat->WriteInt(process_hwnd, (LPVOID)0x00186AAC, COUNT_DOWN, 4);
}
