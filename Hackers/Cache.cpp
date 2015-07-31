//
//  Cache.cpp
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Cache.h"
using namespace std;

map<string, StringRecord*> Cache::records;

bool Cache::isCached(string item) {
    return records.find(item) != records.end();
}

StringRecord* Cache::queryCache(string item, string contents) {
    if(!isCached(item)) {
        addCache(item, contents);
    }
    
    return getCache(item);
}

StringRecord* Cache::queryCache(string item) {
    return queryCache(item, item);
}

void Cache::addCache(string item, string contents) {
    Cache::records[item] = new StringRecord(contents);
}

StringRecord* Cache::getCache(string item) {
    return Cache::records[item];
}

Cache::~Cache() {
    for(auto p: Cache::records) {
        delete p.second;
    }
}