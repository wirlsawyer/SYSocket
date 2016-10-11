// SYSocket2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SYSocket2.h"
#include "SYSocket2Dlg.h"

#include "SYSocket.h"
SYTCPSocket *_pServerSocket = new SYTCPSocket();	//By Sawyer
SYTCPSocket *_pClientSocket1 = new SYTCPSocket();	//By Sawyer
SYTCPSocket *_pClientSocket2 = new SYTCPSocket();	//By Sawyer
void OnSYTCPSocketEvent(SYTCPSocket *sender, SYTCPEvent e);

SYUDPSocket *_pBroadcastServer = new SYUDPSocket(); //By Sawyer
SYUDPSocket *_pBroadcastClient1 = new SYUDPSocket(); //By Sawyer
SYUDPSocket *_pBroadcastClient2 = new SYUDPSocket(); //By Sawyer
void OnSYUDPSocketEvent(SYUDPSocket *sender, SYUDPEvent e);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSYSocket2Dlg dialog




CSYSocket2Dlg::CSYSocket2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSYSocket2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSYSocket2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSYSocket2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSYSocket2Dlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON3, &CSYSocket2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSYSocket2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON10, &CSYSocket2Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON6, &CSYSocket2Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CSYSocket2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CSYSocket2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON7, &CSYSocket2Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CSYSocket2Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CSYSocket2Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON11, &CSYSocket2Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CSYSocket2Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CSYSocket2Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CSYSocket2Dlg::OnBnClickedButton14)
END_MESSAGE_MAP()


// CSYSocket2Dlg message handlers

BOOL CSYSocket2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	_pServerSocket->OnEvent  = &OnSYTCPSocketEvent;	//By Sawyer
	_pClientSocket1->OnEvent = &OnSYTCPSocketEvent;	//By Sawyer
	_pClientSocket2->OnEvent = &OnSYTCPSocketEvent;	//By Sawyer

	_pBroadcastServer->OnEvent = &OnSYUDPSocketEvent; //By Sawyer
	_pBroadcastClient1->OnEvent = &OnSYUDPSocketEvent; //By Sawyer
	_pBroadcastClient2->OnEvent = &OnSYUDPSocketEvent; //By Sawyer
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSYSocket2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSYSocket2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSYSocket2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CSYSocket2Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	delete _pServerSocket;
	delete _pClientSocket1;
	delete _pClientSocket2;

	delete _pBroadcastServer;
	delete _pBroadcastClient1;
	delete _pBroadcastClient2;
}

void OnSYTCPSocketEvent(SYTCPSocket *sender, SYTCPEvent e)
{
	if (sender == _pServerSocket)
	{
		OutputDebugString(L"ServerSocket ");
	}

	if (sender == _pClientSocket1)
	{
		OutputDebugString(L"ClientSocket1 ");
	}

	if (sender == _pClientSocket2)
	{
		OutputDebugString(L"ClientSocket2 ");
	}

	switch (e.Status)
	{
	case SYTCPSOCKET_CLOSE:
		OutputDebugString(L"SYTCPSOCKET_CLOSE\n");
		break;

	case SYTCPSOCKET_RECVDATA:
		OutputDebugString(L"SYTCPSOCKET_RECVDATA\n");
		OutputDebugStringA(e.szData);
		OutputDebugString(L"\n");
		break;

	case SYTCPSOCKET_CONNECTED:
		OutputDebugString(L"SYTCPSOCKET_CONNECTED\n");
		break;

	case SYTCPSOCKET_CONNECTFAULT:
		OutputDebugString(L"SYTCPSOCKET_CONNECTFAULT\n");
		/*
		if (sender == _pClientSocket1){
		((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON3))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON6))->EnableWindow(FALSE);
		}

		if (sender == _pClientSocket2){
		((CButton*)GetDlgItem(IDC_BUTTON7))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON8))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON9))->EnableWindow(FALSE);
		}*/
		break;

	case SYTCPSOCKET_DISCONNECT:
		OutputDebugString(L"SYTCPSOCKET_DISCONNECT\n");
		break;

	case SYTCPSOCKET_LISTENED:
		OutputDebugString(L"SYTCPSOCKET_LISTENED\n");
		break;
	}

	OutputDebugString(e.wszMsg);
}

void OnSYUDPSocketEvent(SYUDPSocket *sender, SYUDPEvent e)
{
	switch (e.Status)
	{
	case SYUDPSOCKET_CONNECTFAULT:
		OutputDebugString(L"SYUDPSOCKET_CONNECTFAULT\n");
		break;
	case SYUDPSOCKET_LISTENED:
		OutputDebugString(L"SYUDPSOCKET_LISTENED\n");
		break;
	case SYUDPSOCKET_RECVDATA:
		OutputDebugString(L"SYUDPSOCKET_RECVDATA\n");
		break;
	case SYUDPSOCKET_FIND_SERVICE:
		OutputDebugString(L"SYUDPSOCKET_FIND_SERVICE\n");
		break;		
	}
	OutputDebugString(e.wszMsg);
}
void CSYSocket2Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	_pServerSocket->LocalPort = 5000;
	_pServerSocket->Listen();
}

void CSYSocket2Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	char tt[32] =  "1234567 from Server";
	_pServerSocket->Send((const char*)tt);
}


void CSYSocket2Dlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	_pServerSocket->Close();
}

void CSYSocket2Dlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	_pClientSocket1->RemoteHost = "127.0.0.1";
	_pClientSocket1->RemotePort = 5000;
	_pClientSocket1->Connect();
}

void CSYSocket2Dlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	char tt[32] =  "1234567 from Client1";
	_pClientSocket1->Send((const char*)tt);
}


void CSYSocket2Dlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	_pClientSocket1->Close();
}

void CSYSocket2Dlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	_pClientSocket2->RemoteHost = "127.0.0.1";
	_pClientSocket2->RemotePort = 5000;
	_pClientSocket2->Connect();
}

void CSYSocket2Dlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	char tt[32] =  "1234567 from Client2";
	_pClientSocket2->Send((const char*)tt);
}

void CSYSocket2Dlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	_pClientSocket2->Close();
}

void CSYSocket2Dlg::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
	_pServerSocket->GetNowOnlineClient();
}
void CSYSocket2Dlg::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
	_pBroadcastServer->StartListenWithPort(8090);

}

void CSYSocket2Dlg::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here
	_pBroadcastClient1->StartBroadcastWithHost("10.10.63.255", 8090, 3);
}

void CSYSocket2Dlg::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here
	_pBroadcastClient2->StartBroadcastWithHost("127.0.0.1", 8090, 3);
}

void CSYSocket2Dlg::OnBnClickedButton14()
{
	// TODO: Add your control notification handler code here
	_pBroadcastServer->StopListen();
}
