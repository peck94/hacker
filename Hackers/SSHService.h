//
//  SSHService.h
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__SSHService__
#define __Hackers__SSHService__

#include "Shell.h"
#include "ShellService.h"
#include "Host.h"
#include "Program.h"
#include <iostream>
#include <vector>
#include <set>

/*
 * The SSH service allows the user to connect through this system onto another one.
 * Basically, it bounces your link.
 */
class SSHService: public ShellService {
private:
    // store current host
    Host* localhost;
    // store executable programs
    std::set<Program*> programs;

public:
    SSHService(unsigned int version);
    
    virtual void run(Host* host);
    virtual void randomInit();
    
    void addProgram(Program *program);
    
    ~SSHService();
};

#endif /* defined(__Hackers__SSHService__) */
