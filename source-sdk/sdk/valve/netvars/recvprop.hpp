#pragma once

typedef void (*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);
typedef void (*RecvVarProxyFn)(void* pData, void* pStruct, void* pOut);
typedef void (*DataTableRecvVarProxyFn)(void* pProp, void** pOut, void* pData, int objectID);

typedef enum
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY, // Only encodes the XY of a vector, ignores Z
	DPT_String,
	DPT_Array,	// An array of the base types (can't be of datatables).
	DPT_DataTable,
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
	DPT_Quaternion,
#endif

#ifdef SUPPORTS_INT64
	DPT_Int64,
#endif

	DPT_NUMSendPropTypes

} SendPropType;

struct RecvTable;

struct RecvProp {
	const char* varName;
	SendPropType type;
	int flags;
private:
	int stringBufferSize;
	bool insideMainArray;
	void* extractData;
	void* arrayData;
	ArrayLengthRecvProxyFn lenhtgProxy;
	RecvVarProxyFn proxy;
	DataTableRecvVarProxyFn dataTableProxyFn;
public:
	RecvTable* dataTable;
	int offset;
	int elementsStride;
	int elements;
	const char* parentArrayPropName;
};