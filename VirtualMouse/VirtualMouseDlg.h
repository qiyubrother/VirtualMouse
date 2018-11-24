
// VirtualMouseDlg.h : 头文件
//

#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CVirtualMouseDlg 对话框
class CVirtualMouseDlg : public CDialogEx
{
// 构造
public:
	CVirtualMouseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIRTUALMOUSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
//	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
//	afx_msg void OnMouseLeave();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	CDateTimeCtrl mEndDate;
	CDateTimeCtrl mEndTime;
	CButton mbtnStart;
	CButton mbtnStop;
	afx_msg void OnBnClickedExit();
};
