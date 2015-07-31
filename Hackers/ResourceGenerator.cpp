//
//  ResourceGenerator.cpp
//  Hackers
//
//  Created by Jonathan Peck on 28/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "ResourceGenerator.h"
using namespace std;

ResourceGenerator::ResourceGenerator(unsigned int maxVersion) {
    this->maxVersion = maxVersion;

    // load resources
    loadFile("resources/usernames.txt", usernames);
    loadFile("resources/passwords.txt", passwords);
    loadFile("resources/subjects.txt", subjects);
    
    // load programs
    programs.push_back([] (unsigned int version) -> Program* {
        return new LogDeleter(version);
    });
    programs.push_back([] (unsigned int version) -> Program* {
        return new Robber(version);
    });
    programs.push_back([] (unsigned int version) -> Program* {
        return new Cracker(version);
    });
    programs.push_back([] (unsigned int version) -> Program* {
        return new TransDeleter(version);
    });
    
    // set counts
    this->num_emails = 1097;
    this->num_files = 2225;
}

void ResourceGenerator::loadFile(string filename, vector<string>& resource) {
    ifstream file(filename, ios_base::in);
    if(!file.is_open()) {
        cerr << "Unable to load file: " << filename << "." << endl;
    }else{
        while(!file.eof()) {
            string line;
            getline(file, line);
            resource.push_back(line);
        }
        file.close();
    }
}

StringRecord* ResourceGenerator::randomString(vector<string> resource) {
    if(resource.size() > 0) {
        string s = resource[rand() % resource.size()];
        return Cache::queryCache(s, s);
    }else{
        cerr << "Error: empty resource" << endl;
        return nullptr;
    }
}

StringRecord* ResourceGenerator::randomContents(string path, unsigned int count) {
    unsigned int num = rand() % count;
    string contents = "";
    
    string filename = path + to_string(num) + ".txt";
    if(Cache::isCached(filename)) {
        return Cache::getCache(filename);
    }
    
    ifstream file(filename, ios_base::in);
    if(!file.is_open()) {
        cerr << "Unable to load file: " << filename << endl;
    }
    while(!file.eof()) {
        string line;
        getline(file, line);
        
        contents+= line + "\n";
    }
    file.close();
    
    return Cache::queryCache(filename, contents);
}

StringRecord* ResourceGenerator::randomName() {
    return randomString(usernames);
}

StringRecord* ResourceGenerator::randomPassword() {
    return randomString(passwords);
}

StringRecord* ResourceGenerator::randomSubject() {
    return randomString(subjects);
}

StringRecord* ResourceGenerator::randomEmail() {
    return randomContents("resources/emails/", num_emails);
}

StringRecord* ResourceGenerator::randomFile() {
    return randomContents("resources/articles/", num_files);
}

Program* ResourceGenerator::randomProgram() {
    return programs[rand() % programs.size()](rand() % maxVersion);
}

unsigned int ResourceGenerator::getNumPrograms() {
    return programs.size();
}