#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
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
GLuint VaoIdCars, VboIdCars, EboIdCars;
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
		-15.0f, -80.0f, 0.0f, 1.0f,

		// highway
		xMin, 80.0f, 0.0f, 1.0f,
		xMax, 80.0f, 0.0f, 1.0f,
		xMax, -80.0f, 0.0f, 1.0f,
		xMin, -80.0f, 0.0f, 1.0f,

		// strip
		-800.0f, 0.0f, 0.0f, 1.0f,
		-700.0f, 0.0f, 0.0f, 1.0f,
		-650.0f, 0.0f, 0.0f, 1.0f,
		-550.0f, 0.0f, 0.0f, 1.0f,
		-500.0f, 0.0f, 0.0f, 1.0f,
		-400.0f, 0.0f, 0.0f, 1.0f,
		-350.0f, 0.0f, 0.0f, 1.0f,
		-250.0f, 0.0f, 0.0f, 1.0f,
		-200.0f, 0.0f, 0.0f, 1.0f,
		-100.0f, 0.0f, 0.0f, 1.0f,
		-50.0f, 0.0f, 0.0f, 1.0f,
		50.0f, 0.0f, 0.0f, 1.0f,
		100.0f, 0.0f, 0.0f, 1.0f,
		200.0f, 0.0f, 0.0f, 1.0f,
		250.0f, 0.0f, 0.0f, 1.0f,
		350.0f, 0.0f, 0.0f, 1.0f,
		400.0f, 0.0f, 0.0f, 1.0f,
		500.0f, 0.0f, 0.0f, 1.0f,
		550.0f, 0.0f, 0.0f, 1.0f,
		650.0f, 0.0f, 0.0f, 1.0f,
		700.0f, 0.0f, 0.0f, 1.0f,
		800.0f, 0.0f, 0.0f, 1.0f,
		850.0f, 0.0f, 0.0f, 1.0f,
		950.0f, 0.0f, 0.0f, 1.0f
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
		0.729f, 0.478f, 0.341f, 1.0f, 

		// highway
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	constexpr GLuint Indices[] = {
		// tree
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		6, 8, 9,

		// highway
		10, 11, 12,
		10, 12, 13,
		
		// strip
		14, 15,
		16, 17,
		18, 19,
		20, 21,
		22, 23,
		24, 25,
		26, 27,
		28, 29,
		30, 31,
		32, 33,
		34, 35,
		36, 37
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

void CreateVAOCars() {
	GLfloat Vertices[] = {
		//GreenCar
		xMin + 300, -65.0f, 1.0f, 1.0f,
		xMin + 400, -65.0f, 1.0f, 1.0f,
		xMin + 400, -15.0f, 1.0f, 1.0f,
		xMin + 300, -15.0f, 1.0f, 1.0f,

		//RedCar
		xMin, -65.0f, 1.0f, 1.0f,
		xMin + 100, -65.0f, 1.0f, 1.0f,
		xMin + 100, -15.0f, 1.0f, 1.0f,
		xMin, -15.0f, 1.0f, 1.0f

	};

	GLfloat Colors[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};

	GLuint Indices[] = {
		0, 1, 2, 3,
		4, 5, 6, 7
	};

	glGenVertexArrays(1, &VaoIdCars);
	glBindVertexArray(VaoIdCars);

	glGenBuffers(1, &VboIdCars);
	glBindBuffer(GL_ARRAY_BUFFER, VboIdCars);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors);

	glGenBuffers(1, &EboIdCars);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboIdCars);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

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
	glDeleteBuffers(1, &EboIdCars);
	glDeleteBuffers(1, &VboIdCars);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoIdBackground);
	glDeleteVertexArrays(1, &VaoIdCars);
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
	CreateVAOCars();
	CreateShaders();

	myMatrixUniformLocation = glGetUniformLocation(ProgramId, "myMatrix");
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

void RenderBackGround() {
	glBindVertexArray(VaoIdBackground);

	// trees
	{
		std::vector<std::pair<GLfloat, GLfloat>> position = {
			std::make_pair(-500.0f, 250.0f),
			std::make_pair(-400.0f, 270.0f),
			std::make_pair(-310.0f, 200.0f),
			std::make_pair(-250.0f, 300.0f),
			std::make_pair(-170.0f, 240.0f),
			std::make_pair(-70.0f, 210.0f),

			std::make_pair(10.0f, 250.0f),
			std::make_pair(100.0f, 270.0f),
			std::make_pair(190.0f, 200.0f),
			std::make_pair(250.0f, 300.0f),
			std::make_pair(330.0f, 240.0f),
			std::make_pair(430.0f, 210.0f)
			// TODO: add
		};

		std::vector<std::pair<GLfloat, GLfloat>> scale = {
			std::make_pair(0.5f, 0.5f),
			std::make_pair(0.7f, 0.7f),
			std::make_pair(0.9f, 0.9f),
			std::make_pair(0.6f, 0.6f),
			std::make_pair(0.8f, 0.8f),
			std::make_pair(1.0f, 1.0f),

			std::make_pair(0.5f, 0.5f),
			std::make_pair(0.7f, 0.7f),
			std::make_pair(0.9f, 0.9f),
			std::make_pair(0.6f, 0.6f),
			std::make_pair(0.8f, 0.8f),
			std::make_pair(1.0f, 1.0f)
			// TODO: add
		};

		for (int i = 0; i < position.size() && i < scale.size(); i++)
		{
			const GLfloat& posX = position[i].first;
			const GLfloat& posY = position[i].second;

			const GLfloat& scaleX = scale[i].first;
			const GLfloat& scaleY = scale[i].second;

			glm::mat4 traslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 1.0f));
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
			glm::mat4 myMatrix = resizeMatrix * traslateMatrix * scaleMatrix;
			glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(0));
		}
	}

	{ // highway
		glm::mat4 myMatrix = resizeMatrix;
		glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint)));

	{ // strip
		glm::mat4 myMatrix = resizeMatrix;
		glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);
	}
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));
}

float speedGreenCar = 1.5f, posXGreenCar = 0.0f;
float speedRedCar = 1.5f, posXRedCar = 0.0f, posYRedCar = 0.0f;
float turningAngle = 0;
const int timer = 16;
unsigned lastSpeedKey = 0;

void recalcSpeed() {
	switch (lastSpeedKey) {
	case 'w':
		speedRedCar += 0.002f * (15.0f - speedRedCar);
		break;
	case 's':
		speedRedCar -= 0.08f;
		break;
	default:
		speedRedCar -= 0.005f;
		break;
	}

	if (speedRedCar > 15.0f) speedRedCar = 15.0f;
	if (speedRedCar < 1.0f) speedRedCar = 1.0f;
}

void recalcAngle() {
	if (turningAngle > 0) turningAngle -= glm::min(0.5f, turningAngle);
	else turningAngle -= glm::max(-0.5f, turningAngle);
	if (turningAngle > 45) turningAngle = 45;
	if (turningAngle < -45) turningAngle = -45;
}

void idleFunction(int val) {
	posXGreenCar += speedGreenCar;
	recalcSpeed();
	recalcAngle();
	posXRedCar += speedRedCar * cos(glm::radians(abs(turningAngle)));
	if(turningAngle > 0) posYRedCar += speedRedCar * sin(glm::radians(abs(turningAngle)));
	else posYRedCar -= speedRedCar * sin(glm::radians(abs(turningAngle)));
	glutPostRedisplay();
	glutTimerFunc(timer, idleFunction, 0);
}


void keyBoardFunc(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			lastSpeedKey = key;
			break;
		case 's':
			lastSpeedKey = key;
			break;
		case ' ':
			lastSpeedKey = key;
			break;
		case 'a':
			turningAngle += 2.0f;
			break;
		case 'd':
			turningAngle -= 2.0f;
			break;
		default:
			break;
	}
}


void RenderCars() {
	glBindVertexArray(VaoIdCars);

	//greencar
	glm::mat4 myMatrix = resizeMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(posXGreenCar, 0.0f, 0.0f));
	glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(0));

	//redCar
	myMatrix = resizeMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(posXRedCar, posYRedCar, 0.0f));
	glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(4 * sizeof(GLuint)));

}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);       
	RenderBackGround();
	RenderCars();

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
	glutTimerFunc(timer, idleFunction, 0);
	glutKeyboardFunc(keyBoardFunc);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

