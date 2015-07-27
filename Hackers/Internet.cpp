//
//  Internet.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Internet.h"
using namespace std;

Internet::Internet(unsigned int size, unsigned int maxVersion) {
    this->maxVersion = maxVersion;
    this->size = size;

    // add localhost
    localhost = new Localhost();
    hosts[localhost->getIP()->toString()] = localhost;
    
    // register services
    registerService([] (unsigned int version) -> Service* {
        return new SSHService(version);
    });
}

void Internet::generate() {
    // create network
    for(unsigned int i = 0; i < size-1; i++) {
        // generate random host
        Host *host = randomHost();

        // connect to random existing hosts
        while(true) {
            auto itr = hosts.begin();
            advance(itr, rand() % hosts.size());
            
            Host *other = itr->second;
            if(!host->hasLink(other)) {
                other->link(host);
                break;
            }
        }
        
        // add to network
        hosts[host->getIP()->toString()] = host;
    }
}

Host* Internet::randomHost() {
    // number of services
    unsigned int num = rand() % services.size();
    
    // random IP
    IP *ip;
    while(true) {
        ip = new IP();
        if(hosts.find(ip->toString()) == hosts.end()) {
            break;
        }else{
            delete ip;
        }
    }
    
    // construct host
    Host *host = new Host(ip);
    for(unsigned int i = 0; i < num; i++) {
        // add random service
        while(true) {
            Service *s = randomService();
            if(!host->hasService(s->getPort())) {
                s->randomInit();
                host->addService(s);
                break;
            }else{
                delete s;
            }
        }
    }
    
    return host;
}

Service* Internet::randomService() {
    // random version
    unsigned int version = rand() % maxVersion;
    
    // random service with version
    Service *s = services[rand() % services.size()](version);
    return s;
}

void Internet::registerService(factory f) {
    services.push_back(f);
}

Host* Internet::getLocalhost() {
    return localhost;
}

Internet::~Internet() {
    for(pair<string, Host*> p: hosts) {
        delete p.second;
    }
}