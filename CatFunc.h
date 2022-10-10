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
DWORD process_id; //����id
HANDLE process_hwnd; //���̾��
BYTE chess_data[11][19]; //��������
POINT p1, p2; //�������Ƿ�������

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
	cat->ReadProcessMemory(process_hwnd, (LPVOID)0x00199F60, (LPVOID)&chess_data, 11 * 19);
}

// SetTimer�ص�����
VOID CALLBACK countDownTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	cat->WriteInt(process_hwnd, (LPVOID)0x00186AAC, COUNT_DOWN, 4);
}

//�����������
//��һ������ 29,243,46,257,���(17,14)
VOID clickTwoPoints(POINT p1, POINT p2)
{
	cat->GetClientRect(game_hwnd, &game_rect); //��ȡ��Ϸ����
	cat->MoveTo(29 + game_rect.left + p1.y * 39, 243 + game_rect.top + p1.x * 44);
	cat->Delay(1);
	cat->LeftClick();
	cat->Delay(1);
	cat->MoveTo(29 + game_rect.left + p2.y * 39, 243 + game_rect.top + p2.x * 44);
	cat->Delay(1);
	cat->LeftClick();
}
