/*
 * PolyLineAnimation.h
 *
 *  Created on: Nov 9, 2012
 *      Author: ster
 */

#ifndef POLYLINEANIMATION_H_
#define POLYLINEANIMATION_H_
#include "LineAnimation.h"

class PolyLineAnimation {
private:
  vector<Animation*> anims;
public:
  float ang;
  PolyLineAnimation();
  void addAnimation(Animation * la);
  float getAngle(float*,float*,float*);
  vector<Animation*> getAnimations();
};


#endif /* POLYLINEANIMATION_H_ */
