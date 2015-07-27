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
        if(hasUser(username) && creds[username] == password) {
            authenticated = true;
            session = pair<string, string>{username, password};
            cout << "Logged in as " << username << "." << endl;
        }else{
            cout << "Invalid login credentials." << endl;
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
        
        if(line.length() == 0) {
            continue;
        }
        
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
    
    // logout
    authenticated = false;
}

void Shell::addCredentials(string username, string password) {
    creds[username] = password;
}

bool Shell::hasUser(string user) {
    return creds.find(user) != creds.end();
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

map<string, string> Shell::getCredentials() {
    return creds;
}

Shell::~Shell() {
    for(LogEntry *entry: logs) {
        delete entry;
    }
}