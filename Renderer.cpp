#include "Renderer.h"
#include "WorldData.h"
#include <array>

void Renderer::RenderSetup(ItemCollection ItemsToDraw)
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

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	std::deque<CompleteItem> UnpackedItems = ItemsToDraw.ItemList;

	for (int i = 0; i != UnpackedItems.size(); ++i)
	{

		const int size = UnpackedItems[i].VertexList.size() * 3;
		float* VertexArray = new float[size];
		for (int j = 0; j != UnpackedItems[i].VertexList.size(); j += 3)
		{
			VertexArray[j] = UnpackedItems[i].VertexList[j].X;
			VertexArray[j + 1] = UnpackedItems[i].VertexList[j + 1].Y;
			VertexArray[j + 2] = UnpackedItems[i].VertexList[j + 2].Z;
		}


		unsigned int VertexArrayObject;
		glGenVertexArrays(1, &VertexArrayObject);
		glBindVertexArray(VertexArrayObject);


		unsigned int VertexBufferObject;
		glGenBuffers(1, &VertexBufferObject);
		glBindBuffer(VertexBufferObject, GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexArray), VertexArray, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VertexArrayObject);
	}
}

void Renderer::RenderLoop(GLFWwindow* window)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}
