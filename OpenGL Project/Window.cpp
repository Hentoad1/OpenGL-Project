
#include "pch.h"
#include "Window.h"

#include "Screen.h"

Window::Window(Camera* wCam) {
	content = std::list<Mesh*>();
	wCamera = wCam;

	//Initalize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Create Window Object
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OPENGL WINDOW", NULL, NULL);


	//Check Window Object
	if (window == nullptr)
	{
		glfwTerminate();

		throw std::exception("Failed to create GLFW window");
	}


	//Create OpenGL Context for Window
	glfwMakeContextCurrent(window);


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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//Stop Overlap
	glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
	for (auto it = content.begin(); it != content.end(); ++it) {
		delete* it;
	}


	//for (Mesh*& _c : content) {
		//delete _c;
	//}

	content.clear();
}

void Window::Load(std::string path) {
	Mesh* newContent = new Mesh(path, wCamera);

	if (newContent != nullptr) {
		content.push_back(newContent);
	}
	else {
		std::cout << "it was null" << std::endl;
	}
}

void Window::Render() {
	//Process Input -- maybe should be handled in input eventually.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}


	//Clear 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Render World
	for (auto it = content.begin(); it != content.end(); ++it) {
		(*it)->Render();
	}



	//Manage Events
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::ShouldClose() const {
	return glfwWindowShouldClose(window);
}