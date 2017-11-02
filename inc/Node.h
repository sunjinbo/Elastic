/* ====================================================================
 * File: Node.h
 * Created: 06/22/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_NODE_H
#define C_NODE_H

// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CNode class
*
* @since S60 5.0
*/
class CNode : public CBase
    {
public: // Destructor and Two-phase constructor
    static CNode* NewL( const TDesC& aLabel );
    virtual ~CNode();

public: // New functions
    void Adjust( const RPointerArray<CNode>& aNodes );
    void Adjust( TInt aWidth, TInt aHeight );
    void SetPosition( const TPoint& aPos );
    void SetX( TInt aX );
    void SetY( TInt aY );
    TPoint Position() const;
    TInt X() const;
    TInt Y() const;
    TDesC& Label() const;
    TBool Fixed() const;
    void SetFixed( TBool aFixed );

private: // Constructor
    void ConstructL( const TDesC& aLabel );
    CNode();

private: // Data
    TPoint iPos;
    TReal iX, iY;
    TBool iFixed;
    HBufC* iLabel;
    };

#endif // C_NODE_H

// End of File
