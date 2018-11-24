
// VirtualMouseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VirtualMouse.h"
#include "VirtualMouseDlg.h"
//#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVirtualMouseDlg 对话框

UINT WINAPI ThreadFunc(LPVOID pParam);

CVirtualMouseDlg::CVirtualMouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIRTUALMOUSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVirtualMouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, mbtnStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, mbtnStop);
}

BEGIN_MESSAGE_MAP(CVirtualMouseDlg, CDialogEx)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CVirtualMouseDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CVirtualMouseDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDEXIT, &CVirtualMouseDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CVirtualMouseDlg 消息处理程序

BOOL CVirtualMouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	srand((unsigned)time(NULL));
	mbtnStop.EnableWindow(0);
	::PostMessage(GetDlgItem(IDC_BUTTON_START)->m_hWnd, WM_SETFOCUS, 0, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVirtualMouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HANDLE hThread;
DWORD ThreadID;
SYSTEMTIME endDate;
SYSTEMTIME endTime;
SYSTEMTIME endDateTime;
void CVirtualMouseDlg::OnBnClickedButtonStart()
{
	mbtnStart.EnableWindow(0);
	mbtnStop.EnableWindow(1);
	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFunc,
		(VOID*)this,
		0,
		&ThreadID);
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

UINT WINAPI ThreadFunc(LPVOID pParam)
{
	int smWidth = GetSystemMetrics(SM_CXSCREEN);
	int smHeight = GetSystemMetrics(SM_CYSCREEN);
	do
	{
		int x = rand() % smWidth;
		int y = rand() % smHeight;
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x * 65535 / smWidth, y * 65535 / smHeight, 0, 0);
		Sleep(50*1000);
	} while (TRUE);

	return 0;
}

void CVirtualMouseDlg::OnBnClickedButtonStop()
{
	try
	{
		TerminateThread(hThread, 0);
		mbtnStart.EnableWindow(1);
		mbtnStop.EnableWindow(0);
		//::AfxMessageBox(L"Stoped.");
	}
	catch (...)
	{
		::AfxMessageBox(L"Error.");
		mbtnStart.EnableWindow(1);
		mbtnStop.EnableWindow(0);
	}
}


void CVirtualMouseDlg::OnBnClickedExit()
{
	exit(0);
}
