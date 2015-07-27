//
//  Robber.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Robber.h"
using namespace std;

Robber::Robber(unsigned int level): Exploit("rob", THEFT, level) {}

void Robber::run(Host *local, Host *remote, unsigned int port) {
    FinanceService *fl = dynamic_cast<FinanceService*>(remote->getService(port));
    if(!fl) {
        cout << "No local finance service running." << endl;
        return;
    }
    FinanceService *fr = dynamic_cast<FinanceService*>(local->getService(port));
    if(!fr) {
        cout << "No remote finance service running." << endl;
        return;
    }
    
    string victim, other;
    int amount;
    
    cout << "Steal from: ";
    getline(cin, victim);
    if(!fr->hasAccount(victim)) {
        cout << "No such account." << endl;
        return;
    }
    
    cout << "Give to: ";
    getline(cin, other);
    if(!fl->hasAccount(other)) {
        cout << "No such account." << endl;
        return;
    }
    
    cout << "Amount: ";
    cin >> amount;
    
    if(fr->transfer(victim, -amount, other, local->getIP()->toString()) &&
       fl->transfer(other, amount, victim, remote->getIP()->toString())) {
        cout << "The exploit completed successfully." << endl;
    }else{
        cout << "The exploit failed." << endl;
    }
}