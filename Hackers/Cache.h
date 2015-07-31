//
//  Cache.h
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Cache__
#define __Hackers__Cache__

#include "Record.h"
#include <map>
#include <string>

class Cache {
private:
    static std::map<std::string, StringRecord*> records;

public:
    static bool isCached(std::string item);
    
    static StringRecord* queryCache(std::string item, std::string contents);
    
    static StringRecord* queryCache(std::string item);
    
    static void addCache(std::string item, std::string contents);
    
    static StringRecord* getCache(std::string item);
    
    ~Cache();
};

#endif /* defined(__Hackers__Cache__) */
