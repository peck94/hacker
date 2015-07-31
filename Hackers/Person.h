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
#include "SSHService.h"
#include "SMTPService.h"
#include "FinanceService.h"
#include "FTPService.h"

class Internet;
class FinanceService;
class SMTPService;
class FTPService;
class SSHService;

/*
 * Represents a person. People own hosts and do stuff with them.
 */
class Person {
private:
    // store system we own
    Host *host;
    // store username
    StringRecord* name;
    // store password
    StringRecord* password;
    // store resource generator
    ResourceGenerator *generator;
    // store current victim
    Host *remote;
    
public:
    // init
    Person(Host *host, StringRecord* name, StringRecord* password);

    // getters
    Host* getHost();
    StringRecord* getName();
    StringRecord* getPassword();
    
    // AI
    virtual void animate(ResourceGenerator *gen, Internet *internet);
    
    // hack routines
    void hack(SSHService *ssh);
    void hack(FTPService *ftp);
    void hack(SMTPService *smtp);
    void hack(FinanceService *finance);
    
    virtual ~Person();
};

#endif /* defined(__Hackers__Person__) */
