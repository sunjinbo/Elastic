/* ====================================================================
 * File: Scene.cpp
 * Created: 06/25/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include "Scene.h"
#include "Node.h"
#include "Edge.h"

// CONSTANTS
const TInt KDelayTimeout = 0;
const TInt KFrameUpdateTimeout = 50000;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScene::NewL
// ----------------------------------------------------------------------------
//
CScene* CScene::NewL( MSceneObserver& aObserver )
    {
    CScene* self = new (ELeave) CScene( aObserver );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CScene::~CScene
// ----------------------------------------------------------------------------
//
CScene::~CScene()
    {
    Stop(); // iPeriodic
    iNodes.ResetAndDestroy();
    iEdges.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CScene::StartL
// ----------------------------------------------------------------------------
//
void CScene::StartL()
    {
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
                KDelayTimeout,
                KFrameUpdateTimeout,
                TCallBack( TimerCallback, this ) ); 
    }

// ----------------------------------------------------------------------------
// CScene::Adjust
// ----------------------------------------------------------------------------
//
void CScene::Adjust()
    {
    TInt index( 0 ), count( 0 );
    // Step 1
    count = iEdges.Count();
    for ( index = 0; index < count; ++index )
        {
        iEdges[ index ]->Adjust();
        }

    // Step 2
    count = iNodes.Count();
    for ( index = 0; index < count; ++index )
        {
        iNodes[ index ]->Adjust( iNodes );
        }

    // Step 3
    count = iNodes.Count();
    for ( index = 0; index < count; ++index )
        {
        iNodes[ index ]->Adjust( iSize.iWidth, iSize.iHeight );
        }
    // Step 4
    iObserver.StateChanged();
    }

// ----------------------------------------------------------------------------
// CScene::SetSize
// ----------------------------------------------------------------------------
//
void CScene::SetSize( const TSize& aSize )
    {
    iSize = aSize;
    }

// ----------------------------------------------------------------------------
// CScene::AddNodeL
// ----------------------------------------------------------------------------
//
void CScene::AddNodeL(  const TDesC& aLabel  )
    {
    if ( ! FindNode( aLabel ) )
        {
        TTime time;
        time.UniversalTime();
        TInt64 seed( time.Int64() );
        TInt x( Math::Rand( seed ) % iSize.iWidth );
        TInt y( Math::Rand( seed ) % iSize.iHeight );
        User::After( 1000 );
        CNode* node = CNode::NewL( aLabel );
        node->SetPosition( TPoint( x, y ) );
        iNodes.Append( node );
        }
    }

// ----------------------------------------------------------------------------
// CScene::AddEdge
// ----------------------------------------------------------------------------
//
void CScene::AddEdgeL( const TDesC& aFrom, const TDesC& aTo, TInt aLen )
    {
    CNode* from = FindNode( aFrom );
    CNode* to = FindNode( aTo );

    if ( from && to )
        {
        iEdges.Append( CEdge::NewL( *from, *to, aLen ) );
        }
    }

// ----------------------------------------------------------------------------
// CScene::SetFixed
// ----------------------------------------------------------------------------
//
void CScene::SetFixed(  const TDesC& aLabel  )
    {
    CNode* node = FindNode( aLabel );
    if ( node )    
        {
        node->SetFixed( ETrue );
        }
    }

// ----------------------------------------------------------------------------
// CScene::PointerPressed
// ----------------------------------------------------------------------------
//
void CScene::PointerPressed( TInt aX, TInt aY )
    {
    TReal bestDist( 100000 );
    for ( TInt i = 0; i < iNodes.Count(); ++i )
        {
        CNode* node = iNodes[ i ];
        TPoint pos( node->Position() );
        TReal dist = ( pos.iX - aX ) * ( pos.iX - aX ) + ( pos.iY - aY ) * ( pos.iY - aY );
        if ( bestDist > dist )
            {
            bestDist = dist;
            iPick = node;
            }
        }
        iPickFixed = iPick->Fixed();
        iPick->SetFixed( ETrue );
        iPick->SetPosition( TPoint( aX, aY ) );
    }

// ----------------------------------------------------------------------------
// CScene::PointerReleased
// ----------------------------------------------------------------------------
//
void CScene::PointerReleased( TInt aX, TInt aY )
    {
    if ( iPick != NULL ) 
        {
        iPick->SetPosition( TPoint( aX, aY ) );
        iPick->SetFixed( iPickFixed );
        iPick = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CScene::PointerDragged
// ----------------------------------------------------------------------------
//
void CScene::PointerDragged( TInt aX, TInt aY )
    {
    iPick->SetPosition( TPoint( aX, aY ) );
    }

// ----------------------------------------------------------------------------
// CScene::PickedNode
// ----------------------------------------------------------------------------
//
CNode* CScene::PickedNode() const
    {
    return iPick;
    }

// ----------------------------------------------------------------------------
// CScene::Shock
// ----------------------------------------------------------------------------
//
void CScene::Shock()
    {
    for ( TInt i = 0; i < iNodes.Count(); ++i )
        {
        TTime time;
        time.UniversalTime();
        TInt64 seed( time.Int64() );
        TInt x( Math::Rand( seed ) % iSize.iWidth );
        TInt y( Math::Rand( seed ) % iSize.iHeight );
        iNodes[ i ]->SetPosition( TPoint( x, y ) );
        User::After( 1000 );
        }
    }

// ----------------------------------------------------------------------------
// CScene::ConstructL
// ----------------------------------------------------------------------------
//
void CScene::ConstructL()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CScene::CScene
// ----------------------------------------------------------------------------
//
CScene::CScene( MSceneObserver& aObserver )
    : iObserver( aObserver )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CScene::FindNode
// ----------------------------------------------------------------------------
//
CNode* CScene::FindNode( const TDesC& aLabel )
    {
    CNode* node( NULL );
    for ( TInt i = 0; i < iNodes.Count(); ++i )
        {
        if ( ! aLabel.Compare( iNodes[ i ]->Label()  ) )
            {
            node = iNodes[ i ];
            break;
            }
        }
    return node;
    }

// ----------------------------------------------------------------------------
// CScene::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CScene::TimerCallback( TAny* aPtr )
    {
    CScene* self = static_cast<CScene*> ( aPtr );
    self->Adjust();
    return 0;
    }

// ----------------------------------------------------------------------------
// CScene::Stop
// ----------------------------------------------------------------------------
//
void CScene::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;
        }
    }

// End of File
