//
//  ResourceGenerator.cpp
//  Hackers
//
//  Created by Jonathan Peck on 28/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "ResourceGenerator.h"
using namespace std;

ResourceGenerator::ResourceGenerator() {
    // load resources
    loadFile("resources/usernames.txt", usernames);
    loadFile("resources/passwords.txt", passwords);
    loadFile("resources/subjects.txt", subjects);
    
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

string ResourceGenerator::randomString(vector<string> resource) {
    if(resource.size() > 0) {
        return resource[rand() % resource.size()];
    }else{
        cerr << "Error: empty resource" << endl;
        return "";
    }
}

string ResourceGenerator::randomContents(string path, unsigned int count) {
    unsigned int num = rand() % count;
    string contents = "";
    
    string filename = path + to_string(num) + ".txt";
    if(cache.find(filename) != cache.end()) {
        return cache[filename];
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
    
    cache[filename] = contents;
    
    return contents;
}

string ResourceGenerator::randomName() {
    return randomString(usernames);
}

string ResourceGenerator::randomPassword() {
    return randomString(passwords);
}

string ResourceGenerator::randomSubject() {
    return randomString(subjects);
}

string ResourceGenerator::randomEmail() {
    return randomContents("resources/emails/", num_emails);
}

string ResourceGenerator::randomFile() {
    return randomContents("resources/articles/", num_files);
}