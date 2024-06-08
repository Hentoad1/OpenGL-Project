#include "pch.h"

#include "PhysicsMesh.h"

#include "World.h"

PhysicsMesh::PhysicsMesh(const std::string& file, Camera* mCam) : Mesh(file, mCam) {}

PhysicsMesh::PhysicsMesh(const BoundingBox& bounds, Camera* mCam) : Mesh(bounds, mCam) {}

PhysicsMesh::~PhysicsMesh() {
	Mesh::~Mesh();
}

void PhysicsMesh::Update(const FrameData& data) {

	//std::cout << data.DeltaTime << std::endl;

	velocity.x *= 1 - (2.0f * data.DeltaTime);
	velocity.z *= 1 - (2.0f * data.DeltaTime);

	if (velocity.y > 0) {
		velocity.y *= 1 - (2.0f * data.DeltaTime);
	}
	else if (velocity.y < 0) {
		//velocity.y *= 1.1f;
		velocity.y *= 1 - (2.0f * data.DeltaTime);
	}

	//test collision

	CollisionInfo info = World::TestCollision(GetBoundingBox(), velocity);

	if (info.collided) {
		//GetBoundingBox().SetPosition(GetBoundingBox().Position() + (info.collisionVelocity * info.overlapAmount));

		std::cout << "-----------------------------------------------------" << std::endl;
		std::cout << "Position: " << glm::to_string(GetBoundingBox().Position()) << std::endl;
		std::cout << "Velocity: " << glm::to_string(velocity) << std::endl;
		std::cout << "CollisionVelocity: " << glm::to_string(info.newPosition) << std::endl;

		GetBoundingBox().SetPosition(GetBoundingBox().Position() - (info.newPosition));

		std::cout << "position" << glm::to_string(GetBoundingBox().Position()) << std::endl;


		velocity = info.collisionVelocity;
		//velocity = info.collisionVelocity;
	}
	
	GetBoundingBox().MoveAbsolute(velocity);

}

//these are temporary
void PhysicsMesh::AccelerateRelative(glm::vec3 v) {
	GetBoundingBox().MoveRelative(v);
}

void PhysicsMesh::AccelerateAbsolute(glm::vec3 v) {
	GetBoundingBox().MoveRelative(v);
}