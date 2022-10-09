#include "framework.h"
#include "llk.h"
#include "llkDlg.h"
#include "afxdialogex.h"
#include "Cat.h"
#pragma comment(lib,"CAT.lib")

Cat* cat = BlackCat();

//QQ��Ϸ - ��������ɫ��
const LPCTSTR game_caption = TEXT("QQ��Ϸ - ��������ɫ��");
const int COUNT_DOWN = 10000; //����ʱʱ��
const int COUNT_DOWN_TIME_ID = 1; //����ʱ�¼�id
HWND game_hwnd; //���ھ��
RECT game_rect; //��������
DWORD process_id;
HANDLE process_hwnd;

//��ʼ��
void init()
{
	game_hwnd = cat->FindWindow(NULL, game_caption);
	if (game_hwnd == 0)
	{
		CatBox("���ȴ���Ϸ");
		return;
	}
	cat->GetClientRect(game_hwnd, &game_rect);
	process_id = cat->GetWindowProcessId(game_hwnd);
	process_hwnd = cat->OpenProcess(process_id);
}

// SetTimer�ص�����
VOID CALLBACK countDownTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	cat->WriteInt(process_hwnd, (LPVOID)0x00186AAC, COUNT_DOWN, 4);
}
