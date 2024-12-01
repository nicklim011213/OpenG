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

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	RenderObjects->FragmentShader = fragmentShader;

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	RenderObjects->ShaderProgram = shaderProgram;


	for (int i = 0; i != ItemsToDraw.ItemList.size(); ++i)
	{
		auto CurrentItem = ItemsToDraw.ItemList[i];
		std::vector<float> Points;
		std::vector<int> Indexes;
		for (int j = 0; j != CurrentItem.VertexList.size(); ++j)
		{
			Points.push_back(CurrentItem.VertexList[j].X);
			Points.push_back(CurrentItem.VertexList[j].Y);
			Points.push_back(CurrentItem.VertexList[j].Z);
		}
		for (int k = 0; k != CurrentItem.VertexIndex.size(); ++k)
		{
			Indexes.push_back(CurrentItem.VertexIndex[k]);
		}

		glGenVertexArrays(1, &RenderObjects->VAO);
		glGenBuffers(1, &RenderObjects->VBO);
		glGenBuffers(1, &RenderObjects->EBO);

		glBindVertexArray(RenderObjects->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, RenderObjects->VBO);
		glBufferData(GL_ARRAY_BUFFER, Points.size() * sizeof(float), Points.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RenderObjects->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indexes.size() * sizeof(int), Indexes.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		RenderObjects->ShaderProgram = shaderProgram;

	}
}

void Renderer::RenderLoop(GLFWwindow* window, RenderAddresses* RenderObjects)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(RenderObjects->ShaderProgram);
	glBindVertexArray(RenderObjects->VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
	glfwPollEvents();
}
