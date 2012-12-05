/*
 * RotateAnimation.cpp
 *
 *  Created on: Nov 11, 2012
 *      Author: ster
 */

#include "RotateAnimation.h"

using namespace std;

RotateAnimation::RotateAnimation(GraphNode * _node, long _span, float _angle):Animation(node,span){
	this->span = _span*1000;
	this->node = _node;
	this->time = 0;
	this->finalTime = 0;
	this->timeInterval = 0;
	delta_rotate = 0;
	this->angle = _angle; cout << "angle = " << this->angle << " _angle = " << _angle << endl;

}

void RotateAnimation::velocityCalcAng(){
	span -= timeInterval;
	delta_rotate = (double) (angle/span)*timeInterval ;
}

void RotateAnimation::endTimeCondition(){
	if( span <= 0){
		end = true; cout << " end is here!!\n\n";
		delta_rotate += (angle - delta_rotate);
	}
}

void RotateAnimation::animate(){
	angle -= delta_rotate;
	cout << "angle = " << angle << endl;
	node->Orientate(delta_rotate);
}

void RotateAnimation::updateTime(long _time){
	if(!end) {
		this->finalTime = this->time;
		this->time = _time;
		timeInterval = this->time - finalTime;

		this->velocityCalcAng();cout << timeInterval << " = " << this->time << " - " << finalTime << endl;
		this->endTimeCondition();cout << timeInterval << " = " << this->time << " - " << finalTime << endl;
		this->animate();cout << timeInterval << " = " << this->time << " - " << finalTime << endl;
	}
}
