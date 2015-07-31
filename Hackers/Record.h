//
//  Record.h
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef Hackers_Record_h
#define Hackers_Record_h

#include <string>

/*
 * An immutable generic record type for use in caching (flyweight).
 */
template<class T>
class Record {
private:
    T contents;

public:
    Record(T contents) {
        this->contents = contents;
    }
};

template class Record<std::string>;
typedef Record<std::string> StringRecord;

#endif
