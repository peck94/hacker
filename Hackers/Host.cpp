//
//  Host.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Host.h"
using namespace std;

Host::Host(IP* ip) {
    // copy IP
    this->ip = ip;
}

void Host::addService(Service* s) {
    // add to services
    services[s->getPort()] = s;
}

Service* Host::getService(unsigned int port) {
    return services[port];
}

bool Host::hasService(unsigned int port) {
    return services.find(port) != services.end();
}

void Host::connect(unsigned int port) {
    if(services.find(port) == services.end()) {
        cout << "Failed to connect." << endl;
        return;
    }
    
    cout << "Connected to " << ip->toString() << endl;
    
    Service* service = services[port];
    cout << service->printBanner() << endl;
    service->run(this);
}

bool Host::hasVuln(Vulnerability vuln) {
    for(pair<unsigned int, Service*> p: services) {
        if(p.second->isVuln(vuln)) {
            return true;
        }
    }
    
    return false;
}

IP* Host::getIP() {
    return ip;
}

bool Host::ping(string ip) {
    // check own IP
    if(ip == getIP()->toString()) {
        return true;
    }
    
    // find IP locally
    for(Host* host: uplinks) {
        if(host->getIP()->toString() == ip) {
            return true;
        }
    }
    
    // contact uplinks
    for(Host* host: uplinks) {
        if(host->ping(ip)) {
            return true;
        }
    }
    
    // nothing found
    return false;
}

Host* Host::resolve(string ip) {
    // check own ip
    if(ip == getIP()->toString()) {
        return this;
    }
    
    // find IP locally
    for(Host* host: uplinks) {
        if(host->getIP()->toString() == ip) {
            return host;
        }
    }
    
    // contact uplinks
    for(Host* host: uplinks) {
        Host* result = host->resolve(ip);
        if(result) {
            return result;
        }
    }
    
    // nothing found
    return nullptr;
}

void Host::link(Host* host) {
    uplinks.push_back(host);
}

vector<Host*> Host::getLinks() {
    return uplinks;
}

Host::~Host() {
    delete ip;
    for(pair<unsigned int, Service*> p: services) {
        delete p.second;
    }
}