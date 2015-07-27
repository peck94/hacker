//
//  LogDeleter.cpp
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#include "LogDeleter.h"

LogDeleter::LogDeleter(unsigned int level): Exploit("logdel", LOG_DELETER, level) {}

void LogDeleter::run(Host *local, Host *remote, unsigned int port) {
    ShellService *s = static_cast<ShellService*>(remote->getService(port));
    Shell *shell = s->getShell();
    shell->clearLogs();
}