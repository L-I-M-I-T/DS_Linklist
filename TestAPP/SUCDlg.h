#pragma once


// SUCDlg 对话框

class SUCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SUCDlg)

public:
	SUCDlg(CString st, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SUCDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString content;
	CStatic message;
};
