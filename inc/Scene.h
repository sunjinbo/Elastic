/* ====================================================================
 * File: Scene.h
 * Created: 06/25/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCENE_H
#define C_SCENE_H

// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>
#include "SceneObserver.h"

// FORWARD DECLARATIONS
class CNode;
class CEdge;
class CPeriodic;

// CLASS DECLARATION
/**
* CScene class
*
* @since S60 5.0
*/
class CScene : public CBase
    {
public:  // Destructor and Two-phase constructor
    static CScene* NewL( MSceneObserver& aObserver );
    virtual ~CScene();

public: // New functions
    void StartL();
    void Adjust();
    void SetSize( const TSize& aSize );
    void AddNodeL(  const TDesC& aLabel  );
    void AddEdgeL( const TDesC& aFrom, const TDesC& aTo, TInt aLen );
    void SetFixed(  const TDesC& aLabel  );
    void PointerPressed( TInt aX, TInt aY );
    void PointerReleased( TInt aX, TInt aY );
    void PointerDragged( TInt aX, TInt aY );
    CNode* PickedNode() const;
    void Shock();

private: // Constructor
    void ConstructL();
    CScene( MSceneObserver& aObserver );

private: // New functions
    CNode* FindNode( const TDesC& aLabel );
    static TInt TimerCallback( TAny* aPtr );
    void Stop();

public: // Data
    RPointerArray<CNode> iNodes;
    RPointerArray<CEdge> iEdges;

private: // Data
    MSceneObserver& iObserver;
    CNode* iPick;
    TBool iPickFixed;
    TSize iSize;
    CPeriodic* iPeriodic;
    };

#endif // C_SCENE_H

// End of File
