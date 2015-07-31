//
//  ShellService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "ShellService.h"
using namespace std;

ShellService::ShellService(StringRecord* name, unsigned int port, unsigned int version): Service(name, port, version) {
    shell = new Shell();
}

Shell* ShellService::getShell() {
    return shell;
}

ShellService::~ShellService() {
    delete shell;
}