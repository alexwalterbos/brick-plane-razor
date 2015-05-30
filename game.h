#pragma once 

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>
#include <memory>
#include "bird.h"
#include "col.h"
#include "obstacle.h"

using namespace std;

bool isVisible(shared_ptr<Obstacle> obstacle, const Rect & rect);

class Game
{
	public:
		Game();
		void play();
		void pause();
		void stop();
		GLFWwindow* getWindow();
		void errorCallback(int error, const char* description);
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void resizeCallback(GLFWwindow* window, int width, int height);
	private:
		float ratio;
		GLuint backgroundTexture;
		double lastFrameTime;
		int shouldPause;
		int startWindowX, startWindowY;
		GLFWwindow* window;
		unique_ptr<Bird> bird;
		unique_ptr<Rect> worldRect;
		vector<shared_ptr<Obstacle>> obstacles;
		vector<shared_ptr<Obstacle>> visibleObstacles;

		void draw();
		void update(double delta);
		void initGLObjs();
		void initWindow();
		void drawBackground();
		void drawWorld();
		void drawObstacles();
		void checkCollision();
		void handleCollision();
		void updateWorldRect();
		void generateWorld();
		void updateVisibility();
		unique_ptr<Rect> getWorldRect();
};
