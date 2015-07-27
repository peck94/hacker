//
//  ResourceGenerator.h
//  Hackers
//
//  Created by Jonathan Peck on 28/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__ResourceGenerator__
#define __Hackers__ResourceGenerator__

#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <map>

class ResourceGenerator {
private:
    // store resources
    std::vector<std::string> usernames;
    std::vector<std::string> passwords;
    unsigned int num_emails;
    unsigned int num_files;
    // store cache
    std::map<std::string, std::string> cache;

    std::string randomString(std::vector<std::string> resource);
    std::string randomContents(std::string path, unsigned int count);
    void loadFile(std::string filename, std::vector<std::string>& resource);
    
public:
    ResourceGenerator();
    
    std::string randomName();
    std::string randomPassword();
    std::string randomEmail();
    std::string randomFile();
};

#endif /* defined(__Hackers__ResourceGenerator__) */
