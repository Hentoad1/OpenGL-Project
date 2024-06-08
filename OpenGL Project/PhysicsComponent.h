#pragma once

#include "pch.h"

#include "ComponentData.h"

//#include "EngineInternal.h"

class PhysicsComponent {
public:
	PhysicsComponent(ComponentData*, const ComponentMeta*);

	void Update(const FrameData&);
private:
	ComponentData* cData;
	const ComponentMeta* cMeta;
};
