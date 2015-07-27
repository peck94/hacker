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
    // TODO
}

Person::~Person() {
    delete host;
}