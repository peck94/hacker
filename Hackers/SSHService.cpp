//
//  SSHService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "SSHService.h"
using namespace std;

SSHService::SSHService(unsigned int version): ShellService("SSH", 22, version) {
    Shell *shell = getShell();
    shell->add("help", [this] (vector<string> args) {
        cout << "Command listing:" << endl;
        cout << "help: display help" << endl;
        cout << "logout: disconnect from this host" << endl;
        cout << "ssh [host] ([port]): connect to host on port (default 22)" << endl;
        cout << "login [username] [password]: login with the specified credentials" << endl;
        cout << "netstat: view active network connections" << endl;
        cout << "ping [ip]: check whether a host is up" << endl;
        cout << "run [program] [args]: run a program" << endl;
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
            cout << host->getIP() << endl;
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
    shell->add("run", [this] (vector<string> args) {
        if(args.size() < 2) {
            cout << "Please specify an executable." << endl;
            return;
        }
        
        string name = args[1];
        for(Program *program: programs) {
            if(program->getName() == name) {
                program->launch(localhost, args);
            }
        }
    }, true);
}

void SSHService::run(Host* host) {
    this->localhost = host;

    // shell
    getShell()->run(host, "$");
}

void SSHService::addProgram(Program *program) {
    programs.insert(program);
}

SSHService::~SSHService() {
    for(Program *program: programs) {
        delete program;
    }
}