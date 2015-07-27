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
    cout << "Services detected on " << host->getIP()->toString() << ":" << endl;
    for(pair<unsigned int, Service*> p: host->getServices()) {
        cout << p.first << ": " << p.second->printBanner() << endl;
    }
}

string ScannerProgram::help() {
    return "Scan for active services on a remote host.";
}