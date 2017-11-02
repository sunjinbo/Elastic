/* ====================================================================
 * File: Node.cpp
 * Created: 06/22/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include "Node.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CNode::NewL
// ----------------------------------------------------------------------------
//
CNode* CNode::NewL( const TDesC& aLabel )
    {
    CNode* self = new (ELeave) CNode;
    CleanupStack::PushL(self);
    self->ConstructL( aLabel );
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CNode::~CNode
// ----------------------------------------------------------------------------
//
CNode::~CNode()
    {
    delete iLabel;
    }

// ----------------------------------------------------------------------------
// CNode::Adjust
// ----------------------------------------------------------------------------
//
void CNode::Adjust( const RPointerArray<CNode>& aNodes )
    {
    TReal dx( 0 ), dy( 0 );
    for ( TInt i = 0; i < aNodes.Count(); ++i )
        {
        if ( aNodes[ i ] != this )
            {
            TReal vx = iPos.iX - aNodes[ i ]->Position().iX;
            TReal vy = iPos.iY - aNodes[ i ]->Position().iY;
            TReal len = vx * vx + vy * vy;
            if ( len == 0 )
                {
                dx += 1;
                dy += 1;
                }
            else if ( len < 100*100 )
                {
                dx += vx / len;
                dy += vy / len;  
                }
            }
        }
 
    TReal dLen = dx * dx + dy * dy;
    if ( dLen > 0 )
        {
        Math::Sqrt( dLen, dLen );
        dLen /= 2;
        iX += dx / dLen;
        iY += dy / dLen;
        }
    }

// ----------------------------------------------------------------------------
// CNode::Adjust
// ----------------------------------------------------------------------------
//
void CNode::Adjust( TInt aWidth, TInt aHeight )
    {
    if ( ! iFixed )
        {
        iPos.iX += Max( -5, Min( 5, iX ) );
        iPos.iY += Max( -5, Min( 5, iY ) );
        }

    if ( iPos.iX < 0) 
        {
        iPos.iX = 0;
        } 
    else if ( iPos.iX > aWidth ) 
        {
        iPos.iX = aWidth;
        }

    if ( iPos.iY < 0) 
        {
        iPos.iY = 0;
        } 
    else if ( iPos.iY > aHeight ) 
        {
        iPos.iY = aHeight;
        }

    iX /= 2;
    iY /= 2;
    }

// ----------------------------------------------------------------------------
// CNode::SetPosition
// ----------------------------------------------------------------------------
//
void CNode::SetPosition( const TPoint& aPos )
    {
    iPos = aPos;
    }

// ----------------------------------------------------------------------------
// CNode::SetX
// ----------------------------------------------------------------------------
//
void CNode::SetX( TInt aX )
    {
    iX = aX;
    }

// ----------------------------------------------------------------------------
// CNode::SetY
// ----------------------------------------------------------------------------
//
void CNode::SetY( TInt aY )
    {
    iY = aY;
    }

// ----------------------------------------------------------------------------
// CNode::Position
// ----------------------------------------------------------------------------
//
TPoint CNode::Position() const
    {
    return iPos;
    }

// ----------------------------------------------------------------------------
// CNode::X
// ----------------------------------------------------------------------------
//
TInt CNode::X() const
    {
    return iX;
    }

// ----------------------------------------------------------------------------
// CNode::Y
// ----------------------------------------------------------------------------
//
TInt CNode::Y() const
    {
    return iY;
    }

// ----------------------------------------------------------------------------
// CNode::Label
// ----------------------------------------------------------------------------
//
TDesC& CNode::Label() const
    {
    return *iLabel;
    }

// ----------------------------------------------------------------------------
// CNode::Fixed
// ----------------------------------------------------------------------------
//
TBool CNode::Fixed() const
    {
    return iFixed;
    }

// ----------------------------------------------------------------------------
// CNode::SetFixed
// ----------------------------------------------------------------------------
//
void CNode::SetFixed( TBool aFixed )
    {
    iFixed = aFixed;
    }

// ----------------------------------------------------------------------------
// CNode::ConstructL
// ----------------------------------------------------------------------------
//
void CNode::ConstructL( const TDesC& aLabel )
    {
    iLabel = HBufC::NewL( aLabel.Length() );
    TPtr label( iLabel->Des() );
    label.Copy( aLabel );
    }

// ----------------------------------------------------------------------------
// CNode::CNode
// ----------------------------------------------------------------------------
//
CNode::CNode()
    { // no implementation required.
    }

// End of File
