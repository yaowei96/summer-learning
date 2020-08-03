// PointDoc.cpp : implementation of the CPointDoc class
//

#include "stdafx.h"
#include "Point.h"

#include "PointDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointDoc

IMPLEMENT_DYNCREATE(CPointDoc, CDocument)

BEGIN_MESSAGE_MAP(CPointDoc, CDocument)
	//{{AFX_MSG_MAP(CPointDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointDoc construction/destruction

CPointDoc::CPointDoc()
{
	// TODO: add one-time construction code here

}

CPointDoc::~CPointDoc()
{
}

BOOL CPointDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPointDoc serialization

void CPointDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPointDoc diagnostics

#ifdef _DEBUG
void CPointDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPointDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPointDoc commands
