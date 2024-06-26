#pragma once
#include "../../math/vector.hpp"

struct SurfaceInfo {
	Vector3 vertices[16];
	unsigned long numberOfVertices;
	Vector3 normal;
	float distance;
	void* engineData;
};