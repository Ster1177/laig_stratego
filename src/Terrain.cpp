/*
 * Terrain.cpp
 */

#include "Terrain.h"

Terrain::Terrain(elem* e){
	this->heightmap = e->attr["heightmap"];
	this->texturemap = e->attr["texturemap"];
	this->fragmentshader = e->attr["fragmentshader"];
	this->vertexshader = e->attr["vertexshader"];

	delete e;
	//	 heightmap, texturemap, fragmentshader, vertexshader;


	shader = new Shader(this->heightmap,this->texturemap,
						this->fragmentshader, this->vertexshader);
	cout << this->heightmap << endl;
	cout << this->texturemap << endl;
	cout << this->fragmentshader << endl;
	cout << this->vertexshader << endl;
	plane = new Plane(200);

}

void Terrain::draw(){

	glPushMatrix();
		glScalef(100,1,100);
		shader->bind();
		plane->draw();
		shader->unbind();
	glPopMatrix();
}


Terrain::~Terrain() {
	// TODO Auto-generated destructor stub
}

