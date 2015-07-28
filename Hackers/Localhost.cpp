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
    ssh->addProgram(new LogDeleter(1));
    ssh->addProgram(new Robber(1));
    ssh->addProgram(new Cracker(1));
    ssh->addProgram(new TransDeleter(1));
    ssh->addProgram(new ScannerProgram());
    addService(ssh);
    
    FTPService *ftp = new FTPService(1);
    ftp->upload(new File{"motd", "Have a nice day!"});
    addService(ftp);
    
    SMTPService *smtp = new SMTPService(1);
    addService(smtp);
    
    FinanceService *f = new FinanceService(1);
    f->addVuln(THEFT);
    addService(f);
}