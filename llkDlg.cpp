// llkDlg.cpp: 实现文件
//


#include "pch.h"
#include "CatFunc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CllkDlg 对话框


CllkDlg::CllkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CllkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TopWindow, m_topwindow);
	DDX_Control(pDX, IDC_ClearCountDown, m_clearcountdown);
}

BEGIN_MESSAGE_MAP(CllkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_AutoStart, &CllkDlg::OnBnClickedAutostart)
	ON_BN_CLICKED(IDC_TopWindow, &CllkDlg::OnBnClickedTopwindow)
	ON_BN_CLICKED(IDC_ClearCountDown, &CllkDlg::OnBnClickedClearcountdown)
END_MESSAGE_MAP()


// CllkDlg 消息处理程序

BOOL CllkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE); // 设置大图标
	SetIcon(m_hIcon, FALSE); // 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CllkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CllkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CllkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//------------------------------------------------------
POINT old_pos;

void CllkDlg::OnBnClickedAutostart()
{
	init();
	//设置窗口置顶
	cat->SetWindowTop(game_hwnd);
	//保存鼠标原来的位置
	cat->GetCursorPos(&old_pos);
	cat->MoveTo(793 + game_rect.left, 699 + game_rect.top);
	cat->Delay(10);
	cat->LeftClick();
	//还原鼠标位置
	cat->Delay(10);
	cat->MoveTo(old_pos.x, old_pos.y);
}

//游戏窗口置顶
void CllkDlg::OnBnClickedTopwindow()
{
	init();

	UpdateData(TRUE);
	if (m_topwindow.GetCheck())
	{
		cat->SetWindowTop(game_hwnd);
	}
	else
	{
		//取消置顶
		::SetWindowPos(game_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

//取消倒计时
void CllkDlg::OnBnClickedClearcountdown()
{
	init();
	if (m_clearcountdown.GetCheck())
	{
		cat->SetTimer(COUNT_DOWN_TIME_ID, 1 * 1000, countDownTimerProc);
	}
	else
	{
		cat->KillTimer(COUNT_DOWN_TIME_ID);
	}
}
