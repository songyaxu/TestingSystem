// HyperLinkButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestingSystem.h"
#include "HyperLinkButton.h"


// CHyperLinkButton

IMPLEMENT_DYNAMIC(CHyperLinkButton, CButton)

CHyperLinkButton::CHyperLinkButton()
{
	//��ʼ��������û�а���
	//���ָ��Ҳ���ڰ�ť��
	m_bMouseOver = m_bLBtnDown = FALSE;
	//����������
	m_hCurHand = AfxGetApp()->LoadCursor(IDC_HANDCUR);
}

CHyperLinkButton::~CHyperLinkButton()
{
}


BEGIN_MESSAGE_MAP(CHyperLinkButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CHyperLinkButton ��Ϣ��������




void CHyperLinkButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	m_bLBtnDown = TRUE;//����������
	CButton::OnLButtonDown(nFlags, point);
}


void CHyperLinkButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	m_bLBtnDown = FALSE;//������û�а���
	if (m_bMouseOver)
	{
		m_bMouseOver = FALSE;
		InvalidateRect(NULL);//�ػ水ť
	}
	CButton::OnLButtonUp(nFlags, point);
}


void CHyperLinkButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	SetTimer(1, 10, NULL);//����һ����ʱ��������OnTimer
	CButton::OnMouseMove(nFlags, point);
}


void CHyperLinkButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	static BOOL bPainted = FALSE;
	POINT pt;
	GetCursorPos(&pt);//��ù��ĵ�ǰλ��
	CRect rect;
	GetWindowRect(rect);//��ð�ť�Ĵ��ھ��δ�С	
	if (m_bLBtnDown)	    //�������
	{
		KillTimer(1);//ȡ����ʱ��
		if (bPainted)
			InvalidateRect(NULL);	//�ػ水ť	
		bPainted = FALSE;
		return;
	}
	if (!rect.PtInRect(pt))	 //��ǰ��겻�ڰ�ť������
	{
		m_bMouseOver = FALSE;
		KillTimer(1);//ȡ����ʱ��
		if (bPainted)
			InvalidateRect(NULL);
		bPainted = FALSE;
		return;
	}
	else//����ڰ�ť�����������û�а���
	{
		m_bMouseOver = TRUE;
		if (!bPainted)
		{
			bPainted = TRUE;
			InvalidateRect(NULL);//�ػ洰��
		}
	}
	CButton::OnTimer(nIDEvent);
}


BOOL CHyperLinkButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (m_bMouseOver)   //�������ڰ�ť�Ϸ�����Ĺ����״ 
	{
		::SetCursor(m_hCurHand);
		return true;
	}
	return CButton::OnSetCursor(pWnd, nHitTest, message);
}


void CHyperLinkButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{	
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);// ��ȡDCָ��
	CRect rect(lpDrawItemStruct->rcItem);//���尴ť���򲢳�ʼ��	
	pDC->SetBkMode(TRANSPARENT);//���ñ���Ϊ͸��
	UINT nBtnState = lpDrawItemStruct->itemState;//ȡ�ð�ť״̬
	CFont * pOldFont = NULL;
	CString strText;
	GetWindowText(strText);	//��ð�ť�ı�
	if (m_bMouseOver)//����ڰ�ť��
	{
		/*if (nBtnState&ODS_SELECTED)//���°�ť,���Ʒ�����ο�
		{
			pDC->Draw3dRect(rect, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
		}
		else//δ���°�ť�������������ο�
		{
			pDC->Draw3dRect(rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
		}*/

		pDC->SetTextColor(RGB(0, 0, 255));	//������ɫ����Ϊ��ɫ

		if (m_fontUnderline.GetSafeHandle() == NULL)
		{
			CFont * pFont = GetFont();
			ASSERT(pFont);
			LOGFONT lf;
			pFont->GetLogFont(&lf);
			lf.lfUnderline = TRUE;	//���»���
			m_fontUnderline.CreateFontIndirect(&lf);
		}
		pOldFont = pDC->SelectObject(&m_fontUnderline);
	}
	else pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));//����ϵͳ����
	pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//��ʾ��ť�ı�
	if (pOldFont)
		pDC->SelectObject(pOldFont);
	// TODO:  �������Ĵ����Ի���ָ����
}