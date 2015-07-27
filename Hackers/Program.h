//
//  Program.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Program__
#define __Hackers__Program__

#include "Host.h"
#include <string>
#include <vector>

class Program {
private:
    // store name (used in shell)
    std::string name;
    // store version
    unsigned int version;
    
public:
    Program(std::string name, unsigned int version);
    
    // launch on host with args
    virtual void launch(Host *host, std::vector<std::string> args) = 0;
    
    // getters
    std::string getName();
    unsigned int getVersion();
    
    // print docs
    virtual std::string help() = 0;
};

#endif /* defined(__Hackers__Program__) */
