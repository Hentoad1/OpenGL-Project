#pragma once

#include "pch.h"

#include "BoundingBox.h"

#include "ModelData.h"


StaticBoundingBox* BuildAABB(const glm::vec3& min, const glm::vec3& max);