// emcc ./src/main.cpp -o ./build/index.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -std=c++11 -s LEGACY_GL_EMULATION

#include <functional>
#include <vector>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "cirobb/RigidBody.h"
#include "cirobb/RigidBody.cpp"
#include "cirobb/Shape.h"
#include "cirobb/Shape.cpp"
#include "cirobb/Manifold.h"
#include "cirobb/Manifold.cpp"
#include "cirobb/Collision.h"
#include "cirobb/Collision.cpp"
#include "cirobb/Scene.h"
#include "cirobb/Scene.cpp"

#include "Render.cpp"

int width = 800;
int height = 600;
real zoom = 10;
real viewScale = 0;

int numScene = 1;
bool pause = false;	
real timeStep = 1.0f / 60.0f;
Vec2 gravity(0.0f, -10.0f);

real mouseX = 0, mouseY = 0;

GLFWwindow* mainWindow = NULL;

Scene scene(gravity, 10, 5);

static void Reshape(GLFWwindow*, int w, int h)
{
	width = w, height = h > 0 ? h : 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	real aspect = real(width) / real(height);

	if (width >= height)
	{
		viewScale = zoom / (height * 0.5);
		glOrtho(-zoom * aspect, zoom * aspect, -zoom, zoom, -1.0, 1.0);
	}
	else
	{
		viewScale = zoom / (width * 0.5);
		glOrtho(-zoom, zoom, -zoom / aspect, zoom / aspect, -1.0, 1.0);
	}
}


static void Start(void)
{
  Scene::CorrectionType = 2;

  scene.Clear();
      
  OBB tempOBB(22.0f, 0.8f);
  RigidBody* b1 = new RigidBody(tempOBB, Vec2(0, -8.5), 0.0f); 
  b1->Static();
  scene.Add(b1);
  OBB tempOBB2(16.5f, 0.8f);
  b1 = new RigidBody(tempOBB2, Vec2(12, -0.8), 85 * RAD); 
  b1->Static();
  scene.Add(b1);
  OBB tempOBB3(16.5f, 0.8f);
  b1 = new RigidBody(tempOBB3, Vec2(-12, -0.8), -85 * RAD); 
  b1->Static();
  scene.Add(b1);
}


static void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action != GLFW_PRESS) return;

	switch(key)
	{
		case GLFW_KEY_B:
    {
      OBB temp(Vec2(1.5f, 1.5f));
			RigidBody* b = new RigidBody(temp, Vec2(mouseX, mouseY), 0.0f);
      b->Dynamic(1.0f);
      scene.Add(b);
    }
    break;
    
		case GLFW_KEY_C:
		{
			Circle temp(0.8f);
			RigidBody* b = new RigidBody(temp, Vec2(mouseX, mouseY), 0.0f);
		  b->Dynamic(1.0f);
			scene.Add(b);
		}
    break;

		case GLFW_KEY_P:
    pause = !pause;
		break;

		case GLFW_KEY_SPACE: Scene::CorrectionType = Scene::CorrectionType > 1 ? 0 : Scene::CorrectionType + 1; 
		break;
	}
}


static void MouseMotion(GLFWwindow*, double x, double y)
{
	mouseX = ((real)x - width  * 0.5) *  viewScale;
	mouseY = ((real)y - height * 0.5) * -viewScale;
}


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}


std::function<void()> Update;

void mainLoop() { Update(); }


int main(int args, char** argv)
{
  glfwSetErrorCallback(error_callback);

  if(glfwInit() == 0) 
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  mainWindow = glfwCreateWindow(width, height, "Cirobb 1.1.8", NULL, NULL);
  
  if(!mainWindow) 
  {
    fprintf(stderr, "Failed to open GLFW mainWindow.\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetWindowSizeCallback(mainWindow, Reshape);
  glfwSetKeyCallback(mainWindow, Keyboard);
	glfwSetCursorPosCallback(mainWindow, MouseMotion);
  glfwMakeContextCurrent(mainWindow);

  Reshape(mainWindow, width, height);

  Start();

  Update = [&] 
  {    
    glfwGetFramebufferSize(mainWindow, &width, &height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
		if(!pause) scene.Step(timeStep);
		for(RigidBody* temp : scene.bodies) DrawShape(temp->shape);

    // printf("RigidBodies: %i \n", (int)scene.bodies.size());

    glfwSwapBuffers(mainWindow);
    glfwPollEvents();
  };

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(mainLoop, 0, true);
  #endif

  glfwDestroyWindow(mainWindow);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}