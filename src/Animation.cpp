/*
 * Animation.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: ster
 */
#include "Animation.h"

// declarações para animacao
double  obj_radius, obj_rotate, delta_radius, delta_rotate;
#define RADIUS_SPEED  0.4  // unidades de comprimento por segundo
#define ANGULAR_SPEED 0.5  // rotacoes por segundo

Animation::Animation(GraphNode* n, long s){
	this->node = n;
	this->span = s;
    end = false;
}

void Animation::CenterObject(){}
void Animation::myInitTransforms(unsigned int mili_secs){}
void Animation::myUpdateTransforms(){}
void Animation::myObjectTransforms(){}
void Animation::Reset(){}
void Animation::updateTime(long _time) {}
Animation::~Animation(){};

