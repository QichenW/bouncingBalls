//
// Created by Qichen on 9/25/16.
//

#ifndef GLUTPROJECT_SETUPFILELOADER_H
#define GLUTPROJECT_SETUPFILELOADER_H


#include "Preferences.h"
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <string>

#else
#include <GL/glut.h>
#endif

class SetupFileLoader {
public:
    static void loadPreferencesFromTextFile(char *path, Preferences *pPreferences);
};


#endif //GLUTPROJECT_SETUPFILELOADER_H
