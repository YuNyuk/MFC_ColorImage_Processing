#pragma once
#include "afxdialogex.h"


// CConstant1Dlg 대화 상자

class CConstant1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant1Dlg)

public:
	CConstant1Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstant1Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constant1;
};
