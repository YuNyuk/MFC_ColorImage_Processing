#pragma once
#include "afxdialogex.h"


// CConstant3Dlg 대화 상자

class CConstant3Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant3Dlg)

public:
	CConstant3Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstant3Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constant3;
	afx_msg void OnEnChangeEditConstant2();
};
