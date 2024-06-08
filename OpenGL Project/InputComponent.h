#pragma once

#include "pch.h"

#include "ComponentData.h"

#include "EngineInternal.h"

class InputComponent {
public:
	InputComponent(ComponentData*, const ComponentMeta*);

	void Update(const FrameData&);
private:
	ComponentData* cData;
};