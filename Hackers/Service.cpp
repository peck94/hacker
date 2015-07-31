//
//  Service.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Service.h"
using namespace std;

Service::Service(StringRecord* name, unsigned int port, unsigned int version) {
    this->name = name;
    this->port = port;
    this->version = version;
    
    // every service has at least these vulns
    addVuln(CRACK);
    addVuln(LOG_DELETER);
}

StringRecord* Service::getName() {
    return name;
}

string Service::printBanner() {
    return getName()->get() + " version " + to_string(getVersion());
}

unsigned int Service::getPort() {
    return port;
}

unsigned int Service::getVersion() {
    return version;
}

void Service::addVuln(Vulnerability vuln) {
    vulns.insert(vuln);
}

bool Service::isVuln(Vulnerability code) {
    return vulns.find(code) != vulns.end();
}

Service::~Service() {}