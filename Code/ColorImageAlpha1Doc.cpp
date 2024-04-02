
// ColorImageAlpha1Doc.cpp: CColorImageAlpha1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageAlpha1.h"
#endif

#include "ColorImageAlpha1Doc.h"

#include <propkey.h>
#include "Constant1Dlg.h" // 정수 값
#include "Constant2Dlg.h" // 감마 값
#include "Constant3Dlg.h" // 배율 값
#include "Constant4Dlg.h" // 각도 값

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImageAlpha1Doc

IMPLEMENT_DYNCREATE(CColorImageAlpha1Doc, CDocument)

BEGIN_MESSAGE_MAP(CColorImageAlpha1Doc, CDocument)
END_MESSAGE_MAP()


// CColorImageAlpha1Doc 생성/소멸

CColorImageAlpha1Doc::CColorImageAlpha1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImageAlpha1Doc::~CColorImageAlpha1Doc()
{
}

BOOL CColorImageAlpha1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CColorImageAlpha1Doc serialization

void CColorImageAlpha1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CColorImageAlpha1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CColorImageAlpha1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImageAlpha1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorImageAlpha1Doc 진단

#ifdef _DEBUG
void CColorImageAlpha1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImageAlpha1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImageAlpha1Doc 명령


BOOL CColorImageAlpha1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// 기존 메모리 해제
	if (m_inImageR != NULL) {
		OnFree2d(m_inImageR, m_inH);
		OnFree2d(m_inImageG, m_inH);
		OnFree2d(m_inImageB, m_inH);
		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2d(m_outImageR, m_outH);
		OnFree2d(m_outImageG, m_outH);
		OnFree2d(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CImage image;
	image.Load(lpszPathName);
	// (중요!) 입력 영상 크기 알아내기~
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	// 메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage의 객체값 --> 메모리
	COLORREF  px;
	for (int i=0; i<m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			px = image.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);
		}

	return TRUE;
}


unsigned char** CColorImageAlpha1Doc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new unsigned char[w];
	return memory;
}


double** CColorImageAlpha1Doc::OnMalloc2D_double(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** memory;
	memory = new double* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new double[w];
	return memory;
}


template <typename T>
void CColorImageAlpha1Doc::OnFree2d(T** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


void CColorImageAlpha1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2d(m_inImageR, m_inH);
	OnFree2d(m_inImageG, m_inH);
	OnFree2d(m_inImageB, m_inH);

	OnFree2d(m_outImageR, m_outH);
	OnFree2d(m_outImageG, m_outH);
	OnFree2d(m_outImageB, m_outH);

	CDocument::OnCloseDocument();
}


void CColorImageAlpha1Doc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2d(m_outImageR, m_outH);
		OnFree2d(m_outImageG, m_outH);
		OnFree2d(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}
}


void CColorImageAlpha1Doc::OnEqualImage()
{

	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}

}


void CColorImageAlpha1Doc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char) avg;
		}
	}
}


BOOL CColorImageAlpha1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;
	CImage image;
	image.Create(m_outW, m_outH, 32);
	unsigned char R, G, B;
	COLORREF px;
	for(int i=0; i<m_outW; i++) 
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);
	return TRUE;
}


double* CColorImageAlpha1Doc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


unsigned char* CColorImageAlpha1Doc::HSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}






// 화소 점 처리 //


void CColorImageAlpha1Doc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant1Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 진짜 영상처리 알고리즘 ***
	int value = (int)dlg.m_constant1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] + value > 255)
				m_outImageR[i][k] = 255;
			else if (m_inImageR[i][k] + value < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = m_inImageR[i][k] + value;

			if (m_inImageG[i][k] + value > 255)
				m_outImageG[i][k] = 255;
			else if (m_inImageG[i][k] + value < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = m_inImageG[i][k] + value;

			if (m_inImageB[i][k] + value > 255)
				m_outImageB[i][k] = 255;
			else if (m_inImageB[i][k] + value < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = m_inImageB[i][k] + value;
		}
	}
}


void CColorImageAlpha1Doc::OnDarkImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant1Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// *** 진짜 영상처리 알고리즘 ***
	int val = (int)dlg.m_constant1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] - val > 0)
				m_outImageR[i][k] = m_inImageR[i][k] - val;
			else
				m_outImageR[i][k] = 0;

			if (m_inImageG[i][k] - val > 0)
				m_outImageG[i][k] = m_inImageG[i][k] - val;
			else
				m_outImageG[i][k] = 0;

			if (m_inImageB[i][k] - val > 0)
				m_outImageB[i][k] = m_inImageB[i][k] - val;
			else
				m_outImageB[i][k] = 0;
		}
	}
}


void CColorImageAlpha1Doc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
		OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = 255 - m_inImageR[i][k];
			m_outImageG[i][k] = 255 - m_inImageG[i][k];
			m_outImageB[i][k] = 255 - m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnBwImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_outImageR[i][k] < 127)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = 255;

			if (m_outImageG[i][k] < 127)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = 255;

			if (m_outImageB[i][k] < 127)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = 255;
		}
	}
}


void CColorImageAlpha1Doc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant2Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double val = (double)dlg.m_constant2;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			//픽셀 값 0~1로 정규화
			float normalized_pixelR = (float)m_inImageR[i][k] / 255.0;
			float normalized_pixelG = (float)m_inImageG[i][k] / 255.0;
			float normalized_pixelB = (float)m_inImageB[i][k] / 255.0;
			//감마 함수 적용후 보정된 값 계산
			float corrected_pixelR = pow(normalized_pixelR, val);
			float corrected_pixelG = pow(normalized_pixelG, val);
			float corrected_pixelB = pow(normalized_pixelB, val);

			corrected_pixelR *= 255.0;
			corrected_pixelG *= 255.0;
			corrected_pixelB *= 255.0;

			if (corrected_pixelR < 0)
				corrected_pixelR = 0;
			if (corrected_pixelR > 255)
				corrected_pixelR = 255;

			if (corrected_pixelG < 0)
				corrected_pixelG = 0;
			if (corrected_pixelG > 255)
				corrected_pixelG = 255;

			if (corrected_pixelB < 0)
				corrected_pixelB = 0;
			if (corrected_pixelB > 255)
				corrected_pixelB = 255;

			m_outImageR[i][k] = (unsigned char)corrected_pixelR;
			m_outImageG[i][k] = (unsigned char)corrected_pixelG;
			m_outImageB[i][k] = (unsigned char)corrected_pixelB;
		}
	}
}


void CColorImageAlpha1Doc::OnParabolaCap()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	m_outImageR, m_outImageG, m_outImageB = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImageR[i][k] = 255 - 255 * pow((m_inImageR[i][k] / 127), 2);
			m_outImageG[i][k] = 255 - 255 * pow((m_inImageG[i][k] / 127), 2);
			m_outImageB[i][k] = 255 - 255 * pow((m_inImageB[i][k] / 127), 2);
		}
	}
}


void CColorImageAlpha1Doc::OnParabolaCup()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	m_outImageR, m_outImageG, m_outImageB = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImageR[i][k] = 255 * pow((m_inImageR[i][k] / 127), 2);
			m_outImageG[i][k] = 255 * pow((m_inImageG[i][k] / 127), 2);
			m_outImageB[i][k] = 255 * pow((m_inImageB[i][k] / 127), 2);
		}
	}
}


void CColorImageAlpha1Doc::OnAndImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant1Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_inImageR[i][k] & (unsigned char)val) >= 255)
				m_outImageR[i][k] = 255;
			else if ((m_inImageR[i][k] & (unsigned char)val) < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = (unsigned char)(m_inImageR[i][k] & (unsigned char)val);

			if ((m_inImageG[i][k] & (unsigned char)val) >= 255)
				m_outImageG[i][k] = 255;
			else if ((m_inImageG[i][k] & (unsigned char)val) < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = (unsigned char)(m_inImageG[i][k] & (unsigned char)val);

			if ((m_inImageB[i][k] & (unsigned char)val) >= 255)
				m_outImageB[i][k] = 255;
			else if ((m_inImageB[i][k] & (unsigned char)val) < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = (unsigned char)(m_inImageB[i][k] & (unsigned char)val);
		}
	}
}


void CColorImageAlpha1Doc::OnOrImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant1Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_inImageR[i][k] | (unsigned char)val) >= 255)
				m_outImageR[i][k] = 255;
			else if ((m_inImageR[i][k] | (unsigned char)val) < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = (unsigned char)(m_inImageR[i][k] | (unsigned char)val);

			if ((m_inImageG[i][k] | (unsigned char)val) >= 255)
				m_outImageG[i][k] = 255;
			else if ((m_inImageG[i][k] | (unsigned char)val) < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = (unsigned char)(m_inImageG[i][k] | (unsigned char)val);

			if ((m_inImageB[i][k] | (unsigned char)val) >= 255)
				m_outImageB[i][k] = 255;
			else if ((m_inImageB[i][k] | (unsigned char)val) < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = (unsigned char)(m_inImageB[i][k] | (unsigned char)val);
		}
	}
}


void CColorImageAlpha1Doc::OnXorImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant1Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_inImageR[i][k] ^ (unsigned char)val) >= 255)
				m_outImageR[i][k] = 255;
			else if ((m_inImageR[i][k] ^ (unsigned char)val) < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = (unsigned char)(m_inImageR[i][k] ^ (unsigned char)val);

			if ((m_inImageG[i][k] ^ (unsigned char)val) >= 255)
				m_outImageG[i][k] = 255;
			else if ((m_inImageG[i][k] ^ (unsigned char)val) < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = (unsigned char)(m_inImageG[i][k] ^ (unsigned char)val);

			if ((m_inImageB[i][k] ^ (unsigned char)val) >= 255)
				m_outImageB[i][k] = 255;
			else if ((m_inImageB[i][k] ^ (unsigned char)val) < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = (unsigned char)(m_inImageB[i][k] ^ (unsigned char)val);
		}
	}
}



// 화소 영역 처리 //



void CColorImageAlpha1Doc::OnEmboss()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {  // 엠보싱 마스크
		{ -1.0, 0.0, 0.0 },
		{  0.0, 0.0, 0.0 },
		{  0.0, 0.0, 1.0 } };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}
	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127;
			tmpOutImageG[i][k] += 127;
			tmpOutImageB[i][k] += 127;
		}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEmbossHsi()
{
	// TODO: 여기에 구현 코드 추가.
		// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {  // 엠보싱 마스크
		{ -1.0, 0.0, 0.0 },
		{  0.0, 0.0, 0.0 },
		{  0.0, 0.0, 1.0 } };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageI[i][k] += 127;
		}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}


	// 임시 메모리 해제
	OnFree2d(tmpInImageR, m_inH + 2);
	OnFree2d(tmpInImageG, m_inH + 2);
	OnFree2d(tmpInImageB, m_inH + 2);
	OnFree2d(tmpInImageH, m_inH + 2);
	OnFree2d(tmpInImageS, m_inH + 2);
	OnFree2d(tmpInImageI, m_inH + 2);
	OnFree2d(tmpOutImageR, m_outH);
	OnFree2d(tmpOutImageG, m_outH);
	OnFree2d(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnBlurImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// *** 진짜 영상처리 알고리즘 ***
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = // 블러 마스크
	{ {1.0 / 20, 1.0 / 20, 1.0 / 20},
	  {1.0 / 20, 2.0 / 20, 1.0 / 20},
	  {1.0 / 20, 1.0 / 20, 1.0 / 20} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}
	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 100; // 예시로 작은 값 100 더하기
			tmpOutImageG[i][k] += 100; // 예시로 작은 값 100 더하기
			tmpOutImageB[i][k] += 100; // 예시로 작은 값 100 더하기
		}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
}


void CColorImageAlpha1Doc::OnSharpImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// *** 진짜 영상처리 알고리즘 ***
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] =
	{ {0.0, -1.0 ,0.0}, // 샤프닝 마스크
	  {-1.0 ,5.0, -1.0},
	  {0.0, -1.0, 0.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}
	// 후처리 (원래 이미지와 샤프닝 처리된 이미지 간의 차이를 적용)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			int diffR = m_inImageR[i][k] - tmpOutImageR[i][k];
			int diffG = m_inImageG[i][k] - tmpOutImageG[i][k];
			int diffB = m_inImageB[i][k] - tmpOutImageB[i][k];

			m_outImageR[i][k] = m_inImageR[i][k] + diffR;
			m_outImageG[i][k] = m_inImageG[i][k] + diffG;
			m_outImageB[i][k] = m_inImageB[i][k] + diffB;

			// 값 범위를 0에서 255로 조정
			if (m_outImageR[i][k] < 0)
				m_outImageR[i][k] = 0;
			else if (m_outImageR[i][k] > 255)
				m_outImageR[i][k] = 255;

			if (m_outImageG[i][k] < 0)
				m_outImageG[i][k] = 0;
			else if (m_outImageG[i][k] > 255)
				m_outImageG[i][k] = 255;

			if (m_outImageB[i][k] < 0)
				m_outImageB[i][k] = 0;
			else if (m_outImageB[i][k] > 255)
				m_outImageB[i][k] = 255;
		}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
}


void CColorImageAlpha1Doc::OnEdgeImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// *** 진짜 영상처리 알고리즘 ***
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = // 수직 에지 검출 마스크
	{ {0.0, 0.0, 0.0},
	  {-1.0, 1.0, 0.0},
	  {0.0,  0.0, 0.0} };

	// 임시 메모리 할당
	double** tmpInImageR, ** tmpInImageG, ** tmpInImageB, ** tmpOutImageR, ** tmpOutImageG, ** tmpOutImageB;
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력 메모리 --> 임시 입력 메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기.

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];
			tmpOutImageR[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];
			tmpOutImageG[i][k] = S;

			S = 0.0;
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];
			tmpOutImageB[i][k] = S;
		}
	}
	// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpOutImageR[i][k] += 127; // 예시로 작은 값 100 더하기
			tmpOutImageG[i][k] += 127; // 예시로 작은 값 100 더하기
			tmpOutImageB[i][k] += 127; // 예시로 작은 값 100 더하기
		}

	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
}




// 기하학적 처리 //



void CColorImageAlpha1Doc::OnZoomIn1() // 포워딩
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int scale = (int)dlg.m_constant3;
	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// *** 진짜 영상처리 알고리즘 ***
	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[(int)(i * scale)][(int)(k * scale)] = m_inImageR[i][k];
			m_outImageG[(int)(i * scale)][(int)(k * scale)] = m_inImageG[i][k];
			m_outImageB[(int)(i * scale)][(int)(k * scale)] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnZoomIn2() // 백워딩
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int scale = (int)dlg.m_constant3;
	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);


	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[(int)(i / scale)][(int)(k / scale)];
			m_outImageG[i][k] = m_inImageG[(int)(i / scale)][(int)(k / scale)];
			m_outImageB[i][k] = m_inImageB[(int)(i / scale)][(int)(k / scale)];
		}
	}
}


void CColorImageAlpha1Doc::OnZoomIn3() // 양선형 보간법
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int scale = (int)dlg.m_constant3;
	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	double rowRatio = (double)(m_inH - 1) / (m_outH - 1);
	double colRatio = (double)(m_inW - 1) / (m_outW - 1);

	// 출력 이미지의 각 픽셀에 대해 양선형 보간법 수행
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			// 현재 픽셀의 위치를 기준으로 입력 이미지에서 가장 가까운 네 개의 픽셀을 찾습니다.
			int baseRow = (int)(round(i * rowRatio));
			int baseCol = (int)(round(k * colRatio));

			// 현재 픽셀의 위치와 가장 가까운 네 개의 픽셀 사이의 거리를 계산합니다.
			double dx = (i * rowRatio) - baseRow;
			double dy = (k * colRatio) - baseCol;

			if (baseRow >= 0 && baseRow < m_inH - 1 && baseCol >= 0 && baseCol < m_inW - 1) {
				// 양선형 보간법을 사용하여 현재 픽셀의 값을 계산합니다.
				double interpolatedValue = (1 - dx) * (1 - dy) * m_inImageR[baseRow][baseCol] +
					dx * (1 - dy) * m_inImageR[baseRow + 1][baseCol] +
					(1 - dx) * dy * m_inImageR[baseRow][baseCol + 1] +
					dx * dy * m_inImageR[baseRow + 1][baseCol + 1];
				// 계산된 값으로 출력 이미지의 현재 픽셀을 설정합니다.
				m_outImageR[i][k] = (unsigned char)interpolatedValue;
			}
			else {
				m_outImageR[i][k] = 255;
			}

			if (baseRow >= 0 && baseRow < m_inH - 1 && baseCol >= 0 && baseCol < m_inW - 1) {
				// 양선형 보간법을 사용하여 현재 픽셀의 값을 계산합니다.
				double interpolatedValue = (1 - dx) * (1 - dy) * m_inImageG[baseRow][baseCol] +
					dx * (1 - dy) * m_inImageG[baseRow + 1][baseCol] +
					(1 - dx) * dy * m_inImageG[baseRow][baseCol + 1] +
					dx * dy * m_inImageG[baseRow + 1][baseCol + 1];
				// 계산된 값으로 출력 이미지의 현재 픽셀을 설정합니다.
				m_outImageG[i][k] = (unsigned char)interpolatedValue;
			}
			else {
				m_outImageG[i][k] = 255;
			}

			if (baseRow >= 0 && baseRow < m_inH - 1 && baseCol >= 0 && baseCol < m_inW - 1) {
				// 양선형 보간법을 사용하여 현재 픽셀의 값을 계산합니다.
				double interpolatedValue = (1 - dx) * (1 - dy) * m_inImageB[baseRow][baseCol] +
					dx * (1 - dy) * m_inImageB[baseRow + 1][baseCol] +
					(1 - dx) * dy * m_inImageB[baseRow][baseCol + 1] +
					dx * dy * m_inImageB[baseRow + 1][baseCol + 1];
				// 계산된 값으로 출력 이미지의 현재 픽셀을 설정합니다.
				m_outImageB[i][k] = (unsigned char)interpolatedValue;
			}
			else {
				m_outImageB[i][k] = 255;
			}
		}
	}
}


void CColorImageAlpha1Doc::OnZoomOut()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int scale = (int)dlg.m_constant3;
	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = (int)(m_inH / scale);
	m_outW = (int)(m_inW / scale);

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[(int)(i / scale)][(int)(k / scale)] = m_inImageR[i][k];
			m_outImageG[(int)(i / scale)][(int)(k / scale)] = m_inImageG[i][k];
			m_outImageB[(int)(i / scale)][(int)(k / scale)] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant1Dlg dlgA;
	if (dlgA.DoModal() != IDOK)
		return;
	int b = (int)dlgA.m_constant1;

	CConstant1Dlg dlgB;
	if (dlgB.DoModal() != IDOK)
		return;

	int a = (int)dlgB.m_constant1;
	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			// 이미지 이동 시 경계를 벗어나는 경우를 고려하여 인덱스를 체크하여 처리
			if (i + a >= 0 && i + a < m_inH && k - b >= 0 && k - b < m_inW)
				m_outImageR[i][k] = m_inImageR[i + a][k - b];
			else
				m_outImageR[i][k] = 0; // 경계를 벗어나는 경우에는 0으로 처리하거나 다른 방법으로 처리

			if (i + a >= 0 && i + a < m_inH && k - b >= 0 && k - b < m_inW)
				m_outImageG[i][k] = m_inImageG[i + a][k - b];
			else
				m_outImageG[i][k] = 0; // 경계를 벗어나는 경우에는 0으로 처리하거나 다른 방법으로 처리

			if (i + a >= 0 && i + a < m_inH && k - b >= 0 && k - b < m_inW)
				m_outImageB[i][k] = m_inImageB[i + a][k - b];
			else
				m_outImageB[i][k] = 0; // 경계를 벗어나는 경우에는 0으로 처리하거나 다른 방법으로 처리
		}
	}
}


void CColorImageAlpha1Doc::OnRotate1() // 회전
{
	// TODO: 여기에 구현 코드 추가.
	CConstant4Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	
	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int degree = (int)dlg.m_constant4;
	double radian = degree * 3.141592 / 180.0;

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int xs = i;
			int ys = k;
			int xd = cos(radian) * xs - sin(radian) * ys;
			int yd = sin(radian) * xs + cos(radian) * ys;

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
				m_outImageR[xd][yd] = m_inImageR[xs][ys];

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
				m_outImageG[xd][yd] = m_inImageG[xs][ys];

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
		}
	}
}


void CColorImageAlpha1Doc::OnRotate2() // 회전+중심+백워딩
{
	// TODO: 여기에 구현 코드 추가.
	CConstant4Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// 기존 메모리 해제
	OnFreeOutImage();

	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int degree = (int)dlg.m_constant4;
	double radian = degree * 3.141592 / 180.0;

	// 회전 중심 계산
	int cx = m_inH / 2;
	int cy = m_inW / 2;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int xd = i;
			int yd = k;
			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;
			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				m_outImageR[xd][yd] = m_inImageR[xs][ys];

			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				m_outImageG[xd][yd] = m_inImageG[xs][ys];

			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
		}
	}
}


void CColorImageAlpha1Doc::OnRotate3() // 회전 + 확대 + 백워딩
{
	// TODO: 여기에 구현 코드 추가.

	CConstant4Dlg dlgA;
	if (dlgA.DoModal() != IDOK)
		return;

	CConstant3Dlg dlgB;
	if (dlgB.DoModal() != IDOK)
		return;

	// 기존 메모리 해제
	OnFreeOutImage();

	int degree = (int)dlgA.m_constant4;
	int scale = (int)dlgB.m_constant3;
	double radian = -degree * 3.141592 / 180.0;
	
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH * scale;
	m_outW = m_inW * scale;

	// 회전 중심 계산
	int cx = m_inH / 2;
	int cy = m_inW / 2;

	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			// 회전 및 확대된 픽셀 위치 계산
			int xd = i / scale;
			int yd = k / scale;
			int xs = (int)(cos(radian) * (xd - cx) - sin(radian) * (yd - cy) + cx);
			int ys = (int)(sin(radian) * (xd - cx) + cos(radian) * (yd - cy) + cy);

			// 회전된 픽셀 위치의 유효성 검사
			if (0 <= xs && xs < m_inH && 0 <= ys && ys < m_inW) {
				m_outImageR[i][k] = m_inImageR[xs][ys];
			}
			else {
				m_outImageR[i][k] = 255; // 흰색으로 설정
			}

			if (0 <= xs && xs < m_inH && 0 <= ys && ys < m_inW) {
				m_outImageG[i][k] = m_inImageG[xs][ys];
			}
			else {
				m_outImageG[i][k] = 255; // 흰색으로 설정
			}

			if (0 <= xs && xs < m_inH && 0 <= ys && ys < m_inW) {
				m_outImageB[i][k] = m_inImageB[xs][ys];
			}
			else {
				m_outImageB[i][k] = 255; // 흰색으로 설정
			}
		}
	}


}


void CColorImageAlpha1Doc::OnReverseImage1() // 상하 반전
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[m_inH - 1 - i][k];
			m_outImageG[i][k] = m_inImageG[m_inH - 1 - i][k];
			m_outImageB[i][k] = m_inImageB[m_inH - 1 - i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnReverseImage2() // 좌우 반전
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[i][m_inW - 1 - k];
			m_outImageG[i][k] = m_inImageG[i][m_inW - 1 - k];
			m_outImageB[i][k] = m_inImageB[i][m_inW - 1 - k];
		}
	}
}



// 히스토그램 처리 //



void CColorImageAlpha1Doc::OnHistoStretch() // 히스토그램 스트레칭
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 여기서부터 영상처리 알고리즘 시작~~
	// new = (old - low) / (high - low) * 255.0
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k] < lowR;
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];

			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k] < lowG;
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];

			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k] < lowB;
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}
	int oldPixelR, oldPixelG, oldPixelB, newPixelR, newPixelG, newPixelB;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			oldPixelR = m_inImageR[i][k];
			oldPixelG = m_inImageG[i][k];
			oldPixelB = m_inImageB[i][k];

			newPixelR = (int)((double)(oldPixelR - lowR) / (double)(highR - lowR) * 255.0);
			if (newPixelR > 255)
				newPixelR = 255;
			if (newPixelR < 0)
				newPixelR = 0;
			m_outImageR[i][k] = newPixelR;

			newPixelG = (int)((double)(oldPixelG - lowG) / (double)(highG - lowG) * 255.0);
			if (newPixelG > 255)
				newPixelG = 255;
			if (newPixelG < 0)
				newPixelG = 0;
			m_outImageG[i][k] = newPixelG;

			newPixelB = (int)((double)(oldPixelB - lowB) / (double)(highB - lowB) * 255.0);
			if (newPixelB > 255)
				newPixelB = 255;
			if (newPixelB < 0)
				newPixelB = 0;
			m_outImageB[i][k] = newPixelB;
		}
	}
}


void CColorImageAlpha1Doc::OnEndIn()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 여기서부터 영상처리 알고리즘 시작~~
	// new = (old - low) / (high - low) * 255.0
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k] < lowR;
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];

			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k] < lowG;
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];

			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k] < lowB;
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}

	highR, highG, highB -= 50;
	lowR, lowG, lowB += 50;

	int oldPixelR, oldPixelG, oldPixelB, newPixelR, newPixelG, newPixelB;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			oldPixelR = m_inImageR[i][k];
			oldPixelG = m_inImageG[i][k];
			oldPixelB = m_inImageB[i][k];

			newPixelR = (int)((double)(oldPixelR - lowR) / (double)(highR - lowR) * 255.0);
			if (newPixelR > 255)
				newPixelR = 255;
			if (newPixelR < 0)
				newPixelR = 0;
			m_outImageR[i][k] = newPixelR;

			newPixelG = (int)((double)(oldPixelG - lowG) / (double)(highG - lowG) * 255.0);
			if (newPixelG > 255)
				newPixelG = 255;
			if (newPixelG < 0)
				newPixelG = 0;
			m_outImageG[i][k] = newPixelG;

			newPixelB = (int)((double)(oldPixelB - lowB) / (double)(highB - lowB) * 255.0);
			if (newPixelB > 255)
				newPixelB = 255;
			if (newPixelB < 0)
				newPixelB = 0;
			m_outImageB[i][k] = newPixelB;
		}
	}
}


void CColorImageAlpha1Doc::OnHistoEqual()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	// 1단계 : 빈도수 세기 (=히스토그램)
	int histoR[256] = { 0. }; int histoG[256] = { 0. }; int histoB[256] = { 0. };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			histoR[m_inImageR[i][k]]++;
			histoG[m_inImageG[i][k]]++;
			histoB[m_inImageB[i][k]]++;
		}
	

	// 2단계 : 누적 히스토그램 생성
	int sumHistoR[256] = { 0, }; int sumHistoG[256] = { 0, }; int sumHistoB[256] = { 0, };
	sumHistoR[0] = histoR[0]; sumHistoG[0] = histoG[0]; sumHistoB[0] = histoB[0];
	for (int i = 1; i < 256; i++) {
		sumHistoR[i] = sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] = sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] = sumHistoB[i - 1] + histoB[i];
	}
	// 3단계 : 정규화된 히스토그램 생성 normalHisto = sumHisto * (1.0 / (inH*inW) * 255.0;
	double normalHistoR[256] = { 1.0, }; double normalHistoG[256] = { 1.0, }; double normalHistoB[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = (unsigned char)normalHistoR[m_inImageR[i][k]];
			m_outImageG[i][k] = (unsigned char)normalHistoG[m_inImageG[i][k]];
			m_outImageB[i][k] = (unsigned char)normalHistoB[m_inImageB[i][k]];
		}
	}
}



// 칼라 이미지 효과 //



void CColorImageAlpha1Doc::OnChangeSatur()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];	S = hsi[1];	I = hsi[2];

			/// 채도(S) 흐리게
			S = S - 0.3;
			if (S < 0)
				S = 0.0;

			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}


void CColorImageAlpha1Doc::OnPickOrange()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];	S = hsi[1];	I = hsi[2];

			/// 오렌지 추출 (H : 8~20)
			if (8 <= H && H <= 20) {
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
			else {
				double avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
			}

		}
	}
}