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
    Ball * b;
    for(i = NUMBER_OF_WALLS; i < numberOfObjects; i++){
        b = (Ball *) all[i];
        for (j = 0; j < numberOfObjects; j++){
            //detecting if collision with a wall
            if (all[j]->isFixed){
                switch (j) {
                    case 0:
                        if(all[j]->getX() - b->getX() <= b->radius && b->getVelocityIn(X_DIRECTION) > 0){
                            b->reverseVelocity(b->velocity);
                        }
                        break;
                    case 1:
                        if(b->getX() - all[j]->getX() <= b->radius && b->getVelocityIn(X_DIRECTION) < 0){
                            b->reverseVelocity(b->velocity);
                        }
                        break;
                    case 2:
                        if(all[j]->getY() - b->getY() <= b->radius && b->getVelocityIn(Y_DIRECTION) > 0){
                            b->reverseVelocity(b->velocity+1);
                        }
                        break;
                    case 3:
                        if(b->getY() - all[j]->getY() <= b->radius && b->getVelocityIn(Y_DIRECTION) < 0){
                            b->reverseVelocity(b->velocity+1);
                        }
                        break;
                    case 4:
                        if(all[j]->getZ() - b->getZ() <= b->radius && b->getVelocityIn(Z_DIRECTION) > 0){
                            b->reverseVelocity(b->velocity+2);
                        }
                        break;
                    case 5:
                        if(b->getZ() - all[j]->getZ() <= b->radius && b->getVelocityIn(Z_DIRECTION) < 0){
                            b->reverseVelocity(b->velocity+2);
                        }
                        break;
                    default:
                        break;
                }

            } else{ //detecting if collision with another ball
                if(Geometry::getDistance(b->getTranslation(), all[j]->getTranslation())
                        < b->radius +  ((Ball *) all[j])->radius) {
                    //TODO fix this

                }
            }
        }
    }
}
