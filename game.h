#pragma once 

#include <GLFW/glfw3.h>
#include "bird.h"

class Game
{
	public:
		Game();
		void update(double delta);
		void draw();
		void play();
		void pause();
		void stop();
		GLFWwindow* getWindow();
		void errorCallback(int error, const char* description);
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void fbResizeCallback(GLFWwindow* window, int width, int height);
	private:
		double lastFrameTime;
		int shouldPause;
		int startWindowX, startWindowY;
		GLFWwindow* window;
		Bird* bird;
};
