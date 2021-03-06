//
//  FinanceService.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__FinanceService__
#define __Hackers__FinanceService__

#include "ShellService.h"
#include "Person.h"
#include "Cache.h"
#include "Record.h"
#include <map>

struct Transaction {
    StringRecord* name;
    int amount;
    StringRecord* sender;
    IP* ip;
};

/*
 * A FinanceService allows for the transfer of monies from one account to another on systems that run Finance.
 */
class FinanceService: public ShellService {
private:
    // store accounts
    std::map<std::string, int> accounts;
    // store host
    Host *localhost;
    // store transaction log
    std::vector<Transaction*> transactions;
    
public:
    FinanceService(unsigned int version);
    
    // add an account
    void addAccount(std::string name, std::string password, int balance);
    
    // check account
    bool hasAccount(std::string name);
    
    // get balance
    int getAccount(std::string name);
    
    // transfer money to account
    bool transfer(std::string name, int amount, std::string sender, IP* ip);
    
    // clear some account's log
    void clearLog(std::string name);
    
    virtual void run(Host *host);
    virtual void randomInit(ResourceGenerator *gen);
    virtual void getHacked(Person *person);
    
    ~FinanceService();
};

#endif /* defined(__Hackers__FinanceService__) */
