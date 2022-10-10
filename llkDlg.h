
// llkDlg.h: 头文件
//

#pragma once


// CllkDlg 对话框
class CllkDlg : public CDialogEx
{
// 构造
public:
	CllkDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAutostart();
	afx_msg void OnBnClickedTopwindow();
private:
	CButton m_topwindow;
	CButton m_clearcountdown;
public:
	afx_msg void OnBnClickedClearcountdown();
	afx_msg void OnBnClickedClearonepair();
	afx_msg void OnBnClickedAutopaly();
};
