#include "parser.h"

//opens opens file and instanciates TiXml*
LSFParser::LSFParser(string file ){

	this->doc=new TiXmlDocument( file.c_str());
	this->doc->LoadFile(file.c_str());

	this->lsfE = doc->FirstChildElement();
	assert(this->lsfE != NULL);

	this->globalsE = lsfE->FirstChildElement("globals");
	assert(this->globalsE != NULL);

	this->camerasE = lsfE->FirstChildElement("cameras");
	assert(this->camerasE != NULL);

	this->lightingE = lsfE->FirstChildElement("lighting");
	assert(this->lightingE != NULL);

	this->appearancesE = lsfE->FirstChildElement("appearances");
	assert(this->appearancesE != NULL);

	this->graphE = lsfE->FirstChildElement("graph");
	assert(this->graphE != NULL);
}


elem*  LSFParser::getElem(TiXmlElement* te){
	elem* el = new elem;

	el->name = te->Value();

	el->attr = map<string,string>();

	//save it's attributes
	for( TiXmlAttribute* at = te->FirstAttribute() ; at != NULL ; at = at->Next() )
		el->attr[at->Name()] = at->Value();

	return el;
}

//returns a list of elements
	//if filter is true it will skip siblings with childs
Elems*  LSFParser::getElems(TiXmlElement* te, bool filter=false){
	Elems* els =new Elems();
	while(te!= NULL){
		if(filter)
			if(!te->NoChildren()){
				te = te->NextSiblingElement();
				continue;
			}


		els->push_back(getElem(te));
		te = te->NextSiblingElement();
	}

	if(els->size() > 0)
		return els;
	else {
		delete els;
		return NULL;
	}
}


//return a list of elemcontainers
	//if filter is true  then skip childless elements
ElemContainers* LSFParser::getElemContainers(TiXmlElement* te, bool filter=false){
	ElemContainers* elcs = new ElemContainers();

	for(; te != NULL; te = te->NextSiblingElement()){

		if(te->NoChildren())
			continue;

		elemContainer * elc = new elemContainer;

		elc->root = getElem(te);
		elc->elems = getElems(te->FirstChildElement(),false);

		elcs->push_back(elc);
	}

	if(elcs->size() > 0)
		return elcs;
	else {
		delete elcs;
		return NULL;
	}
}

BigElemContainers* LSFParser::getBigElemContainers(TiXmlElement* te){
	BigElemContainers *belcs = new BigElemContainers();

	for(; te != NULL; te = te->NextSiblingElement()){
		bigElemContainer* belc = new bigElemContainer;

		belc->root = getElem(te);
		belc->elems = getElems(te->FirstChildElement(),true);
		belc->elemCs = getElemContainers(te->FirstChildElement(),true);

		belcs->push_back(belc);
	}

	if(belcs->size() >0)
		return belcs;
	else {
		delete belcs;
		return NULL;
	}

}



//returns an array of globals and their attributes
Elems* LSFParser::getGlobals(){

	Elems* els= getElems( this->globalsE->FirstChildElement(),false);


	return els;
}

//returns an array of cameras
	//if a camera is perpective then childelements will be
	//converted to attr. ex: elem->attr["fromx"] ...
bigElemContainer* LSFParser::getCameras(){

	//special case!!!  cannot use getBigElemContainers because it isn't a child
	bigElemContainer* bgc = new bigElemContainer;

	bgc->root = getElem(this->camerasE);
	TiXmlElement * t =this->camerasE->FirstChildElement();
	if(t != NULL)
		bgc->elems = getElems(t,true);
	else bgc->elems = NULL;

	t = this->camerasE->FirstChildElement();
	if(t != NULL)
		bgc->elemCs = getElemContainers(t,true);
	else bgc->elemCs = NULL;


	return bgc;
}

//returns lighting configurations
	//elem who's name is "config" refers to the attr of lighting
	// other elems refer to childless childs expl: <ambient r="1" g="1" b="1" a="0" />
elemContainer* LSFParser::getLightingConfig(){
	elemContainer* elc = new elemContainer;

	elc->root = getElem(this->lightingE);
	elc->elems = getElems(this->lightingE->FirstChildElement(),true);

	return elc;
}

//returns an array of array elemcontainers identified by an id
ElemContainers* LSFParser::getLights(){
	ElemContainers* elcs = getElemContainers(this->lightingE->FirstChildElement("lights")->FirstChildElement(),false);
	return elcs;
}

//returns an array of appearances each with their own elems
ElemContainers* LSFParser::getAppearences(){
	ElemContainers *elcs = getElemContainers(this->appearancesE->FirstChildElement(),false);

	return elcs;
}

//returns the graph's root id node
string LSFParser::getGraphRootId(){
	TiXmlAttribute* at = this->graphE->FirstAttribute();
	string str = at->Value();
	return str;
}

//returns array of nodes in graph
BigElemContainers* LSFParser::getGraphNodes(){
	BigElemContainers* becs = getBigElemContainers(this->graphE->FirstChildElement());
	return becs;
}

LSFParser::~LSFParser(){

	delete doc;
	delete lsfE;
	delete globalsE;
	delete camerasE;
	delete lightingE;
	delete appearancesE;
	delete graphE;

}



