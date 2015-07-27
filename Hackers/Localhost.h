//
//  Localhost.h
//  Hackers
//
//  Created by Jonathan Peck on 26/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__Localhost__
#define __Hackers__Localhost__

#include "Host.h"
#include "SSHService.h"
#include "FTPService.h"
#include "LogDeleter.h"
#include "SMTPService.h"
#include "FinanceService.h"

class Localhost: public Host {
public:
    Localhost();
};

#endif /* defined(__Hackers__Localhost__) */
