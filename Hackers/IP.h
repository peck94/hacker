//
//  IP.h
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__IP__
#define __Hackers__IP__

#include <string>
#include <stdlib.h>

/*
 * An IP address is actually just a number. This class wraps around these numbers to convert them into an IPv4-like format.
 */
class IP {
private:
    // underlying number
    unsigned int number;
    // IP address base
    const unsigned int BASE = 256;

public:
    // ctor
    IP(unsigned int);
    
    // random IP
    IP();
    
    // string rep
    std::string toString();
};

#endif /* defined(__Hackers__IP__) */
