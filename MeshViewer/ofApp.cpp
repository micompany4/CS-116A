#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//some intital setups for the easycam 
	cam.setDistance(10);
	cam.setNearClip(.1);
	//cam.setFov(40); //65.5
	ofEnableDepthTest();


	//some hard coded data to test out if the mesh is drawing correctly 
	//pushes 6 triangles to form a pyramid
	mesh.triList.push_back(Triangle(3, 2, 1));
	mesh.triList.push_back(Triangle(1, 4, 3));
	mesh.triList.push_back(Triangle(1, 2, 5));
	mesh.triList.push_back(Triangle(2, 3, 5));
	mesh.triList.push_back(Triangle(3, 4, 5));
	mesh.triList.push_back(Triangle(4, 1, 5));
	

	//the vertices for the 6 triangles
	mesh.vertices.push_back(glm::vec3(0, 0, 1));
	mesh.vertices.push_back(glm::vec3(0, 0, 0));
	mesh.vertices.push_back(glm::vec3(1, 0, 0));
	mesh.vertices.push_back(glm::vec3(0.5, 1, 0.5));
	mesh.vertices.push_back(glm::vec3(1, 0, 1));

	//f = fopen("monster-light-triangles.obj", "r");
	f = fopen("castle.obj", "r");
	if (f == NULL)
	{
		cout << "file does not exist" << endl;
		exit();
	}
	else
	{
		printf("file found\n");
	}

	objMesh.create(f);
	//objMesh.test();

	//fclose(f);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetBackgroundColor(ofColor::black);

	cam.begin();

	//X-axis
	ofSetColor(ofColor::red);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	//Y-axis
	ofSetColor(ofColor::yellow);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//Z-axis
	ofSetColor(ofColor::blue);
	ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	ofSetColor(ofColor::white);
	
	if (monster)
	{
		objMesh.draw();
	}
	else
	{
		mesh.draw();
	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case 'c':
	case 'C':
		//something with mouse
		if (mouse)
		{
			cam.disableMouseInput();
			mouse = false;
		}
		else
		{
			cam.enableMouseInput();
			mouse = true;
		}
		break;
	case 'f' :
	case 'F' :
		ofToggleFullscreen();
		break;
	case 'r' :
	case 'R' :
		cam.reset();
		break;
	case 'm' :
		if (monster)
		{
			monster = false;
		}
		else
		{
			monster = true;
		}
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 
	
}
