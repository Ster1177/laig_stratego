/*
 * LineAnimation.h
 *
 *  Created on: Nov 7, 2012
 *      Author: ster
 */

#ifndef LINEANIMATION_H_
#define LINEANIMATION_H_
#include "Animation.h"
#include "GraphNode.h"

using namespace std;

class LineAnimation: public Animation {
private:
	double delta_translateX, delta_translateY, delta_translateZ;
	double obj_translateX, obj_translateY, obj_translateZ;
	double distX,distY,distZ;
	unsigned int finalTime;
	unsigned int timeInterval;
public:
	LineAnimation(float,float,float,float,float,float,GraphNode*,long);
	void velocityCalc();
	void animate();
	void endTimeCondition();
	void updateTime(long time);
};


#endif /* LINEANIMATION_H_ */
