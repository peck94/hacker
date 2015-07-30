//
//  Cacher.cpp
//  Hackers
//
//  Created by Jonathan Peck on 30/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Cacher.h"
using namespace std;

template<class S, class T>
bool Cacher<S, T>::isCached(S item) {
    return cache.find(item) != cache.end();
}

template<class S, class T>
Record<T>* Cacher<S, T>::queryCache(S item, T contents) {
    if(!isCached(item)) {
        cache[item] = new Record<T>{contents};
    }
    
    return cache[item];
}

template<class S, class T>
Cacher<S, T>::~Cacher() {
    for(auto p: cache) {
        delete p.second;
    }
}

template class Cacher<string, string>;