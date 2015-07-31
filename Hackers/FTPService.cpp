//
//  FTPService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "FTPService.h"
using namespace std;

inline unsigned int max(unsigned int x, unsigned int y) {
    if(x < y) {
        return y;
    }else{
        return x;
    }
}

FTPService::FTPService(unsigned int version): ShellService(Cache::queryCache("FTP"), 21, version) {
    Shell* shell = getShell();
    shell->add("help", [this] (vector<string> args) {
        cout << "list: list all files" << endl;
        cout << "upload [file] [host]: upload file to host" << endl;
        cout << "delete [file]: delete a file" << endl;
        cout << "cat [file]: display file contents" << endl;
    }, false);
    shell->add("list", [this] (vector<string> args) {
        // list all files
        cout << setw(width) << "Filename ";
        cout << "Size" << endl;
        for(File *file: files) {
            cout << left << setw(width) << file->name->get();
            cout << file->contents->get().length() << "b" << endl;
        }
    }, true);
    shell->add("upload", [this] (vector<string> args) {
        // upload a local file to a remote FTP server
        if(args.size() < 3) {
            cout << "Please specify file name and remote host." << endl;
        }
        
        string filename = args[1];
        string ip = args[2];
        
        // check file
        File *file = nullptr;
        for(File *f: files) {
            if(f->name->get() == filename) {
                file = new File{f->name, f->contents};
                break;
            }
        }
        
        if(!file) {
            cout << "File not found." << endl;
            return;
        }
        
        // check host
        if(!localhost->ping(ip)) {
            cout << "Destination host unreachable." << endl;
            delete file;
            return;
        }
        
        // find host
        Host *remote = localhost->resolve(ip);
        if(!remote->hasService(21)) {
            cout << "Connection refused." << endl;
            delete file;
            return;
        }
        
        // contact server
        FTPService *ftp = static_cast<FTPService*>(remote->getService(21));
        ftp->upload(file);
        
        cout << "Upload complete." << endl;
    }, true);
    shell->add("delete", [this] (vector<string> args) {
        if(args.size() < 2) {
            cout << "Please specify a file name." << endl;
        }
        
        // delete file
        string name = args[1];
        for(auto itr = files.begin(); itr != files.end(); itr++) {
            File *file = *itr;
            if(file->name->get() == name) {
                files.erase(itr);
                return;
            }
        }
        
        cout << "File not found." << endl;
    }, true);
    shell->add("cat", [this] (vector<string> args) {
        if(args.size() < 2) {
            cout << "Please specify a file name." << endl;
            return;
        }
        
        string name = args[1];
        for(File *file: files) {
            if(file->name->get() == name) {
                cout << file->contents << endl;
                return;
            }
        }
        
        cout << "File not found." << endl;
    }, true);
}

void FTPService::run(Host *host) {
    localhost = host;
    getShell()->run(host, ">");
}

void FTPService::upload(File *file) {
    files.push_back(file);
    
    if(file->name->get().length() > width) {
        width = max(file->name->get().length(), 9) + 1;
    }
}

list<File*> FTPService::getFiles() {
    return files;
}

void FTPService::randomInit(ResourceGenerator *gen) {
    // add random files
    unsigned int count = rand() % 10;
    for(unsigned int i = 0; i < count; i++) {
        upload(new File{
            Cache::queryCache("file-" + to_string(i)),
            gen->randomFile()});
    }
}

void FTPService::getHacked(Person *person) {
    person->hack(this);
}

FTPService::~FTPService() {
    for(File *file: files) {
        delete file;
    }
}