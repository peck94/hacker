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
    return resolve(ip);
}

Host* Host::resolve(string ip, set<string> record) {
    // check own ip
    if(ip == getIP()->toString()) {
        return this;
    }
    
    // check cache
    if(cache.find(ip) != cache.end()) {
        return cache[ip];
    }
    
    // find IP locally
    for(Host* host: uplinks) {
        if(host->getIP()->toString() == ip) {
            cache[ip] = host;
            return host;
        }
    }
    
    // contact uplinks
    for(Host* host: uplinks) {
        // prevent loops
        if(record.find(host->getIP()->toString()) != record.end()) {
            continue;
        }
        
        // contact neighbor
        record.insert(getIP()->toString());
        Host* result = host->resolve(ip, record);
        if(result) {
            cache[ip] = result;
            return result;
        }
    }
    
    // nothing found
    return nullptr;
}

void Host::link(Host* host) {
    uplinks.insert(host);
    if(!host->hasLink(this)) {
        host->link(this);
    }
}

set<Host*> Host::getLinks() {
    return uplinks;
}

bool Host::hasLink(Host *host) {
    for(Host *other: uplinks) {
        if(other->getIP()->toString() == host->getIP()->toString()) {
            return true;
        }
    }
    
    return false;
}

map<unsigned int, Service*> Host::getServices() {
    return services;
}

Host::~Host() {
    delete ip;
    for(pair<unsigned int, Service*> p: services) {
        delete p.second;
    }
}