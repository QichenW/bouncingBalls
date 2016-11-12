//  Created by Qichen on 9/17/16.
// As required opengl toolkit's api about any matrix and vector related
// calculations are not used. The author implemented them.
//  Copyright © 2016 Qichen Wang. All rights reserved.
//

#include <RotationHelper.h>
#include <UserInputManager.h>
#include <StringUtils.h>
#include <matrix/InterpolationHelper.h>
#include <articulated/Part.h>
#include <articulated/DrawLinks.h>
#include <articulated/Kinematics.h>

using namespace std;

Part *parts[15];
Preferences prefs;
int curveSegmentAmount, currentSegment;
GLfloat increment = 0.008;

GLfloat tVector[4]={}, quaternion[4] = {}, eulerAngle[3] = {}, translation[3] = {};
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
    glMultMatrixf((GLfloat []){1,0,0,0,0,1,0,0,0,0,1,0,0,10,-20,1});

    //TODO insert real local rotation and translation
    //only the local translation of torso change
    Kinematics::setLocalTranslation(parts[0]);
    Kinematics::setLocalRotation(parts, false);

    DrawLinks::drawLinks(parts, quaternion, translation, false);
}


void drawLiks(bool isKeyFraming) {

}

/****
 * This function is for drawing the frames in the interpolated animation.
 */
void drawFrame() {
    glLoadIdentity();
    glPushMatrix();
    //move the model view away from the camera, so that we are not inside the object
    glMultMatrixf((GLfloat []){1,0,0,0,0,1,0,0,0,0,1,0,0,10,-95,1});
    glColor3f(0.1, 0.45, 0.1);

    // prepare the T vector for current time, then increment time.
    // if reach the end of one curve segment, point to next segment/ if end of whole trajectory, stop the animation
    // then return

    if(prefs.getTimeProgress()< 1.0){
        InterpolationHelper::prepareTimeVector(tVector, prefs.getTimeProgress());
        prefs.timeProceed(increment);
    } else if (currentSegment <= curveSegmentAmount) {
        //if reach the end of current curve
        prefs.currentCoefficientMatrices->printCurrentCoefficientMatrices();
        if (currentSegment == curveSegmentAmount) {
            // if current curve is the last segment in trajectory, end the animation then return
            glPopMatrix();
            prefs.setIsPlaying(false);
            return;
        }
        // if current cure is not the last segment in trajectory, shift to next curve then return
        currentSegment++;
        prefs.resetTimeProgress();
        prefs.currentCoefficientMatrices = prefs.currentCoefficientMatrices->next;
        // move and rotate the figure
        Kinematics::setLocalRotation(parts, true);
        DrawLinks::drawLinks(parts, quaternion, translation, true);
        glPopMatrix();
        return;
    }

    /** the interpolation for rotation of links other that torso is NOT written here,
     * it is written in class Kinematics **/

    // prepare the translation vector for torso
    InterpolationHelper::
    prepareTranslationOrEulerAngleVector(translation, tVector, prefs.currentCoefficientMatrices->translation);

    if (prefs.getOrientationMode() == 0) {
        // if getting euler angle version of animation
        // prepare the euler angle vector for torso
        InterpolationHelper::
        prepareTranslationOrEulerAngleVector(eulerAngle, tVector, prefs.currentCoefficientMatrices->eRotation);
        // move the figure
        glMultMatrixf(RotationHelper::generateFlattenedTransformationMatrix(eulerAngle, translation, false));
    } else {
        // if getting quaternion version of animation
        // prepare the quaternion vector
        InterpolationHelper::prepareQuaternionVector(quaternion, tVector, prefs.currentCoefficientMatrices->qRotation);

        // move and rotate the torso; rotate other links
        Kinematics::setLocalRotation(parts, true);
        DrawLinks::drawLinks(parts, quaternion, translation, true);
    }
    glPopMatrix();
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // the setup info char * on the bottom left corner on window when it is idle,
    // or the type of animation when playing animation
    UserInterfaceManager::renderStatusMessage(
            prefs.getOrientationMode(), prefs.getInterpolationMode(), prefs.getIsPlaying());
    if(!prefs.getIsPlaying()){
        // if there is no user input, show an walking in straight line animation
        displayObject();
        //TODO the following two line is bad practice fix it later
        currentSegment = 1;
        prefs.currentCoefficientMatrices = prefs.pCoefficientMatrices;
    } else {
        curveSegmentAmount = prefs.getKeyFrameAmount() - 3;
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
    window = glutCreateWindow("CSCI 6555 project 2 : Articulated Figure");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(UserInputManager::keyboardFunc);
    glutMouseFunc(UserInputManager::mouseFunc);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // calculate All coefficient matrices for walking cycle interpolation
    Kinematics::calculateAllCoefficientMatrices();
    // initiate an instance of prefs to store the user preference
    UserInputManager(&window, &prefs);


    //load the obj files of parts, and create the drawing list
    DrawLinks::prepareLinks(parts);

    UserInputManager::createMouseMenu();
    glutMainLoop();
    return 0;
}