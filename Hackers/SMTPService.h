//
//  SMTPService.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__SMTPService__
#define __Hackers__SMTPService__

#include "ShellService.h"
#include "Person.h"
#include <map>

class Person;

struct Email {
    // IP of sender
    IP* ipSender;
    // username of source
    std::string nameSource;
    // username of target
    std::string nameTarget;
    // subject line
    std::string subject;
    // body of email
    std::string body;
};

/*
 * The SMTP service is used to transfer and store e-mails.
 */
class SMTPService: public ShellService {
private:
    // store e-mails
    std::map<std::string, std::vector<Email*>> emails;
    // store host
    Host *localhost;
    
public:
    SMTPService(unsigned int version);
    
    // add email
    void recv(Email*);
    
    virtual void run(Host *host);
    virtual void randomInit(ResourceGenerator *gen);
    virtual void getHacked(Person *person);
    
    ~SMTPService();
};

#endif /* defined(__Hackers__SMTPService__) */
