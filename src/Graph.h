/*
 * graph.h
 *
 *  Created on: Oct 10, 2012
 *      Author: ster
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include "Terrain.h"
#include "GraphNode.h"
#include "parser.h"
#include <list>
#include "cgf/CGFappearance.h"
#include "cgf/CGFobject.h"
#include "primitives.h"
#include "Patch.h"
#include "Plane.h"
#include <string>
#include <map>
#include "appearence.h"



class Graph
{
private:
	list<GraphNode*> nodes;
	GraphNode *root;
	list<CGFappearance*> appearances;
	list<CGFobject*> objects;

	//Id Node -> lista dos noderef Ids.... and use the info to add to child in graphnode
//	void Populate_nodRef(map1)
	//map<id_grpah, appearence_id>
	map< string, list<string>* > node_children;
	map< string, string > node_appearance;
	map<string, appearence*> looks;

public:
	Graph();
  /*
   * run through elements
   * 	create graphnode
   * 	if elemnt nAMe is Id then is root!
   * 	put id in node
   * 	set transformations
   * 	set appeeareref map
   * 	run through child
   * 		if noderef then add to map
   * 		else -primitive- create CGFobj and set to node and list
   * 	push to nodes
   *
   * copy noderef* to each graph node
   *
   */
  void getGraph(BigElemContainers* bec,string ID);
  GraphNode* getRoot();
  void populateChildren();
  void setNodeAppearance();
  void setAppID(ElemContainers* elcs);
  virtual ~Graph(){};
};

#endif /* GRAPH_H_ */

