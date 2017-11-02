/* ====================================================================
 * File: Edge.cpp
 * Created: 06/22/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include "Edge.h"
#include "Node.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CEdge::NewL
// ----------------------------------------------------------------------------
//
CEdge* CEdge::NewL( CNode& aFrom, CNode& aTo, TInt aLen  )
    {
    CEdge* self = new (ELeave) CEdge( aFrom, aTo, aLen );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CEdge::~CEdge
// ----------------------------------------------------------------------------
//
CEdge::~CEdge()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CEdge::Adjust
// ----------------------------------------------------------------------------
//
void CEdge::Adjust()
    {
    TReal vx = iTo.Position().iX - iFrom.Position().iX;
    TReal vy = iTo.Position().iY - iFrom.Position().iY;
    TReal len( 0.0 );
    Math::Sqrt( len, vx * vx + vy * vy );
    len = (len == 0) ? 0.0001 : len;
    TReal f = ( iLen - len ) / ( len * 3 );
    TReal dx = vx * f;
    TReal dy = vy * f;
    iTo.SetX( iTo.X() + dx );
    iTo.SetY( iTo.Y() + dy );
    iFrom.SetX( iFrom.X() - dx );
    iFrom.SetY( iFrom.Y() - dy );
    }

// ----------------------------------------------------------------------------
// CEdge::SetLen
// ----------------------------------------------------------------------------
//
void CEdge::SetLen( TInt aLen )
    {
    iLen = aLen;
    }

// ----------------------------------------------------------------------------
// CEdge::Len
// ----------------------------------------------------------------------------
//
TInt CEdge::Len() const
    {
    return iLen;
    }

// ----------------------------------------------------------------------------
// CEdge::From
// ----------------------------------------------------------------------------
//
CNode* CEdge::From() const
    {
    return &iFrom;
    }

// ----------------------------------------------------------------------------
// CEdge::To
// ----------------------------------------------------------------------------
//
CNode* CEdge::To() const
    {
    return &iTo;
    }

// ----------------------------------------------------------------------------
// CEdge::ConstructL
// ----------------------------------------------------------------------------
//
void CEdge::ConstructL()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CEdge::CEdge
// ----------------------------------------------------------------------------
//
CEdge::CEdge( CNode& aFrom, CNode& aTo, TInt aLen  )
    : iFrom( aFrom ), iTo( aTo ), iLen( aLen )
    { // no implementation required.
    }

// End of File
