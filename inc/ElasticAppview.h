/* ====================================================================
 * File: ElasticAppView.h
 * Created: 06/22/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ELASTICAPPVIEW_H
#define C_ELASTICAPPVIEW_H

// INCLUDE FILES
#include <coecntrl.h>
#include "SceneObserver.h"

// FORWARD DECLARATIONS
class CScene;
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CPeriodic;
class CFont;

// CLASS DECLARATION

/**
* CNode class
*
* An instance of the Application View object for the Elastic
*
* @since S60 5.0
*/
class CElasticAppView : public CCoeControl, MSceneObserver
    {
public:
    static CElasticAppView* NewL(const TRect& aRect);
    static CElasticAppView* NewLC(const TRect& aRect);
     ~CElasticAppView();

public: // New functions
    void DrawBmp();
    void SetClientRect( const TRect& aRect );
    void Shock();

public:  // from CCoeControl
    void Draw(const TRect& aRect) const;
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    void SizeChanged();
    void HandleResourceChange( TInt aType );

private:  // from MSceneObserver
    virtual void StateChanged();

private:
    void ConstructL(const TRect& aRect);
    CElasticAppView();

private: // New functions
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();
    static TInt TimerCallback( TAny* aPtr );
    void Stop();
    void DoFrame();

private: // Data
    CScene* iScene;
    CFbsBitmap* iBitmap;
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitGc* iBitmapGc;
    CPeriodic* iPeriodic;
    TRect iClientRect;
    CFont* iFont;
    };

#endif // C_ELASTICAPPVIEW_H

// End of File
