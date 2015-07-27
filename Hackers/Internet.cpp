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
    
    // create network
    Host *root = nullptr;
    for(unsigned int i = 0; i < size; i++) {
        // generate random host
        Host *host = randomHost();
        
        if(i > 0) {
            // connect to random existing hosts
            while(true) {
                auto itr = hosts.begin();
                advance(itr, rand() % i);
                
                Host *other = itr->second;
                if(!host->hasLink(other)) {
                    host->link(other);
                    break;
                }
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

Internet::~Internet() {
    for(pair<string, Host*> p: hosts) {
        delete p.second;
    }
}