#include "Light.h"
#include <sstream>
#include <GL/glut.h>

Light::Light(unsigned int lightid, elemContainer * elc) {

//	<light id="primary" enabled="true">
//		<location x="0" y="5" z="0" />
//		<ambient r="1" g="1" b="1" a="0" />
//		<diffuse r="1" g="1" b="1" a="0" />
//		<specular r="1" g="1" b="1" a="0" />
//		<!-- No caso de uma ser uma spotlight, incluir os dados abaixo; se for uma omnilight, omitir -->
//		<spot angle="45" exponent="2" dirx="45" diry="45" dirz="45" />
//	</light>


	spot = false;
	this->name_id = elc->root->attr["id"];
	switch( lightid ) {
	case 0:
		this->id = GL_LIGHT0;
		break;

	case 1:
		this->id = GL_LIGHT1;
		break;

	case 2:
		this->id = GL_LIGHT2;
		break;

	case 3:
		this->id = GL_LIGHT3;
		break;

	case 4:
		this->id = GL_LIGHT4;
		break;

	case 5:
		this->id = GL_LIGHT5;
		break;

	case 6:
		this->id = GL_LIGHT6;
		break;

	case 7:
		this->id = GL_LIGHT7;
		break;

	}



	//just initializing
	this->exponent  = new const float(-1.0);

	Elems::iterator it = elc->elems->begin();

	for(; it != elc->elems->end(); it++) {
		stringstream * ss;


		if( (*it)->name == "location") {
			ss = new stringstream( (*it)->attr["x"] ); *ss >> pos[0]; delete ss;
			ss = new stringstream( (*it)->attr["y"] ); *ss >> pos[1]; delete ss;
			ss = new stringstream( (*it)->attr["z"] ); *ss >> pos[2]; delete ss;

			//1 -> if its not a spot 0 if it is.
			pos[3] = 1.0;
		}
		else if( (*it)->name == "ambient") {
			ss = new stringstream(  (*it)->attr["r"] ); *ss >> ambient[0]; delete ss;
			ss = new stringstream(  (*it)->attr["g"] ); *ss >> ambient[1]; delete ss;
			ss = new stringstream(  (*it)->attr["b"] ); *ss >> ambient[2]; delete ss;
			ss = new stringstream(  (*it)->attr["a"] ); *ss >> ambient[3]; delete ss;

		} else if( (*it)->name == "diffuse") {
			ss = new stringstream(  (*it)->attr["r"] ); *ss >> diffuse[0]; delete ss;
			ss = new stringstream(  (*it)->attr["g"] ); *ss >> diffuse[1]; delete ss;
			ss = new stringstream(  (*it)->attr["b"] ); *ss >> diffuse[2]; delete ss;
			ss = new stringstream(  (*it)->attr["a"] ); *ss >> diffuse[3]; delete ss;

		} else if( (*it)->name == "specular") {
			ss = new stringstream(  (*it)->attr["r"] ); *ss >> specular[0]; delete ss;
			ss = new stringstream(  (*it)->attr["g"] ); *ss >> specular[1]; delete ss;
			ss = new stringstream(  (*it)->attr["b"] ); *ss >> specular[2]; delete ss;
			ss = new stringstream(  (*it)->attr["a"] ); *ss >> specular[3]; delete ss;

		} else if( (*it)->name == "spot") {
			spot = true;
			float i;
			ss = new stringstream(  (*it)->attr["angle"] ); *ss >> angle; delete ss;
			ss = new stringstream(  (*it)->attr["exponent"] ); *ss >> i; delete ss;
			delete this->exponent;
			this->exponent = new const float(i);
			ss = new stringstream(  (*it)->attr["dirx"] ); *ss >> direct[0]; delete ss;
			ss = new stringstream(  (*it)->attr["diry"] ); *ss >> direct[1]; delete ss;
			ss = new stringstream(  (*it)->attr["dirz"] ); *ss >> direct[2]; delete ss;

			//this is a spot light
			pos[3] = 0.0;
		}

		delete *it;

	}



	//after getting what is needed create the f#$% light

	if(this->spot)
		this->light = new CGFlight(this->id,pos,direct);
	else
		this->light = new CGFlight(this->id,pos);



	if( elc->root->attr["enabled"] == "true") {
		this->enabled = true;
	}
	else {
		this->enabled = false;
	}


	delete elc;


}

void Light::init(){
	this->light->disable();
	if( this->enabled)
	{
		this->light->setAmbient(ambient);
		this->light->setSpecular(specular);
		this->light->setDiffuse(diffuse);
		if(spot){
			this->light->setAngle(angle);
			glLightfv( this->id, GL_SPOT_EXPONENT, this->exponent );
		}

		this->light->enable();
	}
	else {
		this->light->disable();
	}
}

void Light::draw(){

	if(this->enabled)
		this->light->draw();
}

CGFlight* Light::getCGFlight(){
	return this->light;
}

unsigned int Light::getId(){
	return this->id;
}

string Light::getName(){
	return this->name_id;
}

bool Light::isEnabled(){
	return this->enabled;
}
void Light::setEnabled(bool a){
	this->enabled = a;
	this->init();
}

Light::~Light() {
	delete this->light;
	delete this->exponent;
}

