#include "game.h"
#include <iostream>
#include "tex.h"

Game::Game()
{
	startWindowX = 640;
	startWindowY = 480;

	//const Texture &tex = loadTextureFromFile("somesprite.png");
	//bird = new Bird(tex);
	
	if(!glfwInit())
		throw "Failed to load glfw context!";
	lastFrameTime = 0;

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

	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		bird->flap();
	//TODO BleepyBird here
}

void Game::update(double delta)
{

	bird->update(delta);
	//TODO update world logic here
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

	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	
	glPushMatrix();
	bird->draw();
	glPopMatrix();

	//TODO draw world, obstacles here
}

void Game::play()
{
	shouldPause = 0;

	while(!glfwWindowShouldClose(window) && !shouldPause)
	{
		double currentFrameTime = glfwGetTime();
		double delta = currentFrameTime - lastFrameTime;

		update(delta);
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastFrameTime = currentFrameTime;
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
