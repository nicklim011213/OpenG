#ifndef RENDERER
#define RENDERER
#include <glad.h> 
#include <glfw3.h>
#include "WorldData.h"

class Renderer
{
	public:
		void RenderSetup(ItemCollection ItemsToDraw);

		void RenderLoop(GLFWwindow* window);
};

#endif