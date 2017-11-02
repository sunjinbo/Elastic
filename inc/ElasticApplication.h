/* ====================================================================
 * File: ElasticApplication.h
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ELASTIC_APPLICATION_H
#define C_ELASTIC_APPLICATION_H

// INCLUDE FILE
#include <aknapp.h>

// CLASS DECLARATION
/**
* CElasticApplication class
*
* An instance of CElasticApplication is 
* the application part of the AVKON
* application framework for the Elastic example application
*
* @since S60 5.0
*/
class CElasticApplication : public CAknApplication
    {

public:  // from CAknApplication
    TUid AppDllUid() const;

protected: // from CAknApplication
    CApaDocument* CreateDocumentL();

    };

#endif // C_ELASTIC_APPLICATION_H

// End of File
