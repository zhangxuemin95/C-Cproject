#pragma once
#include "CGameControl.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	bool m_bPause;
	bool m_bFirstPoint;
	HICON m_hIcon;
	CDC m_dcMem; //内存dc
	//背景dc
	CDC m_dcBG;
	//元素内存dc
	CDC m_dcElement;
	//掩码内存dc
	CDC m_dcMask;
	//暂存内存
	CDC m_dcCache;
	//暂停图片的内存
	CDC m_dcPause;
	//游戏区起始点
	CPoint m_ptGameTop;
	//元素图片大小
	CSize m_sizeEle;
	//游戏区域大小
	CRect rt_GameRect;
	bool m_bPlaying; // 游戏状态标识
	int helpNum; // 一场游戏最大帮助次数
	CGameControl m_GameC; //游戏控制类
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	void InitBackground();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	// 调整游戏窗口大小
	void UpdateWindow();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[4], int nVexNum);
protected:
	void InitElement();
public:
	afx_msg void OnClickedBtnStart();
	// 绘制游戏界面
	void UpdateMap();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnHint();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime(int pos);
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnHelp2();
};
