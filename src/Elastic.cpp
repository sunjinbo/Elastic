/* ====================================================================
 * File: Elastic.cpp
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <eikstart.h>
#include "ElasticApplication.h"

// ======== GLOBAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// NewApplication
// Create an application, and return a pointer to it .
// ---------------------------------------------------------------------------
//
CApaApplication* NewApplication()
    {
    return new CElasticApplication;
    }

// ---------------------------------------------------------------------------
// E32Main
// ---------------------------------------------------------------------------
//
TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
