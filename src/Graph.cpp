/*
 * graph.cpp
 */

#include "Graph.h"
#include <sstream>


Graph::Graph(){
  nodes = list<GraphNode*>();
  root = NULL;
  appearances = list<CGFappearance*>();
  objects = list<CGFobject*>();
  node_children = map< string, list<string>* >();
  node_appearance = map< string, string >();
  looks = map<string, appearence*>();
}

void Graph::getGraph(BigElemContainers* bec, string ID)
{
  //Creat CGFobject
  CGFobject * obj = NULL;
  int i = 0;
  //Parse BigElemContainers
  for (BigElemContainers::iterator it = bec->begin(); it != bec->end(); it++)
    {
      //Create nem Graphnode
      GraphNode * n = new GraphNode();
cout << "1\n";
      //List that will contain the children's Ids
      list<string> * children = new list<string>();
      //Variable where the appearance of this node will be stored
      string appearance = "";

      cout << "2\n";
      //Node to be scanned
      string nodeName = (*it)->root->attr["id"];
      n->setId(nodeName);

      //check if it's a displaylist node.
      if( (*it)->root->attr.find("displaylist") != (*it)->root->attr.end() )
    	  if( (*it)->root->attr["displaylist"] == "true" )
    		  n->setDisplayList(true);
    	  else
    		  cout << "its false\n";
      else cout << "it doesn't have!\n";

      cout << "3\n";
      //Parse ElemContainers
      for (ElemContainers::iterator ecit = (*it)->elemCs->begin();
          ecit != (*it)->elemCs->end(); ecit++)
        {
          string temp = (*ecit)->root->name;
          cout << "4\n";
          //If ElemContainers is transforms
          if(temp == "transforms")
            {
              for (Elems::iterator eit = (*ecit)->elems->begin();
                  eit != (*ecit)->elems->end(); eit++)
                {
                  //If we want to do a rotation
                  if((*eit)-> name == "rotate")
                    {
                      //Conversion of parameter "angle" from string to int
                      istringstream angle((*eit)->attr["angle"]);
                      int angleInt;
                      angle >> angleInt;

                      //Do the actual rotation
                      n->rotate((*eit)->attr["axis"], angleInt);
                    }

                  //If we want to do a translation
                  if((*eit)-> name == "translate")
                    {

                      //Conversion of parameters
                      stringstream x1;
                      double X;
                      x1 << (*eit)->attr["x"];
                      x1 >> X;

                      stringstream y1;
                      double Y;
                      y1 << (*eit)->attr["y"];
                      y1 >> Y;

                      stringstream z1;
                      double Z;
                      z1 << (*eit)->attr["z"];
                      z1 >> Z;

                      //Do the actual translation
                      n->translate(X,Y,Z);
                    }
                  //If we want to scale the object
                  if((*eit)-> name == "scale")
                    {
                      //Conversion of parameters
                      stringstream x1;
                      double X;
                      x1 << (*eit)->attr["x"];
                      x1 >> X;

                      stringstream y1;
                      double Y;
                      y1 << (*eit)->attr["y"];
                      y1 >> Y;

                      stringstream z1;
                      double Z;
                      z1 << (*eit)->attr["z"];
                      z1 >> Z;

                      //Do the actual translation
                      n->scale(X,Y,Z);
                    }
                }
            }
          else
            {
              for (Elems::iterator eit = (*ecit)->elems->begin();
                  eit != (*ecit)->elems->end(); eit++)
                {
                  if((*eit)-> name == "noderef")
                    {
                      children->push_back((*eit)->attr["id"]);
                    }
                  else
                    {

                      if((*eit)-> name == "sphere")
                        {
                          obj = new Sphere((*eit));
                        } else
                      if((*eit)-> name == "cylinder")
                        {
                        obj = new Cylinder((*eit));

                        }else
                      if((*eit)-> name == "torus")
                        {
                          obj = new Torus((*eit));
                        }else
                      if((*eit)-> name == "triangle")
                        {
                          obj = new Triangle((*eit));
                        }else
                      if((*eit)-> name == "rectangle")
                        {
                          obj = new Rectangle((*eit));
                        } else
                      if((*eit)-> name == "patch")
						{
							obj = new Patch((*eit));
						} else
						if((*eit)-> name == "plane")
						{
							obj = new Plane((*eit));
						} else
						if( (*eit)->name == "terrain"){

							//obj = new Terrain((*eit));
						}

                      n->setCGFobject(obj);
                      obj = NULL;
                    }
                  //Set the GraphNode object

                }
            }

          if((*it)->elems != NULL)
			  //Run through Childless elements
			  for (Elems::iterator it_elems = (*it)->elems->begin(); it_elems != (*it)->elems->end(); it_elems++)
				{
				  if((*it_elems)-> name == "appearanceref")
					{
					  node_appearance[n->getId()] = (*it_elems)->attr["id"];
					}
				}

          i++;
        }

      //Insert Graphnode into nodes list
      nodes.push_back(n);

      if(n->getId() == ID)
        {
          root = n;
        }

      //Create map entry for node
      node_children[n->getId()] = children;
    }

  //Now to populate the world!
  populateChildren();
}

GraphNode* Graph::getRoot()
{
  return root;
}

void Graph::populateChildren()
{
  map< string, list<string>* >::iterator map_it;
  list<GraphNode*>::iterator gn;
  list<GraphNode*>::iterator gnk;
  list<string>::iterator cit;

  //Go through map node_children
  for(map_it = node_children.begin(); map_it != node_children.end(); map_it++)
    {
      //Find node in graphnode list
      for(gn=nodes.begin(); gn!=nodes.end(); gn++)
        {
          //  cout << "Size: " << nodes.size() << endl;
          //find node reference in map and add the noderefs to the graphnode children
          if((*gn)->getId() == map_it->first)
            {
              //iterate through the node refs
              for(cit = map_it->second->begin(); cit != map_it->second->end(); cit++)
                {
                  //find the node with the same id as noderef
                  for(gnk=nodes.begin(); gnk!=nodes.end(); gnk++)
                    {
                      if( (*gnk)->getId() == *cit)
                        {
                          //add it to the children list
                          (*gn)->addChild(*gnk);
                        }
                      //children = map_it->second;
                    }
                }

            }
        }
    }
}

void Graph::setNodeAppearance()
{
  map< string, string >::iterator it;
  map<string, appearence*>::iterator itapp;
  list<GraphNode*>::iterator it_graphnode;

  //node_appearance has <idNode,idAppea..
  for(it = node_appearance.begin(); it != node_appearance.end(); it++)
    {
      map<string, appearence*>::iterator look_it = looks.find(it->second);
      if( look_it != looks.end()){
          //found an appearence correesponding to an node
          // lets find the node to insert
          it_graphnode = nodes.begin();
          for(; it_graphnode != nodes.end() ; it_graphnode++){
              if(it->first == (*it_graphnode)->getId()){
                  (*it_graphnode)->setAppearance(look_it->second);
                  break;
              }
          }
      }

    }
}

//Fill looks map
void Graph::setAppID(ElemContainers* elcs)
{
  ElemContainers::iterator it;

  for(it = elcs->begin(); it != elcs->end() ; it++)
    {
      looks[(*it)->root->attr["id"]] = new appearence((*it)->elems);
    }
  this->setNodeAppearance();
}





