//
// Created by Qichen on 11/2/16.
//

#include "DrawLinks.h"

static char* CALF_OBJ_NAME = (char *) "calf.obj";
static char* THIGH_OBJ_NAME = (char *) "thigh.obj";
static char* TORSO_OBJ_NAME = (char *) "torso.obj";
static char* NECK_OBJ_NAME = (char *) "neck.obj";
static char* UPPER_ARM_OBJ_NAME = (char *) "upper_arm.obj";
static char* FIST_OBJ_NAME = (char *) "fist.obj";
static char* HEAD_OBJ_NAME = (char *) "head.obj";
static char *FOOT_OBJ_NAME = (char *) "foot.obj";
static char *FOREARM_OBJ_NAME = (char *) "forearm.obj";


static const GLfloat NO_VECTOR3[3] ={0,0,0};
static const GLfloat NECK_TRANSLATE_1[3] ={0,1.5,0};
static const GLfloat NECK_TRANSLATE_2[3] ={0,6.5,0};

static const GLfloat HEAD_TRANSLATE[3] ={0,4,0};

static const GLfloat UPPER_ARM_TRANSLATE_1[3] ={0,-4.25,0};
static const GLfloat LEFT_UPPER_ARM_TRANSLATE_2[3] ={-4.75,6.5,0};
static const GLfloat RIGHT_UPPER_ARM_TRANSLATE_2[3] ={4.75,6.5,0};

static const GLfloat FOREARM_TRANSLATE_1[3] ={0,-4,0};
static const GLfloat FOREARM_TRANSLATE_2[3] ={0,-4,0};

static const GLfloat FIST_TRANSLATE_1[3] ={0,-0.75,0};
static const GLfloat FIST_TRANSLATE_2[3] ={0,-2.8,-0.3};

static const GLfloat THIGH_TRANSLATE_1[3] ={0,-4.5,0};
static const GLfloat LEFT_THIGH_TRANSLATE_2[3] ={-2,-6,0};
static const GLfloat RIGHT_THIGH_TRANSLATE_2[3] ={2,-6,0};

static const GLfloat CALF_TRANSLATE_1[3] ={0,-4.25,0};
static const GLfloat CALF_TRANSLATE_2[3] ={0,-4.25,0};

static const GLfloat FOOT_TRANSLATE_1[3] ={0,-0.2,-1};
static const GLfloat FOOT_TRANSLATE_2[3] ={0,-4.5,0};

void DrawLinks::prepareLinks(Part **links) {
    // load obj files and create Part instances
    GLuint torsoObjID = SimpleObjLoader::loadObj(TORSO_OBJ_NAME, 1, 1.0);
    links[0] = new Part(1, torsoObjID, (GLfloat *) NO_VECTOR3, (GLfloat *) NO_VECTOR3, nullptr);
    GLuint thighObjID = SimpleObjLoader::loadObj(THIGH_OBJ_NAME, 2, 1.0);
    links[1] = new Part(2, thighObjID, (GLfloat *) THIGH_TRANSLATE_1, (GLfloat *) LEFT_THIGH_TRANSLATE_2,links[0]);
    links[2] = new Part(3, thighObjID, (GLfloat *) THIGH_TRANSLATE_1, (GLfloat *) RIGHT_THIGH_TRANSLATE_2,links[0]);
    GLuint calfObjID = SimpleObjLoader::loadObj(CALF_OBJ_NAME, 3, 1.0);
    links[3] = new Part(4, calfObjID, (GLfloat *) CALF_TRANSLATE_1, (GLfloat *) CALF_TRANSLATE_2, links[1]);
    links[4] = new Part(5, calfObjID, (GLfloat *) CALF_TRANSLATE_1, (GLfloat *) CALF_TRANSLATE_2, links[2]);
    GLuint footObjID = SimpleObjLoader::loadObj(FOOT_OBJ_NAME, 4, 1.0);
    links[5] = new Part(6, footObjID, (GLfloat *) FOOT_TRANSLATE_1, (GLfloat *) FOOT_TRANSLATE_2, links[3]);
    links[6] = new Part(7, footObjID, (GLfloat *) FOOT_TRANSLATE_1, (GLfloat *) FOOT_TRANSLATE_2, links[4]);

    GLuint neckObjID = SimpleObjLoader::loadObj(NECK_OBJ_NAME, 5, 1.0);
    links[7] = new Part(8, neckObjID, (GLfloat *) NECK_TRANSLATE_1, (GLfloat *) NECK_TRANSLATE_2, links[0]);

    GLuint headObjID = SimpleObjLoader::loadObj(HEAD_OBJ_NAME, 5, 1.0);
    links[8] = new Part(9, headObjID, (GLfloat *) HEAD_TRANSLATE, (GLfloat *) NO_VECTOR3, links[7]);

    GLuint upperArmObjID = SimpleObjLoader::loadObj(UPPER_ARM_OBJ_NAME, 5, 1.0);
    links[9] = new Part(10, upperArmObjID,
                        (GLfloat *) UPPER_ARM_TRANSLATE_1, (GLfloat *) LEFT_UPPER_ARM_TRANSLATE_2, links[0]);
    links[10] = new Part(11, upperArmObjID,
                         (GLfloat *) UPPER_ARM_TRANSLATE_1, (GLfloat *) RIGHT_UPPER_ARM_TRANSLATE_2, links[0]);

    GLuint foreArmObjID = SimpleObjLoader::loadObj(FOREARM_OBJ_NAME, 5, 1.0);
    links[11] = new Part(12, foreArmObjID,
                         (GLfloat *) FOREARM_TRANSLATE_1, (GLfloat *) FOREARM_TRANSLATE_2, links[9]);
    links[12] = new Part(13, foreArmObjID,
                         (GLfloat *) FOREARM_TRANSLATE_1, (GLfloat *) FOREARM_TRANSLATE_2, links[10]);

    GLuint fistObjID = SimpleObjLoader::loadObj(FIST_OBJ_NAME, 5, 1.0);
    links[13] = new Part(14, fistObjID, (GLfloat *) FIST_TRANSLATE_1, (GLfloat *) FIST_TRANSLATE_2, links[11]);
    links[14] = new Part(15, fistObjID, (GLfloat *) FIST_TRANSLATE_1, (GLfloat *) FIST_TRANSLATE_2, links[12]);
    // Create the menu structure and attach it to the right mouse button

}


/***
 * generate the transformation matrices for every link (torso, tighs, calfs) w.r.t. world space, then draw them
 * As taught in the lecture, the transformation for a non-root link is the product of 4 matrices.
 */
void DrawLinks::drawLinks(Part **parts, GLfloat * rootQuat, GLfloat * rootTrans, bool isKeyFraming) {
    int i;
    GLfloat * combinedTransformation;
    for (i = 0; i < 15; i++) {
        combinedTransformation = (GLfloat [16]){1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
        glPushMatrix();

        if (parts[i]->parent != nullptr) {
            //finally, go with parent
            RotationHelper::rightDotProduct(combinedTransformation, parts[i]->parent->combinedTransformation);
            //third, move the part to the appropriate position w.r.t parent
            RotationHelper::rightDotProduct(combinedTransformation, parts[i]->secondAlignFlatMatrix);
            //second, local rotate
            RotationHelper::rightDotProduct(combinedTransformation,
                                            RotationHelper::generateFlattenedTransformationMatrix(
                                                    parts[i]->localRotation, nullptr, false));
            //first, move w.r.t parent to align axis
            RotationHelper::rightDotProduct(combinedTransformation, parts[i]->firstAlignFlatMatrix);
            parts[i]->setCombinedTransitions(combinedTransformation);

        } else {
            if (!isKeyFraming) {
                combinedTransformation = RotationHelper::generateFlattenedTransformationMatrix(
                        parts[i]->localRotation, parts[i]->localTranslation, false);
                parts[i]->setCombinedTransitions(combinedTransformation);
            } else{
                combinedTransformation = RotationHelper::
                generateFlattenedTransformationMatrix(rootQuat, rootTrans, true);
                parts[i]->setCombinedTransitions(combinedTransformation);
            }

        }
        glMultMatrixf(combinedTransformation);
        glCallList(parts[i]->objListID);
        glPopMatrix();
    }
}
