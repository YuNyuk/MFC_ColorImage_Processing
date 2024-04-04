// Constant4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "Constant4Dlg.h"


// CConstant4Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant4Dlg, CDialog)

CConstant4Dlg::CConstant4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT4, pParent)
	, m_constant4(0)
{

}

CConstant4Dlg::~CConstant4Dlg()
{
}

void CConstant4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT4, m_constant4);
	DDV_MinMaxDouble(pDX, m_constant4, 0, 180);
}


BEGIN_MESSAGE_MAP(CConstant4Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant4Dlg 메시지 처리기
