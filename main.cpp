#include "game.h"
#include <cstdlib>
#include <exception>
#include <iostream>
using namespace std;

static Game game;

static void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW error:" << description << std::endl;
}

//Because GLFW is a C library, we cannot use member functions of Game directly. Thus we use normal functions and pass the call to Game
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	game.keyCallback(window, key, scancode, action, mods);
}

static void resizeCallback(GLFWwindow* window, int width, int height)
{
	game.resizeCallback(window, width, height);
}
int main() 
{
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(game.getWindow(), keyCallback);
	glfwSetFramebufferSizeCallback(game.getWindow(), resizeCallback); 
	try
	{
		game.play();
		game.stop();
		return EXIT_SUCCESS;
	}
	catch(exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
	
}

