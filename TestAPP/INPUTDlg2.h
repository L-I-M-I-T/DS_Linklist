#pragma once


// INPUTDlg2 对话框

class INPUTDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(INPUTDlg2)

public:
	INPUTDlg2(CString st, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~INPUTDlg2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic message;
	CString content, data1, data2;
	afx_msg void OnBnClickedOk();
};
