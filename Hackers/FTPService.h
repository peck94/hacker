//
//  FTPService.h
//  Hackers
//
//  Created by Jonathan Peck on 27/07/15.
//  Copyright (c) 2015 Jonathan Peck. All rights reserved.
//

#ifndef __Hackers__FTPService__
#define __Hackers__FTPService__

#include "ShellService.h"
#include "Shell.h"
#include "ResourceGenerator.h"
#include <list>
#include <iomanip>

class ResourceGenerator;

struct File {
    std::string name;
    std::string contents;
};

/*
 * The FTP service allows access to the local file system.
 */
class FTPService: public ShellService {
private:
    // store files
    std::list<File*> files;
    // store field width
    unsigned int width = 0;
    // store host
    Host *localhost;
    
public:
    FTPService(unsigned int version);
    
    virtual void run(Host *host);
    virtual void randomInit(ResourceGenerator *gen);
    virtual void getHacked(Person *person);
    
    // add file
    void upload(File *file);
    
    // get file list
    std::list<File*> getFiles();
    
    ~FTPService();
};

#endif /* defined(__Hackers__FTPService__) */
