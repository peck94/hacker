//
//  ResourceGenerator.h
//  Hackers
//
//  Created by Jonathan Peck on 28/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__ResourceGenerator__
#define __Hackers__ResourceGenerator__

#include "Program.h"
#include "LogDeleter.h"
#include "Robber.h"
#include "Cracker.h"
#include "TransDeleter.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <map>

typedef std::function<Program*(unsigned int version)> factory;

class ResourceGenerator {
private:
    // store resources
    std::vector<std::string> usernames;
    std::vector<std::string> passwords;
    std::vector<std::string> subjects;
    std::vector<factory> programs;
    unsigned int num_emails;
    unsigned int num_files;
    // store cache
    std::map<std::string, std::string> cache;
    // store max version
    unsigned int maxVersion;

    std::string randomString(std::vector<std::string> resource);
    std::string randomContents(std::string path, unsigned int count);
    void loadFile(std::string filename, std::vector<std::string>& resource);
    
public:
    ResourceGenerator(unsigned int maxVersion);
    
    std::string randomName();
    std::string randomPassword();
    std::string randomEmail();
    std::string randomSubject();
    std::string randomFile();
    Program* randomProgram();
    
    unsigned int getNumPrograms();
};

#endif /* defined(__Hackers__ResourceGenerator__) */
