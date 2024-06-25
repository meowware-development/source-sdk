#pragma once
#include "../../math/vector.hpp"
#include "../misc/sourcedefs.hpp"

struct Plane 
{
	Vector3	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];
};

struct TraceSurface
{
	const char* name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};


class BaseTrace 
{
public:
	// these members are aligned!!
	Vector3			startpos;				// start position
	Vector3			endpos;					// final position
	Plane		plane;					// surface normal at impact

	float			fraction;				// time completed, 1.0 = didn't hit anything

	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data

	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area
};

class BaseEntity;

class GameTrace : public BaseTrace 
{
public:
	inline bool DidHit() const { return fraction < 1 || allsolid || startsolid; };
	inline bool DidHitEntity() const { return entity; };

	float		fractionleftsolid;		// time we left a solid, only valid if we started in solid
	TraceSurface	surface;				// surface hit (impact surface)

	int			hitgroup;				// 0 == generic, non-zero is specific body part
	short		physicsbone;			// physics bone hit by trace in studio

	BaseEntity* entity;

	// NOTE: this member is overloaded.
	// If hEnt points at the world entity, then this is the static prop index.
	// Otherwise, this is the hitbox index.
	int			hitbox;					// box hit by trace in studio
};

enum class TraceType : int
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the HandleEntity for props through the filter, unlike all other filters
};

class HandleEntity;

class TraceFilter
{
public:
	virtual bool ShouldHitEntity(HandleEntity* pEntity, int contentsMask) = 0;
	virtual TraceFilter	GetTraceType() const = 0;
};

struct Ray 
{
	VectorAligned start; // starting point, centered within the extents
	VectorAligned delta; // direction + length of the ray
	VectorAligned startOffset; // Add this to m_Start to get the actual ray start
	VectorAligned extents; // Describes an axis aligned box extruded along a ray
	bool isRay; // are the extents zero?
	bool isSwept; // is delta != 0?

	void Initialize(const Vector3& startPos, const Vector3& endPos) {
		delta = endPos - startPos;

		isSwept = (delta.LengthSqr() != 0);

		extents.x = extents.y = extents.z = 0.0f;
		isRay = true;

		startOffset.x = startOffset.y = startOffset.z = 0.0f;

		start = startPos;
	}

	void Initialize(const Vector3& vecStart, const Vector3& vecEnd, const Vector3& min, const Vector3& max) {
		delta = vecEnd - vecStart;

		isSwept = (delta.LengthSqr() != 0);

		extents.x = (max.x - min.x);
		extents.y = (max.y - min.y);
		extents.z = (max.z - min.z);
		isRay = false;

		startOffset.x = startOffset.y = startOffset.z = 0.0f;

		start = vecStart + ((max + min) * 0.5f);
	}
};
