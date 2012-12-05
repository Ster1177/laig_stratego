/*
 * Shader.cpp
 */

#include "Shader.h"
	//	 heightmap, texturemap, fragmentshader, vertexshader;

Shader::Shader(string heightmap, string texturemap, string fragmentshader, string vertexshader) {
//		init("shaders/textureDemo2.vert", "shaders/textureDemo2.frag");

	cout << endl << heightmap << endl;
	cout << texturemap << endl;
	cout << fragmentshader << endl;
	cout << vertexshader << endl<< "FUUUUUU" <<endl;

			init((const char*) vertexshader.c_str(), (const char*)fragmentshader.c_str());
			cout << 1;
	CGFshader::bind();

		// Initialize parameter in memory
		normScale=4.0;


		// Store Id for the uniform "normScale", new value will be stored on bind()
		scaleLoc = glGetUniformLocation(id(), "normScale");
		cout << 2;
//		baseTexture=new CGFtexture("textures/HuntersTown.png");
//		secTexture=new CGFtexture("textures/HuntersTown_tex.jpg");
		baseTexture = new CGFtexture(heightmap);
		secTexture =  new CGFtexture(texturemap);
		cout << 3;
		// get the uniform location for the sampler
		baseImageLoc = glGetUniformLocation(id(), "baseImage");
		cout << 4;
		// set the texture id for that sampler to match the GL_TEXTUREn that you
		// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
		glUniform1i(baseImageLoc, 0);
		cout << 5;
		// repeat if you use more textures in your shader(s)
		secImageLoc = glGetUniformLocation(id(), "secondImage");
		glUniform1i(secImageLoc, 1);
		cout << 6;

}
void Shader::bind(){

	CGFshader::bind();

	// update uniforms
	glUniform1f(scaleLoc, normScale);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	baseTexture->apply();

	// do the same for other textures
	glActiveTexture(GL_TEXTURE1);

	secTexture->apply();

	glActiveTexture(GL_TEXTURE0);

}
Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

