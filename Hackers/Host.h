//
//  Host.h
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Host__
#define __Hackers__Host__

#include "IP.h"
#include "Service.h"
#include <map>
#include <memory>
#include <iostream>
#include <set>

class Service;

/*
 * A host consists of an IP address and a collection of services.
 * Each host is linked to a number of other hosts, forming a network graph.
 */
class Host {
private:
    // store IP
    IP* ip;
    // store services
    std::map<unsigned int, Service*> services;
    // store neighbors
    std::set<Host*> uplinks;
    
public:
    // init with IP
    Host(IP* ip);
    
    // add a service
    void addService(Service* s);
    
    // get a service
    Service* getService(unsigned int port);
    
    // check service
    bool hasService(unsigned int port);
    
    // get services
    std::map<unsigned int, Service*> getServices();
    
    // connect to a service
    void connect(unsigned int port);
    
    // check vuln
    bool hasVuln(Vulnerability vuln);
    
    // get IP
    IP* getIP();
    
    // check host
    bool ping(std::string ip);
    
    // get host
    Host* resolve(std::string ip);
    
    // add host to network
    void link(Host* host);
    
    // get links
    std::set<Host*> getLinks();
    
    // check link
    bool hasLink(Host *host);
    
    // dtor
    virtual ~Host();
};

#endif /* defined(__Hackers__Host__) */
