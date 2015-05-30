#include "game.h"
#include "tex.h"
#include <glm/ext.hpp>
#include <functional>
#include <algorithm>

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
	bird = unique_ptr<Bird>(new Bird(tex));

	backgroundTexture = loadTextureFromFile("img/background.png");

	worldRect = unique_ptr<Rect>(new Rect());
	updateWorldRect();
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
	updateVisibility();

	updateWorldRect();

	checkCollision();


	//TODO update world logic here
}
void Game::generateWorld()
{	
	//TODO pretty world	
}

void Game::updateWorldRect()
{
	float birdOffset = bird->getPosition().x;
	worldRect->min = glm::vec2(-ratio + birdOffset, -1);
	worldRect->max = glm::vec2(ratio + birdOffset, 1);
}

void Game::updateVisibility()
{
	auto world = getWorldRect();
	auto func = bind(isVisible, placeholders::_1, *world);

	//Copy all visible objects to visibleObstacles
	auto it = copy_if(obstacles.begin(), obstacles.end(), visibleObstacles.begin(), func);
	visibleObstacles.resize(distance(visibleObstacles.begin(), it));
}

bool isVisible(shared_ptr<Obstacle> obstacle, const Rect & rect)
{
	return obstacle->inside(rect);
}

void Game::checkCollision()
{
	Circle* collider = bird->getCollider();
	
	float top = collider->center.y + collider->radius;
	float bottom = collider->center.y - collider->radius;

	if(top > 0.9f || bottom < -0.9f)
	{
		handleCollision();
	}

	//Only check collision for visible obstacles	
	for (vector<shared_ptr<Obstacle>>::iterator it = visibleObstacles.begin() ; it != visibleObstacles.end(); ++it)
	{
				
	}
}

void Game::handleCollision()
{
	//TODO show replay screen?
	bird->reset();

	//TODO world reset
}

unique_ptr<Rect> Game::getWorldRect()
{
	float birdOffset = bird->getPosition().x;
	auto world = unique_ptr<Rect>(new Rect());
	world->min = glm::vec2(-ratio + birdOffset, -1);
	world->max = glm::vec2(ratio + birdOffset, 1);
	return world;
}

void Game::draw() 
{
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(worldRect->min.x, worldRect->max.x, worldRect->min.y, worldRect->max.y, 0.f, -10.f);
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
	glTexCoord2f(worldRect->min.x, 1.f); glVertex2f(worldRect->min.x, worldRect->max.y);
	glTexCoord2f(worldRect->max.x, 1.f); glVertex2fv(glm::value_ptr(worldRect->max));
	glTexCoord2f(worldRect->max.x, 0.f); glVertex2f(worldRect->max.x, worldRect->min.y);
	glTexCoord2f(worldRect->min.x, 0.f); glVertex2fv(glm::value_ptr(worldRect->min));
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
