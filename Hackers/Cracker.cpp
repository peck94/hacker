//
//  Cracker.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Cracker.h"
using namespace std;

Cracker::Cracker(unsigned int level): Exploit("crack", CRACK, level) {}

void Cracker::run(Host *local, Host *remote, unsigned int port) {
    ShellService *s = dynamic_cast<ShellService*>(remote->getService(port));
    if(!s) {
        cout << "Unknown protocol." << endl;
        return;
    }
    
    map<string, string> creds = s->getShell()->getCredentials();
    if(creds.size() == 0) {
        cout << "The service allows anonymous login." << endl;
        return;
    }
    
    string name;
    cout << "Username: ";
    getline(cin, name);
    if(!s->getShell()->hasUser(name)) {
        cout << "User not found." << endl;
        return;
    }
    
    cout << "Password: " << creds[name] << endl;
}

string Cracker::help() {
    return "Crack a login combination for a remote shell.";
}