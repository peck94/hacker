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
    
    string user, pass;
    cout << "Username: ";
    getline(cin, user);
    cout << "Password: ";
    getline(cin, pass);
    
    cout << "Loading..." << endl;
    ResourceGenerator *gen = new ResourceGenerator(10);
    Internet *internet = new Internet(gen, 10, 10, 10, user, pass);
    internet->generate();
    internet->start();
    cout << endl;
    internet->getLocalhost()->connect(22);
    
    delete internet;
    delete gen;
    return 0;
}
