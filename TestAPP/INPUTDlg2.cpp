// INPUTDlg2.cpp: 实现文件
//

#include "pch.h"
#include "TestAPP.h"
#include "INPUTDlg2.h"
#include "afxdialogex.h"
#include "NULLDlg.h"
#include "tool.h"

// INPUTDlg2 对话框

IMPLEMENT_DYNAMIC(INPUTDlg2, CDialogEx)

INPUTDlg2::INPUTDlg2(CString st,CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_INPUT2, pParent)
{
	content = st;
}

INPUTDlg2::~INPUTDlg2()
{
}

void INPUTDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEG_J, message);
	message.SetWindowText(content);
}


BEGIN_MESSAGE_MAP(INPUTDlg2, CDialogEx)
	ON_BN_CLICKED(IDOK, &INPUTDlg2::OnBnClickedOk)
END_MESSAGE_MAP()


// INPUTDlg2 消息处理程序


void INPUTDlg2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	string s1, s2;
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(data1);
	s1 = CT2A(data1.GetString());
	if (s1.size() == 0)
		return;
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(data2);
	s2 = CT2A(data2.GetString());
	if (s2.size() == 0)
		return;
	if (check(s1, P_MIN, P_MAX) == -1)
	{
		CString sr;
		sr.Format(_T("位置数据非法，请输入%d~%d的整数."), P_MIN, P_MAX);
		NULLDlg dlg(sr);
		dlg.DoModal();
		return;
	}
	if (check(s2, V_MIN, V_MAX) == -1)
	{
		CString sr;
		sr.Format(_T("数值数据非法，请输入%d~%d的整数."), V_MIN, V_MAX);
		NULLDlg dlg(sr);
		dlg.DoModal();
		return;
	}
	Invalidate();
	CDialogEx::OnOK();
}
