#pragma once
#include "../../math/vector.hpp"

#define MODELFLAG_MATERIALPROXY					0x0001	// we've got a material proxy
#define MODELFLAG_TRANSLUCENT					0x0002	// we've got a translucent model
#define MODELFLAG_VERTEXLIT						0x0004	// we've got a vertex-lit model
#define MODELFLAG_TRANSLUCENT_TWOPASS			0x0008	// render opaque part in opaque pass
#define MODELFLAG_FRAMEBUFFER_TEXTURE			0x0010	// we need the framebuffer as a texture
#define MODELFLAG_HAS_DLIGHT					0x0020	// need to check dlights
#define MODELFLAG_STUDIOHDR_USES_FB_TEXTURE		0x0100	// persisted from studiohdr
#define MODELFLAG_STUDIOHDR_USES_BUMPMAPPING	0x0200	// persisted from studiohdr
#define MODELFLAG_STUDIOHDR_USES_ENV_CUBEMAP	0x0400	// persisted from studiohdr
#define MODELFLAG_STUDIOHDR_AMBIENT_BOOST		0x0800	// persisted from studiohdr
#define MODELFLAG_STUDIOHDR_DO_NOT_CAST_SHADOWS	0x1000	// persisted from studiohdr

enum ModelType
{
	BAD = 0,
	BRUSH,
	SPRITE,
	STUDIO
};

struct Model {
	void* fileHandle;
	char* name;
	int loadFlags;
	int serverCount;
	void** Material;
	ModelType type;
	int flags; // MODEFLAG_ shit
	Vector3 min, max;
	float radius;
	unsigned short loadedHandle;
};