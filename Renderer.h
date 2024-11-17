#ifndef RENDERER
#define RENDERER
#include <glad.h> 
#include <glfw3.h>
#include "WorldData.h"

struct RenderAddresses
{
	unsigned int VAO, VBO, VertexShader, FragmentShader, ShaderProgram;
};

class Renderer
{
	public:
		void RenderSetup(ItemCollection ItemsToDraw, RenderAddresses* RenderObjects);

		void RenderLoop(GLFWwindow* window, RenderAddresses* RenderObjects);
};

#endif