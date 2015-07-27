//
//  TransDeleter.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "TransDeleter.h"
using namespace std;

TransDeleter::TransDeleter(unsigned int level): Exploit("transdel", TRANS_DELETER, level) {}

void TransDeleter::run(Host *local, Host *remote, unsigned int port) {
    FinanceService *s = dynamic_cast<FinanceService*>(remote->getService(port));
    if(!s) {
        cout << "Unknown protocol." << endl;
        return;
    }
    
    string victim;
    cout << "Victim: ";
    getline(cin, victim);
    if(!s->hasAccount(victim)) {
        cout << "User not found." << endl;
        return;
    }
    
    s->clearLog(victim);
    cout << "Transaction log of " << victim << " cleared." << endl;
}

string TransDeleter::help() {
    return "Delete transaction logs of an account on a financial system.";
}