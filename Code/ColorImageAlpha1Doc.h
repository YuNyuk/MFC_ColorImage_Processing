
// ColorImageAlpha1Doc.h: CColorImageAlpha1Doc 클래스의 인터페이스
//


#pragma once
#include <iostream>

class CColorImageAlpha1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImageAlpha1Doc() noexcept;
	DECLARE_DYNCREATE(CColorImageAlpha1Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CColorImageAlpha1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	int m_outImage;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;
	int m_inH = 0 ;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char** OnMalloc2D(int h, int w);

	template <typename T>
	void OnFree2d(T** memory, int h);
		
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnFreeOutImage();
	void OnGrayScale();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnChangeSatur();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnPickOrange();
	void OnEmboss();
	double** OnMalloc2D_double(int h, int w);
	void OnEmbossHsi();
	void OnAddImage();
	void OnDarkImage();
	void OnReverseImage();
	void OnBwImage();
	void OnGammaImage();
	void OnParabolaCap();
	void OnParabolaCup();
	void OnAndImage();
	void OnOrImage();
	void OnXorImage();
	void OnBlurImage();
	void OnSharpImage();
	void OnEdgeImage();
	void OnZoomIn1();
	void OnZoomIn2();
	void OnZoomIn3();
	void OnZoomOut();
	void OnMoveImage();
	void OnRotate1();
	void OnRotate2();
	void OnRotate3();
	void OnReverseImage1();
	void OnReverseImage2();
	void OnHistoStretch();
	void OnEndIn();
	void OnHistoEqual();
	void OnAddImage2();
	void OnDarkImage2();
};
