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
    std::string name;
    
public:
    Program(std::string name);
    
    virtual void launch(Host *host, std::vector<std::string> args) = 0;
    
    std::string getName();
};

#endif /* defined(__Hackers__Program__) */
