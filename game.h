#pragma once 

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>
#include <memory>
#include "bird.h"
#include "col.h"
#include "shader.h"

using namespace std;

bool isVisible(Rect obstacle, const Rect & worldRect);

class Game
{
	public:
		Game();
		void play();
		void stop();
		GLFWwindow* getWindow();
		void errorCallback(int error, const char* description);
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void resizeCallback(GLFWwindow* window, int width, int height);
	private:
		float ratio;
		GLuint backgroundTexture;
		double lastFrameTime;
		bool paused = false;
		int startWindowX, startWindowY;
		GLFWwindow* window;
		unique_ptr<Bird> bird;
		unique_ptr<Rect> worldRect;
		vector<Rect> obstacles;
		vector<Rect> visibleObstacles;
		float startSeparation = 2.f, obstacleStartPosition=1.f, obstaclesWidth = 0.2f, playDistance=100.f, obstacleHoleSize=0.5f;
		shared_ptr<Shader> textureShader; 
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
