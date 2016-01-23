
#include "stdafx.h"
#include <ctype.h>

char 
CBaseCaret::MakeAscii( UINT nChar, UINT nFlags )
{

	BYTE KeyState[256];

	WORD TransKey;

	GetKeyboardState(KeyState);
	
	if ( ToAscii(nChar, (nFlags & 0x7f), KeyState, &TransKey, 0) == 1 ) {
		return (char )(TransKey & 0x7f);
	} else {
		return 0;
	}

}

CBaseCaret::CBaseCaret()
{
	m_ControlOn = 0;
	m_ShiftOn = 0;
	m_Clipping = 0;
	// m_Position = CPoint (-1, -1);
	m_XPosition = UINT_MAX;
	m_YPosition = 0;
}

void CBaseCaret::CaretPos()
{
	SetCaretPos ( (int)(m_XPosition - m_ScrollXPosition), (int)(m_YPosition - m_ScrollYPosition) );
	// for status bar updates
//	TRACE ( "CaretPos: X = %d, Y = %d\n", (int)(m_XPosition - m_ScrollXPosition), (int)(m_YPosition - m_ScrollYPosition) );
}

void CBaseCaret::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags, CView* pView)
{
	switch ( nChar ) {
	case VK_CONTROL:
		m_ControlOn = 0;
		break;
	case VK_SHIFT:
		m_ShiftOn = 0;
		LeftUp( m_XPosition, m_YPosition, pView );
		break;
	}
}

void CBaseCaret::ClearKeys()
{
	m_ControlOn = 0;
	m_ShiftOn = 0;
}

void CBaseCaret::SetIncrements( UINT nxi, DWORD nyi, UINT nxs, DWORD nys )
{
	m_xi = nxi;
	m_yi = nyi;
	m_xs = nxs;
	m_ys = nys;
}

void CBaseCaret::SetMaximums( UINT nmx, DWORD nmy )
{
	m_maxx = nmx;
	m_maxy = nmy;
	m_minx = 0;
	m_miny = 0;

	// PreInited Check.
	if ( m_XPosition == UINT_MAX ) return;
	
	if ( m_YPosition > m_maxy ) {
//		do {
//			m_YPosition -= m_yi;
//		} while ( m_YPosition > m_maxy );
		while ( (m_maxy + m_yi) <= m_YPosition) {
			m_YPosition -= m_yi;
		}
	}

}

void CBaseCaret::ClipCaret(int Clipping, UINT XPosition, DWORD YPosition, UINT XSize, DWORD YSize)
{
	if ( Clipping == 0 ) {
		m_Clipping = 0;
	} else {
		m_Clipping = 1;
		m_ClipXPosition = XPosition;
		m_ClipYPosition = YPosition;
		m_ClipXSize = XSize;
		m_ClipYSize = YSize;
		// m_ClipRect = ClipRect;
	}
}

void CBaseCaret::SetPosition( UINT XPosition, DWORD YPosition )
{	
	m_XPosition = XPosition;
	m_YPosition = YPosition;
}

void CBaseCaret::SetHeight( DWORD nCaretHeight )
{
	m_CaretHeight = nCaretHeight;
}

void CBaseCaret::SetScrollPos( UINT XPosition, DWORD YPosition )
{	
	m_ScrollXPosition = XPosition;
	m_ScrollYPosition = YPosition;

	CaretPos();
}

void CBaseCaret::SetViewSize( UINT XSize, DWORD YSize)
{
	m_ViewXSize = XSize;
	m_ViewYSize = YSize;
}

void
CBaseCaret::GetPosition(UINT *XPosition, DWORD *YPosition)
{
	*XPosition = m_XPosition;
	*YPosition = m_YPosition;
	return;
}

void 
CBaseCaret::FollowMouse( UINT XPosition, DWORD YPosition )
{
	if ( m_XPosition < XPosition ) {
		while ( (m_XPosition + m_xi) <= XPosition ) {
			m_XPosition += m_xi;
		}
	} else if ( m_XPosition > XPosition ) {
//		do {
//			m_XPosition -= m_xi;
//		} while ( m_XPosition > XPosition );
		while ( m_XPosition > XPosition ) { 
			m_XPosition -= m_xi;
		}
	}

	if ( m_YPosition < YPosition ) {
		while ( (m_YPosition + m_yi) <= YPosition ) {
			m_YPosition += m_yi;
		}
	} else if ( m_YPosition > YPosition ) {
//		do {
//			m_YPosition -= m_yi;
//		} while ( m_YPosition > YPosition );
		while ( m_YPosition > YPosition ) { 
			m_YPosition -= m_yi;
		}
		
	}

	// Set the caret to the current position
	CaretPos ();
}

void CBaseCaret::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags, CView* pView)
{

	UINT txi = m_xi * nRepCnt;   
	UINT txs = m_xs * nRepCnt;
	DWORD tyi = m_yi * nRepCnt;
	DWORD tys = m_ys * nRepCnt;
	UINT OldXPos = m_XPosition;
	DWORD OldYPos = m_YPosition;
	int nomove = 0, comment = 0;
	UINT smaxx = m_maxx;
	DWORD smaxy = m_maxy;
	UINT sminx = m_minx;
	DWORD sminy = m_miny;
	char tChar;

	// Arange for clipping function	
	if ( m_Clipping ) {
		/*
		m_maxx = m_ClipRect.BottomRight().x;
		m_maxy = m_ClipRect.BottomRight().y - m_CaretHeight;
		m_minx = m_ClipRect.TopLeft().x - 2;
		m_miny = m_ClipRect.TopLeft().y;
		*/
		m_maxx = m_ClipXPosition + m_ClipXSize;
		m_maxy = m_ClipYPosition + m_ClipYSize - m_CaretHeight;
		m_minx = m_ClipXPosition - 2;
		m_miny = m_ClipYPosition;
	}

	// Move m_Position based on char and max's
	switch ( nChar ) {
	case VK_UP:
		if ( (m_miny + tyi) <= m_YPosition ) {
			m_YPosition -= tyi;
		}
		break;
	case VK_DOWN:
		if ( (m_YPosition + tyi) < m_maxy ) {
			m_YPosition += tyi;
		}
		break;
	case VK_LEFT:
		if ( m_ControlOn ) {
			if ( (m_minx + txs) <= m_XPosition ) {
				m_XPosition -= txs;
			} else {
				while ( (m_minx + txi) <= m_XPosition ) {
					m_XPosition -= txi;
				}
			}				
		} else {
			if ( (m_minx + txi) <= m_XPosition ) {
				m_XPosition -= txi;
			}
		}
		break;
	case VK_RIGHT:
		if ( m_ControlOn ) {
			if ( (m_XPosition + txs) < m_maxx ) {
				m_XPosition += txs;
			} else {
				while ( (m_XPosition + txi) < m_maxx ) {
					m_XPosition += txi;
				}
			}				
		} else {
			if ( (m_XPosition + txi) < m_maxx ) {
				m_XPosition += txi;
			}
		}
		break;
	case VK_CONTROL:
		m_ControlOn = 1;
		nomove = 1;
		break;
	case VK_SHIFT:
		m_ShiftOn = 1;
		if ( !(nFlags & 0x4000) ) {
			LeftDown( m_XPosition, m_YPosition, pView );
		}
		nomove = 1;
		break;
	case VK_END:
		if ( m_ControlOn ) {
			m_YPosition = m_maxy;
		} else {
			while ( (m_XPosition + txi) < m_maxx ) {
				m_XPosition += txi;
			}
		}
		break;
	case VK_HOME:
		if ( m_ControlOn ) {
			m_YPosition = m_miny;
		} else {
			while ( (m_minx + txi) <= m_XPosition ) {
				m_XPosition -= txi;
			}
		}
		break;
	case VK_NEXT:
		if ( (m_YPosition + tys) < m_maxy ) {
			m_YPosition += tys;
		} else {
			while ( (m_YPosition + tyi) < m_maxy ) {
				m_YPosition += tyi;
			}
		}				
		break;
	case VK_PRIOR:
		if ( (m_miny + tys) <= m_YPosition ) {
			m_YPosition -= tys;
		} else {
			while ( (m_miny + tyi) <= m_YPosition ) {
				m_YPosition -= tyi;
			}
		}				
		break;
	case VK_RETURN:
		if ( !m_ShiftOn ) {
			// Simulate Mouse double click calls.
			if ( m_ControlOn ) {
				RightDown( m_XPosition, m_YPosition, pView );
//				RightUp( m_XPosition, m_YPosition, pView );
//				Select( m_XPosition, m_YPosition, pView );
//				RightUp( m_XPosition, m_YPosition, pView );
			} else {
				LeftDown( m_XPosition, m_YPosition, pView );
				LeftUp( m_XPosition, m_YPosition, pView );
//				Select( m_XPosition, m_YPosition, pView );
//				LeftUp( m_XPosition, m_YPosition, pView );
			}
		}
		nomove = 1;
		break;
	case VK_INSERT:
		InsKey( m_XPosition, m_YPosition, pView);
		nomove = 1;
		break;
	case VK_DELETE:
		DelKey( m_XPosition, m_YPosition, pView);
		nomove = 1;
		break;
	default:		// Here we going to test for alpha ...
		if ( isprint ( (tChar = MakeAscii(nChar, nFlags)) ) ) {
			comment = 1;
		}
		if ( tChar == 8 ) {
			if ( (m_minx + txi) < m_XPosition ) {
				m_XPosition -= txi;
			}
		}			
		break;
	}

	// Undo clipping function
	if ( m_Clipping ) {
		m_maxx = smaxx;
		m_maxy = smaxy;
		m_minx = sminx;
		m_miny = sminy;
	}

	// Comment processing	
	if ( comment ) {
		if ( Comment( tChar, m_XPosition, m_YPosition, pView ) ) {
			// Advance caret only if char taken
			if ( (m_XPosition + txi) < m_maxx ) {
				m_XPosition += txi;
			}
		}

//		return;
	}

	// Check if keystroke resulted in movement
	if ( !nomove ) {

		// For find again ..	
		CGenethonDoc* pDoc = ((CGenethonView*)pView)->GetDocument();
		ASSERT_VALID(pDoc);

		// If selecting, then call move virtual function
		if ( m_ShiftOn ) {
			Move ( m_XPosition, m_YPosition, pView );
		}
		
		// Check for screen scroll bars positions
	    // CPoint tPos = m_Position;

	    if ( 
			(m_YPosition - m_ScrollYPosition + m_CaretHeight) >= m_ViewYSize 
			&& m_YPosition >= m_ScrollYPosition 
		) {
	
			if ( (m_YPosition + m_CaretHeight) > m_maxy ) {
	    		m_YPosition -= m_CaretHeight;
		    	m_ScrollYPosition = m_maxy - m_ViewYSize;
	    	} else {
		    	m_ScrollYPosition += m_YPosition - OldYPos;
		    }
		    	
	    	((CGenethonView*)pView)->ScrollToPosition ( m_ScrollXPosition, m_ScrollYPosition );
	    	((CGenethonView*)pView)->GetScrollPosition( &m_ScrollXPosition, &m_ScrollYPosition);

		} else if ( m_YPosition < m_ScrollYPosition  ) {

// Changed because of end at second to last line, then page up till error ..
			if ( OldYPos - m_YPosition > m_ScrollYPosition ) {
		    	m_ScrollYPosition = 0;
	    	} else {
		    	m_ScrollYPosition -= OldYPos - m_YPosition;
		    }
	    	
	    	((CGenethonView*)pView)->ScrollToPosition ( m_ScrollXPosition, m_ScrollYPosition );
	    	((CGenethonView*)pView)->GetScrollPosition( &m_ScrollXPosition, &m_ScrollYPosition);
	    
		} else if ( m_XPosition - m_ScrollXPosition >= m_ViewXSize && m_XPosition >= m_ScrollXPosition ) {
	    	m_ScrollXPosition += m_XPosition - OldXPos;
			if ( m_XPosition + m_xi == m_maxx ) {
				m_ScrollXPosition += m_xi;
			}
	    	
	    	((CGenethonView*)pView)->ScrollToPosition ( m_ScrollXPosition, m_ScrollYPosition );
	    	((CGenethonView*)pView)->GetScrollPosition( &m_ScrollXPosition, &m_ScrollYPosition);
		
		} else if ( m_XPosition < m_ScrollXPosition ) {
			if ( OldXPos - m_XPosition > m_ScrollXPosition ) {
				m_ScrollXPosition = 0;
			} else {
		    	m_ScrollXPosition -= OldXPos - m_XPosition;
			}
	    	
	    	((CGenethonView*)pView)->ScrollToPosition ( m_ScrollXPosition, m_ScrollYPosition );
	    	((CGenethonView*)pView)->GetScrollPosition( &m_ScrollXPosition, &m_ScrollYPosition);
		}

		

		// Check if Scroll Call need to be made.
		// CRect tRect ( m_ScrollPos, m_ViewSize );


		if ( !((m_XPosition >= m_ScrollXPosition && m_XPosition < (m_ScrollXPosition + m_ViewXSize)) 
			&&
			(m_YPosition >= m_ScrollYPosition && m_YPosition < (m_ScrollYPosition + m_ViewYSize)))
		) {

			// CPoint tPos = m_ScrollPos;
			UINT tXPos = m_ScrollXPosition;
			DWORD tYPos = m_ScrollYPosition;
			UINT tX = 0;
			if ( m_maxx > m_ViewXSize ) tX = m_maxx - m_ViewXSize;
			DWORD tY = 0;
			if ( m_maxy > m_ViewYSize ) tY = m_maxy - m_ViewYSize;
			tYPos = m_YPosition < tY ? m_YPosition: tY;
			tXPos = m_XPosition < tX ? m_XPosition: tX;
    		((CGenethonView*)pView)->ScrollToPosition ( tXPos, tYPos );
    		((CGenethonView*)pView)->GetScrollPosition( &m_ScrollXPosition, &m_ScrollYPosition);
		}


		// Set the caret to the current position
		CaretPos ();
	}

{
	POSITION tPos = ((CGenethonView*)pView)->m_RowViewList.GetHeadPosition();
	CGPRowView *tGP;

	while ( tPos != NULL ) {
		tGP = (CGPRowView *)((CGenethonView*)pView)->m_RowViewList.GetNext(tPos);
		if ( tGP->IsPointWithin( m_XPosition, m_YPosition ) ) {
			tGP->SetStatusBar(nFlags, m_XPosition, m_YPosition );
			break;
		}
	}
}
}
