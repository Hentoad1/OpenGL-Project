#pragma once

#include "pch.h"

class BoundingBox {

public:
	BoundingBox() {}

	BoundingBox(
		std::vector<glm::vec3> _edges,
		std::vector<glm::vec3> _vertices,
		glm::vec3 _position,
		glm::vec3 _orientation,
		glm::vec3 _center
	) : edges(_edges), vertices(_vertices), position(_position), orientation(_orientation), center(_center) {}

	BoundingBox(glm::vec3 min, glm::vec3 max);

	glm::vec3 Center() const;

	glm::vec3 Position() const;

	void Move(glm::vec3);

	void SetPosition(glm::vec3);

	void SetOrientation(glm::vec3);

	bool CollidesWith(const BoundingBox&);

private:
	const std::vector<glm::vec3> Edges() const {
		return edges;
	}

	const std::vector<glm::vec3> Vertices() const {
		return vertices;
	}

	//edges remain static, regardless of orientation or position
	std::vector<glm::vec3> edges;
	
	//vertices remain static, regardless of orientation or position
	std::vector<glm::vec3> vertices;

	//center remain static, regardless of orientation or position
	glm::vec3 center;

	//position is dynamic, changing possbily every frame.
	glm::vec3 position;

	//orientation is dynamic, chaning possibly every frame.
	glm::vec3 orientation;

};