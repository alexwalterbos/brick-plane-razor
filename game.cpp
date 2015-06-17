#include "game.h"
#include "tex.h"
#include "simplexnoise.h"
#include <glm/ext.hpp>
#include <functional>
#include <algorithm>
#include <random>
#include <iostream>

Game::Game()
{
	startWindowX = 1920;
	startWindowY = 1080;

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

	blade = unique_ptr<Mesh>(new Mesh());
	blade->loadMesh("models/blade.obj");
	bladeTexture = loadTextureFromFile("img/metal.jpg");

	const GLuint tex = loadTextureFromFile("img/cannon.png");
	vector<GLuint> texs;
	for(int i = 0; i < 8; i++)
	{
		auto s = "img/razor" + to_string(i) + ".png";
		texs.push_back(loadTextureFromFile(s.c_str()));
	}
	for(int i = 0; i < 8; i++)
	{
		auto s = "img/plane" + to_string(i) + ".png";
		texs.push_back(loadTextureFromFile(s.c_str()));
	}
	for(int i = 0; i < 8; i++)
	{
		auto s = "img/brick" + to_string(i) + ".png";
		texs.push_back(loadTextureFromFile(s.c_str()));
	}
	bird = unique_ptr<Bird>(new Bird(tex, texs));

	backgroundTexture = loadTextureFromFile("img/background.png");
	worldRect = unique_ptr<Rect>(new Rect());
	updateWorldRect();
}

void Game::initWindow()
{
	const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	window = glfwCreateWindow(vidmode->width, vidmode->height, "Mustache Nemesis", glfwGetPrimaryMonitor(), NULL);
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
	
	if(key == GLFW_KEY_C && action == GLFW_PRESS && !paused)
		handleFire(Material::razor);

	if(key == GLFW_KEY_V && action == GLFW_PRESS && !paused)
		handleFire(Material::plane);

	if(key == GLFW_KEY_B && action == GLFW_PRESS && !paused)
		handleFire(Material::brick);

	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS && !paused)
		bird->flap();
}

void Game::handleFire(Material material)
{
	if(timeSinceFire < fireThreshold)
		return;

	bullets.push_back(bird->fire(material));
	GLuint tex = loadTextureFromFile("img/pew-text.png");
	pew = unique_ptr<Pew>(new Pew(tex, bird->getPosition()));

	timeSinceFire = 0;
}

void Game::update(double delta)
{
	timeSinceFire += (float) delta;

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
	updateWorld();
	checkCollision();
}

void Game::updateWorld()
{	
	bool separationCue = true;

	if(!obstacles.empty())
	{
		float diff = (*worldRect).max.x - obstacles.back().getRect().max.x;

		separationCue = diff > (separation - outsideWorldOffset);
	}

	default_random_engine generator(random_device{}());
	uniform_real_distribution<float> center(-0.8f, 0.8f);

	if(separationCue)
	{
		float centerPos = center(generator);
		Material material = static_cast<Material>(rand() % 3);

		float newMinX = worldRect->max.x + outsideWorldOffset;

		Rect bottomCollider;
		bottomCollider.min = glm::vec2(newMinX, worldRect->min.y);
		bottomCollider.max = glm::vec2(newMinX + obstaclesWidth, centerPos - obstacleHoleSize/2.f);

		obstacles.push_back(Obstacle(material, bottomCollider, true));
	
		Rect topCollider;
		topCollider.min = glm::vec2(newMinX, centerPos + obstacleHoleSize/2.f);
		topCollider.max = glm::vec2(newMinX + obstaclesWidth, worldRect->max.y);

		obstacles.push_back(Obstacle(material, topCollider, false));

		separation -= 0.01f; //increase difficulty (slowly)
	}

	vector<Obstacle>::iterator it = obstacles.begin();

	while((*it).getRect().max.x < (*worldRect).min.x)
	{
		obstacles.erase(it);
	}
}

void Game::updateWorldRect()
{
	float birdOffset = bird->getPosition().x + cameraOffset;
	float hFarHalf = tan(fov * PI / 360.f) * 2.f;
	worldRect->min = glm::vec2(-hFarHalf * ratio + birdOffset, -hFarHalf);
	worldRect->max = glm::vec2(hFarHalf * ratio + birdOffset, hFarHalf);
}

void Game::updateVisibility()
{
	vector<unique_ptr<Bullet>>::iterator it = bullets.begin();

	while(it != bullets.end())
	{
		Circle collider = (*it)->getCollider();
		if(!isCircleVisible(collider, *worldRect))
		{
			it = bullets.erase(it);
		}
		else
		{
			++it;
		}

	}
}

bool isObstacleVisible(Obstacle obstacle, const Rect & worldRect)
{
	return Collision::intersects(obstacle.getRect(), worldRect);
}

bool isCircleVisible(Circle circle, const Rect & worldRect)
{
	return Collision::intersects(worldRect, circle);
}

void Game::checkCollision()
{
	Circle collider = bird->getCollider();
	
	float top = collider.center.y + collider.radius;
	float bottom = collider.center.y - collider.radius;

	if(top > worldRect->max.y || bottom < worldRect->min.y)
	{
		handleCollision();
		return;
	}

	for (vector<Obstacle>::iterator it = obstacles.begin() ; it != obstacles.end(); ++it)
	{
		if(Collision::intersects(it->getRect(), collider)) 
		{
			handleCollision();
			return;
		}
	}

	vector<unique_ptr<Bullet>>::iterator bit = bullets.begin();
	while(bit != bullets.end())
	{
		bool collision;
		vector<Obstacle>::iterator oit = obstacles.begin();
		while(oit != obstacles.end())
		{
			collision = false;
			if(Collision::intersects(oit->getRect(), (*bit)->getCollider()))
			{
				if(winsOf((*bit)->getMaterial(), oit->getMaterial()))
				{
					obstacles.erase(oit);
					currentScore++;
				}
				bullets.erase(bit);
				collision = true;
				break;
			}
			else
				++oit;
		}

		if(!collision)
			++bit;
	}
}

void Game::handleCollision()
{
	if(bird->getPosition().x > distanceHighScore)
		distanceHighScore = bird->getPosition().x;
	
	bird->reset();
	pew = 0;

	bullets.clear();
	obstacles.clear();
	
	if(currentScore > highScore)
		highScore = currentScore;
	currentScore = 0;
}

void Game::draw() 
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	drawBackground();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
	glm::mat4 proj = glm::perspective(fov, ratio, nearDist, farDist);
	proj = glm::translate(proj, glm::vec3(-bird->getPosition().x - cameraOffset, 0.f, 0.f)); 
	proj = glm::translate(proj, glm::vec3(0.f, 0.f, -2.f));
	glLoadMatrixf(glm::value_ptr(proj));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	drawHeightMap();

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

glm::vec3 computeNormal(glm::vec3 const & a, glm::vec3 const & b, glm::vec3 const & c)
{
	return glm::normalize(glm::cross(b - a, c - a));
}

void Game::drawHeightMap()
{
	Rect r;
	float birdOffset = bird->getPosition().x + cameraOffset;
	float hFarHalf = tan(fov * PI / 360.f) * (farDist + 1);
	r.min = glm::vec2(-hFarHalf * ratio + birdOffset, -hFarHalf);
	r.max = glm::vec2(hFarHalf * ratio + birdOffset, hFarHalf);

	float xSize = (r.max.x - r.min.x) / heightMapStepX;
	float zSize = (farDist - nearDist) / heightMapStepZ;
	float startX = xSize * (int)(r.min.x / xSize);
	
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < heightMapStepX; i++)
	{
		for(int j = 0; j < heightMapStepZ; j++)
		{
			drawQuad(i, j, startX, xSize, zSize);				
		}
	}
	glColor3f(1.f, 1.f, 1.f);
	glEnd();
}
glm::vec4 Game::calculateColor(glm::vec3 normal) 
{
	float intensity = glm::dot(normal, invLightDir);
	return groundColor * intensity;
}

void Game::drawQuad(int stepX, int stepZ, float startX, float xSize, float zSize)
{
	glm::vec3 a(startX + stepX * xSize, -2.f, -stepZ * zSize),
		b(startX + (stepX + 1) * xSize, -2.f, -stepZ * zSize),
		c(startX + stepX * xSize, -2.f, -(stepZ + 1) * zSize),
		d(startX + (stepX + 1) * xSize, -2.f, -(stepZ + 1) * zSize);
	
	a.y += raw_noise_2d(a.x * heightMapScale, a.z * heightMapScale);
	b.y += raw_noise_2d(b.x * heightMapScale, b.z * heightMapScale);
	c.y += raw_noise_2d(c.x * heightMapScale, c.z * heightMapScale);
	d.y += raw_noise_2d(d.x * heightMapScale, d.z * heightMapScale);

	glm::vec3 normal = computeNormal(a, b, c);

	glm::vec4 color = calculateColor(normal);
	glColor3fv(glm::value_ptr(color));
	glVertex3fv(glm::value_ptr(a));
	glNormal3fv(glm::value_ptr(normal));

	glVertex3fv(glm::value_ptr(b));
	glNormal3fv(glm::value_ptr(normal));

	glVertex3fv(glm::value_ptr(c));
	glNormal3fv(glm::value_ptr(normal));

	glVertex3fv(glm::value_ptr(b));
	glNormal3fv(glm::value_ptr(normal));

	glVertex3fv(glm::value_ptr(d));
	glNormal3fv(glm::value_ptr(normal));

	glVertex3fv(glm::value_ptr(c));
	glNormal3fv(glm::value_ptr(normal));
}

void Game::drawBackground()
{
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glTexParameteri( GL_TEXTURE_2D, 
                 GL_TEXTURE_WRAP_T, 
                 GL_REPEAT );	
	glTexParameteri( GL_TEXTURE_2D, 
                 GL_TEXTURE_WRAP_S, 
                 GL_REPEAT );
	float xOffset = bird->getPosition().x * 0.1f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(xOffset - ratio, 1.f); glVertex2f(-1.f, 1.f);
	glTexCoord2f(xOffset + ratio, 1.f); glVertex2f(1.f, 1.f);
	glTexCoord2f(xOffset + ratio, 0.f); glVertex2f(1.f, -1.f);
	glTexCoord2f(xOffset - ratio, 0.f); glVertex2f(-1.f, -1.f);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::drawObstacles()
{
	glBindTexture(GL_TEXTURE_2D, bladeTexture);
	for(vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		glPushMatrix();
		switch(it->getMaterial())
		{
			case Material::razor:
				glColor3f(0.f, 1.f, 0.f);
				break;
			case Material::plane:
				glColor3f(0.f, 0.f, 1.f);
				break;
			case Material::brick:
				glColor3f(1.f, 0.f, 0.f);
				break;
		}
		glm::mat4 obj = glm::mat4(1);
		if(it->isBottom()) 
		{
			obj = glm::translate(obj, glm::vec3(it->getRect().min.x, it->getRect().min.y, 0.f));
		}
		else {
			obj = glm::translate(obj, glm::vec3(it->getRect().min.x, it->getRect().max.y, 0.f));
			obj = glm::rotate(obj, 180.f, glm::vec3(0.f, 0.f, 1.f));
		}
		obj = glm::rotate(obj, 90.f, glm::vec3(0.f, 1.f, 0.f));
		obj = glm::scale(obj, glm::vec3(0.1f, (it->getRect().max.y - it->getRect().min.y) / 2.f, 0.5f));
		glLoadMatrixf(glm::value_ptr(obj));
		blade->draw();
		glPopMatrix();
	}	
	glColor3f(1.f, 1.f, 1.f);
	glBindTexture(GL_TEXTURE_2D, 0);
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
	
	cout << "Your highscore was: " << highScore << " razors destroyed, and "<< distanceHighScore << " meters traveled!" << endl;
}

/**
 * Called when the game should terminate
 */
void Game::stop()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
