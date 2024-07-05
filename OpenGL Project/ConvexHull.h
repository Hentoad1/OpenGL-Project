#pragma once

#include "pch.h"

#include "Vertex.h"

#include "BoundingBox.h"

BoundingBox CreateConvexHull(const std::vector<Vertex>&);

//BoundingBox CreateConvexHull(const std::vector<sVertex>&);