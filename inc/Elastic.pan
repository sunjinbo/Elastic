/* ====================================================================
 * File: Elastic.pan
 * Created: 06/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __ELASTIC_PAN__
#define __ELASTIC_PAN__

/** Elastic application panic codes */
enum TElasticPanics 
    {
    EElasticBasicUi = 1
    // add further panics here
    };

inline void Panic(TElasticPanics aReason)
    {
    _LIT(applicationName,"Elastic");
    User::Panic(applicationName, aReason);
    }

#endif // __ELASTIC_PAN__
