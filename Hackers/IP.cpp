//
//  IP.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "IP.h"
using namespace std;

IP::IP(unsigned int number) {
    this->number = number;
}

IP::IP() {
    this->number = rand();
}

string IP::toString() {
    unsigned int first = number % BASE;
    unsigned int second = (number-first)/BASE % BASE;
    unsigned int third = ((number-first)/(BASE*BASE) - second/BASE) % BASE;
    
    return to_string(first) + "." + to_string(second) + "." + to_string(third);
}