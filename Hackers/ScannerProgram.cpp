//
//  ScannerProgram.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "ScannerProgram.h"
using namespace std;

ScannerProgram::ScannerProgram(): Program("nmap", 3) {}

void ScannerProgram::launch(Host *host, vector<string> args) {
    
}

string ScannerProgram::help() {
    return "Scan for active services on a remote host.";
}