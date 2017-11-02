/* ====================================================================
 * File: ElasticAppUi.cpp
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknnotewrappers.h> 

#include "Elastic.pan"
#include "ElasticAppUi.h"
#include "ElasticAppView.h"
#include "Elastic.hrh"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CElasticAppUi::ConstructL
// ConstructL is called by the application framework
// ----------------------------------------------------------------------------
//
void CElasticAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CElasticAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::CElasticAppUi
// ----------------------------------------------------------------------------
//
CElasticAppUi::CElasticAppUi()                              
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::~CElasticAppUi
// ----------------------------------------------------------------------------
//
CElasticAppUi::~CElasticAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::HandleCommandL
// Handle any menu commands
// ----------------------------------------------------------------------------
//
void CElasticAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case EElasticShock:
            {
            iAppView->Shock();
            }
            break;
            
        case EElasticAbout:
            {
            _LIT(message,"(c) 2009 Tieto\nAll rights reseved.");
            CAknInformationNote* informationNote = new (ELeave) CAknInformationNote;
            informationNote->ExecuteLD(message);
            }
            break;

        default:
            Panic(EElasticBasicUi);
            break;
        }
    }

// ---------------------------------------------------------------------------
// CElasticAppUi::HandleResourceChangeL
// ---------------------------------------------------------------------------
//
void CElasticAppUi::HandleResourceChangeL( TInt aType )
    {
    CAknAppUi::HandleResourceChangeL( aType );
    iAppView->SetClientRect( ClientRect() );
    }

// End of File
