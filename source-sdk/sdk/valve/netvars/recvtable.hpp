#pragma once

struct RecvProp;

struct RecvTable {
	// The array of props. The number of props is stored by the "propCount" variable.
	RecvProp* props;
	int propCount;
	void* decoder;
	const char* tableName;
	bool initalized;
	bool inMainList;
};