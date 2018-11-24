
// VirtualMouseDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CVirtualMouseDlg �Ի���
class CVirtualMouseDlg : public CDialogEx
{
// ����
public:
	CVirtualMouseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIRTUALMOUSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
