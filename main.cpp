#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

#include"Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

// Vertices coordinates
GLfloat vertices[] =
{
	// FRONT
	-0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

	// BACK
	-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f,

	// LEFT
	-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

	// RIGHT
	 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

	// TOP
	-0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,

	// BOTTOM
	-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	// Front
	0, 1, 2,
	0, 2, 3,

	// Back
	4, 5, 6,
	4, 6, 7,

	// Left
	8, 9, 10,
	8, 10, 11,

	// Right
	12, 13, 14,
	12, 14, 15,

	// Top
	16, 17, 18,
	16, 18, 19,

	// Bottom
	20, 21, 22,
	20, 22, 23
};

float rotation = 0.0f;
double prevTime = glfwGetTime();



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Learning", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture texture("textures/spruce_log.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapInterval(1);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1/60.0f) {
			rotation += 0.5f;
			prevTime = currentTime;
		};

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -4.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)(800/800), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projectionLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.0f);

		texture.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	texture.Delete();
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}