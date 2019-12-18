
//
//  Starter file for Project 3 - Skeleton Builder
//
//  This file includes functionality that supports selection and translate/rotation
//  of scene objects using the mouse.
//
//  Modifer keys for rotatation are x, y and z keys (for each axis of rotation)
//
//  (c) Kevin M. Smith  - 24 September 2018
//
// *Then further built on by Michael Wong for CS 116A Project 3
#include "ofMain.h"
#include "box.h"
#include "Primitives.h"
#include "ofxGui.h"
#include "Joint.h"
#include <algorithm>
#include <iostream>
#include <fstream> 


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		static void drawAxis(glm::mat4 transform = glm::mat4(1.0), float len = 1.0);
		bool mouseToDragPlane(int x, int y, glm::vec3 &point);
		void printChannels(SceneObject *);
		bool objSelected() { return (selected.size() ? true : false ); };
		void saveToFile();
		void createFromFile();

		// Lights
		//
		ofLight light1;
	
		// Cameras
		//
		ofEasyCam  mainCam;
		ofCamera sideCam;
		ofCamera topCam;
		ofCamera  *theCam;    // set to current camera either mainCam or sideCam

		// Materials
		//
		ofMaterial material;


		// scene components
		//
		vector<SceneObject *> scene;
		vector<SceneObject *> selected;			//was originally SceneObject
		ofPlanePrimitive plane;

		int jointCount = 0;		//change this to 0 when you get rid of the hard coded root joint

		ofstream writeFile;			//file that will be written to when saveToFile is called
		fstream readFile;			//file that will be read from when createToFile is called
		

		//some constant strings to be used when creating the skeleton from a file
		const char* sJoint = "-joint";
		const char* sRotate = "-rotate";
		const char* sTrans = "-translate";
		const char* sParent = "-parent";
		const char* sCreate = "create";

		vector<string> input;					//vector to hold all input values from the file
		
		glm::vec3 cursor = glm::vec3(0, 1, 0);						//the current location of the mouse's cursor

		// state
		bool bDrag = false;
		bool bHide = true;
		bool bAltKeyDown = false;
		bool bRotateX = false;
		bool bRotateY = false;
		bool bRotateZ = false;
		bool bAnimate = false;
		glm::vec3 lastPoint;
};