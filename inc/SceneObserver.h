/* ====================================================================
 * File: SceneObserver.h
 * Created: 06/25/09
 * Modified: 06/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_SCENEOBSERVER_H
#define M_SCENEOBSERVER_H

// INCLUDE FILES

// CLASS DECLARATION
/**
* MSceneObserver class
*
* @since S60 5.0
*/
class MSceneObserver
    {
public:
    virtual void StateChanged() = 0;
    };

#endif // M_SCENEOBSERVER_H

// End of File
