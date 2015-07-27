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
#include "Host.h"

typedef std::function<Service*(unsigned int)> factory;

/*
 * The internet consists of a random assortment of hosts interconnected with each other, all running various services of differing versions.
 */
class Internet {
private:
    // store hosts
    std::map<std::string, Host*> hosts;
    // store service factories
    std::vector<factory> services;
    // store max version
    unsigned int maxVersion;

    // generate random service
    Service* randomService();
    
    // generate random host
    Host* randomHost();

public:
    // init with size and max program version
    Internet(unsigned int size, unsigned int maxVersion);
    
    // register a service
    void registerService(factory f);
    
    ~Internet();
};

#endif /* defined(__Hackers__Internet__) */
