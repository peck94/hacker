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
    
public:
    Program(std::string name);
    
    // launch on host with args
    virtual void launch(Host *host, std::vector<std::string> args) = 0;
    
    // return name
    std::string getName();
    
    // print help
    virtual std::string help() = 0;
};

#endif /* defined(__Hackers__Program__) */
