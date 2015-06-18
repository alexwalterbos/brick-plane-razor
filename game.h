#pragma once 

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>
#include "bird.h"
#include <memory>
#include "col.h"
#include "material.h"
#include "obstacle.h"
#include "mesh.h"

using namespace std;

bool isObstacleVisible(Obstacle obstacle, const Rect & worldRect);
bool isCircleVisible(Circle circle, const Rect & worldRect);

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
		GLuint backgroundTexture, bladeTexture;
		double lastFrameTime;
		bool paused = false;
		int startWindowX, startWindowY;
		GLFWwindow* window;
		unique_ptr<Bird> bird;
		unique_ptr<Rect> worldRect;
		vector<Obstacle> obstacles;
		float separation = 3.f,
		      obstacleStartPosition=1.f,
		      obstaclesWidth = 0.2f,
		      playDistance=100.f,
		      obstacleHoleSize=0.7f,
		      outsideWorldOffset = 1.5f,
		      fireThreshold=0.33f;
		float fov = 60.f, nearDist = 1.f, farDist = 10.f;
		vector<unique_ptr<Bullet>> bullets;
		float cameraOffset = 1.4f;
		unique_ptr<Mesh> blade;
		float timeSinceFire;
		int currentScore, highScore;
		float distanceHighScore;
		int heightMapStepX = 100, heightMapStepZ = 200;
		float heightMapScale = 0.1f;
		glm::vec3 invLightDir = glm::normalize(glm::vec3(1.f, 1.5f, 1.f));
		glm::vec4 groundColor = glm::vec4(0.1f, 0.8f, 0.1f, 1.f);
		void draw();
		void update(double delta);
		void initGLObjs();
		void initWindow();
		void drawBackground();
		void drawObstacles();
		void drawHeightMap();
		glm::vec4 calculateColor(glm::vec3 normal);
		void drawQuad(int stepX, int stepZ, float startX, float xSize, float zSize);
		void checkCollision();
		void handleCollision();
		void updateWorldRect();
		void updateWorld();
		void updateVisibility();
		void handleFire(Material material);
};
