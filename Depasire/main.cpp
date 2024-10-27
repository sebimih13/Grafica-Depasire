#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "loadShaders.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//////////////////////////////////////

constexpr GLuint winWidth = 1800, winHeight = 800;
constexpr GLfloat xMin = -(winWidth / 2.0f), xMax = (winWidth / 2.0f), yMin = -(winHeight / 2.0f), yMax = (winHeight / 2.0f);

GLuint VaoIdBackground, VboIdBackground, EboIdBackground;
GLuint ProgramId;
GLuint myMatrixUniformLocation;

glm::mat4 resizeMatrix;

void CreateVAOBackground()
{
	constexpr GLfloat Vertices[] = {	
		// tree
		-50.0f, 0.0f, 0.0f, 1.0f,
		50.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 80.0f, 0.0f, 1.0f,

		-50.0f, 78.0f, 0.0f, 1.0f,
		50.0f, 78.0f, 0.0f, 1.0f,
		0.0f, 160.0f, 0.0f, 1.0f,

		-15.0f, 0.0f, 0.0f, 1.0f,
		15.0f, 0.0f, 0.0f, 1.0f,
		15.0f, -80.0f, 0.0f, 1.0f,
		-15.0f, -80.0f, 0.0f, 1.0f
	};

	constexpr GLfloat Colors[] = {
		// tree
		0.0f, 0.502f, 0.251f, 1.0f,
		0.0f, 0.502f, 0.251f, 1.0f,
		0.0f, 0.502f, 0.251f, 1.0f,

		0.0f, 0.502f, 0.251f, 1.0f,
		0.0f, 0.502f, 0.251f, 1.0f,
		0.0f, 0.502f, 0.251f, 1.0f,

		0.729f, 0.478f, 0.341f, 1.0f,
		0.729f, 0.478f, 0.341f, 1.0f,
		0.729f, 0.478f, 0.341f, 1.0f,
		0.729f, 0.478f, 0.341f, 1.0f
	};

	constexpr GLuint Indices[] = {
		// tree
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		6, 8, 9
	};

	glGenVertexArrays(1, &VaoIdBackground);
	glBindVertexArray(VaoIdBackground);

	// Vertex Buffer
	GLuint VboIdBackground;
	glGenBuffers(1, &VboIdBackground);
	glBindBuffer(GL_ARRAY_BUFFER, VboIdBackground);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors);

	glGenBuffers(1, &EboIdBackground);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboIdBackground);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	// atribut 0 => (location = 0)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// atribut 1 => (location = 1)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(Vertices));
}

void DestroyVAOBackground(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EboIdBackground);
	glDeleteBuffers(1, &VboIdBackground);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoIdBackground);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("example.vert", "example.frag");
	glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(0.137f, 0.694f, 0.302f, 1.0f);

	CreateVAOBackground();
	CreateShaders();

	myMatrixUniformLocation = glGetUniformLocation(ProgramId, "myMatrix");
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);       

	// Draw background
	glm::mat4 myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

	glBindVertexArray(VaoIdBackground);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(0));
	
	glFlush();
}

void Cleanup(void)
{
	DestroyShaders();
	DestroyVAOBackground();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Depasire");
	
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

