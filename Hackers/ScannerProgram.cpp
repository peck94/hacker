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
    if(args.size() < 2) {
        cout << "Please specify a remote host." << endl;
        return;
    }
    
    string ip = args[1];
    if(!host->ping(ip)) {
        cout << "Destination host unreachable." << endl;
        return;
    }
    
    Host *remote = host->resolve(ip);
    cout << "Services detected on " << remote->getIP()->toString() << ":" << endl;
    for(pair<unsigned int, Service*> p: remote->getServices()) {
        cout << p.first << ": " << p.second->printBanner() << endl;
    }
}

string ScannerProgram::help() {
    return "Scan for active services on a remote host.";
}