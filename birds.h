//
//  birds.h
//  BoidProject
//
//  Created by Mae Horak on 30/01/2023.
//

#ifndef birds_h
#define birds_h
#include "boid.h"
#include <vector>
#include "ofMain.h"

class Birds: Boid
{
// all the methods and variables after the
// private keyword can only be used inside
// the class
private:
    ofVec3f position;
    ofVec3f velocity;
    
    float separationWeight;
    float cohesionWeight;
    float alignmentWeight;
    
    float separationThreshold;
    float neighbourhoodSize;
    
    ofVec3f separation(std::vector<Boid *> &otherBoids);
    ofVec3f cohesion(std::vector<Boid *> &otherBoids);
    ofVec3f alignment(std::vector<Boid *> &otherBoids);
    
// all the methods and variables after the
// public keyword can only be used by anyone
public:
    Birds();
    Birds(ofVec3f &pos, ofVec3f &vel);
    ~Birds();
    
    ofVec3f getPosition();
    ofVec3f getVelocity();
    
    
    float getSeparationWeight();
    float getCohesionWeight();
    float getAlignmentWeight();
    
    float getSeparationThreshold();
    float getNeighbourhoodSize();
    
    void setSeparationWeight(float f);
    void setCohesionWeight(float f);
    void setAlignmentWeight(float f);
    
    void setSeparationThreshold(float f);
    void setNeighbourhoodSize(float f);
    
    void update(std::vector<Birds *> &otherBoids, ofVec3f &min, ofVec3f &max);
    
    void walls(ofVec3f &min, ofVec3f &max);
    
    void draw();
};

#endif /* birds_h */
