/* ====================================================================
 * File: Edge.h
 * Created: 06/22/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_EDGE_H
#define C_EDGE_H

// INCLUDE FILES
#include "e32std.h"
#include "e32base.h"

// FORWARD DECLARATIONS
class CNode;

// CLASS DECLARATION
/**
* CEdge class
*
* @since S60 5.0
*/
class CEdge : public CBase
    {
public:  // Destructor and Two-phase constructor
    static CEdge* NewL( CNode& aFrom, CNode& aTo, TInt aLen );
    virtual ~CEdge();

public: // New functions
    void Adjust();
    void SetLen( TInt aLen );
    TInt Len() const;
    CNode* From() const;
    CNode* To() const;

private: // Constructor
    void ConstructL();
    CEdge( CNode& aFrom, CNode& aTo, TInt aLen );

private: // Data
    CNode& iFrom;
    CNode& iTo;
    TInt iLen;

    };

#endif // C_EDGE_H

// End of File
