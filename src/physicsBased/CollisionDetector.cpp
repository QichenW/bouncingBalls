//
// Created by Qichen on 11/12/16.
//


#include "CollisionDetector.h"


const int CollisionDetector::NUMBER_OF_WALLS = 6;
const int CollisionDetector::X_DIRECTION = 0;
const int CollisionDetector::Y_DIRECTION = 1;
const int CollisionDetector::Z_DIRECTION = 2;
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
                            fakeTheRotation(b1, 0);
                        }
                        break;
                    case 1:
                        if(b1->getX() - all[j]->getX() <= b1->radius && b1->getVelocityIn(X_DIRECTION) < 0){
                            b1->reverseVelocity(b1->velocity);
                            fakeTheRotation(b1, 0);
                        }
                        break;
                    case 2:
                        if(all[j]->getY() - b1->getY() <= b1->radius && b1->getVelocityIn(Y_DIRECTION) > 0){
                            b1->reverseVelocity(b1->velocity+1);
                            fakeTheRotation(b1, 1);
                        }
                        break;
                    case 3:
                        if(b1->getY() - all[j]->getY() <= b1->radius && b1->getVelocityIn(Y_DIRECTION) < 0){
                            b1->reverseVelocity(b1->velocity+1);
                            //TODO test this; Hitting the floor only change the rotation about x and z axes
                            fakeTheRotation(b1, 1);
                        }
                        break;
                    case 4:
                        if(all[j]->getZ() - b1->getZ() <= b1->radius && b1->getVelocityIn(Z_DIRECTION) > 0){
                            b1->reverseVelocity(b1->velocity+2);
                            fakeTheRotation(b1, 2);
                        }
                        break;
                    case 5:
                        if(b1->getZ() - all[j]->getZ() <= b1->radius && b1->getVelocityIn(Z_DIRECTION) < 0){
                            b1->reverseVelocity(b1->velocity+2);
                            fakeTheRotation(b1, 2);
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
                    applyConservationLawForVelos(b1, b2);
                }
            }
        }
    }
}
/***
 * Hard coded laws of conservation (momentum & Kinetic energy) to update velocities
 * @param b1 a ball
 * @param b2 another ball
 */
void CollisionDetector::applyConservationLawForVelos(Ball *b1, Ball *b2) {
    //TODO fix this
    GLfloat unchangedPortion1[3], unchangedPortion2[3];
    GLfloat changingPortion1Before[3], changingPortion2Before[3];
    GLfloat changingPortion1After[3], changingPortion2After[3];
    GLfloat momentum[3], energy[3];

    Geometry::getDirectionOfCollision(b1->directionOfCollision,b2->directionOfCollision,
                                      b1->getTranslation(), b2->getTranslation());
    //Find the portion of velocity to be changed according to law of conservation
    Geometry::getProjection(changingPortion1Before, b1->velocity, b1->directionOfCollision);
    Geometry::getProjection(changingPortion2Before, b2->velocity, b2->directionOfCollision);
    //get the unchanging portion
    int i;
    for(i = 0; i < 3; i++){
        unchangedPortion1[i] = b1->velocity[i] - changingPortion1Before[i];
        unchangedPortion2[i] = b2->velocity[i] - changingPortion2Before[i];

        momentum[i] = changingPortion1Before[i] * b1->mass + changingPortion2Before[i] * b2->mass;
        energy[i] = (GLfloat) (0.5 * powf(changingPortion1Before[i], 2) * b1->mass +
                        0.5 * powf(changingPortion2Before[i],2)* b2->mass);
    }
    // a, b, c as in ax^2 +bx + c = 0
    GLfloat a,b,c, delta,result1, result2, m1tom2Ratio = b1->mass/b2->mass;
    a = b1->mass/2 * (1+m1tom2Ratio);
    //slove for new vx,vy,vz, and assign new velocities to balls
    for(i = 0; i < 3; i++){
        b = -1 * m1tom2Ratio * momentum[i];
        c = 1 / 2 / b2->mass * powf(momentum[i],2) - energy[i];
        delta = powf(b,2) -4 * a * c;
        if(delta < 0){
            //TODO throw exception
            cout<< "b^2 - 4ac < 0"<<endl;
        }
        result1 = (-1 * b + sqrtf(delta))/2/a;
        result2 = (-1 * b - sqrtf(delta))/2/a;

        changingPortion1After[i] = (fabs(result1 - changingPortion1Before[i])
                                    > fabs(result2 - changingPortion1Before[i])) ? result1 :result2;
        changingPortion2After[i] = (momentum[i] - b1->mass * changingPortion1After[i])/ b2->mass;

        b1->velocity[i] = unchangedPortion1[i] + changingPortion1After[i];
        b2->velocity[i] = unchangedPortion2[i] + changingPortion2After[i];
    }

}

/***
 * fake the rotation when the ball hit 1 of the 6 walls
 * based on the relative velocity w.r.t. one of the three axes
 * v = rω (beware the positive direction of rotation about each axes)
 * @param ball
 * @param hitInTheDirectionOfWhichAxe 0 - x/1 - y/ 2 - z
 */
void CollisionDetector::fakeTheRotation(Ball *ball, int hitInTheDirectionOfWhichAxe) {
    switch(hitInTheDirectionOfWhichAxe) {
        case 0:
            ball->angluarVelo[1] = -57 * ball->velocity[2] / ball->radius;
            ball->angluarVelo[2] = -57 * ball->velocity[0] / ball->radius;
            break;
        case 1:
            ball->angluarVelo[0] = 57 * ball->velocity[2] / ball->radius;
            ball->angluarVelo[2] = -57 * ball->velocity[0] / ball->radius;
            break;
        case 2:
            ball->angluarVelo[0] = 57 * ball->velocity[2] / ball->radius;
            ball->angluarVelo[1] = 57 * ball->velocity[0] / ball->radius;
            break;
        default:
            break;
    }
}
