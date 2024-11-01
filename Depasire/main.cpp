#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>
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
GLuint VaoIdCar, VboIdCar, EboIdCar;
GLuint VaoIdCars, VboIdCars, EboIdCars, codColLocation;
GLuint ProgramId;
GLuint myMatrixUniformLocation;

glm::mat4 resizeMatrix;

std::unordered_map<char, bool> keyStates;

float distance = 0;

void CreateVAOBackground()
{
	constexpr GLfloat Vertices[] = {	
		// tree
		-50.0f, 0.0f, 0.0f, 1.0f,
		50.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 80.0f, 0.0f, 1.0f,

		-50.0f, 70.0f, 0.0f, 1.0f,
		50.0f, 70.0f, 0.0f, 1.0f,
		0.0f, 150.0f, 0.0f, 1.0f,

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
		-50.0f, 0.0f, 0.0f, 1.0f,
		50.0f, 0.0f, 0.0f, 1.0f,

		// beach
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
		
		// river
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f
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

		// strip
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		// beach
		0.996f, 0.886f, 0.49f, 1.0f,
		0.996f, 0.886f, 0.49f, 1.0f,
		0.996f, 0.886f, 0.49f, 1.0f,
		0.996f, 0.886f, 0.49f, 1.0f,

		// river
		0.0f, 0.639f, 0.91f, 1.0f,
		0.0f, 0.639f, 0.91f, 1.0f,
		0.0f, 0.639f, 0.91f, 1.0f,
		0.0f, 0.639f, 0.91f, 1.0f
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

		// beach
		16, 17, 18, 19,

		// river
		20, 21, 22, 23
	};

	glGenVertexArrays(1, &VaoIdBackground);
	glBindVertexArray(VaoIdBackground);

	// Vertex Buffer
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
		xMin + 50, -65.0f, 1.0f, 1.0f,
		xMin + 150, -65.0f, 1.0f, 1.0f,
		xMin + 150, -15.0f, 1.0f, 1.0f,
		xMin + 50, -15.0f, 1.0f, 1.0f

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

void CreateVAOCar()
{
	GLfloat Vertices[] = {
		// car
		-50.0f, 25.0f, 0.0f, 1.0f,
		50.0f, 25.0f, 0.0f, 1.0f,
		50.0f, -25.0f, 0.0f, 1.0f,
		-50.0f, -25.0f, 0.0f, 1.0f,

		// brake lights
		-50.0f, 25.0f, 0.0f, 1.0f,
		-40.0f, 25.0f, 0.0f, 1.0f,
		-40.0f, 10.0f, 0.0f, 1.0f,
		-50.0f, 10.0f, 0.0f, 1.0f,

		-50.0f, -25.0f, 0.0f, 1.0f,
		-50.0f, -10.0f, 0.0f, 1.0f,
		-40.0f, -10.0f, 0.0f, 1.0f,
		-40.0f, -25.0f, 0.0f, 1.0f,

		// headlights
		50.0f, 25.0f, 0.0f, 1.0f,
		40.0f, 25.0f, 0.0f, 1.0f,
		40.0f, 5.0f, 0.0f, 1.0f,
		50.0f, 5.0f, 0.0f, 1.0f,

		50.0f, -25.0f, 0.0f, 1.0f,
		50.0f, -5.0f, 0.0f, 1.0f,
		40.0f, -5.0f, 0.0f, 1.0f,
		40.0f, -25.0f, 0.0f, 1.0f,

		// side-view mirror
		30.0f, 25.0f, 0.0f, 1.0f,
		30.0f, 35.0f, 0.0f, 1.0f,
		25.0f, 35.0f, 0.0f, 1.0f,
		25.0f, 25.0f, 0.0f, 1.0f,

		30.0f, -25.0f, 0.0f, 1.0f,
		30.0f, -35.0f, 0.0f, 1.0f,
		25.0f, -35.0f, 0.0f, 1.0f,
		25.0f, -25.0f, 0.0f, 1.0f
	};

	GLfloat Colors[] = {
		// car
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		// brake lights
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		// headlights
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		// Side-view mirror
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f
	};

	GLuint Indices[] = {
		// car
		0, 1, 2, 3,

		// brake lights
		4, 5, 6, 7,
		8, 9, 10, 11,

		// headlights
		12, 13, 14, 15,
		16, 17, 18, 19,

		// Side-view mirror
		20, 21, 22, 23,
		24, 25, 26, 27
	};

	glGenVertexArrays(1, &VaoIdCar);
	glBindVertexArray(VaoIdCar);

	// Vertex Buffer
	GLuint VboIdCar;
	glGenBuffers(1, &VboIdCar);
	glBindBuffer(GL_ARRAY_BUFFER, VboIdCar);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors);

	glGenBuffers(1, &EboIdCar);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboIdCar);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	// atribut 0 => (location = 0)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// atribut 1 => (location = 1)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(Vertices));
}

void DestroyVAOs(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EboIdBackground);
	glDeleteBuffers(1, &VboIdBackground);
	glDeleteBuffers(1, &EboIdCars);
	glDeleteBuffers(1, &VboIdCars);
	glDeleteBuffers(1, &EboIdCar);
	glDeleteBuffers(1, &VboIdCar);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoIdBackground);
	glDeleteVertexArrays(1, &VaoIdCars);
	glDeleteVertexArrays(1, &VaoIdCar);
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
	CreateVAOCar();
	CreateShaders();

	myMatrixUniformLocation = glGetUniformLocation(ProgramId, "myMatrix");
	codColLocation = glGetUniformLocation(ProgramId, "codColShader");

	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

void RenderBackground() {
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

			std::make_pair(10.0f, 220.0f),
			std::make_pair(100.0f, 240.0f),
			std::make_pair(190.0f, 170.0f),
			std::make_pair(250.0f, 270.0f),
			std::make_pair(330.0f, 210.0f),
			std::make_pair(430.0f, 180.0f),

			std::make_pair(510.0f, 250.0f),
			std::make_pair(600.0f, 270.0f),
			std::make_pair(690.0f, 230.0f),
			std::make_pair(750.0f, 300.0f),
			std::make_pair(830.0f, 270.0f),

			std::make_pair(-810.0f, 240.0f),
			std::make_pair(-750.0f, 260.0f),
			std::make_pair(-660.0f, 230.0f),
			std::make_pair(-590.0f, 270.0f)
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
			std::make_pair(1.0f, 1.0f),

			std::make_pair(0.5f, 0.5f),
			std::make_pair(0.7f, 0.7f),
			std::make_pair(0.9f, 0.9f),
			std::make_pair(0.6f, 0.6f),
			std::make_pair(0.8f, 0.8f),

			std::make_pair(0.5f, 0.5f),
			std::make_pair(0.7f, 0.7f),
			std::make_pair(0.9f, 0.9f),
			std::make_pair(0.6f, 0.6f),
			std::make_pair(0.8f, 0.8f)
		};

		for (int i = 0; i < position.size() && i < scale.size(); i++)
		{
			GLfloat posX = position[i].first - distance;
			GLfloat posY = position[i].second;

			const GLfloat& scaleX = scale[i].first;
			const GLfloat& scaleY = scale[i].second;

			if (posX - scaleX < xMin)
			{
				glm::mat4 traslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 1.0f));
				glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
				glm::mat4 myMatrix = resizeMatrix * traslateMatrix * scaleMatrix;
				glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

				glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(0));

				float overflow = xMin - posX;
				posX = xMax - overflow;
			}

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

	// strip
	for (float posX = xMin; posX <= xMax; posX += 150.0f)
	{
		float newPosX = posX - distance;

		if (newPosX - 50.0f < xMin)
		{
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(newPosX, 0.0f, 1.0f));
			glm::mat4 myMatrix = resizeMatrix * translateMatrix;
			glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));

			float overflow = xMin - newPosX;
			newPosX = xMax - overflow;
		}

		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(newPosX, 0.0f, 1.0f));
		glm::mat4 myMatrix = resizeMatrix * translateMatrix;
		glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));
	}

	{ // river
		std::vector<std::pair<GLfloat, GLfloat>> position = {
			std::make_pair(-850, -240.0f),
			std::make_pair(-700, -210.0f),
			std::make_pair(-510, -180.0f),
			std::make_pair(-270, -210.0f),
			std::make_pair(70, -230.0f),
			std::make_pair(440, -250.0f),
			std::make_pair(750, -270.0f)
		};

		std::vector<std::pair<GLfloat, GLfloat>> scale = {
			std::make_pair(50.0f, 80.0f),
			std::make_pair(100.0f, 90.0f),
			std::make_pair(100.0f, 75.0f),
			std::make_pair(150.0f, 80.0f),
			std::make_pair(200.0f, 85.0f),
			std::make_pair(180.0f, 80.0f),
			std::make_pair(150.0f, 75.0f)
		};

		for (int i = 0; i < position.size() && i < scale.size(); i++)
		{
			GLfloat posX = position[i].first - distance;
			GLfloat posY = position[i].second;

			const GLfloat& scaleX = scale[i].first;
			const GLfloat& scaleY = scale[i].second;

			if (posX - scaleX < xMin)
			{
				glm::mat4 traslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 1.0f));
				glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
				glm::mat4 myMatrix = resizeMatrix * traslateMatrix * scaleMatrix;
				glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

				glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint)));

				float overflow = xMin - posX;
				posX = xMax - overflow;
			}

			glm::mat4 traslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 1.0f));
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
			glm::mat4 myMatrix = resizeMatrix * traslateMatrix * scaleMatrix;
			glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint)));
		}
	}

	// beach
	{
		std::vector<std::pair<GLfloat, GLfloat>> position = {
			std::make_pair(-850, -180.0f),
			std::make_pair(-700, -150.0f),
			std::make_pair(-510, -120.0f),
			std::make_pair(-270, -150.0f),
			std::make_pair(70, -170.0f),
			std::make_pair(440, -190.0f),
			std::make_pair(750, -210.0f),

			std::make_pair(-850, -330.0f),
			std::make_pair(-700, -300.0f),
			std::make_pair(-510, -270.0f),
			std::make_pair(-270, -300.0f),
			std::make_pair(70, -320.0f),
			std::make_pair(440, -340.0f),
			std::make_pair(750, -360.0f),
		};

		std::vector<std::pair<GLfloat, GLfloat>> scale = {
			std::make_pair(50.0f, 20.0f),
			std::make_pair(100.0f, 30.0f),
			std::make_pair(100.0f, 15.0f),
			std::make_pair(150.0f, 20.0f),
			std::make_pair(200.0f, 25.0f),
			std::make_pair(180.0f, 20.0f),
			std::make_pair(150.0f, 15.0f),

			std::make_pair(50.0f, 20.0f),
			std::make_pair(100.0f, 30.0f),
			std::make_pair(100.0f, 15.0f),
			std::make_pair(150.0f, 20.0f),
			std::make_pair(200.0f, 25.0f),
			std::make_pair(180.0f, 20.0f),
			std::make_pair(150.0f, 15.0f),
		};

		for (int i = 0; i < position.size() && i < scale.size(); i++)
		{
			GLfloat posX = position[i].first - distance;
			GLfloat posY = position[i].second;

			const GLfloat& scaleX = scale[i].first;
			const GLfloat& scaleY = scale[i].second;

			if (posX - scaleX < xMin)
			{
				glm::mat4 traslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 1.0f));
				glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
				glm::mat4 myMatrix = resizeMatrix * traslateMatrix * scaleMatrix;
				glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

				glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(20 * sizeof(GLuint)));

				float overflow = xMin - posX;
				posX = xMax - overflow;
			}

			glm::mat4 traslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 1.0f));
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
			glm::mat4 myMatrix = resizeMatrix * traslateMatrix * scaleMatrix;
			glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(20 * sizeof(GLuint)));
		}
	}
}

float speedGreenCar = 1.5f, posXGreenCar = 0.0f;
float speedRedCar = 1.5f, posYRedCar = 0.0f;
float turningAngle = 0;
const int timer = 16;
int codCol;
bool colide = false;

void resetState() {
	speedGreenCar = 1.5f; posXGreenCar = 0.0f;
	speedRedCar = 1.5f; posYRedCar = 0.0f;
	turningAngle = 0;
	codCol = 0;
	colide = false;
}

bool checkPointInRectangle(float px, float py, float xMin, float xMax, float yMin, float yMax) {
	if (xMin <= px && px <= xMax && yMin <= py && py <= yMax) return true;
	return false;
}

void checkColision() {
	float greenCarXMin = xMin + 300 + posXGreenCar, greeCarXMax = xMin + 400 + posXGreenCar;
	float greenCarYMin = -65, greenCarYMax = -15;

	float newLowerLeftX = xMin + 50.0f - 50.0f * cos(glm::radians(turningAngle)) + 25.0f * sin(glm::radians(turningAngle));
	float newLowerLeftY = -40.0f + posYRedCar - 25.0f * cos(glm::radians(turningAngle)) - 50.0f * sin(glm::radians(turningAngle));
	colide |= checkPointInRectangle(newLowerLeftX, newLowerLeftY, greenCarXMin, greeCarXMax, greenCarYMin, greenCarYMax);

	float newUpperLeftX = xMin + 50.0f - 50.0f * cos(glm::radians(turningAngle)) - 25.0f * sin(glm::radians(turningAngle));
	float newUpperLeftY = -40.0f + posYRedCar + 25.0f * cos(glm::radians(turningAngle)) - 50.0f * sin(glm::radians(turningAngle));
	colide |= checkPointInRectangle(newUpperLeftX, newUpperLeftY, greenCarXMin, greeCarXMax, greenCarYMin, greenCarYMax);

	float newUpperRightX = xMin + 50.0f + 50.0f * cos(glm::radians(turningAngle)) - 25.0f * sin(glm::radians(turningAngle));
	float newUpperRightY = -40.0f + posYRedCar + 25.0f * cos(glm::radians(turningAngle)) + 50.0f * sin(glm::radians(turningAngle));
	colide |= checkPointInRectangle(newUpperRightX, newUpperRightY, greenCarXMin, greeCarXMax, greenCarYMin, greenCarYMax);

	float newLowerRightX = xMin + 50.0f + 50.0f * cos(glm::radians(turningAngle)) + 25.0f * sin(glm::radians(turningAngle));
	float newLowerRightY = -40.0f + posYRedCar - 25.0f * cos(glm::radians(turningAngle)) + 50.0f * sin(glm::radians(turningAngle));
	colide |= checkPointInRectangle(newLowerRightX, newLowerRightY, greenCarXMin, greeCarXMax, greenCarYMin, greenCarYMax);

	if (newLowerLeftY < -85.0f || newUpperLeftY < -85.0f || newUpperRightY < -85.0f || newLowerRightY < -85.0f) colide = true;
	if (newLowerLeftY > 85.0f || newUpperLeftY > 85.0f || newUpperRightY > 85.0f || newLowerRightY > 85.0f) colide = true;
}

void recalcSpeed(unsigned int lastSpeedKey) {
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
	if (speedRedCar < 1.5f) speedRedCar = 1.5f;
}

void recalcAngle() {
	if (turningAngle > 0) turningAngle -= glm::min(0.5f, turningAngle);
	else turningAngle -= glm::max(-0.5f, turningAngle);
	if (turningAngle > 45) turningAngle = 45;
	if (turningAngle < -45) turningAngle = -45;
}

void idleFunction(int val) {
	checkColision();
	if (colide) {
		codCol += 1;
		codCol %= 2;
		glutPostRedisplay();
		glutTimerFunc(500, idleFunction, 0);
		return;
	}
	posXGreenCar += speedGreenCar;

	// input
	if (keyStates['w'] || keyStates['W'])
	{
		recalcSpeed('w');
	}
	
	if (keyStates['s'] || keyStates['S'])
	{
		recalcSpeed('s');
	}
	
	if (keyStates['a'] || keyStates['A'])
	{
		if (!colide) turningAngle += 2.0f;
	}
	
	if (keyStates['d'] || keyStates['D'])
	{
		if (!colide) turningAngle -= 2.0f;
	}

	recalcAngle();
	// posXRedCar += speedRedCar * cos(glm::radians(turningAngle));
	posYRedCar += speedRedCar * sin(glm::radians(turningAngle));
	glutPostRedisplay();
	glutTimerFunc(timer, idleFunction, 0);

	distance += speedRedCar;
	if (distance > winWidth)
	{
		distance -= winWidth;
	}
}


void keyBoardFunc(unsigned char key, int x, int y)
{
	keyStates[key] = true;

	if (key == 'r' || key == 'R')
	{
		resetState();
	}
}

void keyBoardUpFunc(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}


void RenderCars() {
	glBindVertexArray(VaoIdCars);

	//greencar
	glm::mat4 myMatrix = resizeMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(posXGreenCar, 0.0f, 0.0f));
	glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(0));

	//redCar
	glUniform1i(codColLocation, codCol);
	myMatrix = resizeMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, posYRedCar, 0.0f))
							* glm::translate(glm::mat4(1.0f), glm::vec3(xMin + 50, -40, 0.0f))
							* glm::rotate(glm::mat4(1.0f), glm::radians(turningAngle), glm::vec3(0.0f, 0.0f, 1.0f))
							* glm::translate(glm::mat4(1.0f), glm::vec3(-xMin - 50, 40, 0.0f));
	glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (void*)(4 * sizeof(GLuint)));
	glUniform1i(codColLocation, 0);

	// new car
	glBindVertexArray(VaoIdCar);

	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixUniformLocation, 1, GL_FALSE, &myMatrix[0][0]);

	glDrawElements(GL_QUADS, 28, GL_UNSIGNED_INT, (void*)(0));
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);       
	RenderBackground();
	RenderCars();

	glFlush();
}

void Cleanup(void)
{
	DestroyShaders();
	DestroyVAOs();
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
	glutKeyboardUpFunc(keyBoardUpFunc);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}

