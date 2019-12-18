#pragma once

#include "ofMain.h"

/*
  Michael Wong CS 116A Project1
*/
class Triangle
{
public:
	Triangle();
	Triangle(int i1, int i2, int i3);		//constructor for the triangle class
	~Triangle();

	void test();

	int i, j, k;						//indices for each of the three vertices in the triangle

};

