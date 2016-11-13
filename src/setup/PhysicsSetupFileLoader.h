//
// Created by Qichen on 11/13/16.
//

#ifndef BOUNCINGBALLS_PHYSICSSETUPFILELOADER_H
#define BOUNCINGBALLS_PHYSICSSETUPFILELOADER_H

#include "physicsBased/Object.h"
#include "PhysicsPrefs.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <string>

#else
#include <GL/glut.h>
#endif

class PhysicsSetupFileLoader {
public:
    static void loadPreferencesFromTextFile(char *path, PhysicsPrefs *prefs);
};


#endif //BOUNCINGBALLS_PHYSICSSETUPFILELOADER_H
