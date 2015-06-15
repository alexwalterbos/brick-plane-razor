#include "game.h"
#include "tex.h"
#include <glm/ext.hpp>
#include <functional>
#include <algorithm>
#include <random>
#include <iostream>

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

	const GLuint tex = loadTextureFromFile("img/cannon.png");
	bird = unique_ptr<Bird>(new Bird(tex));

	backgroundTexture = loadTextureFromFile("img/background.png");

	worldRect = unique_ptr<Rect>(new Rect());
	updateWorldRect();
	generateWorld();
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
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, GL_TRUE);

	if(key == GLFW_KEY_P && action == GLFW_PRESS)
		paused = !paused;

	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		bird->flap();

	if(key == GLFW_KEY_F && action == GLFW_PRESS)
		handleFire();
}

void Game::handleFire()
{
	// TODO handle multiple bullets.
	bullets.push_back(bird->fire());
	GLuint tex = loadTextureFromFile("img/pew-text.png");
	pew = unique_ptr<Pew>(new Pew(tex, bird->getPosition()));
}

void Game::update(double delta)
{
	bird->update(delta);

	if(!bullets.empty())
	{
		vector<unique_ptr<Bullet>>::iterator i;
		for(i = bullets.begin(); i != bullets.end(); ++i) 
		{
			(*i)->update(delta);
		}
	}

	updateVisibility();
	updateWorldRect();
	checkCollision();
}

void Game::generateWorld()
{	
	//Separation between obstacles
	float separation = startSeparation;
	float currentPosition = obstacleStartPosition;

	default_random_engine generator(random_device{}());
	uniform_real_distribution<float> center(-0.8f, 0.8f);

	while(currentPosition < playDistance)
	{
		float centerPos = center(generator);

		Rect bottomCollider;
		bottomCollider.min = glm::vec2(currentPosition, -1.f);
		bottomCollider.max = glm::vec2(currentPosition + obstaclesWidth, centerPos - obstacleHoleSize/2.f);

		obstacles.push_back(bottomCollider);
	
		Rect topCollider;
		topCollider.min = glm::vec2(currentPosition, centerPos + obstacleHoleSize/2.f);
		topCollider.max = glm::vec2(currentPosition + obstaclesWidth, 1.f);

		obstacles.push_back(topCollider);

		currentPosition += separation;
		separation -= 0.01f;
	}
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
	copy_if(obstacles.begin(), obstacles.end(), back_inserter(visibleObstacles), func);

	vector<unsigned int> invisibles;
	unsigned int i;
	for(i = 0; i < bullets.size(); i++)
	{
		Circle* collider = bullets[i]->getCollider();
		if(!isCircleVisible(*collider, *world))
		{
			invisibles.push_back(i);
		}
	}

	vector<unsigned int>::iterator it;
	for(it = invisibles.end(); it != invisibles.begin(); --it)
	{
		bullets.erase(bullets.begin() + (*it - 1));
		std::cout << "Erased: " + std::to_string(*it) << std::endl;
	}

	invisibles.clear();
}

bool isVisible(Rect obstacle, const Rect & worldRect)
{
	return Collision::intersects(obstacle, worldRect);
}

bool isCircleVisible(Circle circle, const Rect & worldRect)
{
	return Collision::intersects(worldRect, circle);
}

void Game::checkCollision()
{
	Circle* collider = bird->getCollider();
	
	float top = collider->center.y + collider->radius;
	float bottom = collider->center.y - collider->radius;

	if(top > 0.9f || bottom < -0.9f)
	{
		handleCollision();
		return;
	}

	//Only check collision for visible obstacles	
	for (vector<Rect>::iterator it = visibleObstacles.begin() ; it != visibleObstacles.end(); ++it)
	{
		if(Collision::intersects(*it, *collider)) 
		{
			handleCollision();
			return;
		}
	}
}

void Game::handleCollision()
{
	//TODO show replay screen?
	bird->reset();
	pew = 0;

	bullets.clear();
	obstacles.clear();
	visibleObstacles.clear();
	generateWorld();
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
	
	glPushMatrix();
	bird->draw();
	if(pew != 0){
		pew->draw();
	}
	if(!bullets.empty())
	{
		vector<unique_ptr<Bullet>>::iterator i;
		for(i = bullets.begin(); i != bullets.end(); ++i) 
		{
			(*i)->draw();
		}
	}
	glPopMatrix();

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
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3f(1.f, 0.f, 0.f);
	for (vector<Rect>::iterator it = visibleObstacles.begin() ; it != visibleObstacles.end(); ++it)
	{
		glm::vec2 a = it->min, 
			b = glm::vec2(it->min.x, it->max.y),
			c = it->max, 
			d = glm::vec2(it->max.x, it->min.y);

		glVertex2fv(glm::value_ptr(a));
		glVertex2fv(glm::value_ptr(b));

		glVertex2fv(glm::value_ptr(b));
		glVertex2fv(glm::value_ptr(c));

		glVertex2fv(glm::value_ptr(c));
		glVertex2fv(glm::value_ptr(d));

		glVertex2fv(glm::value_ptr(d));
		glVertex2fv(glm::value_ptr(a));
	}
	glColor3f(1.f, 1.f, 1.f);
	glEnd();
	glEnable(GL_DEPTH_TEST);
}

void Game::play()
{
	while(!glfwWindowShouldClose(window))
	{
		double currentFrameTime = glfwGetTime();
		if(!paused)
		{
			double delta = currentFrameTime - lastFrameTime;
			update(delta);
		}
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
