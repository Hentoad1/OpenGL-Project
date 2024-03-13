
#include "pch.h"
#include "Engine.h"

/* -------------------------------- CALLBACK DECLARATIONS -------------------------------- */

static void onInput(GLFWwindow* window, int key, int scancode, int action, int mods);
static void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset);
static void onResize(GLFWwindow* window, int width, int height);
static void onCursorMovement(GLFWwindow* window, double xpos, double ypos);

/* ----------------------------------- CLASS FUNCTIONS ----------------------------------- */

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

	//Set User Pointer to Engine
	glfwSetWindowUserPointer(eWindow, reinterpret_cast<void*>(this));

	//Set Callbacks
	glfwSetKeyCallback(eWindow, onInput);
	glfwSetScrollCallback(eWindow, onMouseWheel);
	glfwSetFramebufferSizeCallback(eWindow, onResize);
	glfwSetCursorPosCallback(eWindow, onCursorMovement);

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

Camera* Engine::GetCamera() const {
	return eCamera;
}

/* --------------------------------- CALLBACK FUNCTIONS ---------------------------------- */

static void onInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Engine* e = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));

	float amount = 0.2f;

	if (action == GLFW_REPEAT) {
		amount = 0.1f;
	}
	else if (action == GLFW_RELEASE) {
		return;
	}

	switch (key)
	{
	case(GLFW_KEY_RIGHT):
		e->GetCamera()->Rotate(true, amount);
		break;
	case(GLFW_KEY_LEFT):
		e->GetCamera()->Rotate(true, -amount);
		break;
	case(GLFW_KEY_UP):
		e->GetCamera()->Rotate(false, amount);
		break;
	case(GLFW_KEY_DOWN):
		e->GetCamera()->Rotate(false, -amount);
		break;
	default:
		break;
	}
}

static void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) {
	Engine* e = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));

	e->GetCamera()->Zoom(yoffset);
}

static void onResize(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

static void onCursorMovement(GLFWwindow * window, double xpos, double ypos) {

}