// SUCDlg.cpp: 实现文件
//

#include "pch.h"
#include "TestAPP.h"
#include "SUCDlg.h"
#include "afxdialogex.h"


// SUCDlg 对话框

IMPLEMENT_DYNAMIC(SUCDlg, CDialogEx)

SUCDlg::SUCDlg(CString st,CWnd* pParent /*=nullptr*/): CDialogEx(IDD_SUC, pParent)
{
	content = st;
}

SUCDlg::~SUCDlg()
{
}

void SUCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG1, message);
	message.SetWindowText(content);
}


BEGIN_MESSAGE_MAP(SUCDlg, CDialogEx)
END_MESSAGE_MAP()


// SUCDlg 消息处理程序
