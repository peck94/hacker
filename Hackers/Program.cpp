//
//  Program.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Program.h"
using namespace std;

Program::Program(string name) {
    this->name = name;
}

string Program::getName() {
    return name;
}