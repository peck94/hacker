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
    
    // for every service
    for(pair<unsigned int, Service*> p: host->getServices()) {
        Service *s = p.second;
        
        // install credentials to shell
        ShellService *ss = dynamic_cast<ShellService*>(s);
        if(ss) {
            ss->getShell()->addCredentials(name, password);
        }
        
        // get money
        FinanceService *fs = dynamic_cast<FinanceService*>(s);
        if(fs) {
            fs->addAccount(getName(), getPassword(), rand());
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
    this->generator = gen;
    
    // get random victim
    remote = internet->getRandomPerson()->getHost();
    if(remote->getServices().empty()) {
        return;
    }

    // get random service from victim
    Service *service = nullptr;
    while(!service) {
        for(pair<unsigned int, Service*> p: remote->getServices()) {
            if(rand() % 2) {
                service = p.second;
                break;
            }
        }
    }
    
    // do we have a similar service?
    if(!host->hasService(service->getPort())) {
        return;
    }
    
    Service *local = host->getService(service->getPort());

    // hack it if we can
    if(service->getVersion() <= local->getVersion()) {
        service->getHacked(this);
    }
}

void Person::hack(SSHService *ssh) {
    // leave a taunt in the logs
    ssh->getShell()->addLog(getHost()->getIP(), getName() + " waz here");
}

void Person::hack(FTPService *ftp) {
    // create a file
    ftp->upload(new File{"file_" + generator->randomName(), generator->randomFile()});
}

void Person::hack(SMTPService *smtp) {
    // send spam
    string ipSender = getHost()->getIP()->toString();
    string nameSource = getName();
    string nameTarget;
    string subject = generator->randomSubject();
    string body = generator->randomEmail();
    
    auto creds = smtp->getShell()->getCredentials();
    if(creds.size() == 0) {
        return;
    }
    
    auto itr = creds.begin();
    advance(itr, rand() % creds.size());
    nameTarget = itr->second;

    smtp->recv(new Email{ipSender, nameSource, nameTarget, subject, body});
}

void Person::hack(FinanceService *finance) {
    // transfer money
    FinanceService *local = dynamic_cast<FinanceService*>(getHost()->getService(8080));
    if(!local) {
        return;
    }
    
    auto creds = finance->getShell()->getCredentials();
    if(creds.size() == 0) {
        return;
    }
    
    auto itr = creds.begin();
    advance(itr, rand() % creds.size());
    string victim = itr->second;
    if(finance->getAccount(victim) <= 0) {
        return;
    }
    
    int amount = rand() % finance->getAccount(victim);
    local->transfer(getName(), amount, victim, remote->getIP()->toString());
    finance->transfer(victim, -amount, getName(), getHost()->getIP()->toString());
}

Person::~Person() {}