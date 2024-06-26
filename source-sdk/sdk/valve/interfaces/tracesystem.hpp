#pragma once
#include "../structures/trace.hpp"

class TraceSystem {
public:
	virtual int GetPointContents(const Vector3& pos, int mask = MASK_ALL, void** ent = nullptr) = 0;
	virtual int GetPointContentsWorld(const Vector3& pos, int mask = MASK_ALL) = 0;
	virtual int GetPointContentsCollideable(void* collide, const Vector3& pos) = 0;
	virtual void ClipRayToEntity(const Ray& ray, unsigned int mask, BaseEntity* ent, Trace* trace) = 0;
	virtual void ClipRayToCollideable(const Ray& ray, unsigned int mask, void* collide, Trace* trace) = 0;
	virtual void TraceRay(const Ray& ray, unsigned int mask, TraceFilter* filter, Trace* trace) = 0;
};