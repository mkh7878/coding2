/*
 *  boid.cpp
 *  boids
 *
 *  Created by Marco Gillies on 05/10/2010.
 *  Copyright 2010 Goldsmiths, University of London. All rights reserved.
 *
 */

#include "boid.h"
#include "ofMain.h"
#include <cmath>
//****************************************************************************************************//
Boid::Boid()
{
	separationWeight = 1.0f;
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;
	
	separationThreshold = 15;
	neighbourhoodSize = 100;
	
    //setting up random position at the beginning 
	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
	velocity = ofVec3f(ofRandom(10, 10), ofRandom(-10, 10));
}

//****************************************************************************************************//
Boid::Boid(ofVec3f &pos, ofVec3f &vel)
{
	separationWeight = 1.0f;
	cohesionWeight = 0.2f;
	alignmentWeight = 0.1f;
	
	separationThreshold = 15;
	neighbourhoodSize = 100;
	
	position = pos;
	velocity = vel;
}

Boid::~Boid()
{
}

//****************************************************************************************************//
float Boid::getSeparationWeight()
{
	return separationWeight;
}
float Boid::getCohesionWeight()
{
	return cohesionWeight;
}

float Boid::getAlignmentWeight()
{
	return alignmentWeight;
}


float Boid::getSeparationThreshold()
{
	return separationThreshold;
}

float Boid::getNeighbourhoodSize()
{
	return neighbourhoodSize;
}


void Boid::setSeparationWeight(float f)
{
	separationWeight = f;
}
void Boid::setCohesionWeight(float f)
{
	cohesionWeight = f;
}

void Boid::setAlignmentWeight(float f)
{
	alignmentWeight = f;
}


void Boid::setSeparationThreshold(float f)
{
	separationThreshold = f;
}

void Boid::setNeighbourhoodSize(float f)
{
	neighbourhoodSize = f;
}


ofVec3f Boid::getPosition()
{
	return position;
}

ofVec3f Boid::getVelocity()
{
	return velocity;
}
//****************************************************************************************************//
ofVec3f Boid::separation(std::vector<Boid *> &otherBoids)
{
	// finds the first collision and avoids that
	// should probably find the nearest one
	// can you figure out how to do that?
    
    //two for loops
    //for any particular boid looks at position value for every other instance using nested for loops
    
	for (int i = 0; i < otherBoids.size(); i++)
	{	
		if(position.distance(otherBoids[i]->getPosition()) < separationThreshold) //if distance betwen current boid and original
		{
			ofVec3f v = position -  otherBoids[i]->getPosition(); //if below threshhold, the current boid subtracts a=a-b from each xyz to send it in the opposite direction
			v.normalize(); //getting unit vector - if you were to just flip it and go much faster in the other direction (the actual distance they go is restricted to 1 every frame
			return v; //returns normalised vector
		}
	}
    
    ofVec3f returnValue;
    return returnValue;
}

//****************************************************************************************************//
//calculating the average position of flock

ofVec3f Boid::cohesion(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize) //only if the target boid is farther than a specific threshold it will not be in the average
            //neighbourhoodSize means they only travel towards flock (not free roaming boids)
		{
			average += otherBoids[i]->getPosition();
			count += 1;
		}
	}
	average /= count;//only averages the boids in the flock
	ofVec3f v =  average - position;
	v.normalize();
	return v;//returns normalised vector
}

//****************************************************************************************************//
//works for the flock as a whole
//creates average of expected position of all boids around it will be added to current position
//where the flock is on average traveling


ofVec3f Boid::alignment(std::vector<Boid *> &otherBoids) //if a boid is within threshold of other boid it will influence
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count; //calculating same average as cohesion (using the same threshold)
	ofVec3f v =  average - velocity;
	v.normalize();
	return v;
}

//****************************************************************************************************//
void Boid::update(std::vector<Boid *> &otherBoids, ofVec3f &min, ofVec3f &max)
{
    //the target position is an average of what is happening through separation, cohesion and alignment
    //all 3 forces are acting on the boid
    velocity += separationWeight*separation(otherBoids);
	velocity += cohesionWeight*cohesion(otherBoids);
	velocity += alignmentWeight*alignment(otherBoids);
	
	walls(min, max);
	position += velocity;
}

//****************************************************************************************************//
void Boid::walls(ofVec3f &min, ofVec3f &max)
{
	if (position.x < min.x){
		position.x = min.x;
		velocity.x *= -1;
	} else if (position.x > max.x){
		position.x = max.x;
		velocity.x *= -1;
	}
	
	if (position.y < min.y){
		position.y = min.y;
		velocity.y *= -1;
	} else if (position.y > max.y){
		position.y = max.y;
		velocity.y *= -1;
	}
	
}


//void Boid::checkFishCollision(std::vector<Fish*> &fishes) {
//    for (int i = 0; i < fishes.size(); i++) {
//        if (position.distance(fishes[i]->getPosition()) < 10) {
//            fishCollision = true;
//            break;
//        }
//    }
//}
//****************************************************************************************************//

void Boid::draw()
{
	ofSetColor((int (round(position.y)) % 255), (int (round(position.x)) % 150), 100);
	ofCircle(position.x, position.y, 5);
}



//****************************************************************************************************//
//****************************************************************************************************//
//****************************************************************************************************//
//****************************************************************************************************//
//****************************************************************************************************//

Fish::Fish()
{
    separationWeight = 1.0f;
    cohesionWeight = 0.2f;
    alignmentWeight = 0.1f;
    
    separationThreshold = 15;
    neighbourhoodSize = 100;
    
    //setting up random position at the beginning
    position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
    velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));
}

//****************************************************************************************************//
Fish::Fish(ofVec3f &pos, ofVec3f &vel)
{
    separationWeight = 1.0f;
    cohesionWeight = 0.2f;
    alignmentWeight = 0.1f;
    
    separationThreshold = 15;
    neighbourhoodSize = 100;
    
    position = pos;
    velocity = vel;
}

Fish::~Fish()
{
}

//****************************************************************************************************//
ofVec3f Fish::separation(std::vector<Fish *> &otherFish)
{
    // finds the first collision and avoids that
    // should probably find the nearest one
    // can you figure out how to do that?

    //two for loops
    //for any particular boid looks at position value for every other instance using nested for loops

    for (int i = 0; i < otherFish.size(); i++)
    {
        if(position.distance(otherFish[i]->getPosition()) < separationThreshold) //if distance betwen current boid and original
        {
            ofVec3f v = position -  otherFish[i]->getPosition(); //if below threshhold, the current boid subtracts a=a-b from each xyz to send it in the opposite direction
            v.normalize(); //getting unit vector - if you were to just flip it and go much faster in the other direction (the actual distance they go is restricted to 1 every frame
            return v; //returns normalised vector
        }
    }

    ofVec3f returnValue;
    return returnValue;
}


//****************************************************************************************************//
ofVec3f Fish::cohesion(std::vector<Fish *> &otherFish)
{
    ofVec3f average(0,0,0);
    int count = 0;
    for (int i = 0; i < otherFish.size(); i++)
    {
        if (position.distance(otherFish[i]->getPosition()) < neighbourhoodSize)
        {
            average += otherFish[i]->getPosition();
            count += 1;
        }
    }
    average /= count;
    ofVec3f v =  average - position;
    v.normalize();
    return v;
}
//****************************************************************************************************//
ofVec3f Fish::alignment(std::vector<Fish *> &otherFish)
{
    ofVec3f average(0,0,0);
    int count = 0;
    for (int i = 0; i < otherFish.size(); i++)
    {
        if (position.distance(otherFish[i]->getPosition()) < neighbourhoodSize)
        {
            average += otherFish[i]->getVelocity();
            count += 1;
        }
    }
    average /= count;
    ofVec3f v =  average - velocity;
    v.normalize();
    return v;
}
//****************************************************************************************************//
void Fish::update(std::vector<Fish *> &otherFish, ofVec3f &min, ofVec3f &max)
{

    
    velocity += separationWeight*separation(otherFish);
    velocity += cohesionWeight*cohesion(otherFish);
    velocity += alignmentWeight*alignment(otherFish);
    
    walls(min, max);
    position += velocity;
}

//void Fish::colour(){
//    if
//}
//****************************************************************************************************//
void Fish::draw()
{
    ofSetColor(255, 255, 255);
    ofCircle(position.x, position.y, 3);
}
