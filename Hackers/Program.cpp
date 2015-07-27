//
//  Program.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Program.h"
using namespace std;

Program::Program(string name, unsigned int version) {
    this->name = name;
    this->version = version;
}

string Program::getName() {
    return name;
}

unsigned int Program::getVersion() {
    return version;
}