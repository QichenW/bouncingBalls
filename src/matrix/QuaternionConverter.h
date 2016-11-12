//
// Created by Qichen on 9/27/16.
//

#ifndef GLUTPROJECT_QUATERNIONCONVERTER_H
#define GLUTPROJECT_QUATERNIONCONVERTER_H
// glut
#if defined(__APPLE__)

#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


using namespace std;
class QuaternionConverter {

public:
    static void eulerAngleToQuaternion(GLfloat dest[4][4], GLfloat **listOfEulerAngle, int offset);
    static GLfloat getMagnitudeOfQuaternion(GLfloat quaternion[4]);

private:
    static void getQuaternionList(GLfloat dest[4][4], GLfloat leftQuaternion[4][4],
                                  GLfloat middleQuaternion[4][4], GLfloat rightQuaternion[4][4]);
};


#endif //GLUTPROJECT_QUATERNIONCONVERTER_H
