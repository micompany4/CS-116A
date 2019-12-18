#pragma once

#include "ofMain.h"
#include "Primitives.h"

/*
	Michael Wong CS 116A - Project 3
*/
class Joint : public SceneObject
{
public:
	Joint();
	~Joint();

	Joint(glm::vec3 pos, float r, ofColor c, string n)
	{
		diffuseColor = c;
		position = pos;
		radius = r;
		name = n;
	}


	void draw();
	bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal);
	
};

