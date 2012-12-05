#include "Cameras.h"
#include <sstream>
#include <GL/glut.h>


//    <ortho id="primary" near="1" far="10" left="10" right="10" top="10" bottom="0" />

Cameras::Cameras(elem* cam){
	//unecessery?
	if(cam->name == "ortho"){
		this->id = cam->attr["id"];
		this->type = cam->name ;
		stringstream *ss;
		ss = new stringstream(cam->attr["near"] );
		*ss >> this->near;
		delete ss;

		ss = new stringstream(cam->attr["far"] );
		*ss >> this->far;
		delete ss;

		ss = new stringstream(cam->attr["left"] );
		*ss >> this->left;
		delete ss;

		ss = new stringstream(cam->attr["right"] );
		*ss >> this->right;
		delete ss;

		ss = new stringstream(cam->attr["top"] );
		*ss >> this->top;
		delete ss;

		ss = new stringstream(cam->attr["bottom"] );
		*ss >> this->bottom;
		delete ss;

	}

}

//    <perspective id="primary" near="1" far="10" angle="45">
//       <from x="10" y="10" z="10" />
//       <to x="0" y="0" z="0" />
//    </perspective>
//
Cameras::Cameras(elemContainer* cam){
	if( cam->root->name == "perspective"){
		this->type = "perspective";

		this->id = cam->root->attr["id"];

		stringstream *ss;

		ss = new stringstream( cam->root->attr["near"] );
		*ss >> this->near;
		delete ss;

		ss = new stringstream( cam->root->attr["far"] );
		*ss >> this->far;
		delete ss;

		ss = new stringstream( cam->root->attr["angle"] );
		*ss >> this->angle;
		delete ss;

		Elems::iterator it;
		for( it = cam->elems->begin(); it != cam->elems->end() ; it++){
			if( (*it)->name == "from"){

				ss = new stringstream( (*it)->attr["x"] );
				*ss >> this->from[0];
				delete ss;

				ss = new stringstream( (*it)->attr["y"] );
				*ss >> this->from[1];
				delete ss;

				ss = new stringstream( (*it)->attr["z"] );
				*ss >> this->from[2];
				delete ss;
			} else if( (*it)->name == "to"){

				ss = new stringstream( (*it)->attr["x"] );
				*ss >> this->to[0];
				delete ss;

				ss = new stringstream( (*it)->attr["y"] );
				*ss >> this->to[1];
				delete ss;

				ss = new stringstream( (*it)->attr["z"] );
				*ss >> this->to[2];
				delete ss;
			}

		}
	}
}

void Cameras::setInitial(elem* root){
//	Cameras::initial = root->attr["initial"];

}

void Cameras::updateProjectionMatrix(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(this->type == "ortho"){
		glOrtho(left,right,bottom,top,near,far);

	} else if(this->type == "perspective"){
		double rat = (float)w/(float)h;
		gluPerspective(angle,rat,near,far);
	}
}

void Cameras::applyView(){
	if(this->type == "perspective"){
		gluLookAt(to[0],to[1],to[2],from[0],from[1],from[2], 0.0, 1.0, 0.0);
	}
}

Cameras::~Cameras() {

}

