//
//  Localhost.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Localhost.h"
using namespace std;

Localhost::Localhost(): Host(new IP()) {
    SSHService *ssh = new SSHService(2);
    ssh->addProgram(new LogDeleter(2));
    ssh->addVuln(LOG_DELETER);
    addService(ssh);
    
    FTPService *ftp = new FTPService(3);
    ftp->addVuln(LOG_DELETER);
    ftp->upload(new File{"motd", 1337});
    addService(ftp);
    
    SMTPService *smtp = new SMTPService(6);
    smtp->getShell()->addCredentials("smtp", "smtp");
    addService(smtp);
    
    FinanceService *f = new FinanceService(1);
    f->addAccount("smtp", "smtp", 100);
    f->addAccount("admin", "admin", 50);
    addService(f);
}