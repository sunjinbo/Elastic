/* ====================================================================
 * File: ElasticDocument.h
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ELASTICDOCUMENT_H
#define C_ELASTICDOCUMENT_H

// INCLUDE FILES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CElasticAppUi;
class CEikApplication;

// CLASS DECLARATION
/**
* CElasticDocument class
*
* An instance of class CElasticDocument is 
* the Document part of the AVKON
* application framework for the Elastic example application.
* 
* @since S60 5.0
*/
class CElasticDocument : public CAknDocument
    {
public:  // Destructor and Two-phase constructor
    static CElasticDocument* NewL(CEikApplication& aApp);
    static CElasticDocument* NewLC(CEikApplication& aApp);

    ~CElasticDocument();

public: // from CAknDocument
    CEikAppUi* CreateAppUiL();

private: // Constructor
    void ConstructL();
    CElasticDocument(CEikApplication& aApp);

    };


#endif // C_ELASTICDOCUMENT_H

// End of File
