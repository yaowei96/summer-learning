// PointView.cpp : implementation of the CPointView class
//

#include "stdafx.h"
#include "Point.h"

#include "PointDoc.h"
#include "PointView.h"
#include "gl\gl.h"
#include "gl\glu.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include"math.h"
/////////////////////////////////////////////////////////////////////////////
// CPointView




/** 再定义一个默认的光源 */
static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };	 
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	 
static float lightPosition[] = { 0.0f, 0.0f, 10.0f, 1.0f };



IMPLEMENT_DYNCREATE(CPointView, CView)

BEGIN_MESSAGE_MAP(CPointView, CView)
	//{{AFX_MSG_MAP(CPointView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointView construction/destruction

CPointView::CPointView()
{
	// TODO: add construction code here
    m_pDC=NULL;
	m_Angle=0;
	m_Pivot = 1;  
	m_bRedX = 0.0f;


}

CPointView::~CPointView()
{
}

BOOL CPointView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPointView drawing

void CPointView::OnDraw(CDC* pDC)
{
	CPointDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawScene();
//	DrawCube();
}

/////////////////////////////////////////////////////////////////////////////
// CPointView printing

BOOL CPointView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPointView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPointView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPointView diagnostics

#ifdef _DEBUG
void CPointView::AssertValid() const
{
	CView::AssertValid();
}

void CPointView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPointDoc* CPointView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPointDoc)));
	return (CPointDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPointView message handlers
BOOL CPointView::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
	     1,
	     PFD_DRAW_TO_WINDOW |
		 PFD_SUPPORT_OPENGL|
		 PFD_DOUBLEBUFFER,
	     PFD_TYPE_RGBA,
		 24,
		 0, 0, 0, 0, 0, 0, 
		 0, 
		 0,
		 0, 
		 0, 0, 0, 0,
		 32,
		 0,
		 0,
		 PFD_MAIN_PLANE,
		 0,
		 0, 0, 0
	};
	int pixelformat;

	if((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	 {
		 MessageBox("ChoosePixelFormat failed");
		 return FALSE;
	 }
	if(SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	 }
    return TRUE;
}
void CPointView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;
    m_pDC=new CClientDC(this);
    if(!bSetupPixelFormat())
		return;
	hrc=wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(),hrc);



	
	/** 设置0号光源 */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); /**< 启用0号灰色光源,让物体可见 */
	

}
void CPointView::DrawScene(void)
{
	//设置清屏颜色为黑色
	glClearColor(0.0f,0.0f,0.0f,0.0f);
    //清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	
	glEnable(	GL_DEPTH_TEST);
   
   /** 用户自定义的绘制过程 */
 
	glLoadIdentity();	
	
	glTranslatef(0.0f, 0.0f, -10.0f); /**< 移入屏幕 */
	



  	glColor3f(1.0f,0.0f, 1.0f);
	glColorMaterial(GL_FRONT,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

 /** 绘制立方体 */
	glPushMatrix();

	glRotatef(m_Angle,1.0,1.0,0.0);
   glShadeModel(GL_SMOOTH);
   
   glBegin(GL_QUADS);
	
//top
   glNormal3f(0,1.0,0);
    glVertex3f(1,1,1);
	glVertex3f(1,1,-1);
	glVertex3f(-1,1,-1);
	glVertex3f(-1,1,1);
	//front
	  glNormal3f(0.0,0,1.0);
	glVertex3f(-1,1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(1,-1,1);
	glVertex3f(1,1,1);
	//right
	 glNormal3f(1.0,0,0);
	glVertex3f(1,1,1);
	glVertex3f(1,-1,1);
	glVertex3f(1,-1,-1);
	glVertex3f(1,1,-1);
	//bottom
	 glNormal3f(0,-1.0,0);
	glVertex3f(1,-1,-1);
	glVertex3f(1,-1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(-1,-1,-1);

	//back
	 glNormal3f(0,0,-1.0);
	glVertex3f(1,1,-1);
	glVertex3f(1,-1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,1,-1);
//left
	 glNormal3f(-1.0,0,0);
	glVertex3f(-1,1,1);
	glVertex3f(-1,1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,-1,1);


	glEnd();
	glPopMatrix();
 
	glFlush();									/**< 强制执行所有的OpenGL命令 */							
	 SwapBuffers(wglGetCurrentDC());
}

int CPointView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	Init();

	SetTimer(1,100,NULL);
	SetTimer(2,100,NULL);

	return 0;
}

void CPointView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	HGLRC hrc;
	hrc = ::wglGetCurrentContext();
	::wglMakeCurrent(NULL,NULL);
	if(hrc)
		::wglDeleteContext(hrc);
	if(m_pDC)
		delete m_pDC;


	KillTimer(1);

}

BOOL CPointView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return true;
}

void CPointView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
		int w=cx;int h=cy;
		glViewport(0,0,w,h); //设置视口与窗口匹配
		glMatrixMode(GL_PROJECTION); //重新设置坐标系统
		glLoadIdentity();
	
		gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

void CPointView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(nIDEvent==1)
	{
		m_Angle+=5;
	   if(m_Angle==360)
	    	m_Angle=0;
	   }
  
       

	   

	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CPointView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case '1':
		glDisable(GL_LIGHT0);
		
		break;
	case '2':
			glEnable(GL_LIGHT0);
		
		break;

	}
	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}
