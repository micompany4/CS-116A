
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

#include "ofApp.h"



//--------------------------------------------------------------
//
void ofApp::setup() {

	ofSetBackgroundColor(ofColor::black);
	ofEnableDepthTest();
	mainCam.setDistance(15);
	mainCam.setNearClip(.1);
	
	sideCam.setPosition(40, 0, 0);
	sideCam.lookAt(glm::vec3(0, 0, 0));
	topCam.setNearClip(.1);
	topCam.setPosition(0, 16, 0);
	topCam.lookAt(glm::vec3(0, 0, 0));
	ofSetSmoothLighting(true);


	// setup one point light
	//
	light1.enable();
	light1.setPosition(5, 5, 0);
	light1.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
	light1.setSpecularColor(ofColor(255.f, 255.f, 255.f));


	theCam = &mainCam;

	//  create a scene consisting of a ground plane with 2x2 blocks
	//  arranged in semi-random positions, scales and rotations
	//
	// ground plane
	//
	scene.push_back(new Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0)));   //default scene object always in scene, DO NOT DELETE
	
}

 
//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	theCam->begin();
	ofNoFill();
	drawAxis();
	ofEnableLighting();

	//  draw the objects in scene
	//
	material.begin();
	ofFill();
	for (int i = 0; i < scene.size(); i++) {
		if (objSelected() && scene[i] == selected[0])
			ofSetColor(ofColor::white);
		else ofSetColor(scene[i]->diffuseColor);
		scene[i]->draw();
	}

	material.end();
	ofDisableLighting();
	theCam->end();
}

// 
// Draw an XYZ axis in RGB at transform
//
void ofApp::drawAxis(glm::mat4 m, float len) {

	ofSetLineWidth(1.0);

	// X Axis
	ofSetColor(ofColor(255, 0, 0));
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(len, 0, 0, 1)));


	// Y Axis
	ofSetColor(ofColor(0, 255, 0));
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, len, 0, 1)));

	// Z Axis
	ofSetColor(ofColor(0, 0, 255));
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, 0, len, 1)));
}

// print C++ code for obj tranformation channels. (for debugging);
//
void ofApp::printChannels(SceneObject *obj) {
	cout << "name: " << obj->name << " parent: ";
	if (obj->parent != NULL)
		cout << obj->parent->name << endl;
	else
		cout << "none" << endl;
	cout << "position = glm::vec3(" << obj->position.x << "," << obj->position.y << "," << obj->position.z << ");" << endl;
	cout << "rotation = glm::vec3(" << obj->rotation.x << "," << obj->rotation.y << "," << obj->rotation.z << ");" << endl;
	cout << "scale = glm::vec3(" << obj->scale.x << "," << obj->scale.y << "," << obj->scale.z << ");" << endl;
}

/*
	Michael Wong CS 116A - Project 3
*/
//save the hierarchy skeleton to a file
void ofApp::saveToFile()
{
	//initial check to see if there are joints in the scene to be saved
	if (scene.size() <= 1)
	{
		cout << "Save failed: No joints found on screen" << endl;
		return;
	}

	//create and save the sceen to a file
	writeFile.open("skeletonHierarchy.txt");
	for (int i = 1; i < scene.size(); i++)
	{
		//when joints are created they will always have these data associated with them
		writeFile << "create -joint " << scene[i]->name << " -rotate <" << scene[i]->rotation << "> -translate <" << scene[i]->position << "> ";
		//check if this joint is a root
		if (scene[i]->parent != NULL)
		{
			writeFile << "-parent ";
			writeFile << scene[i]->parent->name << "\n";
		}
		else
		{
			writeFile << "\n";
		}
	}
	writeFile.close();					//close the file, prevents memory leaks
	cout << "Save complete" << endl;
}

//read from a file and generate a skeleton from that file
//not sure how to handle if no specific data (rotation, translation, parent) was given
//handled two ways: if (for example) "-parent" not found, then assign as root
//the other: -parent "null" or "root" or "" or invalid parent name, assign as a root
void ofApp::createFromFile()
{
	readFile.open("skeletonHierarchy.txt");

	//reads the words of the file into a vector of strings 
	string str;
	while (readFile >> str)
	{
		input.push_back(str);
	}
	cout << "done reading" << endl;

	//initial data required to create a joint from input commands in the file
	string theeName = "";						//the name of the joint
	glm::vec3 rotar = glm::vec3(0, 0, 0);		//the rotation of the joint
	glm::vec3 trat = glm::vec3(0, 0, 0);		//the translation of the joint
	int index = -1;								//the index to the joint's parent
	for (int i = 0; i < input.size(); i++)
	{
		//sets the name for the read joint
		//all joints need a name so we don't need to check anything 
		if (input[i] == sJoint)
		{	
			theeName = input[i + 1];
			//cout << "set name" << endl;
		}
		else if (input[i] == sRotate)
		{
			//check if no rotation option was given
			if (input[i + 1].substr(0, 1) != "<")
			{
				//generated.rotation = glm::vec3(0, 0, 0);
				rotar = glm::vec3(0, 0, 0);
			}
			else
			{
				//converts the file information into floats so that they can be assigned to glm::vec3
				float xRot = stof(input[i + 1].substr(1, input[i + 1].length() - 1));
				float yRot = stof(input[i + 2].substr(0, input[i + 2].length() - 1));
				float zRot = stof(input[i + 3].substr(0, input[i + 3].length() - 1));
				
				//cout << "rotation: " << xRot << " " << yRot << " " << zRot << endl;
				rotar = glm::vec3(xRot, yRot, zRot);
			}

			//cout << "set rotation" << endl;
		}
		else if (input[i] == sTrans)
		{
			//check if no translation option was given
			if (input[i + 1].substr(0, 1) != "<")
			{
				trat = glm::vec3(0, 0, 0);
			}
			else
			{
				//converts the file info into floats so that they can be assigned to glm::vec3
				float xTran = stof(input[i + 1].substr(1, input[i + 1].length() - 1));
				float yTran = stof(input[i + 2].substr(0, input[i + 2].length() - 1));
				float zTran = stof(input[i + 3].substr(0, input[i + 3].length() - 1));
				
				trat = glm::vec3(xTran, yTran, zTran);
			}

			//cout << "set translation" << endl;
		}
		else if (input[i] == sParent)
		{
			//check if no parent option was given
			if (input[i + 1].substr(0, 5) != "joint")
			{
				index = -1;
				//cout << "no parent" << endl;
			}
			else
			{
				//cout << "parent: " << input[i + 1] << endl;
				//find the index of this joint's parent
				for (int j = 0; j < scene.size(); j++)
				{
					if (scene[j]->name == input[i + 1])
					{
						index = j;
						break;
					}
				}
				//cout << "found index: " << index << endl;
				
				//cout << "set parent" << endl << endl;
			}
			
		}
		else if ((input[i] == sCreate && i != 0) || i == input.size()-1)	//reached the end of the line so create the joint
		{
			scene.push_back(new Joint(trat, 1.0, ofColor::blue, theeName));	
			scene[scene.size() - 1]->rotation = rotar;
			if (index == -1)
			{
				scene[scene.size() - 1]->parent = NULL;
				scene[scene.size() - 1]->diffuseColor = ofColor::red;
			}
			else
			{
				scene[scene.size() - 1]->parent = scene[index];
				scene[scene.size() - 1]->parent->addChild(scene[scene.size() - 1]);
			}
			cout << "joint created" << endl;

			//reset the data for the joints
			theeName = "";
			rotar = glm::vec3(0, 0, 0);
			trat = glm::vec3(0, 0, 0);
			index = -1;
		}
	}

	input.clear();			//clear out the input vector to prevent duplicate joints from a previous load
	readFile.close();		//close the file
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key) {
	case OF_KEY_ALT:
		bAltKeyDown = false;
		mainCam.disableMouseInput();
		break;
	case 'a':
		bAnimate = false;
		break;
	case 'x':
		bRotateX = false;
		break;
	case 'y':
		bRotateY = false;
		break;
	case 'z':
		bRotateZ = false;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'C':
	case 'c':
		if (mainCam.getMouseInputEnabled()) mainCam.disableMouseInput();
		else mainCam.enableMouseInput();
		break;
	case 'F':
	case 'b':
		break;
	case 'f':
		ofToggleFullscreen();
		break;
	case 'a':
		bAnimate = true;
		break;
	case 'h':
		bHide = !bHide;
		break;
	case 'd':
		//delete the selected joint
		if (objSelected())
		{
			selected[0]->deleteJoint(selected[0]->parent);
			

			//get the indices of the child and selected joint of the scene object to remove, -1 so it'll throw an exception if nothing was found
			int index = -1;
			int child = -1;
			for (int i = 0; i < scene.size(); i++)
			{
				if (scene[i]->name == selected[0]->name)
				{
					index = i;
					break;
				}
			}
			
			//update the child list, by removing that child from the child list
			if (selected[0]->parent != NULL)
			{
				for (int j = 0; j < selected[0]->parent->childList.size(); j++)
				{
					if (selected[0]->parent->childList[j]->name == selected[0]->name)
					{
						child = j;
						break;
					}
				}
				
				selected[0]->parent->childList.erase(selected[0]->parent->childList.begin() + child);	//delete the child from the children list
				
			}
			
			scene.erase(scene.begin() + index);			//delete the joint at that index
			selected.clear();							//clear out the selected vector so that nothing is selected
		}
		break;
	case 'i':
		break;
	case 'j':
		if (objSelected())
		{
			//adding a child joint(s) to a parent joint
			string strCount = std::to_string(jointCount++);
			Joint *addJoint = new Joint(cursor - selected[0]->getPosition(), 1.0, ofColor::skyBlue, "joint" + strCount);
			scene.push_back(addJoint);
			selected[0]->addChild(addJoint);
			addJoint->parent = selected[0];
			
		}
		else
		{
			//creating a completely new joint (root)
			string strCount = std::to_string(jointCount++);
			Joint *ownJoint = new Joint(cursor, 1.0, ofColor::red, "joint" + strCount);
			scene.push_back(ownJoint);
		}
		break;
	case 'n':
		//print out the object names in the scene
		for (int i = 0; i < scene.size(); i++)
		{
			cout << scene[i]->name << endl;
		}
		cout << endl;
		break;
	case 'N':
		//print out the children of a selected joint
		if (objSelected())
		{
			if (selected[0]->childList.size() == 0)
			{
				cout << "no children" << endl;
				break;
			}
			for (int i = 0; i < selected[0]->childList.size(); i++)
			{
				cout << selected[0]->childList[i]->name << endl;
			}
		}
		break;
	case 'p':
		if (objSelected()) 
		{
			printChannels(selected[0]);
		}
		break;
	case 's':
		//save the skeleton to a file
		cout << "Saving..." << endl;
		saveToFile();
		break;
	case 'q':
		//read a file to create a skeleton on screen
		cout << "Generating skeleton..." << endl;
		createFromFile();
		cout << "Skeleton complete" << endl;
		break;
	case 'r':
		mainCam.reset();
		break;
	case 'x':
		bRotateX = true;
		break;
	case 'y':
		bRotateY = true;
		break;
	case 'z':
		bRotateZ = true;
		break;
	case OF_KEY_F1: 
		theCam = &mainCam;
		break;
	case OF_KEY_F2:
		theCam = &sideCam;
		break;
	case OF_KEY_F3:
		theCam = &topCam;
		break;
	case OF_KEY_ALT:
		bAltKeyDown = true;
		if (!mainCam.getMouseInputEnabled()) mainCam.enableMouseInput();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mouseToDragPlane(x, y, cursor);		//updates the position of the mouse's cursor
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	if (objSelected() && bDrag) {
		glm::vec3 point; 
		mouseToDragPlane(x, y, point);
		if (bRotateX) {
			selected[0]->rotation += glm::vec3((point.x - lastPoint.x) * 20.0, 0, 0);
		}
		else if (bRotateY) {
			selected[0]->rotation += glm::vec3(0, (point.x - lastPoint.x) * 20.0, 0);
		}
		else if (bRotateZ) {
			selected[0]->rotation += glm::vec3(0, 0, (point.x - lastPoint.x) * 20.0);
		}
		else {
			selected[0]->position += (point - lastPoint);
		}
		lastPoint = point;
	}

}

//  This projects the mouse point in screen space (x, y) to a 3D point on a plane
//  normal to the view axis of the camera passing through the point of the selected object.
//  If no object selected, the plane passing through the world origin is used.
//
bool ofApp::mouseToDragPlane(int x, int y, glm::vec3 &point) {
	glm::vec3 p = theCam->screenToWorld(glm::vec3(x, y, 0));
	glm::vec3 d = p - theCam->getPosition();
	glm::vec3 dn = glm::normalize(d);

	float dist;
	glm::vec3 pos;
	if (objSelected()) {
		pos = selected[0]->position;
	}
	else pos = glm::vec3(0, 0, 0);
	if (glm::intersectRayPlane(p, dn, pos, glm::normalize(theCam->getZAxis()), dist)) {
		point = p + dn * dist;
		return true;
	}
	return false;
}

//--------------------------------------------------------------
//
// Provides functionality of single selection and if something is already selected,
// sets up state for translation/rotation of object using mouse.
//
void ofApp::mousePressed(int x, int y, int button){

	// if we are moving the camera around, don't allow selection
	//
	if (mainCam.getMouseInputEnabled()) return;

	// clear selection list
	//
	selected.clear();

	//
	// test if something selected
	//
	vector<SceneObject *> hits;

	glm::vec3 p = theCam->screenToWorld(glm::vec3(x, y, 0));
	glm::vec3 d = p - theCam->getPosition();
	glm::vec3 dn = glm::normalize(d);

	// check for selection of scene objects
	//
	for (int i = 0; i < scene.size(); i++) {
		
		glm::vec3 point, norm;
		
		//  We hit an object
		//
		if (scene[i]->isSelectable && scene[i]->intersect(Ray(p, dn), point, norm)) {
			hits.push_back(scene[i]);
		}
	}


	// if we selected more than one, pick nearest
	//
	SceneObject *selectedObj = NULL;
	if (hits.size() > 0) {
		selectedObj = hits[0];
		float nearestDist = std::numeric_limits<float>::infinity();
		for (int n = 0; n < hits.size(); n++) {
			float dist = glm::length(hits[n]->position - theCam->getPosition());
			if (dist < nearestDist) {
				nearestDist = dist;
				selectedObj = hits[n];
			}	
		}
	}
	if (selectedObj) {
		selected.push_back(selectedObj);
		bDrag = true;
		mouseToDragPlane(x, y, lastPoint);
	}
	else {
		selected.clear();
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	bDrag = false;

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
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

