/* ====================================================================
 * File: ElasticAppView.cpp
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <coemain.h>
#include <fbs.h>
#include <bitdev.h>
#include <bitstd.h>
#include <w32std.h>
#include <akndef.h>
#include <Elastic.rsg>
#include <eikenv.h>

#include "ElasticAppView.h"
#include "Scene.h"
#include "Node.h"
#include "Edge.h"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 50000;

_LIT( KNodeOne, "One" );
_LIT( KNodeTwo, "Two" );
_LIT( KNodeThree, "Three" );
_LIT( KNodeFour, "Four" );
_LIT( KNodeFive, "Five" );
_LIT( KNodeSix, "Six" );
_LIT( KNodeSeven, "Seven" );
_LIT( KNodeEight, "Eight" );
_LIT( KNodeNine, "Nine" );
_LIT( KNodeTen, "Ten" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CElasticAppView::NewL
// Standard construction sequence
// ----------------------------------------------------------------------------
//
CElasticAppView* CElasticAppView::NewL(const TRect& aRect)
    {
    CElasticAppView* self = CElasticAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CElasticAppView::NewLC
// Standard construction sequence
// ----------------------------------------------------------------------------
//
CElasticAppView* CElasticAppView::NewLC(const TRect& aRect)
    {
    CElasticAppView* self = new (ELeave) CElasticAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

// ----------------------------------------------------------------------------
// CElasticAppView::CElasticAppView
// ----------------------------------------------------------------------------
//
CElasticAppView::~CElasticAppView()
    {
    Stop();
    ReleaseBmpBuffer();
    delete iScene;
    }

// ----------------------------------------------------------------------------
// CElasticAppView::DrawBmp
// ----------------------------------------------------------------------------
//
void CElasticAppView::DrawBmp()
    {
    iBitmapGc->SetBrushColor( KRgbGray );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->Clear( Rect() );

    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );

    // Draw Edges
    for ( TInt i = 0; i < iScene->iEdges.Count(); ++i )
        {
        CEdge* edge( iScene->iEdges[ i ] );
        TPoint from ( edge->From()->Position() );
        TPoint to ( edge->To()->Position() );
        iBitmapGc->DrawLine( from, to );
        }
    
    // Draw Nodes
    iBitmapGc->UseFont( iFont );
    TInt fontHeight = iFont->HeightInPixels();   
    iBitmapGc->SetBrushColor( KRgbBlack );
    iBitmapGc->SetPenColor( KRgbYellow );
    CGraphicsContext::TTextAlign align( CGraphicsContext::ECenter );
    for ( TInt i = 0; i < iScene->iNodes.Count(); ++i )
        {
        if ( iScene->iNodes[ i ] == iScene->PickedNode() )
            {
            iBitmapGc->SetPenColor( KRgbMagenta );
            }
        
        if ( iScene->iNodes[ i ]->Fixed() && iScene->iNodes[ i ] != iScene->PickedNode() )
            {
            iBitmapGc->SetBrushColor( KRgbDarkCyan );
            }
        
        TPoint pos( iScene->iNodes[ i ]->Position() );
        TInt len = iScene->iNodes[ i ]->Label().Length();
        TSize size( len * iFont->MaxCharWidthInPixels() / 2, iFont->HeightInPixels() );
        pos.iX -= ( size.iWidth / 2 );
        pos.iY -= ( size.iHeight / 2 );
        TRect rect( pos, size );
        iBitmapGc->DrawRect( rect );
        iBitmapGc->DrawText( iScene->iNodes[ i ]->Label(), rect, size.iHeight, align);
        if ( iScene->iNodes[ i ] == iScene->PickedNode() )
            {
            iBitmapGc->SetPenColor( KRgbYellow );
            }
        if ( iScene->iNodes[ i ]->Fixed() )
            {
            iBitmapGc->SetBrushColor( KRgbBlack );
            }
        }
        
    iBitmapGc->DiscardFont();
    }

// ----------------------------------------------------------------------------
// CElasticAppView::SetClientRect
// ----------------------------------------------------------------------------
//
void CElasticAppView::SetClientRect( const TRect& aRect )
    {
    iClientRect = aRect;
    }

// ----------------------------------------------------------------------------
// CElasticAppView::Shock
// ----------------------------------------------------------------------------
//
void CElasticAppView::Shock()
    {
    if ( iScene )
        {
        iScene->Shock();
        }
    }

// ----------------------------------------------------------------------------
// CElasticAppView::StateChanged
// ----------------------------------------------------------------------------
//
void CElasticAppView::StateChanged()
    {
    DrawBmp();
    }

// ----------------------------------------------------------------------------
// CElasticAppView::ConstructL
// ----------------------------------------------------------------------------
//
void CElasticAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);
    CreateBmpBufferL();

    TFontSpec fontSpec = iEikonEnv->AnnotationFont()->FontSpecInTwips();
    fontSpec.iHeight  -= fontSpec.iHeight / 4;
    fontSpec.iFontStyle.SetBitmapType( ESubPixelGlyphBitmap );
    iEikonEnv->ScreenDevice()->GetNearestFontInTwips( iFont, fontSpec );

    iScene = CScene::NewL( *this );
    iScene->SetSize( aRect.Size() );

    /* For internal testing */
    iScene->AddNodeL( KNodeOne );
    iScene->AddNodeL( KNodeTwo);
    iScene->AddNodeL( KNodeThree );
    iScene->AddNodeL( KNodeFour );
    iScene->AddNodeL( KNodeFive );
    iScene->AddNodeL( KNodeSix );
    iScene->AddNodeL( KNodeSeven );
    iScene->AddNodeL( KNodeEight );
    iScene->AddNodeL( KNodeNine );
    iScene->AddNodeL( KNodeTen );
    iScene->SetFixed( KNodeTwo );
    
    iScene->AddEdgeL( KNodeOne, KNodeTwo, 70 );
    iScene->AddEdgeL( KNodeOne, KNodeThree, 85 );
    iScene->AddEdgeL( KNodeTwo, KNodeThree, 55 );
     iScene->AddEdgeL( KNodeThree, KNodeFour, 75 );
    iScene->AddEdgeL( KNodeFour, KNodeFive, 155 );
    iScene->AddEdgeL( KNodeFive, KNodeSix, 200 );
    iScene->AddEdgeL( KNodeSix, KNodeSeven, 187 );
    iScene->AddEdgeL( KNodeSeven, KNodeEight, 32 );
    iScene->AddEdgeL( KNodeEight, KNodeNine, 65 );
    iScene->AddEdgeL( KNodeNine, KNodeTen, 42 );
    iScene->AddEdgeL( KNodeTen, KNodeThree, 125 );
    iScene->AddEdgeL( KNodeSix, KNodeOne, 165 );
    iScene->AddEdgeL( KNodeSeven, KNodeFour, 23 );
    iScene->AddEdgeL( KNodeOne, KNodeFive, 43 );
    iScene->StartL();
    
    
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
                    KDoDelayTimeout,
                    KDoFrameUpdateTimeout,
                    TCallBack( TimerCallback, this ) );

    // Enable Drag Events.
    EnableDragEvents();
 
    // OR can also be done with
    Window().PointerFilter( EPointerFilterDrag, 0 );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CElasticAppView::CElasticAppView
// ----------------------------------------------------------------------------
//
CElasticAppView::CElasticAppView()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CElasticAppView::DrawBmp
// Draw this application's view to the screen
// ----------------------------------------------------------------------------
//
void CElasticAppView::Draw(const TRect& /*aRect*/) const
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CElasticAppView::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CElasticAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    TInt x = aPointerEvent.iPosition.iX;
    TInt y = aPointerEvent.iPosition.iY;
    switch ( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            iScene->PointerPressed( x, y );
            break;
            }
        case TPointerEvent::EButton1Up:
            {
            iScene->PointerReleased( x, y );
            break;
            }
        case TPointerEvent::EDrag:
            {
            iScene->PointerDragged( x, y );
            break;
            }
        default:
            {
            // do something
            break;
            }
        }
    }

// ----------------------------------------------------------------------------
// CElasticAppView::SizeChanged
// ----------------------------------------------------------------------------
//
void CElasticAppView::SizeChanged()
    {
    if ( iScene )
        {
        TRAPD( err, CreateBmpBufferL() );
        if ( err == KErrNone )
            {
            iScene->Shock();
            }
        }
    }

// ----------------------------------------------------------------------------
// CElasticAppView::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CElasticAppView::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetRect( iClientRect );
        iScene->SetSize( iClientRect.Size() );
        }
    }

// ----------------------------------------------------------------------------
// CElasticAppView::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CElasticAppView::CreateBmpBufferL()
    {
    ReleaseBmpBuffer();

    // Create double buffer bitmap
    iBitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iBitmap->Create( Size(), EColor16MU ) );

    // Create double buffer graphics context
    iBitmapDevice = CFbsBitmapDevice::NewL( iBitmap );
    User::LeaveIfError( iBitmapDevice->CreateContext( iBitmapGc ) );

    }

// ----------------------------------------------------------------------------
// CElasticAppView::ReleaseBmpBuffer
// ----------------------------------------------------------------------------
//
void CElasticAppView::ReleaseBmpBuffer()
    {
    if ( iBitmapGc )
        {
        delete iBitmapGc;
        iBitmapGc = NULL;
        }
    if ( iBitmapDevice )
        {
        delete iBitmapDevice;
        iBitmapDevice = NULL;
        }
    if ( iBitmap )
        {
        delete iBitmap;
        iBitmap = NULL;
        }
    }
    
// ----------------------------------------------------------------------------
// CElasticAppView::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CElasticAppView::TimerCallback( TAny* aPtr )
    {
    CElasticAppView* self = static_cast<CElasticAppView*> ( aPtr );
    self->DoFrame();
    return 0;
    }

// ----------------------------------------------------------------------------
// CElasticAppView::Stop
// ----------------------------------------------------------------------------
//
void CElasticAppView::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CElasticAppView::DoFrame
// ----------------------------------------------------------------------------
//
void CElasticAppView::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    CWindowGc& gc = SystemGc();
    gc.BitBlt( TPoint( 0, 0 ), iBitmap );
    Window().EndRedraw();
    DeactivateGc();
    }

// End of File
