#pragma once


// CGameHelp 对话框

class CGameHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CGameHelp)

public:
	void InitBackground();
	CGameHelp(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameHelp();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDC_GAME_HELP };
#endif

protected:
	HICON m_hIcon;
	CDC m_Mem;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
