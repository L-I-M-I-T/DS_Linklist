#pragma once


// INPUTDlg1 对话框

class INPUTDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(INPUTDlg1)

public:
	INPUTDlg1(CString st, int m, int n, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~INPUTDlg1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT1 };
#endif
	CString content;
	CString data;
	int MIN, MAX;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic message;
};
