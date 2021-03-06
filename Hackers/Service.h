//
//  Service.h
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Service__
#define __Hackers__Service__

#include <string>
#include <set>
#include <memory>
#include "Vulnerability.h"
#include "Record.h"
#include "Program.h"

class Person;
class Host;
class ResourceGenerator;

/*
 * A service is any program that runs on a certain port on a host. It has a name and a version, which together determine its vulnerabilities.
 */
class Service {
private:
    // port the service runs on
    unsigned int port;
    // name of service
    StringRecord* name;
    // version
    unsigned int version;
    // store vulnerabilities
    std::set<Vulnerability> vulns;

public:
    // ctor
    Service(StringRecord* name, unsigned int port, unsigned int version);
    
    // print banner
    virtual std::string printBanner();
    
    // getters
    StringRecord* getName();
    unsigned int getPort();
    unsigned int getVersion();
    
    // add vulnerabilities
    void addVuln(Vulnerability vuln);
    
    // check for vulnerability
    bool isVuln(Vulnerability code);
    
    // run the service
    virtual void run(Host* host) = 0;
    
    // init the service with random data
    virtual void randomInit(ResourceGenerator *gen) = 0;

    // get hacked
    virtual void getHacked(Person *person) = 0;
    
    virtual ~Service();
};

#endif /* defined(__Hackers__Service__) */
