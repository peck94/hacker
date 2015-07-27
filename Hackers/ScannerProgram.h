//
//  ScannerProgram.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__ScannerProgram__
#define __Hackers__ScannerProgram__

#include "Program.h"
#include <string>

class ScannerProgram: public Program {
public:
    ScannerProgram();
    
    virtual void launch(Host *host, std::vector<std::string> args);
    virtual std::string help();
};

#endif /* defined(__Hackers__ScannerProgram__) */
