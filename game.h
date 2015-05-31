#pragma once 

#include <GLFW/glfw3.h>
#include "bird.h"
#include <memory>
#include "col.h"

using namespace std;

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
		void draw();
		void update(double delta);
		void initGLObjs();
		void initWindow();
		void drawBackground();
		void drawObstacles();
		void checkCollision();
		void handleCollision();
		void updateWorldRect();
};
