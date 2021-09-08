// NULLDlg.cpp: 实现文件
//

#include "pch.h"
#include "TestAPP.h"
#include "NULLDlg.h"
#include "afxdialogex.h"


// NULLDlg 对话框

IMPLEMENT_DYNAMIC(NULLDlg, CDialogEx)

NULLDlg::NULLDlg(CString st,CWnd* pParent /*=nullptr*/): CDialogEx(IDD_NULL, pParent)
{
	content = st;
}

NULLDlg::~NULLDlg()
{
}

void NULLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG, message);
	message.SetWindowText(content);
}


BEGIN_MESSAGE_MAP(NULLDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// NULLDlg 消息处理程序


void NULLDlg::OnPaint()
{

}
