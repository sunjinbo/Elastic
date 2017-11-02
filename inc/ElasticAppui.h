/* ====================================================================
 * File: ElasticAppUi.h
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ELASTICAPPUI_H
#define C_ELASTICAPPUI_H

// INCLUDE FILES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CElasticAppView;


// CLASS DECLARATION
/**
* CElasticAppUi class
*
* An instance of class CElasticAppUi is
* the UserInterface part of the AVKON
* application framework for the Elastic 
* example application.
*
* @since S60 5.0
*/
class CElasticAppUi : public CAknAppUi
    {
public: // Constructor and Destructor.
    void ConstructL();
    CElasticAppUi();
    ~CElasticAppUi();

public: // from CAknAppUi
    void HandleCommandL(TInt aCommand);
    void HandleResourceChangeL( TInt aType );

private: // Data
    CElasticAppView* iAppView;

    };

#endif // C_ELASTICAPPUI_H

// End of File
