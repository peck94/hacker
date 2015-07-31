//
//  FingerService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "FingerService.h"
#include "Person.h"
using namespace std;

FingerService::FingerService(unsigned int version): ShellService(Cache::queryCache("Finger"), 79, version) {
    getShell()->add("list", [this] (vector<string> args) {
        cout << "User account listing:" << endl;
        for(auto p: getShell()->getCredentials()) {
            cout << p.first << endl;
        }
    }, false);
}

void FingerService::run(Host *host) {
    localhost = host;
    getShell()->run(host, "?");
}

void FingerService::randomInit(ResourceGenerator *gen) {}

void FingerService::getHacked(Person *person) {
    person->hack(this);
}