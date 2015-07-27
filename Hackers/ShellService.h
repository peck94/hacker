//
//  ShellService.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__ShellService__
#define __Hackers__ShellService__

#include "Service.h"
#include "Shell.h"
#include <string>

/*
 * Represents a service with a shell.
 */
class ShellService: public Service {
private:
    Shell *shell;

public:
    ShellService(std::string name, unsigned int port, unsigned int version);
    
    Shell* getShell();
    
    virtual ~ShellService();
};

#endif /* defined(__Hackers__ShellService__) */
