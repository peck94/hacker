//
//  Cracker.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Cracker__
#define __Hackers__Cracker__

#include "Exploit.h"
#include "ShellService.h"
#include <iterator>

class Cracker: public Exploit {
public:
    Cracker(unsigned int level);
    
    virtual void run(Host *local, Host *remote, unsigned int port);
};

#endif /* defined(__Hackers__Cracker__) */
