#include "pch.h"

#include "BoundingBox.h"

#ifdef _DEBUG
#include "DebugShader.h"
#endif // _DEBUG

static float GetAxisOverlap(const glm::vec3& axis, const BoundingBox& boxA, const BoundingBox& boxB) {
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

	if (overlap < 0) {
		return 0;
	}
	else {
		return overlap;
	}
}

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


BoundingBox::BoundingBox(
	const std::vector<glm::vec3>& _vertices,
	const std::vector<unsigned int>& _indices,
	const std::vector<glm::vec3>& _normals) : vertices(_vertices), indices(_indices), normals(_normals) {
	
}

//Generates a cube shaped BoundingBox
BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) :
	center(((max + min) * 0.5f)),
	orientation(glm::vec3(0,0,-1))
{
	vertices = {
		glm::vec3(max),
		glm::vec3(min.x, max.y, max.z),
		glm::vec3(max.x, min.y, max.z),
		glm::vec3(min.x, min.y, max.z),
		glm::vec3(min),
		glm::vec3(max.x, min.y, min.z),
		glm::vec3(min.x, max.y, min.z),
		glm::vec3(max.x, max.y, min.z),
	};

	unsigned int indexes[24] = {
		0, 1, 3, 2,
		4, 5, 7, 6,

		0, 1, 6, 7,
		2, 3, 4, 5,

		0, 2, 5, 7,
		1, 3, 4, 6
	};



	normals = {
		glm::vec3(0,0,1),
		glm::vec3(0,0,-1),
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
		glm::vec3(1,0,0),
		glm::vec3(-1,0,0),
	};

	/*
	
	renderIndices.insert(renderIndices.end(), {
		indices[i],
		indices[i + 1],
		indices[i],
		indices[i + 2],
		indices[i + 1],
		indices[i + 2]
	});

	*/

	for (int i = 0; i < 6; i++) {
		int index1 = i * 4;
		int index2 = index1 + 1;
		int index3 = index1 + 2;
		int index4 = index1 + 3;
		
		indices.insert(indices.end(), {
			indexes[index1], indexes[index2],
			indexes[index2], indexes[index3],
			indexes[index1], indexes[index3],

			indexes[index1], indexes[index3],
			indexes[index1], indexes[index4],
			indexes[index3], indexes[index4],
		});
	}


	position = glm::vec3(0);
}

const glm::vec3& BoundingBox::Center() const {
	return position + center;
}

const glm::vec3& BoundingBox::Position() const {
	return position;
}

const std::vector<glm::vec3>& BoundingBox::Vertices() const {
	return vertices;
}

const Orientation& BoundingBox::GetOrientation() const {
	return orientation;
}

void BoundingBox::SetPosition(const glm::vec3& value) {
	position = value;
}

void BoundingBox::SetOrientation(const Orientation& o) {
	orientation = o;
}

void BoundingBox::MoveRelative(const glm::vec3& delta) {
	AxisVectors directions = GetOrientation().GetAxis();

	glm::vec3 rotatedDelta = 
		(glm::vec3(delta.x) * glm::normalize(glm::vec3(directions.Front.x, 0, directions.Front.z))) +
		(glm::vec3(delta.z) * glm::normalize(glm::vec3(directions.Right.x, 0, directions.Right.z)));

	rotatedDelta.y = 0;
	
	position += rotatedDelta;
}

void BoundingBox::MoveAbsolute(const glm::vec3& delta) {
	position += delta;
}

glm::vec3 BoundingBox::ConvertAbsolute(glm::vec3 value) const {
	AxisVectors directions = GetOrientation().GetAxis();

	return 
		(glm::vec3(value.x) * directions.Front) +
		(glm::vec3(value.y) * directions.Up) +
		(glm::vec3(value.z) * directions.Right);
}

bool BoundingBox::CollidesWith(const BoundingBox& boxB) {
	int numAxisA = normals.size();
	int numAxisB = boxB.normals.size();
	int numAxisCross = numAxisA * numAxisB;
	int totalAxis = numAxisA + numAxisB + numAxisCross;

	for (int i = 0; i < normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(normals[i]);
		
		if (GetAxisOverlap(axis, *this, boxB) == 0) {
			return false;
		}
	}

	for (int i = 0; i < boxB.normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxB.normals[i]);

		if (GetAxisOverlap(axis, *this, boxB) == 0) {
			return false;
		}
	}

	for (int i = 0; i < normals.size(); ++i) {
		for (int j = 0; j < boxB.normals.size(); ++j) {
			glm::vec3 cross = glm::cross(normals[i], boxB.normals[j]);

			if (cross == glm::vec3(0, 0, 0)) {
				continue;
			}

			glm::vec3 axis = glm::normalize(cross);

			if (GetAxisOverlap(axis, *this, boxB) == 0) {
				return false;
			}
		}
	}

	return true;
}

CollisionInfo BoundingBox::CollidesWith(const BoundingBox& boxB, const glm::vec3& velocity) {
	int numAxisA = normals.size();
	int numAxisB = boxB.normals.size();
	int numAxisCross = numAxisA * numAxisB;
	int totalAxis = numAxisA + numAxisB + numAxisCross;

	//axis, overlap
	glm::vec3 axisWithOverlap;
	float LargestOverlap = FLT_MAX;
	float positivePenetration = 0;
	float negativePenetration = 0;
	float PenetrationResult[2];

	glm::vec3 normalizedVelocity = glm::normalize(velocity);

	for (int i = 0; i < normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(normals[i]);

		float overlap = GetAxisOverlap(axis, *this, boxB, PenetrationResult);

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

	for (int i = 0; i < boxB.normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxB.normals[i]);

		float overlap = GetAxisOverlap(axis, *this, boxB, PenetrationResult);

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

	for (int i = 0; i < normals.size(); ++i) {
		for (int j = 0; j < boxB.normals.size(); ++j) {
			glm::vec3 cross = glm::cross(normals[i], boxB.normals[j]);

			if (cross == glm::vec3(0, 0, 0)) {
				continue;
			}

			std::cout << "axis: " << glm::to_string(cross) << std::endl;

			glm::vec3 axis = glm::normalize(cross);

			float overlap = GetAxisOverlap(axis, *this, boxB, PenetrationResult);

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

	return CollisionInfo{true, postitionChange, newVelocity };
}


#ifdef _DEBUG

void BoundingBox::BindGL(Camera* bCam){
	shader = (ShaderProgram*)new DebugShader(bCam, Position());

	GLuint mBuffers[2];

	glGenVertexArrays(1, &VertexBuffer);
	glBindVertexArray(VertexBuffer);

	glGenBuffers(2, mBuffers);

	size_t Vertex_Size = sizeof(vertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, Vertex_Size * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	numIndices = indices.size();
	
	glBindVertexArray(0);
}

void BoundingBox::Render() {

	shader->SetPosition(Position());

	shader->Use();

	shader->Update();

	glBindVertexArray(VertexBuffer);

	glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

#endif // _DEBUG