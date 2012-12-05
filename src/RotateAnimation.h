/*
 * RotateAnimation.h
 */

#ifndef ROTATEANIMATION_H_
#define ROTATEANIMATION_H_
#include "Animation.h"
#include <iostream>
#define PI 3.14159265

class RotateAnimation: public Animation {
private:
	unsigned int finalTime;
	unsigned int timeInterval;
	double delta_rotate;
	float angle;
public:
	RotateAnimation(GraphNode * _node,long _span, float _angle);
	void velocityCalcAng();
	void animate();
	void endTimeCondition();
	void updateTime(long time);
	virtual ~RotateAnimation(){};
};

#endif /* ROTATEANIMATION_H_ */
