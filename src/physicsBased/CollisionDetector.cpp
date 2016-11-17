//
// Created by Qichen on 11/12/16.
//


#include "CollisionDetector.h"


const int CollisionDetector::NUMBER_OF_WALLS = 6;
const int CollisionDetector::X_DIRECTION = 0;
const int CollisionDetector::Y_DIRECTION = 1;
const int CollisionDetector::Z_DIRECTION = 2;
const GLfloat CollisionDetector::ratio = 0.8;
/***
 *
 * @param all - all[0,1,2,3,4,5] are walls (right, left, top, bottom, near, rear)
 * @param numberOfObjects
 */
void CollisionDetector::detectAll(Object **all, int numberOfObjects) {
    int i,j;
    Ball * b1, * b2;
    for(i = NUMBER_OF_WALLS; i < numberOfObjects; i++){
        b1 = (Ball *) all[i];
        for (j = 0; j < i; j++){
            //detecting if collision with a wall
            if (all[j]->isFixed){
                switch (j) {
                    case 0:
                        if(all[j]->getX() - b1->getX() <= b1->radius && b1->getVelocityIn(X_DIRECTION) > 0){
                            b1->reverseVelocity(b1->velocity);
                        }
                        break;
                    case 1:
                        if(b1->getX() - all[j]->getX() <= b1->radius && b1->getVelocityIn(X_DIRECTION) < 0){
                            b1->reverseVelocity(b1->velocity);
                        }
                        break;
                    case 2:
                        if(all[j]->getY() - b1->getY() <= b1->radius && b1->getVelocityIn(Y_DIRECTION) > 0){
                            b1->reverseVelocity(b1->velocity+1);
                        }
                        break;
                    case 3:
                        if(b1->getY() - all[j]->getY() <= b1->radius && b1->getVelocityIn(Y_DIRECTION) < 0){
                            b1->reverseVelocity(b1->velocity+1);
                        }
                        break;
                    case 4:
                        if(all[j]->getZ() - b1->getZ() <= b1->radius && b1->getVelocityIn(Z_DIRECTION) > 0){
                            b1->reverseVelocity(b1->velocity+2);
                        }
                        break;
                    case 5:
                        if(b1->getZ() - all[j]->getZ() <= b1->radius && b1->getVelocityIn(Z_DIRECTION) < 0){
                            b1->reverseVelocity(b1->velocity+2);
                        }
                        break;
                    default:
                        break;
                }

            } else{ //detecting if collision with another ball
                if(i == j) {
                    continue;
                }
                b2 = ((Ball *) all[j]);
                if(Geometry::getDistance(b1->getTranslation(), b2->getTranslation())
                        < b1->radius +  b2->radius) {
                    //TODO fix this

                }
            }
        }
    }
}
