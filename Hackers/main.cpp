//
//  main.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Internet.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(nullptr));
    
    cout << "Loading..." << endl;
    Internet *internet = new Internet(256, 10);
    internet->generate();
    cout << endl;
    internet->getLocalhost()->connect(22);
    
    delete internet;
    return 0;
}
