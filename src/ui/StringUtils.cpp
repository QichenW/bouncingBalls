//
// Created by Qichen on 9/24/16.
//

#include <cstring>
#include <cstdlib>
#include "StringUtils.h"

static const char * strReqestMouseInput ="Right click and load a setup (.txt) file";
static const char *strFileLoaded =" selected, start animation or reset";
static const char *strCatmull ="Catmull-Rom";
static const char *strBspline ="B-Spline";
static const char *strEuler ="Euler Angle & ";
static const char *strQuaternion ="Quaternion & ";
static char *strStatusInfo;

/****
 * This function takes care of what text to be displayed on the window
 */
void UserInterfaceManager::renderStatusMessage(int orientationMode, int interpolationMode, bool isPlaying) {
    int numberOfStrs;
    if (orientationMode == -1 || interpolationMode == -1){
            strStatusInfo = buildString((const char *[]) {strReqestMouseInput}, 1);
    } else {
        numberOfStrs = isPlaying ? 2 : 3;
        if(orientationMode == 0) {
            if(interpolationMode == 0) {
                strStatusInfo = buildString((const char *[]) {strEuler, strCatmull, strFileLoaded}, numberOfStrs);
            } else {
                strStatusInfo = buildString((const char *[]) {strEuler, strBspline, strFileLoaded}, numberOfStrs);
            }
        } else {
            if(interpolationMode == 0) {
                strStatusInfo = buildString((const char *[]) {strQuaternion, strCatmull, strFileLoaded}, numberOfStrs);
            } else {
                strStatusInfo = buildString((const char *[]) {strQuaternion, strBspline, strFileLoaded}, numberOfStrs);
            }
        }
    }
    printInWindow(strStatusInfo, !isPlaying);
}

/***
 * This function prints a char * to the window.
 * @param strInfo is to be printed.
 * @param isStatusInfo true to print in the lower line; false to print in the upper line.
 */
void UserInterfaceManager::printInWindow(char *strInfo, bool isStatusInfo) {
    int x, y; // position in the window
    if (isStatusInfo) {
        x = 20;
        y = 20;
    } else {
        x = 540;
        y = 100;
    }
//set the text position in the window and color
    glWindowPos2f(x,y);
    glColor3f(1.0f, 1.0f, 0.0f);
    int len = (int) strlen(strInfo);
//loop to display character by character
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strInfo[i]);
    }
}

/****
 * buildString is the helper function to generate a char * , which is a piece of info to display in the window.
 * @param pointer points to an array of array of char
 * @param numberOfSegments is the size of *pointer
 * @return the char * ready to be printed in the window.
 */
char *UserInterfaceManager::buildString(const char **pointer, int numberOfSegments) {
    // allocate enough memory for this char*
    char *infoString= (char *) malloc(strlen(strFileLoaded)* 3);

    while(numberOfSegments > 0) {
        strcat(infoString, *pointer++);
        numberOfSegments--;
    }
    return infoString;
};