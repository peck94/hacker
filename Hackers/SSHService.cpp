//
//  SSHService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "SSHService.h"
using namespace std;

SSHService::SSHService(unsigned int version): ShellService(Cache::queryCache("SSH"), 22, version) {
    Shell *shell = getShell();
    shell->add("help", [this] (vector<string> args) {
        cout << "Command listing:" << endl;
        cout << "help: display help" << endl;
        cout << "logout: disconnect from this host" << endl;
        cout << "ssh [host] ([port]): connect to host on port (default 22)" << endl;
        cout << "login [username] [password]: login with the specified credentials" << endl;
        cout << "netstat: view active network connections" << endl;
        cout << "ping [ip]: check whether a host is up" << endl;
        cout << "logs: view logs" << endl;
        cout << "newuser [username] [password]: create a new user" << endl;
        cout << "passwd: change your password" << endl;
        cout << endl;
        cout << "The following programs are installed:" << endl;
        for(Program *program: programs) {
            cout << program->getName() << " v" << program->getVersion() << ": " << program->help() << endl;
        }
    }, false);
    shell->add("ssh", [this] (vector<string> args) {
        // check args
        if(args.size() < 2) {
            cout << "Please specify a host and/or port." << endl;
            return;
        }

        // connect to a service of another host
        string ip = args[1];
        unsigned int port = 22;
        if(args.size() > 2) {
            port = stoi(args[2]);
        }
        
        cout << "Connecting to " << ip << " on port " << port << "..." << endl;
        if(localhost->ping(ip)) {
            Host* host = localhost->resolve(ip);
            host->connect(port);
        }else{
            cout << "Destination host unreachable." << endl;
        }
        
        cout << "Disconnected." << endl;
    }, true);
    shell->add("netstat", [this] (vector<string> args) {
        cout << "Active network connections:" << endl;
        for(Host* host: localhost->getLinks()) {
            cout << host->getIP()->toString() << endl;
        }
    }, true);
    shell->add("ping", [this] (vector<string> args) {
        if(args.size() < 2) {
            cout << "Please specify an IP address." << endl;
            return;
        }
        
        if(localhost->ping(args[1])) {
            cout << args[1] << " is up." << endl;
        }else{
            cout << args[1] << " is unreachable." << endl;
        }
    }, true);
    shell->add("*", [this] (vector<string> args) {
        string name = args[0];
        for(Program *program: programs) {
            if(program->getName() == name) {
                program->launch(localhost, args);
                return;
            }
        }
        
        cout << "Unknown command: " << name << endl;
    }, true);
}

void SSHService::run(Host* host) {
    this->localhost = host;

    // shell
    getShell()->run(host, "$");
}

void SSHService::randomInit(ResourceGenerator *gen) {
    // add random programs
    unsigned int count = rand() % gen->getNumPrograms();
    for(unsigned int i = 0; i < count; i++) {
        addProgram(gen->randomProgram());
    }
}

void SSHService::addProgram(Program *program) {
    for(Program *p: programs) {
        if(p->getName() == program->getName()) {
            return;
        }
    }

    programs.insert(program);
}

void SSHService::getHacked(Person *person) {
    person->hack(this);
}

Exploit* SSHService::getExploit(Vulnerability vuln) {
    for(Program *p: programs) {
        Exploit *e = dynamic_cast<Exploit*>(p);
        if(e && e->getVuln() == vuln) {
            return e;
        }
    }
    
    return nullptr;
}

SSHService::~SSHService() {
    for(Program *program: programs) {
        delete program;
    }
}