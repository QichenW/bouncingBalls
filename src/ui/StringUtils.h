//
// Created by Qichen on 9/24/16.
//

#ifndef GLUTPROJECT_USERINTERFACEMANAGER_H
#define GLUTPROJECT_USERINTERFACEMANAGER_H

// glut
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class UserInterfaceManager {
public:
    static void printMessageForBouncingBalls(int numberOfObjs, int numberOfWalls, bool isPlaying);

private:
    static char* buildString(int nb, int nw, const char **pointer, int numberOfSegments);

    static void printInWindow(char *strInfo, bool isStatusInfo);

    static char *buildString(const char **pointer, int numberOfSegments);
};


#endif //GLUTPROJECT_USERINTERFACEMANAGER_H
