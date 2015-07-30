//
//  Cacher.h
//  Hackers
//
//  Created by Jonathan Peck on 30/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Cacher__
#define __Hackers__Cacher__

#include <map>

template<class T>
struct Record {
    T contents;
};

template<class S, class T>
class Cacher {
private:
    std::map<S, Record<T>*> cache;

public:
    bool isCached(S item);
    Record<T>* queryCache(S item, T contents);
    
    ~Cacher();
};

#endif /* defined(__Hackers__Cacher__) */
