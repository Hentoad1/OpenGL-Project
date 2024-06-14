
#include "pch.h"

#include "Scene.h"

static glslSceneLight Light = glslSceneLight{ glm::vec3(0, -1, 0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0), glm::vec3(0) };
static glslLightSource Lights[NUM_LIGHT_SOURCES];


const glslSceneLight* Scene::GetSceneLight() {
	return &Light;
}

const glslLightSource* Scene::GetLightSources() {
	return Lights;
}

void Scene::AddLight(const glslLightSource& source) {

	for (int i = 0; i < NUM_LIGHT_SOURCES; ++i) {
		if (!Lights[i].loaded) {
			Lights[i] = source;
			return;
		}
	}

	Lights[9] = source;
}