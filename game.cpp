#include "game.h"
#include <iostream>
#include "tex.h"

Game::Game()
{
	startWindowX = 640;
	startWindowY = 480;

	if(!glfwInit())
		throw "Failed to load glfw context!";
	lastFrameTime = 0;

	initWindow();

	
	initGLObjs();
}

//All OpenGL-related initalization logic should be put here
void Game::initGLObjs()
{
	glfwMakeContextCurrent(window);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);

    	glfwSwapInterval(1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	const GLuint tex = loadTextureFromFile("img/pidgeot.png");
	bird = new Bird(tex);

	backgroundTexture = loadTextureFromFile("img/background.png");
}

void Game::initWindow()
{
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

void Game::resizeCallback(GLFWwindow* window, int width, int height)
{
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, GL_TRUE);

	if(key == GLFW_KEY_P && action == GLFW_PRESS)
		pause();

	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		bird->flap();
}

void Game::update(double delta)
{
	bird->update(delta);
	//TODO update world logic here
}

void Game::draw() 
{
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 0.f, -10.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

	drawBackground();

	bird->draw();

	drawObstacles();
}

void Game::drawBackground()
{
	glDisable(GL_DEPTH_TEST);
	glTexParameteri( GL_TEXTURE_2D, 
                 GL_TEXTURE_WRAP_T, 
                 GL_REPEAT );	
	glTexParameteri( GL_TEXTURE_2D, 
                 GL_TEXTURE_WRAP_S, 
                 GL_REPEAT );
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f); glVertex3f(-ratio, 1.f, 10.f);
    	glTexCoord2f(ratio, 1.f); glVertex3f(ratio, 1.f, 10.f);
	glTexCoord2f(ratio, 0.f); glVertex3f(ratio, -1.f, 10.f);
	glTexCoord2f(0.f, 0.f); glVertex3f(-ratio, -1.f, 10.f);
	glEnd();
	glEnable(GL_DEPTH_TEST);
}

void Game::drawObstacles()
{
	//TODO obstacles
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
