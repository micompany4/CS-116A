#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

//loops through all the vertices in the mesh and draws triangles based on their positions
void Mesh::draw()
{
	for (int n = 0; n < triList.size(); n++)
	{
		ofNoFill();
		ofSetColor(ofColor::limeGreen);
		ofDrawTriangle(vertices[triList[n].i - 1], vertices[triList[n].j - 1], vertices[triList[n].k - 1]);
	}
}

//creates a mesh from an obj file 
//scans through the entire file to find vertices and faces
void Mesh::create(FILE* f)
{
	//scans through the file until it reaches the end of the file
	while (fscanf(f, "%s", s) != EOF)
	{
		sizeOfFile++;
		
		//add triangles to the mesh's vector of triangles
		if (strcmp(s, face) == 0)
		{
			fscanf(f, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &c, &v, &b);		//scans and only gets the index for the vertices
			triList.push_back(Triangle(c, v, b));
		}
		
		//add vertices to the mesh's vector of vertices
		if (strcmp(s, vert) == 0)
		{
			fscanf(f, "%f %f %f", &v1, &v2, &v3);
			vertices.push_back(glm::vec3(v1, v2, v3));
		}
	}

	cout << "number of faces: " << triList.size() << endl;
	cout << "number of vertices: " << vertices.size() << endl;
	cout << "Size of mesh structure: "  << sizeOfFile/1000 << " kB" << endl;

	
	fclose(f);
}

