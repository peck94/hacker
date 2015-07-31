//
//  TracerService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "TracerService.h"
using namespace std;

TracerService::TracerService(unsigned int version): Service(Cache::queryCache("Tracer"), 13, version) {}

void TracerService::run(Host *host) {
    if(!active) {
        cout << "tracer inactive on " << host->getIP()->toString() << endl;
        return;
    }
    
    // perform trace
    cout << host->getIP()->toString() << " is running a trace" << endl;
}

void TracerService::randomInit(ResourceGenerator *gen) {
    // not needed
}

void TracerService::getHacked(Person *person) {
    person->hack(this);
}

string TracerService::printBanner() {
    string result = Service::printBanner();
    if(active) {
        result+= " (ENABLED)";
    }else{
        result+= " (DISABLED)";
    }
    
    return result;
}

void TracerService::setEnabled(bool flag) {
    active = flag;
}

