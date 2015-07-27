//
//  LogDeleter.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__LogDeleter__
#define __Hackers__LogDeleter__

#include "Exploit.h"
#include "ShellService.h"

/*
 * This exploit clears the logs of a vulnerable remote system.
 */
class LogDeleter: public Exploit {
public:
    LogDeleter(unsigned int level);
    
    virtual void run(Host *local, Host *remote, unsigned int port);
};

#endif /* defined(__Hackers__LogDeleter__) */
