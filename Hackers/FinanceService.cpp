//
//  FinanceService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "FinanceService.h"
using namespace std;

FinanceService::FinanceService(unsigned int version): ShellService(Cache::queryCache("Finance"), 8080, version) {
    getShell()->add("help", [this] (vector<string> args) {
        cout << "status: check your account" << endl;
        cout << "transfer: transfer money to another account" << endl;
    }, false);
    getShell()->add("status", [this] (vector<string> args) {
        // get account status
        string name = getShell()->getSession().first;
        int balance = accounts[name];
        cout << "Balance: " << balance << endl;
        cout << "Transaction log:" << endl;
        for(Transaction *t: transactions) {
            if(t->name->get() == name) {
                cout << t->sender->get() << "@" << t->ip->toString() << ": " << t->amount << endl;
            }
        }
    }, true);
    getShell()->add("transfer", [this] (vector<string> args) {
        // transfer money from this account
        string localname = getShell()->getSession().first;
        IP* localip = localhost->getIP();
        string ip, remotename;
        int amount;
        
        cout << "Remote IP: ";
        getline(cin, ip);
        Host *remote;
        if(!localhost->ping(ip)) {
            cout << "Destination host unreachable." << endl;
            return;
        }
        remote = localhost->resolve(ip);
        if(!remote->hasService(8080)) {
            cout << "Remote finance service not responding." << endl;
            return;
        }
        
        FinanceService *f = static_cast<FinanceService*>(remote->getService(8080));
        
        cout << "Beneficiary: ";
        getline(cin, remotename);
        if(!f->hasAccount(remotename)) {
            cout << "User not found." << endl;
            return;
        }
        
        cout << "Amount: ";
        cin >> amount;
        
        if(amount <= 0) {
            cout << "Invalid amount." << endl;
            return;
        }
        
        if(f->transfer(remotename, amount, localname, localip)) {
            transfer(localname, -amount, remotename, remote->getIP());
            cout << "The transfer was ACCEPTED." << endl;
        }else{
            cout << "The transfer was REJECTED." << endl;
        }
    }, true);
}

void FinanceService::addAccount(string name, string password, int balance) {
    accounts[name] = balance;
    getShell()->addCredentials(name, password);
}

bool FinanceService::transfer(string name, int amount, string sender, IP* ip) {
    int result = accounts[name] + amount;
    if(result >= 0) {
        accounts[name] = result;
        transactions.push_back(new Transaction{
            Cache::queryCache(name),
            amount,
            Cache::queryCache(sender),
            ip});
        return true;
    }else{
        return false;
    }
}

bool FinanceService::hasAccount(string name) {
    return getShell()->hasUser(name);
}

void FinanceService::clearLog(string name) {
    for(auto itr = transactions.begin(); itr != transactions.end(); itr++) {
        if((*itr)->name->get() == name) {
            transactions.erase(itr);
        }
    }
}

int FinanceService::getAccount(string name) {
    return accounts[name];
}

void FinanceService::run(Host *host) {
    localhost = host;
    getShell()->run(host, "#");
}

void FinanceService::randomInit(ResourceGenerator *gen) {
    // not needed
}

void FinanceService::getHacked(Person *person) {
    person->hack(this);
}

FinanceService::~FinanceService() {
    for(Transaction *t: transactions) {
        delete t;
    }
}