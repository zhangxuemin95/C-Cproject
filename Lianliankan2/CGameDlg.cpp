// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "Lianliankan2.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "CGameControl.h"
#include "global.h"
#include "CGameHelp.h"
#include <cstring>
// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bFirstPoint = true;
	rt_GameRect.top = 50; rt_GameRect.left = 20; rt_GameRect.right = 20 + 40 * CGameControl::s_nCols; rt_GameRect.bottom = 50 + 40 * CGameControl::s_nRows;
	m_ptGameTop.x = 20; m_ptGameTop.y = 50;
	m_sizeEle.cx = 40;
	m_sizeEle.cy = 40;
	m_bPlaying = false;
	helpNum = 0;
	m_bPause = true;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Game_Time, m_GameProgress);
}

void CGameDlg::InitBackground()
{
	HANDLE hBmpimage = LoadImageW(NULL, _T("D:\\C\\Lianliankan2\\res\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建兼容dc
	CClientDC dc(this);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(hBmpimage);
	m_dcMem.CreateCompatibleDC(&dc);
	/// <summary>
	/// 一开始没给dmMem创建兼容dc导致打不开界面
	/// </summary>
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	//将位图选进dc
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CGameDlg::OnBnClickedBtnRefresh)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_HINT, &CGameDlg::OnBnClickedBtnHint)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_HELP2, &CGameDlg::OnBnClickedBtnHelp2)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化
	InitBackground();
	UpdateWindow();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
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
		//创建CPaintDC对象
		CPaintDC dc(this);
		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	}
}


// 调整游戏窗口大小
void CGameDlg::UpdateWindow()
{
	// TODO: 在此处添加实现代码.
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect tipFrame;
	tipFrame.top = rt_GameRect.top + nRow * m_sizeEle.cy;
	tipFrame.bottom = tipFrame.top + m_sizeEle.cy;
	tipFrame.left = rt_GameRect.left + nCol * m_sizeEle.cx;
	tipFrame.right = tipFrame.left + m_sizeEle.cx;
	dc.FrameRect(tipFrame, &brush);
}


void CGameDlg::InitElement()
{
	// TODO: 在此处添加实现代码.
	//获得当前视频dc
	CClientDC dc(this);
	// 加载图片资源
	HANDLE hBmp = LoadImageW(NULL, _T("D:\\C\\Lianliankan2\\res\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc);//创建兼容的内存dc
	m_dcElement.SelectObject(hBmp);//将图片加入内存dc
	HANDLE hMask = LoadImageW(NULL, _T("D:\\C\\Lianliankan2\\res\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
	HANDLE hPause = LoadImageW(NULL, _T("D:\\C\\Lianliankan2\\res\\pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(hPause);
}


void CGameDlg::DrawTipLine(Vertex avPath[4], int nVexNum)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pOldPen = dc.SelectObject(&penLine);
	for (int i = 0; i < nVexNum - 1; i++) {
		dc.MoveTo(m_ptGameTop.x + m_sizeEle.cx * avPath[i].nCol + m_sizeEle.cx / 2, m_ptGameTop.y + m_sizeEle.cy * avPath[i].nRow + m_sizeEle.cy / 2);
		dc.LineTo(m_ptGameTop.x + m_sizeEle.cx * avPath[i + 1].nCol + m_sizeEle.cx / 2, m_ptGameTop.y + m_sizeEle.cy * avPath[i + 1].nRow + m_sizeEle.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

void CGameDlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameC.StartGame();
	UpdateMap();
	m_bPlaying = true; // 游戏正在进行
	m_bPause = false;
	CWnd* cSeBkBtnMy = GetDlgItem(IDC_BTN_START);
	cSeBkBtnMy->EnableWindow(false);
	m_GameProgress.SetRange(0, 5 * 60);
	m_GameProgress.SetStep(-1);
	m_GameProgress.SetPos(5 * 60);
	this->SetTimer(PLAT_TIMER_ID, 1000, NULL);
	DrawGameTime(m_GameProgress.GetPos());
}


// 绘制游戏界面
void CGameDlg::UpdateMap()
{
	// TODO: 在此处添加实现代码.
	//计算图片的顶点坐标与图片大小
	int nElemH = m_sizeEle.cy;
	int nElemW = m_sizeEle.cx;
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	//获取行数和列数
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	m_dcMem.BitBlt(rt_GameRect.left, rt_GameRect.top, rt_GameRect.Width(), rt_GameRect.Height(), &m_dcBG, rt_GameRect.left, rt_GameRect.top, SRCCOPY);
	//绘图
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			int nElemVal = m_GameC.GetElement(i, j);
			//将图片与掩码相或, 边保留, 图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			//将元素图片相与, 边保留, 图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH/*图片所在的区域*/, SRCAND);
		}//因为所有元素的图片时一整张图,所以要扣出要加载的一张图,后面的x, y就是抠图时开始的位置
	}
	InvalidateRect(NULL);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 判断鼠标点击区域是否合法
	if (point.x > rt_GameRect.right || point.x < rt_GameRect.left || point.y < rt_GameRect.top || point.y > rt_GameRect.bottom) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else
	{
		int nRow = (point.y - m_ptGameTop.y) / m_sizeEle.cy; int nCol = (point.x - m_ptGameTop.x) / m_sizeEle.cx;
		// [0 , 10)行 [0 , 16)列
		if (m_bFirstPoint) {
			DrawTipFrame(nRow, nCol);
			m_GameC.SetFirstPoint(nRow, nCol);
		}
		else
		{
			DrawTipFrame(nRow, nCol);
			m_GameC.SetSecondPoint(nRow, nCol);
			//判断是否是相同图片
			Vertex avPath[4];
			int nVexNum = 0;
			if (m_GameC.Link(avPath, nVexNum)) {
				DrawTipLine(avPath, nVexNum);
				UpdateMap();
				}
			Sleep(200);
			InvalidateRect(rt_GameRect, FALSE);
			//判断胜负
			int result = m_GameC.IsWin(m_GameProgress.GetPos());
			if (result == WIN) {
				m_bPlaying = false; // 游戏已结束进行
				CWnd* cSeBkBtnMy = GetDlgItem(IDC_BTN_START);
				cSeBkBtnMy->EnableWindow(true);
				MessageBox(TEXT("恭喜获胜!"), TEXT("提示"), MB_OK);
				m_GameC.Close();
			}
			if(result == NOTIME)
			{
				m_bPlaying = false; // 游戏已结束进行
				KillTimer(IDC_Game_Time);
				CWnd* cSeBkBtnMy = GetDlgItem(IDC_BTN_START);
				cSeBkBtnMy->EnableWindow(true);
				MessageBox(TEXT("很遗憾, 没时间了!"), TEXT("提示"), MB_OK);
				m_GameC.Close();
			}
		}
		m_bFirstPoint = !m_bFirstPoint; // 改为第二次
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
}


void CGameDlg::OnBnClickedBtnRefresh()
{
	if (m_bPlaying) // 游戏正在运行
	{
		m_GameC.Reset();
		UpdateMap();
		Sleep(200);
		InvalidateRect(rt_GameRect, FALSE);
	}
	else {
		MessageBox(TEXT("游戏还未开始！"), TEXT("提示"), MB_OK);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_GameC.Close();
	CDialogEx::OnClose();
}


void CGameDlg::OnBnClickedBtnHint()
{
		if (m_bPlaying) {
			if (helpNum < 10) {
				Vertex avPath[4];
				int nVexNum = 0;
				if (!m_GameC.Help(avPath, nVexNum)) MessageBox(TEXT("无可消去项，请重排！"), TEXT("提示"), MB_OK);
				else
				{
					DrawTipLine(avPath, nVexNum);
					helpNum++;
					Sleep(200);
				}
			}
			else
			{
				MessageBox(TEXT("已超过最大提示次数"), TEXT("提示"), MB_OK);
				CWnd* cSeBkBtnMy = GetDlgItem(IDC_BTN_HINT);
				cSeBkBtnMy->EnableWindow(false);
			}
		}
		// TODO: 在此添加控件通知处理程序代码
		else {
			MessageBox(TEXT("游戏还未开始！"), TEXT("提示"), MB_OK);
		}
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAT_TIMER_ID && m_bPlaying && !m_bPause) {
		m_GameProgress.StepIt();
		DrawGameTime(m_GameProgress.GetPos());
		if (m_GameProgress.GetPos() == 0) {
			m_bPlaying = false; // 游戏已结束进行
			KillTimer(IDC_Game_Time);
			CWnd* cSeBkBtnMy = GetDlgItem(IDC_BTN_START);
			cSeBkBtnMy->EnableWindow(true);
			MessageBox(TEXT("很遗憾, 没时间了!"), TEXT("提示"), MB_OK);
			m_GameC.Close();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::DrawGameTime(int pos)
{
	CString t;
	t.Format(_T("%d"), pos);
	SetDlgItemText(IDC_TEXT_TIME, t);
	// TODO: 在此处添加实现代码.
}




void CGameDlg::OnBnClickedBtnPause()
{
	if (!m_bPlaying) {
		MessageBox(TEXT("游戏还未开始！"), TEXT("提示"), MB_OK);
	}
	else
	{
		if (m_bPause == false) {
			m_bPause = !m_bPause;
			// TODO: 在此添加控件通知处理程序代码
			m_dcMem.BitBlt(rt_GameRect.left, rt_GameRect.top, rt_GameRect.Width(), rt_GameRect.Height(), &m_dcBG, rt_GameRect.left, rt_GameRect.top, SRCCOPY);
			m_dcMem.BitBlt(rt_GameRect.left, rt_GameRect.top, 640, 400, &m_dcPause, 0, 0, SRCCOPY);
			InvalidateRect(NULL);
			SetDlgItemTextW(IDC_BTN_PAUSE, TEXT("继续游戏"));
		}
		else
		{
			m_bPause = !m_bPause;
			UpdateMap();
			SetDlgItemTextW(IDC_BTN_PAUSE, TEXT("暂停游戏"));
		}
	}
}


void CGameDlg::OnBnClickedBtnHelp2()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	CGameHelp dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}
