/*
 * PolyLineAnimation.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: ster
 */
#include "PolyLineAnimation.h"
#include "RotateAnimation.h"
#include <cmath>
PolyLineAnimation::PolyLineAnimation(){
    anims.clear();
}

void PolyLineAnimation::addAnimation(Animation * la){
	RotateAnimation * rot;


	if(anims.size() == 0){
		float p[2] = {0,1};
		float ang = this->getAngle(p,la->xyzi,la->xyzf);
		rot = new RotateAnimation(la->node, 3, ang);
		anims.push_back(rot);
	} else {
		float p[2] = { anims.back()->xyzf[0],anims.back()->xyzf[1]};
		float ang = this->getAngle(p,la->xyzi,la->xyzf);
		rot = new RotateAnimation(la->node, 3, ang);
		anims.push_back(rot);
	}
//	float deltaX = la->xyzf[0]-la->xyzi[0];
//	float deltaY = la->xyzf[1]-la->xyzi[1];

    anims.push_back(la);
}

float PolyLineAnimation::getAngle(float * a, float * b,float * c){
	float angle;
	float ab[2] =  {b[0] - a[0], b[1] - a[1]};
	float bc[2] =  {c[0] - b[0], c[1] - b[1]};

	angle = atan(sqrt(ab[0]*ab[0]+ab[1]*ab[1])/sqrt(bc[0]*bc[0] + bc[1]*bc[1]));
	angle = angle*180/M_PI;

	return angle;
}

vector<Animation*>  PolyLineAnimation::getAnimations(){
  return anims;
}

