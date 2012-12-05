

#ifndef CAMERAS_H_
#define CAMERAS_H_

#include "cgf/CGFcamera.h"
#include "parser.h"
#include <string>

using namespace std;

class Cameras: public CGFcamera {
private:
	string id;
	string type;
	double near;
	double far;
	double angle;
	double from[3];
	double to[3];
	double left;
	double right;
	double top;
	double bottom;
public:
	static string initial;
	Cameras(elem* cam);
	Cameras(elemContainer* cam);
	void setInitial(elem * root);
	void applyView();
	virtual ~Cameras();
	void updateProjectionMatrix(int w, int h);
};

#endif /* CAMERAS_H_ */
