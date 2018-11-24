
// VirtualMouseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtualMouse.h"
#include "VirtualMouseDlg.h"
//#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVirtualMouseDlg �Ի���

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


// CVirtualMouseDlg ��Ϣ�������

BOOL CVirtualMouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	srand((unsigned)time(NULL));
	mbtnStop.EnableWindow(0);
	::PostMessage(GetDlgItem(IDC_BUTTON_START)->m_hWnd, WM_SETFOCUS, 0, 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
