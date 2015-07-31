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
    
    unsigned int size = 1024;
    unsigned int maxVersion = 10;
    unsigned int maxUsers = 100;
    ResourceGenerator *gen = new ResourceGenerator(maxVersion);

    Internet *internet = new Internet(gen, size, maxVersion, maxUsers, user, pass);
    internet->generate();
    internet->start();
    cout << endl;
    internet->getLocalhost()->connect(22);
    
    cout << "Shutting down..." << endl;
    delete internet;
    delete gen;
    
    cout << "Done." << endl;
    return 0;
}
