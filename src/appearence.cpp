#include "appearence.h"
#include <sstream>
#include <GL/glut.h>
#include <iostream>
appearence::appearence(Elems *els) {
//	<emissive r="0.2" g="0.9" b="0.9" a="1" />
//	<ambient r="0.5" g="0.5" b="0.5" a="0.7" />
//	<diffuse r="0.7" g="0.7" b="0.3" a="0.8" />
//	<specular r="0" g="0.3" b="0.98" a="1" />
//	<shininess value="0.5" />
//	<texture file="tex.jpg" length_s="1" length_t="1" />

	Elems::iterator it = els->begin();

	for(; it != els->end() ; it++){
		stringstream *ss;
		float temp[4];
		if( (*it)->name == "emissive") {

			ss = new stringstream( (*it)->attr["r"]); *ss >> this->emissive[0]; delete ss;
			ss = new stringstream( (*it)->attr["g"]); *ss >> this->emissive[1]; delete ss;
			ss = new stringstream( (*it)->attr["b"]); *ss >> this->emissive[2]; delete ss;
			ss = new stringstream( (*it)->attr["a"]); *ss >> this->emissive[3]; delete ss;

		}
		else  if( (*it)->name == "ambient") {
			ss = new stringstream( (*it)->attr["r"]); *ss >> temp[0];
			delete ss;
			ss = new stringstream( (*it)->attr["g"]); *ss >> temp[1];
			delete ss;
			ss = new stringstream( (*it)->attr["b"]); *ss >> temp[2];
			delete ss;
			ss = new stringstream( (*it)->attr["a"]); *ss >> temp[3];
			delete ss;
			this->setAmbient(temp);

		}
		else  if( (*it)->name == "diffuse") {
			ss = new stringstream( (*it)->attr["r"]); *ss >> temp[0];
			delete ss;
			ss = new stringstream( (*it)->attr["g"]); *ss >> temp[1];
			delete ss;
			ss = new stringstream( (*it)->attr["b"]); *ss >> temp[2];
			delete ss;
			ss = new stringstream( (*it)->attr["a"]); *ss >> temp[3];
			delete ss;
			this->setDiffuse(temp);
		}
		else  if( (*it)->name == "specular") {
			ss = new stringstream( (*it)->attr["r"]); *ss >> temp[0];
			delete ss;
			ss = new stringstream( (*it)->attr["g"]); *ss >> temp[1];
			delete ss;
			ss = new stringstream( (*it)->attr["b"]); *ss >> temp[2];
			delete ss;
			ss = new stringstream( (*it)->attr["a"]); *ss >> temp[3];
			delete ss;
			this->setSpecular(temp);
		}
		else  if( (*it)->name == "shininess") {
			ss = new stringstream( (*it)->attr["value"]); *ss >> temp[0];
			delete ss;
			this->setShininess(temp[0]);
		}
		else  if( (*it)->name == "texture") {
			this->setTexture((*it)->attr["file"]);
			int i,j;
			ss = new stringstream( (*it)->attr["length_s"]); *ss >> i; delete ss;
			ss = new stringstream( (*it)->attr["length_t"]); *ss >> j; delete ss;

			this->setTextureWrap(i,j);
		}
		//take care of pointer..
		delete *it;
	}

	delete els;
}

void appearence::apply(){
	CGFappearance::apply();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,this->emissive);

}

appearence::~appearence() {
}

