//
//  Person.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Person__
#define __Hackers__Person__

#include "Host.h"
#include "Service.h"
#include "ShellService.h"
#include "Internet.h"
#include "ResourceGenerator.h"

class Internet;

/*
 * Represents a person. People own hosts and do stuff with them.
 */
class Person {
private:
    // store system we own
    Host *host;
    // store username
    std::string name;
    // store password
    std::string password;
    
public:
    // init
    Person(Host *host, std::string name, std::string password);

    // getters
    Host* getHost();
    std::string getName();
    std::string getPassword();
    
    // AI
    virtual void animate(ResourceGenerator *gen, Internet *internet);
    
    virtual ~Person();
};

#endif /* defined(__Hackers__Person__) */
