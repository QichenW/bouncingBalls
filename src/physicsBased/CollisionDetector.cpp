//
// Created by Qichen on 11/12/16.
//


#include "CollisionDetector.h"


const int CollisionDetector::NUMBER_OF_WALLS = 6;
const int CollisionDetector::X_DIRECTION = 0;
const int CollisionDetector::Y_DIRECTION = 1;
const int CollisionDetector::Z_DIRECTION = 2;
const GLfloat CollisionDetector::ratio = 0.9;
/***
 *
 * @param all - all[0,1,2,3,4,5] are walls (right, left, top, bottom, near, rear)
 * @param numberOfObjects
 */
void CollisionDetector::detectAll(Object **all, int numberOfObjects) {
    int i,j;
    for(i = NUMBER_OF_WALLS; i < numberOfObjects; i++){
        for (j = 0; j < numberOfObjects; j++){
            //detecting if collision with a wall
            if (all[j]->isFixed){
                switch (j) {
                    case 0:
                        if(all[j]->getX() - all[i]->getX() <= ((Ball *) all[i])->radius
                                && ((Ball *) all[i])->getVelocityIn(X_DIRECTION) > 0){
                            ((Ball *) all[i])->reverseVelocity(X_DIRECTION,ratio);
                        }
                        break;
                    case 1:
                        if(all[i]->getX() - all[j]->getX() <= ((Ball *) all[i])->radius
                                && ((Ball *) all[i])->getVelocityIn(X_DIRECTION) < 0){
                            ((Ball *) all[i])->reverseVelocity(X_DIRECTION,ratio);
                        }
                        break;
                    case 2:
                        if(all[j]->getY() - all[i]->getY() <= ((Ball *) all[i])->radius
                                && ((Ball *) all[i])->getVelocityIn(Y_DIRECTION) > 0){
                            ((Ball *) all[i])->reverseVelocity(Y_DIRECTION,ratio);
                        }
                        break;
                    case 3:
                        if(all[i]->getY() - all[j]->getY() <= ((Ball *) all[i])->radius
                                && ((Ball *) all[i])->getVelocityIn(Y_DIRECTION) < 0){
                            ((Ball *) all[i])->reverseVelocity(Y_DIRECTION,ratio);
                        }
                        break;
                    case 4:
                        if(all[j]->getZ() - all[i]->getZ() <= ((Ball *) all[i])->radius
                                && ((Ball *) all[i])->getVelocityIn(Z_DIRECTION) > 0){
                            ((Ball *) all[i])->reverseVelocity(Z_DIRECTION,ratio);
                        }
                        break;
                    case 5:
                        if(all[i]->getZ() - all[j]->getZ() <= ((Ball *) all[i])->radius
                                && ((Ball *) all[i])->getVelocityIn(Z_DIRECTION) < 0){
                            ((Ball *) all[i])->reverseVelocity(Z_DIRECTION,ratio);
                        }
                        break;
                    default:
                        break;
                }

            } else{ //detecting if collision with another ball
                if(Geometry::getDistance(all[i]->getTranslation(), all[j]->getTranslation())
                        < ((Ball *) all[i])->radius +  ((Ball *) all[j])->radius) {
                    //TODO fix this

                }
            }
        }
    }
}
