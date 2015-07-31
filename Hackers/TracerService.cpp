//
//  TracerService.cpp
//  Hackers
//
//  Created by Jonathan Peck on 31/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "TracerService.h"

TracerService::TracerService(unsigned int version): Service(Cache::queryCache("Tracer"), 13, version) {}

void TracerService::run(Host *host) {
    if(!active) {
        return;
    }
    
    // perform trace
}

void TracerService::randomInit(ResourceGenerator *gen) {
    // not needed
}

void TracerService::getHacked(Person *person) {
    // disable the service
    active = false;
}