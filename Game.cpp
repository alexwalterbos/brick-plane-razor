#include "Game.h"
#include <iostream>

Game::Game()
{
	startWindowX = 640;
	startWindowY = 480;
	
	if(!glfwInit())
		throw "Failed to load glfw context!";
	window = glfwCreateWindow(startWindowX, startWindowY, "Mustache Nemesis", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		throw "Could not create new window!";
	}

}

GLFWwindow* Game::getWindow()
{
	return window;
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, GL_TRUE);

	if(key == GLFW_KEY_P && action == GLFW_PRESS)
		pause();

	//TODO BleepyBird here
}

void Game::update()
{
	//TODO update logic here
}

void Game::draw() 
{
	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//TODO matrix here
	//TODO draw world, bird, obstacles here
}

void Game::play()
{
	shouldPause = 0;

	while(!glfwWindowShouldClose(window) && !shouldPause)
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

/**
 * Called when the game should terminate
 */
void Game::stop()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

/**
 * We use a simple boolean based toggle to switch the state. 
 */
void Game::pause()
{
	shouldPause = 1;
}
