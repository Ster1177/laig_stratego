/*
 * LineAnimation.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: ster
 */
#include "LineAnimation.h"
#include <iostream>
//Variaveis para a animação

int duration = 0;
#define MOVEMENT_SPEED  3  // unidades de comprimento por segundo

LineAnimation::LineAnimation(float xi, float yi, float zi, float xf, float yf, float zf, GraphNode * _node, long  _span)
:Animation(node,span)
{
	distX = xf - xi;
	distY = yf - yi;
	distZ = zf - zi;
	xyzi[0] = xi;  xyzi[1] = yi;
	xyzf[0] = xf;  xyzi[1] = yf;
	end = false;
	this->time = 0;
	this->finalTime = 0;
	this->timeInterval = 0;
	this->span = _span*1000;
	this->node = _node;
}

void LineAnimation::velocityCalc(){
	span -= timeInterval;

	delta_translateX = (double) (distX/span) * timeInterval;
	delta_translateY = (double) (distY/span) * timeInterval;
	delta_translateZ = (double) (distZ/span) * timeInterval;
}

void LineAnimation::endTimeCondition(){
	if( span <= 0){
		end = true; cout << " end is here!!\n\n";
	}
}

void LineAnimation::animate(){
	distX -= delta_translateX;
	distY -= delta_translateY;
	distZ -= delta_translateZ;

	node->translate(delta_translateX,delta_translateY,delta_translateZ);
}

void LineAnimation::updateTime(long _time){
	if(!end) {
		this->finalTime = this->time;
		this->time = _time;
		timeInterval = this->time - finalTime;
		this->velocityCalc();
		this->endTimeCondition();
		this->animate();
	}
}



