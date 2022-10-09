// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 CAT_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// CAT_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef CAT_EXPORTS
#define CAT_API __declspec(dllexport)
#else
#define CAT_API __declspec(dllimport)
#endif
#include <Windows.h>
#include <iostream>

// 调试输出对话框
#define CatBox(fmt, ...); \
CString str; \
str.Format(CString(fmt), __VA_ARGS__); \
AfxMessageBox(str);


// SetTimer回调函数

// VOID CALLBACK TimerProc(  HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);



class Cat {
public:
	// 窗口
	virtual HWND FindWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName) = 0;
	virtual int GetClientRect(HWND hWnd, LPRECT lpRect) = 0;
	virtual int SetWindowTop(HWND hWnd) = 0;
	// 键鼠
	virtual int MoveTo(int x, int y) = 0;
	virtual void LeftClick() = 0;
	virtual int GetCursorPos(LPPOINT lpPoint) = 0;

	// 进程线程
	virtual DWORD GetWindowProcessId(HWND hWnd) = 0;
	virtual HANDLE OpenProcess(DWORD dwProcessId) = 0;
	
	// 内存
	virtual long long ReadInt(HANDLE hProcess, LPCVOID lpBaseAddress, int nBytes) = 0;
	virtual int WriteInt(HANDLE hProcess, LPVOID lpBaseAddress, long long num, int nBytes) = 0;
	virtual int ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize) = 0;

	// 系统
	virtual void Delay(DWORD dwMilliseconds) = 0;
	virtual UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) = 0;
	virtual BOOL KillTimer(UINT_PTR uIDEvent) = 0;
	

};

class MyCat : public Cat {
public:
	// 窗口
	virtual HWND FindWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName);		// 查找窗口
	virtual int GetClientRect(HWND hWnd, LPRECT lpRect);		// 获取窗口客户区域在屏幕上的位置
	virtual int SetWindowTop(HWND hWnd);	// 设置窗口置顶


	// 键鼠
	virtual int MoveTo(int x, int y);
	virtual void LeftClick();
	virtual int GetCursorPos(LPPOINT lpPoint);

	// 进程线程
	virtual DWORD GetWindowProcessId(HWND hWnd);
	virtual HANDLE OpenProcess(DWORD dwProcessId);


	// 内存
	virtual long long ReadInt(HANDLE hProcess, LPCVOID lpBaseAddress, int nBytes);	
	virtual int WriteInt(HANDLE hProcess, LPVOID lpBaseAddress, long long num, int nBytes);
	virtual int ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize);

	// 系统
	virtual void Delay(DWORD dwMilliseconds);
	virtual UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc);
	virtual BOOL KillTimer(UINT_PTR uIDEvent);
};

CAT_API Cat* BlackCat();

