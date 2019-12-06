#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "documentparser.h"

class userInterface
{
public:
    userInterface();
    void maintenanceMode();
    void interactiveMode();
public:
    documentParser buffer();

};

#endif // USERINTERFACE_H
