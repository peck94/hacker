//
//  Robber.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Robber__
#define __Hackers__Robber__

#include "Exploit.h"
#include "FinanceService.h"

/*
 * This exploit steals money from financial services.
 */
class Robber: public Exploit {
public:
    Robber(unsigned int level);
    
    virtual void run(Host *local, Host *remote, unsigned int port);
};

#endif /* defined(__Hackers__Robber__) */
