
/*

 *
 */

#ifndef _BOID
#define _BOID
#include <vector>
#include "ofMain.h"

class Boid
{
// all the methods and variables after the
// private keyword can only be used inside
// the class
public:
	ofVec3f position;
	ofVec3f velocity; //location of boid in the next frame
    
    
	//ignore for now
	float separationWeight;
	float cohesionWeight;
	float alignmentWeight;
	
	float separationThreshold;
	float neighbourhoodSize;
    
	//all three return a vector for velocity
    //update function averages all of these values by multiplying with corresponding factor 
	ofVec3f separation(std::vector<Boid *> &otherBoids); //move boids away from each other based on position from other boids
	ofVec3f cohesion(std::vector<Boid *> &otherBoids); //any boid that is separated beyong a certain threshhold is brough back into the group
	ofVec3f alignment(std::vector<Boid *> &otherBoids); //aligns the direction of entire flock (entire flock vs. individual)
	
// all the methods and variables after the
// public keyword can only be used by anyone
	Boid();
	Boid(ofVec3f &pos, ofVec3f &vel);
	~Boid();
    
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
	
	void virtual update(std::vector<Boid *> &otherFish, ofVec3f &min, ofVec3f &max); //virtual when changing in child class
	
	void walls(ofVec3f &min, ofVec3f &max);
	
	void draw();
};


class Fish: public Boid{
    
public:
    
    //child class will not inherit constructors and destructors
    Fish();
    Fish(ofVec3f &pos, ofVec3f &vel);
    ~Fish();
    
    ofVec3f separation(std::vector<Fish *> &otherFsh);
    ofVec3f cohesion(std::vector<Fish *> &otherFish);
    ofVec3f alignment(std::vector<Fish *> &otherFish);
    ofVec3f reaction(std::vector<Boid *> &otherFish);
    
    float FishSize;
    void virtual update(std::vector<Fish *> &otherFish, ofVec3f &min, ofVec3f &max);
    void draw();
    
    
    
};

#endif
