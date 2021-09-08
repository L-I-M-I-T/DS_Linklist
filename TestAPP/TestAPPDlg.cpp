
// TestAPPDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TestAPP.h"
#include "TestAPPDlg.h"
#include "afxdialogex.h"
#include "NULLDlg.h"
#include "SUCDlg.h"
#include "INPUTDlg1.h"
#include "INPUTDlg2.h"
#include "tool.h"
#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define cx(t) (int((t)*scale+startPoint.x))
#define cy(t) (int((t)*scale+startPoint.y))

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
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


// CTestAPPDlg 对话框

static UINT BASED_CODE indicators[] =
{
	IDS_STATUS
};

CTestAPPDlg::CTestAPPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	coin = 0;
	index = 0;
	nID = 0;
	nStyle = 0;
	nWidth = 0;
	startPoint.x = 0;
	startPoint.y = 0;
	endPoint.x = 0;
	endPoint.y = 0;
	topLeft.x = 0;
	topLeft.y = 0;
	scale = 0.8;
	rVector.x = 0;
	rVector.y = 0;
	type = NONE;
	length = 0;
	lt = -2;
	ll = -2;
	pos = NONE;
	value = NONE;
	moveFlag = false;
	view = NONE;
	L = NULL;
}

void CTestAPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestAPPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32774, &CTestAPPDlg::OnCreateSingle)
	ON_COMMAND(ID_32775, &CTestAPPDlg::OnCreateDouble)
	ON_COMMAND(ID_32776, &CTestAPPDlg::OnCreateLoop)
	ON_COMMAND(ID_32777, &CTestAPPDlg::OnDestroy)
	ON_COMMAND(ID_32781, &CTestAPPDlg::OnInsert)
	ON_COMMAND(ID_32779, &CTestAPPDlg::OnLocate)
	ON_COMMAND(ID_32780, &CTestAPPDlg::OnFind)
	ON_COMMAND(ID_32782, &CTestAPPDlg::OnDelete)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_32780, &CTestAPPDlg::OnUpdate32780)
	ON_UPDATE_COMMAND_UI(ID_32781, &CTestAPPDlg::OnUpdate32781)
	ON_UPDATE_COMMAND_UI(ID_32782, &CTestAPPDlg::OnUpdate32782)
	ON_UPDATE_COMMAND_UI(ID_32777, &CTestAPPDlg::OnUpdate32777)
	ON_UPDATE_COMMAND_UI(ID_32774, &CTestAPPDlg::OnUpdate32774)
	ON_UPDATE_COMMAND_UI(ID_32775, &CTestAPPDlg::OnUpdate32775)
	ON_UPDATE_COMMAND_UI(ID_32776, &CTestAPPDlg::OnUpdate32776)
	ON_WM_INITMENUPOPUP()
	ON_UPDATE_COMMAND_UI(ID_32779, &CTestAPPDlg::OnUpdate32779)
END_MESSAGE_MAP()


// CTestAPPDlg 消息处理程序

BOOL CTestAPPDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;
	GetClientRect(rect);
	m_bar.Create(this);
	m_bar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	index = this->m_bar.CommandToIndex(IDS_STATUS);
	m_bar.GetPaneInfo(index, nID, nStyle, nWidth);
	m_bar.SetPaneInfo(index, nID, nStyle, rect.Width());
	m_bar.GetStatusBarCtrl().SetMinHeight(25);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, AFX_IDW_CONTROLBAR_FIRST);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestAPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestAPPDlg::OnPaint()
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
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_bar.m_hWnd, WM_SETREDRAW, 0, 0);
	int i, l;
	CString st;
	string sr;
	CClientDC dc(this);
	CDC* pDC = &dc;
	CFont newfont, * oldfont;
	CPen newpen, * oldpen;
	newpen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	CRect rect;
	CDC dcMem;                         // 创建用于缓冲作图的内存DC对象dcMem
	CBitmap bmp;                       // 创建内存中存放临时图像的位图对象bmp
	GetClientRect(&rect);
	dcMem.CreateCompatibleDC(pDC);     // 依附窗口DC(窗口对象为pDC),创建兼容内存DC(就是创建一个内存DC,所有图形先画在这上面)
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height() - 25); // 在兼容内存DC上，创建兼容位图  ，第一个参数是pDC，图像才为彩色，若为&dcMem,图像为黑白
	dcMem.SelectObject(&bmp);                                     // 将位图选入内存DC
	dcMem.FillSolidRect(rect, pDC->GetBkColor());                 // 按照原有背景色填充客户区,否则会成为黑色，同时也使内存DC的背景色保持一致
	newfont.CreateFontW(int(20 * scale), 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));
	oldfont = dcMem.SelectObject(&newfont);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (L != NULL)
	{
		LinkList p = L->next;
		int x1, y1, x2, y2;
		i = 0;
		if (type != DOUBLE)
		{
			x1 = 200 * (i + 1) - 140;
			y1 = 170;
			x2 = 200 * (i + 1) + 20;
			y2 = 230;
			dcMem.Rectangle(cx(x1), cy(y1), cx(x2), cy(y2));
			dcMem.MoveTo(cx((x1 + x2) / 2), cy(y1));
			dcMem.LineTo(cx((x1 + x2) / 2), cy(y2));
			st.Format(_T("head"));
			sr = CT2A(st.GetString());
			l = sr.size();
			dcMem.TextOut(cx(x1 + ((x2 + x1) / 2 - x1 - int(l * 11)) / 2), cy(190), st);
			if (L->next == L)
			{
				if (type == SINGLE)
				{
					dcMem.MoveTo(cx((x1 + x2) / 2 + 35), cy((y1 + y2) / 2 + 5));
					dcMem.LineTo(cx((x1 + x2) / 2 + 40), cy((y1 + y2) / 2 - 5));
					dcMem.LineTo(cx((x1 + x2) / 2 + 45), cy((y1 + y2) / 2 + 5));
				}
				else
				{
					dcMem.MoveTo(cx(((x1 + x2) / 2 + x2) / 2), cy((y1 + y2) / 2));
					dcMem.LineTo(cx(((x1 + x2) / 2 + x2) / 2 + 80), cy((y1 + y2) / 2));
					dcMem.LineTo(cx(((x1 + x2) / 2 + x2) / 2 + 80), cy((y1 + y2) / 2 + 50));
					dcMem.LineTo(cx(x1 - 40), cy((y1 + y2) / 2 + 50));
					dcMem.LineTo(cx(x1 - 40), cy((y1 + y2) / 2));
					dcMem.LineTo(cx(x1), cy((y1 + y2) / 2));
					dcMem.MoveTo(cx(x1 - 10), cy((y1 + y2) / 2 - 10));
					dcMem.LineTo(cx(x1), cy((y1 + y2) / 2));
					dcMem.LineTo(cx(x1 - 10), cy((y1 + y2) / 2 + 10));
				}
			}
			while (p != L)
			{
				i++;
				dcMem.MoveTo(cx(((x1 + x2) / 2 + x2) / 2), cy((y1 + y2) / 2));
				x1 = 200 * (i + 1) - 140;
				y1 = 170;
				x2 = 200 * (i + 1) + 20;
				y2 = 230;
				dcMem.LineTo(cx(x1), cy((y1 + y2) / 2));
				dcMem.MoveTo(cx(x1 - 10), cy((y1 + y2) / 2 - 10));
				dcMem.LineTo(cx(x1), cy((y1 + y2) / 2));
				dcMem.LineTo(cx(x1 - 10), cy((y1 + y2) / 2 + 10));
				oldpen = NULL;
				if (i == view)
					oldpen = dcMem.SelectObject(&newpen);
				dcMem.Rectangle(cx(x1), cy(y1), cx(x2), cy(y2));
				dcMem.SelectObject(oldpen);
				dcMem.MoveTo(cx((x1 + x2) / 2), cy(y1));
				dcMem.LineTo(cx((x1 + x2) / 2), cy(y2));
				st.Format(_T("%d"), p->data);
				sr = CT2A(st.GetString());
				l = sr.size();
				dcMem.TextOut(cx(x1 + ((x2 + x1) / 2 - x1 - int(l * 11)) / 2), cy(190), st);
				if (p->next == L)
				{
					if (type == SINGLE)
					{
						dcMem.MoveTo(cx((x1 + x2) / 2 + 35), cy((y1 + y2) / 2 + 5));
						dcMem.LineTo(cx((x1 + x2) / 2 + 40), cy((y1 + y2) / 2 - 5));
						dcMem.LineTo(cx((x1 + x2) / 2 + 45), cy((y1 + y2) / 2 + 5));
					}
					else
					{
						dcMem.MoveTo(cx(((x1 + x2) / 2 + x2) / 2), cy((y1 + y2) / 2));
						dcMem.LineTo(cx(((x1 + x2) / 2 + x2) / 2 + 80), cy((y1 + y2) / 2));
						dcMem.LineTo(cx(((x1 + x2) / 2 + x2) / 2 + 80), cy((y1 + y2) / 2 + 50));
						dcMem.LineTo(cx(20), cy((y1 + y2) / 2 + 50));
						dcMem.LineTo(cx(20), cy((y1 + y2) / 2));
						dcMem.LineTo(cx(60), cy((y1 + y2) / 2));
						dcMem.MoveTo(cx(50), cy((y1 + y2) / 2 - 10));
						dcMem.LineTo(cx(60), cy((y1 + y2) / 2));
						dcMem.LineTo(cx(50), cy((y1 + y2) / 2 + 10));
					}
				}
				p = p->next;
			}
		}
		else
		{
			x1 = 280 * (i + 1) - 140;
			y1 = 170;
			x2 = 280 * (i + 1) + 100;
			y2 = 230;
			dcMem.Rectangle(cx(x1), cy(y1), cx(x2), cy(y2));
			dcMem.MoveTo(cx(x1 + (x2 - x1) / 3), cy(y1));
			dcMem.LineTo(cx(x1 + (x2 - x1) / 3), cy(y2));
			dcMem.MoveTo(cx(x1 + 2 * (x2 - x1) / 3), cy(y1));
			dcMem.LineTo(cx(x1 + 2 * (x2 - x1) / 3), cy(y2));
			st.Format(_T("head"));
			sr = CT2A(st.GetString());
			l = sr.size();
			dcMem.TextOut(cx(x1 + ((x2 - x1) / 3 - int(l * 11)) / 2 + (x2 - x1) / 3), cy(190), st);
			dcMem.MoveTo(cx(x1 + 35), cy((y1 + y2) / 2 + 5));
			dcMem.LineTo(cx(x1 + 40), cy((y1 + y2) / 2 - 5));
			dcMem.LineTo(cx(x1 + 45), cy((y1 + y2) / 2 + 5));
			if (L->next == L)
			{
				dcMem.MoveTo(cx(x2 - 35), cy((y1 + y2) / 2 + 5));
				dcMem.LineTo(cx(x2 - 40), cy((y1 + y2) / 2 - 5));
				dcMem.LineTo(cx(x2 - 45), cy((y1 + y2) / 2 + 5));
			}
			while (p != L)
			{
				i++;
				x1 = 280 * (i + 1) - 140;
				y1 = 170;
				x2 = 280 * (i + 1) + 100;
				y2 = 230;
				oldpen = NULL;
				if (i == view)
					oldpen = dcMem.SelectObject(&newpen);
				dcMem.Rectangle(cx(x1), cy(y1), cx(x2), cy(y2));
				dcMem.SelectObject(oldpen);
				dcMem.MoveTo(cx(x1 + (x2 - x1) / 3), cy(y1));
				dcMem.LineTo(cx(x1 + (x2 - x1) / 3), cy(y2));
				dcMem.MoveTo(cx(x1 + 2 * (x2 - x1) / 3), cy(y1));
				dcMem.LineTo(cx(x1 + 2 * (x2 - x1) / 3), cy(y2));
				dcMem.MoveTo(cx((x1 - 280 + 2 * (x2 - x1) / 3 + x2 - 280) / 2), cy(y1 + 2 * (y2 - y1) / 3));
				dcMem.LineTo(cx(x1), cy(y1 + 2 * (y2 - y1) / 3));
				dcMem.MoveTo(cx(x1 - 10), cy(y1 + 2 * (y2 - y1) / 3 - 10));
				dcMem.LineTo(cx(x1), cy(y1 + 2 * (y2 - y1) / 3));
				dcMem.LineTo(cx(x1 - 10), cy(y1 + 2 * (y2 - y1) / 3 + 10));
				dcMem.MoveTo(cx((x1 + (x2 - x1) / 3 + x1) / 2), cy(y1 + (y2 - y1) / 3));
				dcMem.LineTo(cx(x2 - 280), cy(y1 + (y2 - y1) / 3));
				dcMem.MoveTo(cx(x2 - 270), cy(y1 + (y2 - y1) / 3 - 10));
				dcMem.LineTo(cx(x2 - 280), cy(y1 + (y2 - y1) / 3));
				dcMem.LineTo(cx(x2 - 270), cy(y1 + (y2 - y1) / 3 + 10));
				st.Format(_T("%d"), p->data);
				sr = CT2A(st.GetString());
				l = sr.size();
				dcMem.TextOut(cx(x1 + ((x2 - x1) / 3 - int(l * 11)) / 2 + (x2 - x1) / 3), cy(190), st);
				if (p->next == L)
				{
					dcMem.MoveTo(cx(x2 - 35), cy((y1 + y2) / 2 + 5));
					dcMem.LineTo(cx(x2 - 40), cy((y1 + y2) / 2 - 5));
					dcMem.LineTo(cx(x2 - 45), cy((y1 + y2) / 2 + 5));
				}
				p = p->next;
			}
		}
	}
	topLeft = startPoint;
	if (type == SINGLE)
		st.Format(_T("当前链表 : 单链表, 长度%d"), length);
	else
		if (type == DOUBLE)
			st.Format(_T("当前链表 : 双链表, 长度%d"), length);
		else
			if (type == LOOP)
				st.Format(_T("当前链表 : 循环链表, 长度%d"), length);
			else
				st.Format(_T("当前链表 : 无"));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//IntersectClipRect(HDC(*pDC), 0, 0, rect.Width(), rect.Height());
	pDC->BitBlt(0, 0, rect.Width(), rect.Height()-25, &dcMem, 0, 0, SRCCOPY);     // 将内存DC上的图像复制到前台pDC，即实际屏幕对象pDC
	dcMem.SelectObject(oldfont);
	dcMem.DeleteDC();        // 删除内存DC
	bmp.DeleteObject();      // 删除内存位图
	newpen.DeleteObject();
	ReleaseDC(pDC);
	if ((lt != type) || (ll != length))
	{
		::SendMessage(m_bar.m_hWnd, WM_SETREDRAW, 1, 0);
		m_bar.SetPaneText(0, st);
	}
	lt = type; 
	ll = length;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestAPPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestAPPDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rectDlg, rectBar;
	GetClientRect(rectDlg);
	if (m_bar && (rectDlg.Width() != 0))
	{
		CStatusBar* m_pbar = (CStatusBar*)&m_bar;
		m_pbar->GetClientRect(&rectBar);
		m_pbar->SetPaneInfo(index, nID, nStyle, rectDlg.Width());
		m_pbar->MoveWindow(0, cy - rectBar.Height(), rectDlg.Width(), rectBar.Height());
	}
	// TODO: 在此处添加消息处理程序代码
}


void CTestAPPDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pt(800, 500); //定义宽和高
	lpMMI->ptMinTrackSize = pt; //限制最小宽和高
	lpMMI->ptMaxTrackSize = pt; //限制最小宽和高
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CTestAPPDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (type == NONE)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CTestAPPDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (type == NONE)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	moveFlag = TRUE;
	CPoint mousePoint;                       //定义当前鼠标的坐标点
	GetCursorPos(&mousePoint);               //获取当前鼠标在窗框中的坐标值
	ScreenToClient(&mousePoint);
	rVector.x = topLeft.x - mousePoint.x;//获取矩形起始点到当前鼠标位置x方向向量
	rVector.y = topLeft.y - mousePoint.y;//获取矩形起始点到当前鼠标位置y方向向量
	CDialogEx::OnMButtonDown(nFlags, point);
}


void CTestAPPDlg::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (type == NONE)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	moveFlag = FALSE;
	CDialogEx::OnMButtonUp(nFlags, point);
}


BOOL CTestAPPDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (type == NONE)
		return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint mousePoint;                      //定义当前鼠标的坐标点
	GetCursorPos(&mousePoint);              //获取当前鼠标在窗框中的坐标值
	ScreenToClient(&mousePoint);
	int dx = mousePoint.x - topLeft.x; //计算鼠标坐标点到矩形起始点X方向的向量
	int dy = mousePoint.y - topLeft.y; //计算鼠标坐标点到矩形起始点Y方向的向量
	//根据鼠标滚轮滚动方向判断缩放 与 滚动格数计算缩放比例 
	if (zDelta > 0)
	{
		startPoint.x = topLeft.x - (int)(dx * POSITION_SCALE);//计算放大后的矩形起始点坐标
		startPoint.y = topLeft.y - (int)(dy * POSITION_SCALE);
		scale *= UP_SCALE;
	}
	else
	{
		if (scale * DOWN_SCALE > 0.1)
		{
			startPoint.x = topLeft.x + (int)(dx * POSITION_SCALE);//计算缩小后的矩形起始点坐标
			startPoint.y = topLeft.y + (int)(dy * POSITION_SCALE);
			scale *= DOWN_SCALE;
		}
	}
	Invalidate(false);   //重新绘制图形
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CTestAPPDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (type == NONE)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (moveFlag == TRUE)
	{
		CPoint mousePoint;                      //定义当前鼠标的坐标点
		GetCursorPos(&mousePoint);              //获取当前鼠标在窗框中的坐标值
		ScreenToClient(&mousePoint);
		startPoint.x = mousePoint.x + rVector.x; //计算鼠标拖动时矩形起始点（左上角点）坐标值
		startPoint.y = mousePoint.y + rVector.y;
		//endPoint.x = startPoint.x + rc.Width();     //计算鼠标拖动时矩形终点（右下角点）坐标值
		//endPoint.y = startPoint.y + rc.Height();
		Invalidate(false);   //重新绘制图形
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CTestAPPDlg::OnCreateSingle()
{
	// TODO: 在此添加命令处理程序代码
	if (type != NONE)
	{
		if (type == SINGLE)
		{
			NULLDlg dlg(_T("存在已创建的单链表."));
			dlg.DoModal();
		}
		else
			if (type == DOUBLE)
			{
				NULLDlg dlg(_T("存在已创建的双链表."));
				dlg.DoModal();
			}
			else
			{
				NULLDlg dlg(_T("存在已创建的循环链表."));
				dlg.DoModal();
			}
	}
	else
	{
		L = (LNode*)malloc(sizeof(LNode));
		if (L == NULL)
		{
			NULLDlg dlg(_T("内存空间不足，创建链表失败."));
			dlg.DoModal();
		}
		else
		{
			L->next = L;
			L->prior = L;
			type = SINGLE;
			view = 0;
			Invalidate(false);
			SUCDlg dlg(_T("创建单链表成功."));
			dlg.DoModal();
		}
	}
}


void CTestAPPDlg::OnCreateDouble()
{
	// TODO: 在此添加命令处理程序代码
	if (type != NONE)
	{
		if (type == SINGLE)
		{
			NULLDlg dlg(_T("存在已创建的单链表."));
			dlg.DoModal();
		}
		else
			if (type == DOUBLE)
			{
				NULLDlg dlg(_T("存在已创建的双链表."));
				dlg.DoModal();
			}
			else
			{
				NULLDlg dlg(_T("存在已创建的循环链表."));
				dlg.DoModal();
			}
	}
	else
	{
		L = (LNode*)malloc(sizeof(LNode));
		if (L == NULL)
		{
			NULLDlg dlg(_T("内存空间不足，创建链表失败."));
			dlg.DoModal();
		}
		else
		{
			L->next = L;
			L->prior = L;
			length = 0;
			type = DOUBLE;
			view = 0;
			Invalidate(false);
			SUCDlg dlg(_T("创建双链表成功."));
			dlg.DoModal();
		}
	}
}


void CTestAPPDlg::OnCreateLoop()
{
	// TODO: 在此添加命令处理程序代码
	if (type != NONE)
	{
		if (type == SINGLE)
		{
			NULLDlg dlg(_T("存在已创建的单链表."));
			dlg.DoModal();
		}
		else
			if (type == DOUBLE)
			{
				NULLDlg dlg(_T("存在已创建的双链表."));
				dlg.DoModal();
			}
			else
			{
				NULLDlg dlg(_T("存在已创建的循环链表."));
				dlg.DoModal();
			}
	}
	else
	{
		L = (LNode*)malloc(sizeof(LNode));
		if (L == NULL)
		{
			NULLDlg dlg(_T("内存空间不足，创建链表失败."));
			dlg.DoModal();
		}
		else
		{
			L->next = L;
			L->prior = L;
			length = 0;
			type = LOOP;
			view = 0;
			Invalidate(false);
			SUCDlg dlg(_T("创建循环链表成功."));
			dlg.DoModal();
		}
	}
}


void CTestAPPDlg::OnDestroy()
{
	if (type == NONE)
	{
		NULLDlg dlg(_T("当前不存在链表."));
		dlg.DoModal();
	}
	else
	{
		LinkList p;
		while (L->next != L)
		{
			p = L->next;
			L->next->prior = L->prior;
			L->next = L->next->next;
			free(p);
		}
		free(L);
		L = NULL;
		length = 0;
		view = NONE;
		type = NONE;
		Invalidate(false);
		SUCDlg dlg(_T("销毁链表成功."));
		dlg.DoModal();
	}
}


void CTestAPPDlg::OnInsert()
{
	// TODO: 在此添加命令处理程序代码
	LinkList s, p = L;	//p指向头结点
	int now = 0;
	CString st;
	st.Format(_T("请输入元素插入位置(%d~%d)和值(%d~%d): "), P_MIN, P_MAX, V_MIN, V_MAX);
	INPUTDlg2 dlg(st);
	if (dlg.DoModal() != IDOK)
		return;
	pos = _ttoi(dlg.data1);
	value = _ttoi(dlg.data2);
	while ((p->next != L) && (now < pos - 1))
	{
		p = p->next;
		now++;
	}
	if (((p->next == L)) && (now != pos - 1))
	{
		NULLDlg dlg(_T("插入位置非法."));
		dlg.DoModal();
	}
	else
	{
		s = (LinkList)malloc(sizeof(LNode));
		if (s == NULL)
		{
			NULLDlg dlg(_T("内存空间不足，插入元素失败."));
			dlg.DoModal();
		}
		else
		{
			s->data = value;
			s->next = p->next;
			s->prior = p;
			p->next->prior = s;
			p->next = s;
			length++;
			view = pos;
			Invalidate(false);
			CString st;
			st.Format(_T("在第%d个位置插入元素成功."), pos);
			SUCDlg dlg(st);
			dlg.DoModal();
		}
	}
}


void CTestAPPDlg::OnLocate()
{
	// TODO: 在此添加命令处理程序代码
	CString st;
	st.Format(_T("请输入要查找元素的值(%d~%d) : "), V_MIN, V_MAX);
	INPUTDlg1 dlg(st, V_MIN, V_MAX);
	if (dlg.DoModal() != IDOK)
		return;
	value = _ttoi(dlg.data);
	LinkList p = L->next;
	pos = 1;
	while ((p->next != L) && (p->data != value))
	{
		p = p->next;
		pos++;
	}
	if ((p == L) || (p->data != value))
	{
		CString st;
		st.Format(_T("不存在值为%d的元素."), value);
		NULLDlg dlg(st);
		dlg.DoModal();
	}
	else
	{
		view = pos;
		Invalidate(false);
		CString st;
		st.Format(_T("值为%d的元素首次出现在第%d个."), value, pos);
		SUCDlg dlg(st);
		dlg.DoModal();
	}
}


void CTestAPPDlg::OnFind()
{
	CString st;
	st.Format(_T("请输入要查找元素的位置(%d~%d) : "), P_MIN, P_MAX);
	INPUTDlg1 dlg(st, P_MIN, P_MAX);
	if (dlg.DoModal() != IDOK)
		return;
	pos = _ttoi(dlg.data);
	LinkList p = L->next;
	int now = 1;
	while ((p != L) && (now < pos))
	{
		p = p->next;
		now++;
	}
	if ((p == L) || (now > pos))
	{
		NULLDlg dlg(_T("查找位置非法."));
		dlg.DoModal();
	}
	else
	{
		value = p->data;
		view = pos;
		Invalidate(false);
		CString st;
		st.Format(_T("第%d个元素值为%d."), pos, value);
		SUCDlg dlg(st);
		dlg.DoModal();
	}
	// TODO: 在此添加命令处理程序代码
}


void CTestAPPDlg::OnDelete()
{
	CString st;
	st.Format(_T("请输入要删除元素的位置(%d~%d) : "), P_MIN, P_MAX);
	INPUTDlg1 dlg(st, P_MIN, P_MAX);
	if (dlg.DoModal() != IDOK)
		return;
	pos = _ttoi(dlg.data);
	LinkList q, p = L;	
	int now = 0;
	while ((p->next != L) && (now < pos - 1))
	{
		p = p->next;
		now++;
	}
	if ((p->next == L) || (now > pos - 1))
	{
		NULLDlg dlg(_T("删除位置非法."));
		dlg.DoModal();
	}
	else
	{
		q = p->next;
		value = q->data;
		p->next = q->next;
		q->next->prior = p;
		free(q);
		view = pos;
		length--;
		Invalidate(false);
		CString st;
		st.Format(_T("删除第%d个元素成功."), pos);
		SUCDlg dlg(st);
		dlg.DoModal();
	}
	// TODO: 在此添加命令处理程序代码
}


BOOL CTestAPPDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return false;
}



void CTestAPPDlg::OnUpdate32780(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(type != NONE);
}


void CTestAPPDlg::OnUpdate32781(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(type != NONE);
}


void CTestAPPDlg::OnUpdate32782(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((type != NONE) && (length > 0));
}


void CTestAPPDlg::OnUpdate32777(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(type != NONE);
}


void CTestAPPDlg::OnUpdate32774(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(type == NONE);
}


void CTestAPPDlg::OnUpdate32775(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(type == NONE);
}


void CTestAPPDlg::OnUpdate32776(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(type == NONE);
}

void CTestAPPDlg::OnUpdate32779(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(type != NONE);
}

void CTestAPPDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	ASSERT(pPopupMenu != NULL);
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue;
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;
			}
			state.DoUpdate(this, TRUE);
		}
		else
		{
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}
