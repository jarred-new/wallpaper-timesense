
// TimeSenseDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CTimeSenseDlg dialog
class CTimeSenseDlg : public CDialogEx
{
// Construction
public:
	CTimeSenseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TIMESENSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnBnClickedButton4();
	CEdit m_morning;
	CEdit m_afternoon;
	CEdit m_night;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
private:
	CString defaultMorningPath;
	CString defaultAfternoonPath;
	CString defaultNightPath;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton5();
};
