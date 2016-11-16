//  Created by Qichen on Nov 12, 2016
// As required opengl toolkit's api about any matrix and vector related
// calculations are not used. The author implemented them.
//  Copyright © 2016 Qichen Wang. All rights reserved.
//

#include "physicsBased/CollisionDetector.h"
#include "RotationHelper.h"
#include "UserInputManager.h"
#include "StringUtils.h"
#include "matrix/InterpolationHelper.h"
#include "physicsBased/Object.h"
#include "physicsBased/DrawObjects.h"

using namespace std;

Object *objects[7];
PhysicsPrefs prefs;
GLfloat t = 0, increment = 0.08;
int window;

void drawFrame();

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

/***
 * display the figure when idle
 */
void displayObject() {

    glLoadIdentity();
    glColor3f(0.1, 0.45, 0.1);
    glMatrixMode(GL_MODELVIEW);
    //move the model view away from the camera, so that we are not inside the object1
    glMultMatrixf((GLfloat []){1,0,0,0,0,1,0,0,0,0,1,0,0,0,-150,1});

    //TODO insert real local rotation and translation
    if(objects[0]!= nullptr) {

        DrawObjects::draw(objects);
    }
}

/****
 * This function is for drawing the frames in the interpolated animation.
 */
void drawFrame() {
    glLoadIdentity();
    glPushMatrix();
    //move the model view away from the camera, so that we are not inside the object
    glMultMatrixf((GLfloat []){1,0,0,0,0,1,0,0,0,0,1,0,0,0,-150,1});
    glColor3f(0.1, 0.45, 0.1);
    int i;
    CollisionDetector::detectAll(objects, prefs.numberOfObjects);
    for(i = 6; i <prefs.numberOfObjects; i++){
        ((Ball *) objects[i])->updateFlattenedTransformationMatrix(increment);
    }
    DrawObjects::draw(objects);

    glPopMatrix();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UserInterfaceManager::printMessageForBouncingBalls(
            prefs.numberOfObjects, DrawObjects::NUMBER_OF_WALLS, prefs.getIsPlaying());
    if(!prefs.getIsPlaying()){
        // if there is no user input, show an walking in straight line animation
        displayObject();
    } else {
//tODO
        drawFrame();
    }
    glutSwapBuffers(); //swap the buffers

}

/**
 *  Note that openGL works in a right-handed coordinate system by default
 * **/
int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("CSCI 6555 project 3 : Physics-Base Motion Control System");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(UserInputManager::keyboardFunc);
    glutMouseFunc(UserInputManager::mouseFunc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // initiate an instance of prefs to store the user preference
    UserInputManager(&window, &prefs, objects);

    UserInputManager::createMouseMenu();
    //TODO fix this, this function is also called in userInputManager
    DrawObjects::prepareObjects(&prefs,objects);
    glutMainLoop();
    return 0;
}