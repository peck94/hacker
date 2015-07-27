//
//  TransDeleter.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__TransDeleter__
#define __Hackers__TransDeleter__

#include "Exploit.h"
#include "FinanceService.h"

/*
 * This exploit clears the transaction logs of a vulnerable remote financial system.
 */
class TransDeleter: public Exploit {
public:
    TransDeleter(unsigned int level);
    
    virtual void run(Host *local, Host *remote, unsigned int port);
    
    virtual std::string help();
};

#endif /* defined(__Hackers__TransDeleter__) */
