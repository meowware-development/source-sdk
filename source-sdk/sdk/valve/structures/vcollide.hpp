#pragma once

struct VCollide
{
	unsigned short solidCount : 15;
	unsigned short isPacked : 1;
	unsigned short descSize;
	// VPhysicsSolids
	void** solids;
	char* pKeyValues;
};