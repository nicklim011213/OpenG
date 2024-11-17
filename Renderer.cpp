#include "Renderer.h"
#include "WorldData.h"
#include <array>

void Renderer::RenderSetup(ItemCollection ItemsToDraw, RenderAddresses* RenderObjects)
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	RenderObjects->VertexShader = vertexShader;

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	float VertexArray[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	RenderObjects->FragmentShader = fragmentShader;

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	RenderObjects->ShaderProgram = shaderProgram;

	unsigned int VertexArrayObject;
	unsigned int VertexBufferObject;
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glBindVertexArray(VertexArrayObject);
	RenderObjects->VAO = VertexArrayObject;

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexArray), VertexArray, GL_STATIC_DRAW);
	RenderObjects->VBO = VertexBufferObject;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
}

void Renderer::RenderLoop(GLFWwindow* window, RenderAddresses* RenderObjects)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(RenderObjects->ShaderProgram);
	glBindVertexArray(RenderObjects->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glfwSwapBuffers(window);
	glfwPollEvents();
}
