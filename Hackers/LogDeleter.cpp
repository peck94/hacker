//
//  LogDeleter.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "LogDeleter.h"
using namespace std;

LogDeleter::LogDeleter(unsigned int level): Exploit("logdel", LOG_DELETER, level) {}

void LogDeleter::run(Host *local, Host *remote, unsigned int port) {
    ShellService *s = dynamic_cast<ShellService*>(remote->getService(port));
    if(s) {
        Shell *shell = s->getShell();
        shell->clearLogs();
        cout << "Logs cleared." << endl;
    }else{
        cout << "Unknown protocol." << endl;
    }
}

string LogDeleter::help() {
    return "Delete logs of a remote shell.";
}