#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <Windows.h>

#include <GL\glew.h>
#include <GL\freeglut.h>

#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "lib/glut32.lib")

#include <glm\glm.hpp>
#include <glm\gtx\projection.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "MathCommon.h"
#include "Camera.h"
#include "Shader.hpp"
#include "TextureManager.h"
#include "Mesh.hpp"
#include "ParticleSystem.hpp"

using namespace std;


int screenWidth = 1280;
int screenHeight = 720;

Camera camera;

// model parameters
unsigned int	vaoId[1];
unsigned int	vboId[4];
glm::mat4		modelMatrix;
//glm::mat4		normalMatrix;
//int				modelMatrixLocation;
//int				normalMatrixLocation;
int				texLocation;

TextureManager texManager;
GLuint tex;
GLuint cubeMap;

Shader basicShader;
Shader lightShader;
Shader texShader;

ParticleSystem psys;

Mesh squareMesh;


//void createSquare()
//{
//	// verts
//	float *verts = new float[18];
//	verts[0] = -1.0f; verts[1] = -1.0f; verts[2] = 0.0f;
//	verts[3] = 1.0f; verts[4] = -1.0f; verts[5] = 0.0f;
//	verts[6] = 1.0f; verts[7] = 1.0f; verts[8] = 0.0f;
//	
//	verts[9] = -1.0f; verts[10] = -1.0f; verts[11] = 0.0f;
//	verts[12] = 1.0f; verts[13] = 1.0f; verts[14] = 0.0f;
//	verts[15] = -1.0f; verts[16] = 1.0f; verts[17] = 0.0f;
//
//	// normals
//	float *normals = new float[18];
//	normals[0] = -0.7070f; normals[1] = 0.0f; normals[2] = 0.7070f;
//	normals[3] = 0.7070f; normals[4] = 0.0f; normals[5] = 0.7070f;
//	normals[6] = 0.7070f; normals[7] = 0.0f; normals[8] = 0.7070f;
//	
//	normals[9] = -0.7070f; normals[10] = 0.0f; normals[11] = 0.7070f;
//	normals[12] = 0.7070f; normals[13] = 0.0f; normals[14] = 0.7070f;
//	normals[15] = -0.7070f; normals[16] = 0.0f; normals[17] = 0.7070f;
//
//	// colors
//	float *colors = new float[24];
//	colors[0] = 1.0f; colors[1] = 0.0f; colors[2] = 0.0f; colors[3] = 1.0f;
//	colors[4] = 0.0f; colors[5] = 1.0f; colors[6] = 0.0f; colors[7] = 1.0f;
//	colors[8] = 0.0f; colors[9] = 0.0f; colors[10] = 1.0f; colors[11] = 1.0f;
//
//	colors[12] = 1.0f; colors[13] = 0.0f; colors[14] = 0.0f; colors[15] = 1.0f;
//	colors[16] = 0.0f; colors[17] = 0.0f; colors[18] = 1.0f; colors[19] = 1.0f;
//	colors[20] = 1.0f; colors[21] = 1.0f; colors[22] = 1.0f; colors[23] = 1.0f;
//
//	// uvs
//	float *uvs = new float[12];
//	uvs[0] = 0.0; uvs[1] = 0.0f;
//	uvs[2] = 1.0; uvs[3] = 0.0f;
//	uvs[4] = 1.0; uvs[5] = 1.0f;
//	
//	uvs[6] = 0.0; uvs[7] = 0.0f;
//	uvs[8] = 1.0; uvs[9] = 1.0f;
//	uvs[10] = 0.0; uvs[11] = 1.0f;
//
//
//	glGenVertexArrays(1, &vaoId[0]);
//	glBindVertexArray(vaoId[0]);
//
//	glGenBuffers(1, &vboId[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
//	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), verts, GL_STATIC_DRAW);
//	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);
//	
//	glGenBuffers(1, &vboId[1]);
//	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
//	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), colors, GL_STATIC_DRAW);
//	glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glGenBuffers(1, &vboId[2]);
//	glBindBuffer(GL_ARRAY_BUFFER, vboId[2]);
//	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), normals, GL_STATIC_DRAW);
//	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(2);
//
//	glGenBuffers(1, &vboId[3]);
//	glBindBuffer(GL_ARRAY_BUFFER, vboId[3]);
//	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), uvs, GL_STATIC_DRAW);
//	glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(3);
//
//	glBindVertexArray(0);
//
//	delete [] verts;
//	delete [] normals;
//	delete [] colors;
//	delete [] uvs;
//}


void createSquare(Mesh &m)
{
	m.numVao = 1;
	m.numVbo = 4;

	m.vao = new unsigned int[m.numVao];
	m.vbo = new unsigned int[m.numVbo];

	m.numVerts = 6;
	m.primitiveType = GL_TRIANGLES;

	// verts
	float *verts = new float[18];
	verts[0] = -1.0; verts[1] = -1.0; verts[2] = 0.0;
	verts[3] = 1.0; verts[4] = -1.0; verts[5] = 0.0;
	verts[6] = 1.0; verts[7] = 1.0; verts[8] = 0.0;
	
	verts[9] = -1.0; verts[10] = -1.0; verts[11] = 0.0;
	verts[12] = 1.0; verts[13] = 1.0; verts[14] = 0.0;
	verts[15] = -1.0; verts[16] = 1.0; verts[17] = 0.0;

	// normals
	float *normals = new float[18];
	normals[0] = 0.0f; normals[1] = 0.0f; normals[2] = 0.7070f;
	normals[3] = 0.0f; normals[4] = 0.0f; normals[5] = 0.7070f;
	normals[6] = 0.0f; normals[7] = 0.0f; normals[8] = 0.7070f;
	
	normals[9] = 0.0f; normals[10] = 0.0f; normals[11] = 0.7070f;
	normals[12] = 0.0f; normals[13] = 0.0f; normals[14] = 0.7070f;
	normals[15] = -0.0f; normals[16] = 0.0f; normals[17] = 0.7070f;

	// colors
	float *colors = new float[24];
	colors[0] = 1.0f; colors[1] = 0.0f; colors[2] = 0.0f; colors[3] = 1.0f;
	colors[4] = 0.0f; colors[5] = 1.0f; colors[6] = 0.0f; colors[7] = 1.0f;
	colors[8] = 0.0f; colors[9] = 0.0f; colors[10] = 1.0f; colors[11] = 1.0f;

	colors[12] = 1.0f; colors[13] = 0.0f; colors[14] = 0.0f; colors[15] = 1.0f;
	colors[16] = 0.0f; colors[17] = 0.0f; colors[18] = 1.0f; colors[19] = 1.0f;
	colors[20] = 1.0f; colors[21] = 1.0f; colors[22] = 1.0f; colors[23] = 1.0f;

	// uvs
	float *uvs = new float[12];
	uvs[0] = 0.0; uvs[1] = 0.0f;
	uvs[2] = 1.0; uvs[3] = 0.0f;
	uvs[4] = 1.0; uvs[5] = 1.0f;
	
	uvs[6] = 0.0; uvs[7] = 0.0f;
	uvs[8] = 1.0; uvs[9] = 1.0f;
	uvs[10] = 0.0; uvs[11] = 1.0f;

	glGenVertexArrays(1, &m.vao[0]);
	glBindVertexArray(m.vao[0]);

	glGenBuffers(1, &m.vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), verts, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	glGenBuffers(1, &m.vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, m.vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), colors, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &m.vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, m.vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), normals, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &m.vbo[3]);
	glBindBuffer(GL_ARRAY_BUFFER, m.vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), uvs, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	delete [] verts;
	delete [] normals;
	delete [] colors;
	delete [] uvs;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	modelMatrix = glm::rotate<float>(modelMatrix, 1.0, glm::vec3(0,1,0));
	
	//glBindTexture(GL_TEXTURE_2D, );
	basicShader.Bind();
	//lightShader.Bind();
	//texShader.Bind();
		// load variables to shader
		glUniformMatrix4fv(basicShader.projMatrixLocation, 1, GL_FALSE, &camera.projMatrix[0][0]);
		glUniformMatrix4fv(basicShader.viewMatrixLocation, 1, GL_FALSE, &camera.viewMatrix[0][0]);
		glUniformMatrix4fv(basicShader.modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
		//glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, &normalMatrix[0][0]);
		glUniform1i(texLocation, 0);

		// bind and draw vertex array
		/*glBindVertexArray(vaoId[0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);*/
		squareMesh.Render();

		/*glm::mat4 iden = glm::mat4();
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &iden[0][0]);
		glBindVertexArray(vaoId[0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);*/
	basicShader.UnBind();
	//lightShader.UnBind();
	//texShader.UnBind();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == (int)27)
	{
		exit(0);
	}
}

void resize(int width, int height)
{
	if (height == 0)
		height = 1;

	float ratio = (float)width / (float)height;
	
	camera.resize(width, height, 90.0f);
	camera.resizeDepth(0.1f, 1000.0f);
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glewInit();

	char *str = (char*)glGetString(GL_VERSION);
	cout << "OpenGL Version " << str << endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glActiveTexture(GL_TEXTURE0);
	texManager.Init();
	glDisable(GL_TEXTURE_2D);
	
	camera.lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//viewMatrix = glm::lookAt(glm::vec3(0,0,2), glm::vec3(0,0,0), glm::vec3(0,1,0));

	// shader setup
	basicShader.Init("basic.vert", "basic.frag");
	//lightShader.Init("light.vert", "light.frag");
	//texShader.Init("basicTexture.vert", "basicTexture.frag");

	basicShader.projMatrixLocation = glGetUniformLocation(basicShader.progId, "projMatrix");
	basicShader.viewMatrixLocation = glGetUniformLocation(basicShader.progId, "viewMatrix");
	basicShader.modelMatrixLocation = glGetUniformLocation(basicShader.progId, "modelMatrix");
	/*projMatrixLocation = glGetUniformLocation(texShader.progId, "projMatrix");
	viewMatrixLocation = glGetUniformLocation(texShader.progId, "viewMatrix");
	modelMatrixLocation = glGetUniformLocation(texShader.progId, "modelMatrix");
	texLocation = glGetUniformLocation(texShader.progId, "tex");*/

	cout << "texLocation = " << texLocation << endl;
	
	psys.pos = glm::vec3(0,0,0);
	psys.dir = glm::normalize(glm::vec3(1,1,0));
	psys.startSpeed = 0.001f;

	//createSquare(squareMesh);
	createSquare(squareMesh);

	// models
	//createSquare();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Particle System");
	
	init();

	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 1;
}