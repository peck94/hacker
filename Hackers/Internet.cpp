//
//  Internet.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Internet.h"
using namespace std;

Internet::Internet(unsigned int size, unsigned int maxVersion, string username, string password) {
    this->maxVersion = maxVersion;
    this->size = size;

    // add localhost
    localhost = new Localhost();
    Person *player = new Person(localhost, username, password);
    people[localhost->getIP()->toString()] = player;
    
    // load usernames
    ifstream file("resources/usernames.txt", ios_base::in);
    if(!file.is_open()) {
        cerr << "Unable to load usernames." << endl;
    }else{
        while(!file.eof()) {
            string line;
            getline(file, line);
            usernames.push_back(line);
        }
        file.close();
    }
    // load passwords
    ifstream file2("resources/passwords.txt", ios_base::in);
    if(!file2.is_open()) {
        cerr << "Unable to load passwords." << endl;
    }else{
        while(!file2.eof()) {
            string line;
            getline(file2, line);
            passwords.push_back(line);
        }
        file.close();
    }
    
    // register services
    registerService([] (unsigned int version) -> Service* {
        return new SSHService(version);
    });
    registerService([] (unsigned int version) -> Service* {
        return new FTPService(version);
    });
    registerService([] (unsigned int version) -> Service* {
        return new SMTPService(version);
    });
    registerService([] (unsigned int version) -> Service* {
        return new FinanceService(version);
    });
}

void Internet::generate() {
    // create network
    for(unsigned int i = 0; i < size-1; i++) {
        // generate random host
        Host *host = randomHost();

        // connect to random existing hosts
        while(true) {
            auto itr = people.begin();
            advance(itr, rand() % people.size());
            
            Host *other = itr->second->getHost();
            if(!host->hasLink(other)) {
                other->link(host);
                break;
            }
        }
        
        // create random person
        Person *person = randomPerson(host);
        
        // add to network
        people[host->getIP()->toString()] = person;
    }
}

Host* Internet::randomHost() {
    // number of services
    unsigned int num = rand() % services.size();
    
    // random IP
    IP *ip;
    while(true) {
        ip = new IP();
        if(people.find(ip->toString()) == people.end()) {
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

Person* Internet::randomPerson(Host *host) {
    string username = usernames[rand() % usernames.size()];
    string password = passwords[rand() % passwords.size()];
    
    return new Person(host, username, password);
}

void Internet::registerService(factory f) {
    services.push_back(f);
}

Host* Internet::getLocalhost() {
    return localhost;
}

Internet::~Internet() {
    for(pair<string, Person*> p: people) {
        delete p.second;
    }
}