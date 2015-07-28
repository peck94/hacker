//
//  Internet.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Internet__
#define __Hackers__Internet__

#include <map>
#include <vector>
#include <functional>
#include <fstream>
#include <thread>
#include "Person.h"
#include "Host.h"
#include "Localhost.h"
#include "SSHService.h"
#include "FTPService.h"
#include "SMTPService.h"
#include "FinanceService.h"
#include "ResourceGenerator.h"

typedef std::function<Service*(unsigned int)> service_factory;

class Person;

/*
 * The internet consists of a random assortment of hosts interconnected with each other, all running various services of differing versions.
 */
class Internet {
private:
    // store people
    std::map<std::string, std::vector<Person*>> people;
    // store service factories
    std::vector<service_factory> services;
    // store max version
    unsigned int maxVersion;
    // store max users per system
    unsigned int maxUsers;
    // store size
    unsigned int size;
    // store localhost
    Host *localhost;
    // store resource generator
    ResourceGenerator *gen;
    // store thread flag
    bool active;
    // store AI thread
    std::thread aiThread;

    // generate random service
    Service* randomService();
    
    // generate random host
    Host* randomHost();
    
    // generate random person
    Person* randomPerson(Host *host);

public:
    // init
    Internet(ResourceGenerator *gen, unsigned int size, unsigned int maxVersion, unsigned int maxUsers, std::string username, std::string password);
    
    // create the network
    void generate();
    
    // start the AI
    void start();
    
    // stop the AI
    void stop();
    
    // register a service
    void registerService(service_factory f);
    
    // get local host
    Host* getLocalhost();
    
    // get random person
    Person* getRandomPerson();
    
    // AI
    void animate();
    
    ~Internet();
};

#endif /* defined(__Hackers__Internet__) */
