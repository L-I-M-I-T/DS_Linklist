
// TestAPPDlg.h: 头文件
//

#pragma once
#define WIDTH 800         //矩形的宽（初始状态）
#define HEIGHT 475        //矩形的长（初始状态）
#define UP_SCALE 1.1      //放大的比例值
#define DOWN_SCALE 0.9    //缩小的比例值
#define POSITION_SCALE 0.1//位置偏移比例
#define SINGLE 0
#define DOUBLE 1
#define LOOP 2
#define NONE -1

typedef struct LNode 
{
	int data;	        //存放数据
	struct LNode* next;	//存放直接后继的指针
	struct LNode* prior;//存放直接前驱的指针
} LNode, * LinkList;

// CTestAPPDlg 对话框
class CTestAPPDlg : public CDialogEx
{
// 构造
public:
	CTestAPPDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTAPP_DIALOG };
#endif
	int coin, index, nWidth, length, type, pos, value, view, lt, ll;
	UINT  nID, nStyle;
	CStatusBar m_bar;
	CPoint startPoint, endPoint, topLeft, rVector;
	double scale;
	BOOL moveFlag;
	LinkList L;
	
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
private:
	CEdit Text1;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCreateSingle();
	afx_msg void OnCreateDouble();
	afx_msg void OnCreateLoop();
	afx_msg void OnDestroy();
	afx_msg void OnInsert();
	afx_msg void OnLocate();
	afx_msg void OnFind();
	afx_msg void OnDelete();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdate32780(CCmdUI* pCmdUI);
	afx_msg void OnUpdate32781(CCmdUI* pCmdUI);
	afx_msg void OnUpdate32782(CCmdUI* pCmdUI);
	afx_msg void OnUpdate32777(CCmdUI* pCmdUI);
	afx_msg void OnUpdate32774(CCmdUI* pCmdUI);
	afx_msg void OnUpdate32775(CCmdUI* pCmdUI);
	afx_msg void OnUpdate32776(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnUpdate32779(CCmdUI* pCmdUI);
};
