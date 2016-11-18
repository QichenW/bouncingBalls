//
// Created by Qichen on 9/23/16.
//

#ifndef BOUNCINGBALLS_USERINPUTMANAGER_H
#define BOUNCINGBALLS_USERINPUTMANAGER_H

// glut
#if defined(__APPLE__)
#include <GLUT/glut.h>
#include "setup/PhysicsPrefs.h"
#include "physicsBased/DrawObjects.h"

#else
#include <GL/glut.h>
#endif

class UserInputManager {
private:
    static void setMouseMenuBehavior(int id);

public:
    UserInputManager(int * window, PhysicsPrefs * preferences, Object ** allObjects);
    static void createMouseMenu();
    static void mouseFunc (int button, int state, int x, int y);
    static void keyboardFunc(unsigned char, int, int);

    static bool loadUserInputFromFileDialog();
};


#endif //BOUNCINGBALLS_USERINPUTMANAGER_H
