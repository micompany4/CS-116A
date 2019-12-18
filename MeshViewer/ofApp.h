#pragma once

#include "ofMain.h"
#include "Mesh.h"
#include <fstream>
#include <iostream>
/*
	Michael Wong 
	CS - 116a Project1
*/
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
	
		
		Mesh mesh;			//mesh used to hard code data to test the mesh's draw function
		Mesh objMesh;		//mesh used to create a triangle mesh from an obj file
		
		bool mouse = true, monster = false;

		FILE* f;

		ofEasyCam cam;

};
