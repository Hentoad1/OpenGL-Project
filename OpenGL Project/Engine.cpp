
#include "pch.h"
#include "Engine.h"

Engine::Engine() {
	eCamera = new Camera();
	eWorld = new World(eCamera);

	//Initalize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Create Window Object
	eWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OPENGL WINDOW", NULL, NULL);


	//Check Window Object
	if (eWindow == nullptr)
	{
		glfwTerminate();

		throw std::exception("Failed to create GLFW window");
	}


	//Create OpenGL Context for Window
	glfwMakeContextCurrent(eWindow);


	//Check for Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::exception("Failed to initialize GLAD");
	}


	//Set Viewport
	glad_glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Set Callbacks
	//-----TODO-------

	//Set Mouse Cursor Style
	glfwSetInputMode(eWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//Stop Overlap
	glEnable(GL_DEPTH_TEST);
}

Engine::~Engine() {
	delete eCamera;
	delete eWorld;
}

void Engine::Terminate() {
	glfwTerminate();
}

void Engine::Load(std::string path) {
	eWorld->Load(path);
}

void Engine::Draw() {
	//Clear 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Render content
	eWorld->Render();


	//Manage Events
	glfwSwapBuffers(eWindow);
	glfwPollEvents();
}

void Engine::Update() {
	//Process Input -- maybe should be handled in input eventually.
	if (glfwGetKey(eWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(eWindow, true);
	}

	glfwPollEvents();
}

bool Engine::ShouldClose() const {
	return glfwWindowShouldClose(eWindow);
}