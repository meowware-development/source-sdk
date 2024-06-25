#pragma once
#include "../../math/vector.hpp"
#include "../../math/matrix.hpp"
#include "trace.hpp"

class HandleEntity;
class ClientUnknown;
struct Model;

enum class SolidType : int
{
	SOLID_NONE = 0,	// no solid model
	SOLID_BSP = 1,	// a BSP tree
	SOLID_BBOX = 2,	// an AABB
	SOLID_OBB = 3,	// an OBB (not implemented yet)
	SOLID_OBB_YAW = 4,	// an OBB, constrained so that it can only yaw
	SOLID_CUSTOM = 5,	// Always call into the entity for tests
	SOLID_VPHYSICS = 6,	// solid vphysics object, get vcollide from the model and collide with that
	SOLID_LAST,
};

enum class CollideType : int
{
	ENTITY_SHOULD_NOT_COLLIDE = 0,
	ENTITY_SHOULD_COLLIDE,
	ENTITY_SHOULD_RESPOND
};

enum class SolidFlag : int
{
	FSOLID_CUSTOMRAYTEST = 0x0001,	// Ignore solid type + always call into the entity for ray tests
	FSOLID_CUSTOMBOXTEST = 0x0002,	// Ignore solid type + always call into the entity for swept box tests
	FSOLID_NOT_SOLID = 0x0004,	// Are we currently not solid?
	FSOLID_TRIGGER = 0x0008,	// This is something may be collideable but fires touch functions
	// even when it's not collideable (when the FSOLID_NOT_SOLID flag is set)
	FSOLID_NOT_STANDABLE = 0x0010,	// You can't stand on this
	FSOLID_VOLUME_CONTENTS = 0x0020,	// Contains volumetric contents (like water)
	FSOLID_FORCE_WORLD_ALIGNED = 0x0040,	// Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
	FSOLID_USE_TRIGGER_BOUNDS = 0x0080,	// Uses a special trigger bounds separate from the normal OBB
	FSOLID_ROOT_PARENT_ALIGNED = 0x0100,	// Collisions are defined in root parent's local coordinate space
	FSOLID_TRIGGER_TOUCH_DEBRIS = 0x0200,	// This trigger will touch debris objects

	FSOLID_MAX_BITS = 10
};

class Collideable
{
public:
	// Gets at the entity handle associated with the collideable
	virtual HandleEntity* GetEntityHandle() = 0;

	// These methods return the bounds of an OBB measured in "collision" space
	// which can be retreived through the CollisionToWorldTransform or
	// GetCollisionOrigin/GetCollisionAngles methods
	virtual const Vector3& OBBMinsPreScaled() const = 0;
	virtual const Vector3& OBBMaxsPreScaled() const = 0;
	virtual const Vector3& OBBMins() const = 0;
	virtual const Vector3& OBBMaxs() const = 0;

	// Returns the bounds of a world-space box used when the collideable is being traced
	// against as a trigger. It's only valid to call these methods if the solid flags
	// have the FSOLID_USE_TRIGGER_BOUNDS flag set.
	virtual void			WorldSpaceTriggerBounds(Vector3* pVecWorldMins, Vector3* pVecWorldMaxs) const = 0;

	// custom collision test
	virtual bool			TestCollision(const Ray& ray, unsigned int fContentsMask, GameTrace& tr) = 0;

	// Perform hitbox test, returns true *if hitboxes were tested at all*!!
	virtual bool			TestHitboxes(const Ray& ray, unsigned int fContentsMask, GameTrace& tr) = 0;

	// Returns the BRUSH model index if this is a brush model. Otherwise, returns -1.
	virtual int				GetCollisionModelIndex() = 0;

	// Return the model, if it's a studio model.
	virtual const Model* GetCollisionModel() = 0;

	// Get angles and origin.
	virtual const Vector3& GetCollisionOrigin() const = 0;
	virtual const Vector3& GetCollisionAngles() const = 0;
	virtual const Matrix3x4& CollisionToWorldTransform() const = 0;

	// Return a SOLID_ define.
	virtual SolidType		GetSolid() const = 0;
	virtual int				GetSolidFlags() const = 0;

	// Gets at the containing class...
	virtual ClientUnknown* GetIClientUnknown() = 0;

	// We can filter out collisions based on collision group
	virtual int				GetCollisionGroup() const = 0;

	// Returns a world-aligned box guaranteed to surround *everything* in the collision representation
	// Note that this will surround hitboxes, trigger bounds, physics.
	// It may or may not be a tight-fitting box and its volume may suddenly change
	virtual void			WorldSpaceSurroundingBounds(Vector3* pVecMins, Vector3* pVecMaxs) = 0;

	virtual bool			ShouldTouchTrigger(int triggerSolidFlags) const = 0;

	// returns NULL unless this collideable has specified FSOLID_ROOT_PARENT_ALIGNED
	virtual const Matrix3x4* GetRootParentToWorldTransform() const = 0;
};