
#include "pch.h"
#include "Engine.h"

#include "Screen.h"

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
	glfwSetScrollCallback(eWindow, onMouseWheel);
	glfwSetFramebufferSizeCallback(eWindow, onResize);
	glfwSetCursorPosCallback(eWindow, onCursorMovement);

	//Set Mouse Cursor Style
	if (glfwRawMouseMotionSupported()){
		glfwSetInputMode(eWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	glfwSetInputMode(eWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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


	//Determine if window should be closed.
	if (GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(eWindow, true);
	}

#ifdef ENGINE_SETTING_DISPLAY_MODEL
	
	int8_t ForwardState = GetKeyState(ACTION_WALK_FORWARD);
	int8_t BackwardState = GetKeyState(ACTION_WALK_BACKWARD);
	int8_t LeftState = GetKeyState(ACTION_WALK_LEFT);
	int8_t RightState = GetKeyState(ACTION_WALK_RIGHT);
	int8_t JumpState = GetKeyState(ACTION_JUMP);
	int8_t CrouchState = GetKeyState(ACTION_CROUCH);
	int8_t InteractState = GetKeyState(ACTION_INTERACT);

	if (ForwardState == GLFW_PRESS) {
		GetCamera()->Move(1, 0, 0);
	}
	if (BackwardState == GLFW_PRESS) {
		GetCamera()->Move(-1, 0, 0);
	}
	if (LeftState == GLFW_PRESS) {
		GetCamera()->Move(0, 0, -1);
	}
	if (RightState == GLFW_PRESS) {
		GetCamera()->Move(0, 0, 1);
	}

	if (JumpState == GLFW_PRESS) {
		GetCamera()->MoveAbsolute(0, 1, 0);
	}
	if (CrouchState == GLFW_PRESS) {
		GetCamera()->MoveAbsolute(0, -1, 0);
	}

	if (InteractState == GLFW_PRESS) {
		GetCamera()->LightPos = GetCamera()->GetPosition();
	}
#else

#endif


	glfwPollEvents();
}

bool Engine::ShouldClose() const {
	return glfwWindowShouldClose(eWindow);
}

Camera* Engine::GetCamera() const {
	return eCamera;
}

int8_t Engine::GetKeyState(int key) {
	return glfwGetKey(eWindow, key);
}

/* ---------------------------- MESH VIEW CALLBACK FUNCTIONS ----------------------------- */

#ifdef ENGINE_SETTING_DISPLAY_MODEL

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
	case(GLFW_KEY_W):
		e->GetCamera()->Move(1, 0, 0);
		break;
	case(GLFW_KEY_A):
		e->GetCamera()->Move(0, 0, -1);
		break;
	case(GLFW_KEY_S):
		e->GetCamera()->Move(-1, 0, 0);
		break;
	case(GLFW_KEY_D):
		e->GetCamera()->Move(0, 0, 1);
		break;
	case(GLFW_KEY_SPACE):
		e->GetCamera()->MoveAbsolute(0, 1, 0);
		break;
	case(GLFW_KEY_LEFT_CONTROL):
		e->GetCamera()->MoveAbsolute(0, -1, 0);
		break;
	case(GLFW_KEY_F):
		e->GetCamera()->LightPos = e->GetCamera()->GetPosition();
		break;
	default:
		break;
	}
}


static void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) {
	
}

static void onResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void onCursorMovement(GLFWwindow* window, double xpos, double ypos) {
	Engine* e = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));


	//Change (in pixels) since last event
	double deltaCursorX = -(e->CursorPos.x - xpos); //inverted
	double deltaCursorY = e->CursorPos.y - ypos;

	e->CursorPos = glm::dvec2(xpos, ypos);

	//Change (in % of screen) since last event
	double percentDeltaCursorX = deltaCursorX / SCREEN_WIDTH;
	double percentDeltaCursorY = deltaCursorY / SCREEN_HEIGHT;


	//Change (in % of screen) with adjusted sensitivy
	static constexpr int SENSITIVITY_MAX = 150;
	static constexpr int SENSITIVITY_MIN = 30;

	double adjustedDeltaCursorX = percentDeltaCursorX * SENSITIVITY_MIN;
	double adjustedDeltaCursorY = percentDeltaCursorY * SENSITIVITY_MIN;

	e->GetCamera()->Rotate(adjustedDeltaCursorX, adjustedDeltaCursorY);
}
#endif // ENGINE_SETTING_DISPLAY_MODEL



/* ------------------------------- MAIN CALLBACK FUNCTIONS ------------------------------- */



#ifdef ENGINE_SETTING_MAIN

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
	case(GLFW_KEY_W):
		e->GetCamera()->Move(1, 0, 0);
		break;
	case(GLFW_KEY_A):
		e->GetCamera()->Move(0, 0, -1);
		break;
	case(GLFW_KEY_S):
		e->GetCamera()->Move(-1, 0, 0);
		break;
	case(GLFW_KEY_D):
		e->GetCamera()->Move(0, 0, 1);
		break;
	case(GLFW_KEY_SPACE):
		e->GetCamera()->Move(0, 1, 0);
		break;
	case(GLFW_KEY_LEFT_CONTROL):
		e->GetCamera()->Move(0, -1, 0);
		break;
	default:
		break;
	}
}


static void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) {

}

static void onResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void onCursorMovement(GLFWwindow* window, double xpos, double ypos) {
	Engine* e = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));


	//Change (in pixels) since last event
	double deltaCursorX = -(e->CursorPos.x - xpos); //inverted
	double deltaCursorY = e->CursorPos.y - ypos;

	e->CursorPos = glm::dvec2(xpos, ypos);

	//Change (in % of screen) since last event
	double percentDeltaCursorX = deltaCursorX / SCREEN_WIDTH;
	double percentDeltaCursorY = deltaCursorY / SCREEN_HEIGHT;


	//Change (in % of screen) with adjusted sensitivy
	static constexpr int SENSITIVITY_MAX = 150;
	static constexpr int SENSITIVITY_MIN = 30;

	double adjustedDeltaCursorX = percentDeltaCursorX * SENSITIVITY_MIN;
	double adjustedDeltaCursorY = percentDeltaCursorY * SENSITIVITY_MIN;

	e->GetCamera()->Rotate(adjustedDeltaCursorX, adjustedDeltaCursorY);
}
#endif // ENGINE_SETTING_MAIN