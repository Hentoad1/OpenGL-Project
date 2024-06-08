#include "pch.h"

#include "World.h"
#include "PhysicsComponent.h"

#include "ComponentData.h"

PhysicsComponent::PhysicsComponent(ComponentData* _cData, const ComponentMeta* _cMeta) : cData(_cData), cMeta(_cMeta) {}

void PhysicsComponent::Update(const FrameData& data) {

	cData->velocity.x *= 1 - (2.0f * data.DeltaTime);
	cData->velocity.z *= 1 - (2.0f * data.DeltaTime);

	if (cData->velocity.y > 0) {
		cData->velocity.y *= 1 - (2.0f * data.DeltaTime);
	}
	else if (cData->velocity.y < 0) {
		//velocity.y *= 1.1f;
		cData->velocity.y *= 1 - (2.0f * data.DeltaTime);
	}

	//test collision

	CollisionInfo info = World::TestCollision(cData->bounds, cData->velocity);

	if (info.collided) {
		std::cout << "-----------------------------------------------------" << std::endl;
		std::cout << "Position: " << glm::to_string(cData->bounds.Position()) << std::endl;
		std::cout << "Velocity: " << glm::to_string(cData->velocity) << std::endl;
		std::cout << "CollisionVelocity: " << glm::to_string(info.newPosition) << std::endl;

		cData->bounds.SetPosition(cData->bounds.Position() - (info.newPosition));

		std::cout << "position" << glm::to_string(cData->bounds.Position()) << std::endl;


		cData->velocity = info.collisionVelocity;
	}

	cData->bounds.MoveAbsolute(cData->velocity);



	/* ------------------------------- UPDATE ATTACHED CAMERA -------------------------------- */

	if (cMeta->has(MESH_ATTACHEDCAMERA)) {
		Camera* cam = cData->camera;
		const AxisVectors& axis = cData->bounds.GetOrientation().GetAxis();

		const glm::vec3 ModelCenter = cData->bounds.Center();
		const glm::vec3 CameraOffset = axis.Front * -10.0f; //50 units away from player.


		cam->SetPosition(ModelCenter + CameraOffset);
		cam->SetOrientation(cData->bounds.GetOrientation());
	}
	


}