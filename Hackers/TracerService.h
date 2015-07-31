//
//  TracerService.h
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__TracerService__
#define __Hackers__TracerService__

#include "Service.h"
#include "Cache.h"
#include "Person.h"
#include "ResourceGenerator.h"
#include "Host.h"

/*
 * The tracer service allows an AI to trace people that left logs on its systems.
 */
class TracerService: public Service {
private:
    bool active = true;

public:
    TracerService(unsigned int version);

    // run the service
    virtual void run(Host* host);
    
    // init the service with random data
    virtual void randomInit(ResourceGenerator *gen);
    
    // get hacked
    virtual void getHacked(Person *person);
};

#endif /* defined(__Hackers__TracerService__) */
