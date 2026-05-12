
// TimeSenseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimeSense.h"
#include "TimeSenseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTimeSenseDlg dialog



CTimeSenseDlg::CTimeSenseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeSenseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	defaultMorningPath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\timebackup\\morning.jpg");
	defaultAfternoonPath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\timebackup\\afternoon.jpg");
	defaultNightPath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\timebackup\\evening.jpg");
}

void CTimeSenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_morning);
	DDX_Control(pDX, IDC_EDIT2, m_afternoon);
	DDX_Control(pDX, IDC_EDIT3, m_night);
}

BEGIN_MESSAGE_MAP(CTimeSenseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL2, &CTimeSenseDlg::OnBnClickedCancel2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTimeSenseDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CTimeSenseDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTimeSenseDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTimeSenseDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CTimeSenseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTimeSenseDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON5, &CTimeSenseDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CTimeSenseDlg message handlers

CString morningPath;
CString afternoonPath;
CString nightPath;

BOOL CTimeSenseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// Intialize path for morning, evening, and night
	morningPath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\morning.jpg");
	afternoonPath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\afternoon.jpg");
	nightPath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\evening.jpg");
	
	m_morning.SetWindowTextW(morningPath);
	m_afternoon.SetWindowTextW(afternoonPath);
	m_night.SetWindowTextW(nightPath);
	
	m_morning.UpdateData();
	m_afternoon.UpdateData();
	m_night.UpdateData();

	// 1. Find the window of the second process by its title
	HWND hSecondWnd = this->GetSafeHwnd();

	DWORD dwTargetThread = ::GetWindowThreadProcessId(hSecondWnd, NULL);
	DWORD dwCurrentThread = ::GetCurrentThreadId();

	// Attach, show, then detach
	::AttachThreadInput(dwCurrentThread, dwTargetThread, TRUE);
	::SetForegroundWindow(hSecondWnd);
	::ShowWindow(hSecondWnd, SW_HIDE);
	::AttachThreadInput(dwCurrentThread, dwTargetThread, FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimeSenseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimeSenseDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimeSenseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimeSenseDlg::OnBnClickedCancel2()
{
	//Note: this is apply button, not cancel button ;)
	//Don't be confused...
	int copyCounter;
	copyCounter = 0;
	BOOL copy1 = CopyFile(morningPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\morning.jpg", FALSE);
	BOOL copy2 = CopyFile(afternoonPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\afternoon.jpg", FALSE);
	BOOL copy3 = CopyFile(nightPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\evening.jpg", FALSE);
	if (copy1 == TRUE) {
		copyCounter++;
	}
	if (copy2 == TRUE) {
		copyCounter++;
	}
	if (copy3 == TRUE) {
		copyCounter++;
	}
	CString output1;
	output1.Format(L"Applied Successfully\nSuccess: %d", copyCounter);
	if (MessageBox(output1, L"GOOD!", MB_OK | MB_ICONINFORMATION) == IDOK) {
		copyCounter = 0;
	}
}


void CTimeSenseDlg::OnBnClickedButton4()
{
	// Reset button
	INT_PTR alertAreYouSure = MessageBox(L"Are you sure to reset", L"Alert", MB_YESNO | MB_ICONQUESTION);

	if (alertAreYouSure == IDYES) {
		int copyResetCounter;
		copyResetCounter = 0;
		BOOL resetCopy1 = CopyFile(defaultMorningPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\morning.jpg", FALSE);
		BOOL resetCopy2 = CopyFile(defaultAfternoonPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\afternoon.jpg", FALSE);
		BOOL resetCopy3 = CopyFile(defaultNightPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\evening.jpg", FALSE);
		if (resetCopy1 == TRUE) {
			copyResetCounter++;
		}
		if (resetCopy2 == TRUE) {
			copyResetCounter++;
		}
		if (resetCopy3 == TRUE) {
			copyResetCounter++;
		}

		m_morning.SetWindowTextW(morningPath);
		m_afternoon.SetWindowTextW(afternoonPath);
		m_night.SetWindowTextW(nightPath);

		m_morning.UpdateData();
		m_afternoon.UpdateData();
		m_night.UpdateData();

		CString output2;
		output2.Format(L"Applied Successfully\nSuccess: %d", copyResetCounter);
		if (MessageBox(output2, L"GOOD!", MB_OK | MB_ICONINFORMATION) == IDOK) {
			copyResetCounter = 0;
		}
	}
}


void CTimeSenseDlg::OnBnClickedButton1()
{
	// Browse for morning
	CFileDialog fileDlg(TRUE, _T("jpg"), _T(""), OFN_EXPLORER | OFN_READONLY,
		_T("JPG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png|GIF Files (*.gif)|*.gif|TIF Files (*.tif; *.tiff)|*.tif; *.tiff|All Files (*.*)|*.*|"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString filepath;
		filepath = fileDlg.GetPathName();
		m_morning.SetWindowTextW(filepath);
		m_morning.UpdateData();
		m_morning.GetWindowTextW(morningPath);
		UpdateWindow();
	}
}


void CTimeSenseDlg::OnBnClickedButton2()
{
	// Browse for afternoon
	CFileDialog fileDlg(TRUE, _T("jpg"), _T(""), OFN_EXPLORER | OFN_READONLY,
		_T("JPG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png|GIF Files (*.gif)|*.gif|TIF Files (*.tif; *.tiff)|*.tif; *.tiff|All Files (*.*)|*.*|"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString filepath;
		filepath = fileDlg.GetPathName();
		m_afternoon.SetWindowTextW(filepath);
		m_afternoon.UpdateData();
		m_afternoon.GetWindowTextW(afternoonPath);
		UpdateWindow();
	}
}


void CTimeSenseDlg::OnBnClickedButton3()
{
	// Browse for evening
	CFileDialog fileDlg(TRUE, _T("jpg"), _T(""), OFN_EXPLORER | OFN_READONLY,
		_T("JPG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png|GIF Files (*.gif)|*.gif|TIF Files (*.tif; *.tiff)|*.tif; *.tiff|All Files (*.*)|*.*|"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString filepath;
		filepath = fileDlg.GetPathName();
		m_night.SetWindowTextW(filepath);
		m_night.UpdateData();
		m_night.GetWindowTextW(nightPath);
		UpdateWindow();
	}
}


void CTimeSenseDlg::OnBnClickedOk()
{
	int copyCounter;
	copyCounter = 0;
	BOOL copy1 = CopyFile(morningPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\morning.jpg", FALSE);
	BOOL copy2 = CopyFile(afternoonPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\afternoon.jpg", FALSE);
	BOOL copy3 = CopyFile(nightPath, L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\evening.jpg", FALSE);
	if (copy1 == TRUE) {
		copyCounter++;
	}
	if (copy2 == TRUE) {
		copyCounter++;
	}
	if (copy3 == TRUE) {
		copyCounter++;
	}
	CString output1;
	output1.Format(L"Applied Successfully\nSuccess: %d", copyCounter);
	if (MessageBox(output1, L"GOOD!", MB_OK | MB_ICONINFORMATION) == IDOK) {
		copyCounter = 0;
		CDialogEx::OnOK();
	}
}


void CTimeSenseDlg::OnBnClickedCancel()
{
	if (MessageBox(L"Are you sure to discard these changes?", L"Before you leave...", MB_YESNO) == IDYES) {
		CDialogEx::OnCancel();
	}
}


void CTimeSenseDlg::OnBnClickedButton5()
{
	if (MessageBox(L"Do you want to set WallpaperTimeSense?\nWarning: This might impact your performance when you turn on your PC...", L"Are you sure", MB_YESNO | MB_ICONQUESTION) == IDYES) {
		CString strSource = L"C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\WallpaperTimeSenseStartup.exe";

		// 1. If no path is provided, default to the current running EXE
		if (strSource.IsEmpty()) {
			TCHAR szExePath[MAX_PATH];
			::GetModuleFileName(NULL, szExePath, MAX_PATH);
			strSource = szExePath;
		}

		// 2. Get the Startup folder path
		TCHAR szStartupPath[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, 0, szStartupPath))) {
			CString strDest(szStartupPath);

			// 3. Extract the filename from whatever source path was provided
			// Example: "C:\Downloads\test.exe" -> "test.exe"
			int nPos = strSource.ReverseFind(_T('\\'));
			CString strFileName = (nPos != -1) ? strSource.Mid(nPos + 1) : strSource;

			strDest += _T("\\") + strFileName;

			// 4. Copy the file
			if (::CopyFile(strSource, strDest, FALSE)) {
				AfxMessageBox(_T("Successfully copied to startup: ") + strFileName);
			}
			else {
				DWORD dwError = GetLastError();
				CString strErr;
				strErr.Format(_T("Failed to copy. Error code: %d"), dwError);
				AfxMessageBox(strErr);
			}
		}
	}
}
