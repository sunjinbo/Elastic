/* ====================================================================
 * File: ElasticDocument.cpp
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#include "ElasticAppUi.h"
#include "ElasticDocument.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CElasticAppUi::ConstructL
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CElasticDocument* CElasticDocument::NewL(CEikApplication& aApp)
    {
    CElasticDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::NewLC
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CElasticDocument* CElasticDocument::NewLC(CEikApplication& aApp)
    {
    CElasticDocument* self = new (ELeave) CElasticDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::ConstructL
// ----------------------------------------------------------------------------
//
void CElasticDocument::ConstructL()
    {
    // no implementation required
    }    

// ----------------------------------------------------------------------------
// CElasticAppUi::CElasticDocument
// ----------------------------------------------------------------------------
//
CElasticDocument::CElasticDocument(CEikApplication& aApp)
     : CAknDocument(aApp) 
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::~CElasticDocument
// ----------------------------------------------------------------------------
//
CElasticDocument::~CElasticDocument()
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::CreateAppUiL
// ----------------------------------------------------------------------------
//
CEikAppUi* CElasticDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CElasticAppUi;
    return appUi;
    }

// End of File

