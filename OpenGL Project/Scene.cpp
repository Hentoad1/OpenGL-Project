
#include "pch.h"

#include "Scene.h"

static SceneLight Light = SceneLight{ glm::vec3(0, -1, 0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0), glm::vec3(0) };
static LightSource Lights[NUM_LIGHT_SOURCES];


const SceneLight* Scene::GetSceneLight() {
	return &Light;
}

const LightSource* Scene::GetLightSources() {
	return Lights;
}

void Scene::AddLight(const LightSource& source) {

	for (int i = 0; i < NUM_LIGHT_SOURCES; ++i) {
		if (!Lights[i].loaded) {
			Lights[i] = source;
			return;
		}
	}

	Lights[9] = source;
}