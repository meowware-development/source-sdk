#pragma once

#pragma once
#include <cstdint>
#include "../../math/matrix.hpp"
#include "../../math/vector.hpp"

#define MAX_QPATH  260

#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01    // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL         0x02    // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL          0x04    // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE        0x08    // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER      0x10    // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x0007FF00
#define BONE_USED_BY_HITBOX             0x00000100    // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT         0x00000200    // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400    // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1        0x00000800
#define BONE_USED_BY_VERTEX_LOD2        0x00001000
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000    // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		128		// total bones actually used

#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32

enum class HitGroups {
	GENERIC = 0,
	HEAD = 1,
	CHEST = 2,
	STOMACH = 3,
	LEFTARM = 4,
	RIGHTARM = 5,
	LEFTLEG = 6,
	RIGHTLEG = 7,
	GEAR = 10
};

enum class HitBoxes {
	HEAD,
	NECK,
	PELVIS,
	STOMACH,
	LOWER_CHEST,
	CHEST,
	UPPER_CHEST,
	RIGHT_THIGH,
	LEFT_THIGH,
	RIGHT_CALF,
	LEFT_CALF,
	RIGHT_FOOT,
	LEFT_FOOT,
	RIGHT_HAND,
	LEFT_HAND,
	RIGHT_UPPER_ARM,
	RIGHT_FORE_ARM,
	LEFT_UPPER_ARM,
	LEFT_FORE_ARM,
	MAX
};

struct StudioBone {
	int nameIndex;

	inline char* const Name(void) const {
		return ((char*)this) + nameIndex;
	}

	int parent;
	int boneController[6];

	Vector3 pos;
	float quat[4];
	float rotation[3];

	Vector3 posScale;
	Vector3 rotScale;

	Matrix3x4 poseToBone;
	float quatAlignement[4];
	int flags;
	int procType;
	int procIndex;
	mutable int physicsBone;

	inline void* Procedure() const {
		if (procIndex == 0) return NULL;
		else return(void*)(((unsigned char*)this) + procIndex);
	};

	int surfacePropIdx;
	inline char* const SurfaceProp(void) const {
		return ((char*)this) + surfacePropIdx;
	}
	inline int GetSurfaceProp(void) const {
		return surfPropLookup;
	}

	int contents;
	int surfPropLookup;
};

struct StudioBox {
	int bone;
	int group;
	Vector3 mins;
	Vector3 maxs;
	int name_index;
	int pad01[3];
	float radius;
	int pad02[4];
};

struct StudioHitboxSet {
	int nameIndex;
	int hitboxCount;
	int hitboxIndex;

	inline char* const Name(void) const {
		return ((char*)this) + nameIndex;
	}

	inline StudioBox* Hitbox(int i) const {
		return (StudioBox*)(((unsigned char*)this) + hitboxIndex) + i;
	}
};

class StudioHDR {
public:
	int id;
	int version;
	long checksum;
	char name[64];
	int length;
	Vector3 eyePosition;
	Vector3 illiumPos;
	Vector3 hullMin;
	Vector3 hullMax;
	Vector3 viewMins;
	Vector3 viewMaxs;
	int flags;
	int bonesCount;
	int boneIndex;
	int boneControllersCount;
	int boneControllerIndex;
	int hitboxSetsCount;
	int hitboxSetIndex;
	int localAnimCount;
	int localAnimIndex;
	int localSeqIount;
	int localSeqIndex;
	int activityListVersion;
	int eventsIndexed;
	int texturesCount;
	int textureIndex;

	StudioHitboxSet* HitboxSet(int i) {
		if (i > hitboxSetsCount) return nullptr;
		return (StudioHitboxSet*)((uint8_t*)this + hitboxSetIndex) + i;
	}

	StudioBone* Bone(int i) {
		if (i > bonesCount) return nullptr;
		return (StudioBone*)((uint8_t*)this + boneIndex) + i;
	}
};