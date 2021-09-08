// INPUTDlg1.cpp: 实现文件
//

#include "pch.h"
#include "TestAPP.h"
#include "INPUTDlg1.h"
#include "afxdialogex.h"
#include "NULLDlg.h"
#include "tool.h"


// INPUTDlg1 对话框

IMPLEMENT_DYNAMIC(INPUTDlg1, CDialogEx)

INPUTDlg1::INPUTDlg1(CString st, int m, int n, CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_INPUT1, pParent)
{
	content = st;
	MIN = m;
	MAX = n;
}

INPUTDlg1::~INPUTDlg1()
{
}

void INPUTDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEG_I, message);
	message.SetWindowText(content);
}


BEGIN_MESSAGE_MAP(INPUTDlg1, CDialogEx)
	ON_BN_CLICKED(IDOK, &INPUTDlg1::OnBnClickedOk)
END_MESSAGE_MAP()


// INPUTDlg1 消息处理程序


void INPUTDlg1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(data);
	string st = CT2A(data.GetString());
	if (st.size() == 0)
		return;
	if (check(st, MIN, MAX) == -1)
	{
		CString sr;
		sr.Format(_T("数据非法，请输入%d~%d的整数."), MIN, MAX);
		NULLDlg dlg(sr);
		dlg.DoModal();
		return;
	}
	Invalidate();
	CDialogEx::OnOK();
}
