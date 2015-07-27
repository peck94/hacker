//
//  Shell.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Shell.h"
using namespace std;

Shell::Shell() {
    add("logout", [] (vector<string> args) {}, false);
    add("login", [this] (vector<string> args) {
        // check args
        if(args.size() < 3) {
            cout << "Please specify username and password." << endl;
            return;
        }
        
        // reset state
        authenticated = false;
        
        // fetch credentials
        string username = args[1];
        string password = args[2];
        
        // anonymous login
        if(creds.size() == 0 && username == "anon" && password == "anon") {
            authenticated = true;
            return;
        }
        
        // check them
        for(pair<string, string> p: creds) {
            if(username == p.first && password == p.second) {
                authenticated = true;
                session = p;
                break;
            }
        }
        
        if(!authenticated) {
            cout << "Invalid login credentials." << endl;
        }else{
            cout << "Logged in as " << username << "." << endl;
        }
    }, false);
    add("logs", [this] (vector<string> args) {
        for(LogEntry *entry: logs) {
            cout << left << setw(12) << entry->ip->toString();
            cout << entry->data << endl;
        }
    }, true);
}

void Shell::add(string cmd, command c, bool auth) {
    cmds[cmd] = [this, auth, c] (vector<string> args) {
        if(auth && !authenticated) {
            cout << "Please login first." << endl;
        }else{
            c(args);
        }
    };
}

void Shell::run(Host *host, string prompt) {
    string line;
    
    localhost = host;
    
    // log shell start
    addLog("[New connection]");
    
    // anonymous login?
    if(creds.size() == 0) {
        authenticated = true;
        session = pair<string, string>{"anon",""};
    }
    
    while(line != "logout") {
        // get line
        if(authenticated) {
            cout << session.first;
        }
        cout << prompt << " ";
        getline(cin, line);
        
        // log command
        addLog(line);
        
        // process arguments
        stringstream s(line);
        string arg;
        vector<string> args;
        while(s >> arg) {
            args.push_back(arg);
        }
        
        // run command if exists
        if(cmds.find(args[0]) == cmds.end()) {
            cout << "Unknown command: " << args[0] << endl;
        }else{
            cmds[args[0]](args);
        }
    }
    
    // log shell exit
    addLog("[Disconnected]");
}

void Shell::addCredentials(string username, string password) {
    creds.push_back(pair<string, string>{username, password});
}

bool Shell::hasUser(string user) {
    for(pair<string, string> c: creds) {
        if(c.first == user) {
            return true;
        }
    }
    
    return false;
}

void Shell::addLog(string entry) {
    logs.push_back(new LogEntry{localhost->getIP(), entry});
}

void Shell::clearLogs() {
    logs.clear();
}

pair<string, string> Shell::getSession() {
    return session;
}

Shell::~Shell() {
    for(LogEntry *entry: logs) {
        delete entry;
    }
}