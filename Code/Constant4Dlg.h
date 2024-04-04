#pragma once
#include "afxdialogex.h"


// CConstant4Dlg 대화 상자

class CConstant4Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant4Dlg)

public:
	CConstant4Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstant4Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constant4;
};
