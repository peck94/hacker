//
//  FingerService.h
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__FingerService__
#define __Hackers__FingerService__

#include "ShellService.h"

/*
 * The finger service allows a remote host to probe user accounts.
 */
class FingerService: public ShellService {
private:
    Host *localhost;
    
public:
    FingerService(unsigned int version);
    
    virtual void run(Host *host);
    virtual void randomInit(ResourceGenerator *gen);
    virtual void getHacked(Person *person);
};

#endif /* defined(__Hackers__FingerService__) */
