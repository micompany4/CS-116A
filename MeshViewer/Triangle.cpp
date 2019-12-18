#include "Triangle.h"

Triangle::Triangle()
{

}

//ctor for triangle class 
//takes three ints to assign an value for the different indices
Triangle::Triangle(int i1, int i2, int i3)
{
	i = i1;
	j = i2;
	k = i3;
}


Triangle::~Triangle()
{
}


void Triangle::test()
{
	cout << "did it work?" << endl;
}