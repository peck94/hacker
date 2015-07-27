//
//  SMTPService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "SMTPService.h"
using namespace std;

SMTPService::SMTPService(unsigned int version): ShellService("SMTP", 25, version) {
    getShell()->add("help", [this] (vector<string> args) {
        cout << "list: list e-mails for your account" << endl;
        cout << "send: send an e-mail" << endl;
        cout << "show [id]: show an e-mail" << endl;
        cout << "delete [id]: delete an e-mail" << endl;
    }, false);
    getShell()->add("list", [this] (vector<string> args) {
        // list emails
        string name = getShell()->getSession().first;
        if(emails.find(name) == emails.end() ||
           emails[name].empty()) {
            cout << "No messages for " << name << "." << endl;
            return;
        }
        
        cout << "Messages for " << name << ":" << endl;
        for(int i = 0; i < emails[name].size(); i++) {
            Email *email = emails[name][i];
            if(email->nameTarget == name) {
                cout << i+1 << ". " << email->subject << endl;
            }
        }
    }, true);
    getShell()->add("send", [this] (vector<string> args) {
        // send email
        string ipRecv;
        cout << "Receiver IP: ";
        getline(cin, ipRecv);
        // resolve ip
        if(!localhost->ping(ipRecv)) {
            cout << "Destination host unreachable." << endl;
            return;
        }
        Host *remote = localhost->resolve(ipRecv);
        if(!remote->hasService(25)) {
            cout << "Remote SMTP service is not responding." << endl;
            return;
        }
        SMTPService *s = static_cast<SMTPService*>(remote->getService(25));
        
        string name;
        cout << "Target user: ";
        getline(cin, name);
        // check user
        if(!s->getShell()->hasUser(name)) {
            cout << "Remote user not found." << endl;
            return;
        }
        
        string subject;
        cout << "Subject: ";
        getline(cin, subject);
        
        string body;
        string line;
        cout << "Body: " << endl;
        while(line != ".") {
            getline(cin, line);
            body+= line + "\n";
        }
        
        string localname = getShell()->getSession().first;
        string ipSender = localhost->getIP()->toString();
        Email *email = new Email{ipSender, localname, name, subject, body};
        s->recv(email);
        cout << "E-mail sent to " << name << "@" << ipRecv << " from " << localname << "@" << ipSender << "." << endl;
    }, true);
    getShell()->add("show", [this] (vector<string> args) {
        if(args.size() < 2) {
            cout << "Please specify a number." << endl;
            return;
        }
        
        int index = stoi(args[1])-1;
        string name = getShell()->getSession().first;
        if(emails.find(name) == emails.end() || emails[name].size() <= index) {
            cout << "No such e-mail." << endl;
            return;
        }
        
        Email *email = emails[name][index];
        cout << "Sender: " << email->nameSource << "@" << email->ipSender << endl;
        cout << "Subject: " << email->subject << endl;
        cout << email->body << endl;
    }, true);
    getShell()->add("delete", [this] (vector<string> args) {
        if(args.size() < 2) {
            cout << "Please specify a number." << endl;
            return;
        }
        
        int index = stoi(args[1])-1;
        string name = getShell()->getSession().first;
        if(emails.find(name) == emails.end() || emails[name].size() <= index) {
            cout << "No such e-mail." << endl;
            return;
        }
        
        Email *email = emails[name][index];
        swap(emails[name][index], emails[name].back());
        emails[name].pop_back();
        delete email;
        cout << "Message " << index+1 << " erased." << endl;
    }, true);
}

void SMTPService::recv(Email *email) {
    if(emails.find(email->nameTarget) == emails.end()) {
        emails[email->nameTarget] = vector<Email*>{email};
    }else{
        emails[email->nameTarget].push_back(email);
    }
}

void SMTPService::run(Host *host) {
    localhost = host;
    getShell()->run(host, ":");
}

void SMTPService::randomInit() {
    // TODO
}

SMTPService::~SMTPService() {
    for(pair<string, vector<Email*>> p: emails) {
        for(Email* email: p.second) {
            delete email;
        }
    }
}