#include "pch.h"

#include "BoundingBox.h"

static float GetAxisOverlap(const glm::vec3& axis, const BoundingBox& boxA, const BoundingBox& boxB, float* penetrationDistances) {
	float amin = FLT_MAX;
	float amax = -FLT_MAX;
	float bmin = FLT_MAX;
	float bmax = -FLT_MAX;

	glm::vec3 aminP;
	glm::vec3 amaxP;
	glm::vec3 bminP;
	glm::vec3 bmaxP;

	for (int j = 0; j < boxA.Vertices().size(); ++j) {
		glm::vec3 vertex = boxA.Vertices()[j] + boxA.Position();

		float dotProduct = glm::dot(vertex, axis);

		if (dotProduct < amin) {
			amin = dotProduct;
			aminP = vertex;
		}
		if (dotProduct > amax) {
			amax = dotProduct;
			amaxP = vertex;
		}
	}

	for (int j = 0; j < boxB.Vertices().size(); ++j) {
		glm::vec3 vertex = boxB.Vertices()[j] + boxB.Position();

		float dotProduct = glm::dot(vertex, axis);

		if (dotProduct < bmin) {
			bmin = dotProduct;
			bminP = vertex;
		}
		if (dotProduct > bmax) {
			bmax = dotProduct;
			bmaxP = vertex;
		}
	}

	float overlap = std::min(amax, bmax) - std::max(amin, bmin);

	//float correctDistance = std::max(penetrationDistance1, penetrationDistance2);

	/*
	* Now there are 2 potential options.
	* The overlap is the current value, or it is the same value but negative.
	*
	* To determine this the values need to tested in some manner with the velocity to see what is the appropriate exit direction.
	*
	* the testing is the dot product of the axis and velocity.
	*
	*/

	if (overlap > 0) {
		/*std::cout << "axis: " << glm::to_string(axis) << std::endl;
		std::cout << "axisDistance: " << axisDistance << std::endl;
		std::cout << "distanceToLeave1: " << distanceToLeave1 << std::endl;
		std::cout << "distanceToLeave2: " << distanceToLeave2 << std::endl;
		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;*/
	}

	if (overlap < 0) {
		return 0;
	}
	else {
		/*
		The assumption is made here that A is going to move away from B.
		*/

		/*
		These vars are how FAR the object has penetrated into the collision.
		Overlap maxes at the smaller of the objects size.
		Penetration does not.

		If an overlap is present, both of these numbers will be positive.

		If boxB is supposed to be moving, then these values will be inverted.
		*/
		if (true) {
			float pos1 = bmax - amin;
			float pos2 = -(amax - bmin);

			/*

			*/

			float newpos1 = overlap + std::max(amin, bmin) - std::min(amin, bmin);
			float newpos2 = overlap + std::max(amax, bmax) - std::min(amax, bmax);

			/*std::cout << "pos1: " << pos1 << std::endl;
			std::cout << "pos2: " << pos2 << std::endl;
			std::cout << "newpos1: " << newpos1 << std::endl;
			std::cout << "newpos2: " << newpos2 << std::endl;*/

			penetrationDistances[0] = newpos1; //big
			penetrationDistances[1] = newpos2; //small

			/*if (pos1 > pos2) {
				penetrationDistances[0] = pos1; //big
				penetrationDistances[1] = pos2; //small
			}
			else {
				penetrationDistances[0] = pos2; //big
				penetrationDistances[1] = pos1; //small
			}*/


			/*std::cout << "-------------------------" << std::endl;
			std::cout << "amin" << amin << std::endl;
			std::cout << "amax" << amax << std::endl;
			std::cout << "bmin" << bmin << std::endl;
			std::cout << "bmax" << bmax << std::endl;*/

			//std::cout << bmax - amin << std::endl;
			//std::cout << amax - bmin << std::endl;
		}

		return overlap;
	}
}

CollisionInfo BoundingBox::Collision_Complex(const BoundingBox& boxA, const BoundingBox& boxB, const glm::vec3& velocity) {
	int numAxisA = boxA.sbb->normals.size();
	int numAxisB = boxB.sbb->normals.size();
	int numAxisCross = numAxisA * numAxisB;
	int totalAxis = numAxisA + numAxisB + numAxisCross;

	//axis, overlap
	glm::vec3 axisWithOverlap;
	float LargestOverlap = FLT_MAX;
	float positivePenetration = 0;
	float negativePenetration = 0;
	float PenetrationResult[2];

	for (int i = 0; i < boxA.sbb->normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxA.sbb->normals[i]);

		float overlap = GetAxisOverlap(axis, boxA, boxB, PenetrationResult);

		if (overlap == 0) {
			return CollisionInfo{ false };
		}
		else {
			float approachSpeed = glm::dot(axis, velocity);

			if (approachSpeed == 0) {
				continue;
			}

			float adjusted = std::min(PenetrationResult[0] / approachSpeed, PenetrationResult[1] / approachSpeed);
			if (std::abs(LargestOverlap) > std::abs(adjusted)) {
				LargestOverlap = adjusted;
				axisWithOverlap = axis;
				positivePenetration = PenetrationResult[0];
				negativePenetration = PenetrationResult[1];
			}
		}
	}

	for (int i = 0; i < boxB.sbb->normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxB.sbb->normals[i]);

		float overlap = GetAxisOverlap(axis, boxA, boxB, PenetrationResult);

		if (overlap == 0) {
			return CollisionInfo{ false };
		}
		else {
			float approachSpeed = glm::dot(axis, velocity);

			if (approachSpeed == 0) {
				continue;
			}

			float adjusted = std::min(PenetrationResult[0] / approachSpeed, PenetrationResult[1] / approachSpeed);
			if (std::abs(LargestOverlap) > std::abs(adjusted)) {
				LargestOverlap = adjusted;
				axisWithOverlap = axis;
				positivePenetration = PenetrationResult[0];
				negativePenetration = PenetrationResult[1];
			}
		}
	}

	for (int i = 0; i < boxA.sbb->normals.size(); ++i) {
		for (int j = 0; j < boxB.sbb->normals.size(); ++j) {
			glm::vec3 cross = glm::cross(boxA.sbb->normals[i], boxB.sbb->normals[j]);

			if (cross == glm::vec3(0, 0, 0)) {
				continue;
			}

			std::cout << "axis: " << glm::to_string(cross) << std::endl;

			glm::vec3 axis = glm::normalize(cross);

			float overlap = GetAxisOverlap(axis, boxA, boxB, PenetrationResult);

			if (overlap == 0) {
				return CollisionInfo{ false };
			}
			else {
				float approachSpeed = glm::dot(axis, velocity);

				if (approachSpeed == 0) {
					continue;
				}

				float adjusted = std::min(PenetrationResult[0] / approachSpeed, PenetrationResult[1] / approachSpeed);
				if (std::abs(LargestOverlap) > std::abs(adjusted)) {
					LargestOverlap = adjusted;
					axisWithOverlap = axis;
					positivePenetration = PenetrationResult[0];
					negativePenetration = PenetrationResult[1];
				}
			}
		}
	}



	std::cout << "velocity: " << glm::to_string(velocity) << std::endl;
	std::cout << "axis: " << glm::to_string(axisWithOverlap) << std::endl;
	std::cout << "dot: " << glm::dot(velocity, axisWithOverlap) << std::endl;
	std::cout << "overlap: " << LargestOverlap << std::endl;
	std::cout << "overlap times dot: " << LargestOverlap * glm::dot(velocity, axisWithOverlap) << std::endl;
	std::cout << "overlap divided by dot: " << LargestOverlap / glm::dot(velocity, axisWithOverlap) << std::endl;
	std::cout << "pos penetration: " << positivePenetration << std::endl;
	std::cout << "neg penetration: " << negativePenetration << std::endl;
	std::cout << "pos penetration divided by dot: " << positivePenetration / glm::dot(velocity, axisWithOverlap) << std::endl;
	std::cout << "neg penetration divided by dot: " << negativePenetration / glm::dot(velocity, axisWithOverlap) << std::endl;
	std::cout << "potential coefficient: " << glm::dot(glm::normalize(glm::vec3(1)), axisWithOverlap) << std::endl;

	//overlap is infinity gg

	/*
	*
	* Here we use the velocity to figure out what way the axis needs to go to push the object out of the wall.
	*
	*
	*/
	glm::vec3 axisAndVelocity = axisWithOverlap * velocity;

	/*
	* If the velocity direction is positive then only one penetration value should be correct otherwise its the other.
	*/
	float velocityUnit = glm::dot(axisWithOverlap, glm::normalize(velocity));
	std::cout << "velocity unit: " << velocityUnit << std::endl;

	glm::vec3 postitionChange;
	if (positivePenetration < negativePenetration) {
		//postitionChange = axisWithOverlap * positivePenetration;
	}
	else {
		//postitionChange = axisWithOverlap * negativePenetration;
		postitionChange = axisWithOverlap * std::min(positivePenetration, negativePenetration);
	}

	if (velocityUnit > 0) {
		postitionChange = axisWithOverlap * std::min(positivePenetration, negativePenetration) * velocityUnit * 10.0f;
	}
	else {
		postitionChange = axisWithOverlap * negativePenetration * velocityUnit * 10.0f;
	}
	postitionChange = axisWithOverlap * std::min(positivePenetration, negativePenetration);


	glm::vec3 testone = axisWithOverlap * positivePenetration;
	glm::vec3 testtwo = axisWithOverlap * negativePenetration;

	std::cout << "one: " << glm::to_string(testone) << std::endl;
	std::cout << "two: " << glm::to_string(testtwo) << std::endl;

	//bouncy movement
	//glm::vec newVelocity = glm::reflect(velocity, axisWithOverlap);

	//testing
	glm::vec newVelocity = (velocity - 1.0f * glm::dot(axisWithOverlap, velocity) * axisWithOverlap);

	return CollisionInfo{ true, postitionChange };
}