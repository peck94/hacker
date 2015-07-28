//
//  Internet.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Internet.h"
#include "Person.h"
using namespace std;

Internet::Internet(ResourceGenerator *gen, unsigned int size, unsigned int maxVersion, unsigned int maxUsers, string username, string password) {
    this->gen = gen;
    this->maxVersion = maxVersion;
    this->maxUsers = maxUsers;
    this->size = size;

    // add localhost
    localhost = new Localhost();
    Person *player = new Person(localhost, username, password);
    people[localhost->getIP()->toString()].push_back(player);
    
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
            
            Host *other = itr->second[rand() % itr->second.size()]->getHost();
            if(!host->hasLink(other)) {
                other->link(host);
                break;
            }
        }
        
        // add random persons
        unsigned int owners = rand() % maxUsers;
        for(unsigned int j = 0; j < owners; j++) {
            Person *person = randomPerson(host);
            people[host->getIP()->toString()].push_back(person);
        }
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
                s->randomInit(gen);
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
    string username = gen->randomName();
    string password = gen->randomPassword();
    
    return new Person(host, username, password);
}

void Internet::registerService(service_factory f) {
    services.push_back(f);
}

Host* Internet::getLocalhost() {
    return localhost;
}

void Internet::start() {
    active = true;
    aiThread = thread(&Internet::animate, this);
}

void Internet::stop() {
    active = false;
    aiThread.join();
}

void Internet::animate() {
    while(active) {
        for(pair<string, vector<Person*>> p: people) {
            for(Person *person: p.second) {
                person->animate(gen, this);
                this_thread::sleep_for(chrono::milliseconds(10));
                
                if(!active) {
                    break;
                }
            }
        }
    }
}

Person* Internet::getRandomPerson() {
    auto itr = people.begin();
    advance(itr, rand() % people.size());
    return itr->second[rand() % itr->second.size()];
}

Internet::~Internet() {
    stop();
    for(pair<string, vector<Person*>> p: people) {
        for(Person *person: p.second) {
            delete person;
        }
    }
}