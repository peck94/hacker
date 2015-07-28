//
//  Person.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Person.h"
#include "Internet.h"
using namespace std;

Person::Person(Host *host, string name, string password) {
    this->host = host;
    this->name = name;
    this->password = password;
    
    // install credentials
    for(pair<unsigned int, Service*> p: host->getServices()) {
        Service *s = p.second;
        ShellService* ss = dynamic_cast<ShellService*>(s);
        if(ss) {
            ss->getShell()->addCredentials(name, password);
        }
    }
}

string Person::getName() {
    return name;
}

string Person::getPassword() {
    return password;
}

Host* Person::getHost() {
    return host;
}

void Person::animate(ResourceGenerator *gen, Internet *internet) {
    Host *host = getHost();
    
    // throw dice
    unsigned int code = rand() % 5;
    
    // make a decision
    switch(code) {
        case 0:
        {
            // create a file
            if(host->hasService(21)) {
                FTPService *s = static_cast<FTPService*>(host->getService(21));
                s->upload(new File{"file_" + gen->randomName(), gen->randomFile()});
            }
            break;
        }
        
        case 1:
        {
            // upload a file
            Host *remote = internet->getRandomPerson()->getHost();
            if(remote->hasService(21)) {
                FTPService *s = static_cast<FTPService*>(remote->getService(21));
                s->upload(new File{"file_" + gen->randomName(), gen->randomFile()});
            }
            break;
        }
            
        case 2:
        {
            // send an email
            Person *other = internet->getRandomPerson();
            Host *remote = other->getHost();
            if(remote->hasService(25)) {
                SMTPService *s = static_cast<SMTPService*>(remote->getService(25));
                
                string ipSender = host->getIP()->toString();
                string nameSource = getName();
                string nameTarget = other->getName();
                string subject = gen->randomSubject();
                string body = gen->randomEmail();
                s->recv(new Email{ipSender, nameSource, nameTarget, subject, body});
            }
            break;
        }
            
        case 3:
        {
            // transfer money
            Person *other = internet->getRandomPerson();
            Host *remote = other->getHost();
            if(host->hasService(8080) && remote->hasService(8080)) {
                FinanceService *fl = static_cast<FinanceService*>(host->getService(8080));
                FinanceService *fr = static_cast<FinanceService*>(remote->getService(8080));
                if(fl->getAccount(getName()) > 0) {
                    int amount = rand() % fl->getAccount(getName());
                    fl->transfer(getName(), -amount, other->getName(), remote->getIP()->toString());
                    fr->transfer(other->getName(), amount, getName(), host->getIP()->toString());
                }
            }
            break;
        }
            
        default:
        {
            // do nothing
            break;
        }
    }
}

Person::~Person() {
    delete host;
}