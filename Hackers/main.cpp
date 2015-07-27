//
//  main.cpp
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "Localhost.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    srand(time(nullptr));
    
    Localhost localhost;
    localhost.connect(22);
    
    return 0;
}
