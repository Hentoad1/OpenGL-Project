#include "pch.h"

#include "BoundingBox.h"

CollisionInfo BoundingBox::Collision_AABB_With_AABB(const BoundingBox& AABB1, const BoundingBox& AABB2, const glm::vec3& velocity) {
	bool collided = false;

	return CollisionInfo{ collided };
}