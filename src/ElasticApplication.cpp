/* ====================================================================
 * File: ElasticApplication.cpp
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#include "ElasticDocument.h"
#include "ElasticApplication.h"

// CONSTANTS
// UID for the application,
// this should correspond to the uid defined in the mmp file
static const TUid KUidElasticApp = {0xAFF05672};

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CElasticAppUi::CElasticApplication
// ----------------------------------------------------------------------------
//
CApaDocument* CElasticApplication::CreateDocumentL()
    {  
    // Create an Elastic document, and return a pointer to it
    CApaDocument* document = CElasticDocument::NewL(*this);
    return document;
    }

// ----------------------------------------------------------------------------
// CElasticAppUi::AppDllUid
// ----------------------------------------------------------------------------
//
TUid CElasticApplication::AppDllUid() const
    {
    // Return the UID for the Elastic application
    return KUidElasticApp;
    }

// End of File
