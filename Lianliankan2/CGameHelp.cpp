// CGameHelp.cpp: 实现文件
//

#include "pch.h"
#include "Lianliankan2.h"
#include "CGameHelp.h"
#include "afxdialogex.h"


// CGameHelp 对话框

IMPLEMENT_DYNAMIC(CGameHelp, CDialogEx)

void CGameHelp::InitBackground()
{
	CClientDC dc(this);
	m_Mem.CreateCompatibleDC(&dc);
	HANDLE hHelpBmp = LoadImageW(NULL, _T("D:\\C\\Lianliankan2\\res\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_Mem.SelectObject(hHelpBmp);
}

CGameHelp::CGameHelp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDC_GAME_HELP, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGameHelp::~CGameHelp()
{
}

void CGameHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameHelp, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGameHelp 消息处理程序



BOOL CGameHelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化
	InitBackground();
	UpdateWindow();
	return TRUE;  // retu  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameHelp::OnPaint()
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
		dc.BitBlt(0, 0, 800, 600, &m_Mem, 0, 0, SRCCOPY);
	} // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}
