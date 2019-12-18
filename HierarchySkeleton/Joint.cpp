#include "Joint.h"
#include "ofApp.h"

/*
	Michael Wong CS 116A - Project 3
*/
Joint::Joint()
{
}


Joint::~Joint()
{
}


void Joint::draw()
{
	//   get the current transformation matrix for this object
   //
	glm::mat4 m = getMatrix();

	//   push the current stack matrix and multiply by this object's
	//   matrix. now all vertices drawn will be transformed by this matrix
	//
	
	ofPushMatrix();
	ofMultMatrix(m);
	ofDrawSphere(radius);
	ofPopMatrix();

	//if this joint has a parent, draw a bone 
	if (this->parent != NULL)
	{
		glm::vec3 pointTo = this->parent->getPosition() - this->getPosition();					//vector that points to the parent

		float distance = glm::length(this->parent->getPosition() - this->getPosition());		//the distance between the two joints

		glm::vec3 v1 = glm::normalize(glm::vec3(0, 1, 0));
		glm::vec3 v2 = glm::normalize(pointTo);
		glm::mat4 rotationMatrix = rotateToVector(v1, v2);								//gets the rotation matrix for the bone

		ofPushMatrix();
		glm::mat4 transMatrix = glm::translate(this->getPosition());
		glm::mat4 offsetMatrix = glm::translate(glm::vec3(0, distance / 2, 0));
		ofMultMatrix(transMatrix * rotationMatrix * offsetMatrix);						//translate and rotates the bone so it looks like a "ball and socket" joint structure
		ofSetColor(ofColor::lightSeaGreen);
		ofDrawCone(0.75, distance - (this->radius + this->parent->radius));				//minus radius of itself and parent so that they are aligned/oriented correctly
		ofPopMatrix();

	}

	// draw axis
	//
	ofApp::drawAxis(m, 1.5);
}

bool Joint::intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) {

	// transform Ray to object space.  
	//
	glm::mat4 mInv = glm::inverse(getMatrix());
	glm::vec4 p = mInv * glm::vec4(ray.p.x, ray.p.y, ray.p.z, 1.0);
	glm::vec4 p1 = mInv * glm::vec4(ray.p + ray.d, 1.0);
	glm::vec3 d = glm::normalize(p1 - p);

	return (glm::intersectRaySphere(glm::vec3(p), d, glm::vec3(0, 0, 0), radius, point, normal));
}
