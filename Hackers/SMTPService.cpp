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
            if(email->name == name) {
                cout << i+1 << ". " << email->subject << endl;
            }
        }
    }, true);
    getShell()->add("send", [this] (vector<string> args) {
        // send email
        string ipSender;
        cout << "Receiver IP: ";
        getline(cin, ipSender);
        // resolve ip
        if(!localhost->ping(ipSender)) {
            cout << "Destination host unreachable." << endl;
            return;
        }
        Host *remote = localhost->resolve(ipSender);
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
        
        Email *email = new Email{ipSender, name, subject, body};
        s->recv(email);
        cout << "E-mail sent to " << name << "@" << ipSender << "." << endl;
    }, true);
    getShell()->add("show", [this] (vector<string> args) {
        
    }, true);
}

void SMTPService::recv(Email *email) {
    if(emails.find(email->name) == emails.end()) {
        emails[email->name] = vector<Email*>{email};
    }else{
        emails[email->name].push_back(email);
    }
}

void SMTPService::run(Host *host) {
    localhost = host;
    getShell()->run(host, ":");
}