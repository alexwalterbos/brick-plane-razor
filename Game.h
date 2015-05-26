#pragma once 

#include <GLFW/glfw3.h>

class Game
{
	public:
		Game();
		void update();
		void draw();
		void play();
		void pause();
		void stop();
		GLFWwindow* getWindow();
		void errorCallback(int error, const char* description);
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void fbResizeCallback(GLFWwindow* window, int width, int height);
	private:
		int shouldPause;
		int startWindowX, startWindowY;
		GLFWwindow* window;
};
