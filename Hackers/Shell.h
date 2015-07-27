//
//  Shell.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Shell__
#define __Hackers__Shell__

#include "IP.h"
#include "Host.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

typedef std::function<void(std::vector<std::string>)> command;

struct LogEntry {
    IP *ip;
    std::string data;
};

/*
 * A shell allows a user to execute commands via a command line.
 */
class Shell {
private:
    // store commands
    std::map<std::string, command> cmds;
    /*
     * Stores login credentials.
     * Services with no credentials are assumed to allow anonymous login.
     */
    std::vector<std::pair<std::string, std::string>> creds;
    // store auth status
    bool authenticated = false;
    // store session
    std::pair<std::string, std::string> session;
    // store logs
    std::vector<LogEntry*> logs;
    // store host
    Host *localhost;

public:
    Shell();
    
    // add command
    void add(std::string cmd, command f, bool auth);
    
    // register credentials
    void addCredentials(std::string username, std::string password);
    
    // check credentials
    bool hasUser(std::string user);
    
    // run with prompt
    void run(Host *host, std::string prompt);
    
    // add log entry
    void addLog(std::string entry);
    void addLog(std::string ip, std::string entry);
    
    // clear logs
    void clearLogs();
    
    // getters
    std::pair<std::string, std::string> getSession();
    
    ~Shell();
};

#endif /* defined(__Hackers__Shell__) */
