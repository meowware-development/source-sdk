#pragma once
#include "../../math/vector.hpp"
#include "../datatypes/trace.hpp"
#include "../datatypes/studio.hpp"

struct Model;
struct Material;
class ClientRenderable;

struct VCollide
{
	unsigned short solidCount : 15;
	unsigned short isPacked : 1;
	unsigned short descSize;
	// VPhysicsSolids
	void** solids;
	char* pKeyValues;
};

class ModelInfo
{
public:
	virtual							~ModelInfo(void) { }

	// Returns Model* pointer for a model given a precached or dynamic model index.
	virtual const Model* GetModel(int modelindex) = 0;

	// Returns index of model by name for precached or known dynamic models.
	// Does not adjust reference count for dynamic models.
	virtual int						GetModelIndex(const char* name) const = 0;

	// Returns name of model
	virtual const char* GetModelName(const Model* model) const = 0;
	virtual VCollide* GetVCollide(const Model* model) = 0;
	virtual VCollide* GetVCollide(int modelindex) = 0;
	virtual void					GetModelBounds(const Model* model, Vector3& mins, Vector3& maxs) const = 0;
	virtual	void					GetModelRenderBounds(const Model* model, Vector3& mins, Vector3& maxs) const = 0;
	virtual int						GetModelFrameCount(const Model* model) const = 0;
	virtual int						GetModelType(const Model* model) const = 0;
	virtual void* GetModelExtraData(const Model* model) = 0;
	virtual bool					ModelHasMaterialProxy(const Model* model) const = 0;
	virtual bool					IsTranslucent(Model const* model) const = 0;
	virtual bool					IsTranslucentTwoPass(const Model* model) const = 0;
	virtual void					RecomputeTranslucency(const Model* model, int nSkin, int nBody, void /*IClientRenderable*/* pClientRenderable, float fInstanceAlphaModulate = 1.0f) = 0;
	virtual int						GetModelMaterialCount(const Model* model) const = 0;
	virtual void					GetModelMaterials(const Model* model, int count, Material** ppMaterial) = 0;
	virtual bool					IsModelVertexLit(const Model* model) const = 0;
	virtual const char* GetModelKeyValueText(const Model* model) = 0;
	virtual bool					GetModelKeyValue(const Model* model, void* buf) = 0; // supports keyvalue blocks in submodels
	virtual float					GetModelRadius(const Model* model) = 0;

	virtual const StudioHDR* FindModel(const StudioHDR* pStudioHdr, void** cache, const char* modelname) const = 0;
	virtual const StudioHDR* FindModel(void* cache) const = 0;
	virtual	void* GetVirtualModel(const StudioHDR* pStudioHdr) const = 0;
	virtual byte* GetAnimBlock(const StudioHDR* pStudioHdr, int iBlock) const = 0;

	// Available on client only!!!
	virtual void					GetModelMaterialColorAndLighting(const Model* model, Vector3 const& origin,
		Vector3 const& angles, GameTrace* pTrace,
		Vector3& lighting, Vector3& matColor) = 0;
	virtual void					GetIlluminationPoint(const Model* model, ClientRenderable* pRenderable, Vector3 const& origin,
		Vector3 const& angles, Vector3* pLightingCenter) = 0;

	virtual int						GetModelContents(int modelIndex) = 0;
	virtual StudioHDR* GetStudiomodel(const Model* model) = 0;
	virtual int						GetModelSpriteWidth(const Model* model) const = 0;
	virtual int						GetModelSpriteHeight(const Model* model) const = 0;

	// Sets/gets a map-specified fade range (client only)
	virtual void					SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual void					GetLevelScreenFadeRange(float* pMinArea, float* pMaxArea) const = 0;

	// Sets/gets a map-specified per-view fade range (client only)
	virtual void					SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;

	// Computes fade alpha based on distance fade + screen fade (client only)
	virtual unsigned char			ComputeLevelScreenFade(const Vector3& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual unsigned char			ComputeViewScreenFade(const Vector3& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;

	// both client and server
	virtual int						GetAutoplayList(const StudioHDR* pStudioHdr, unsigned short** pAutoplayList) const = 0;

	// Gets a virtual terrain collision model (creates if necessary)
	// NOTE: This may return NULL if the terrain model cannot be virtualized
	virtual void* GetCollideForVirtualTerrain(int index) = 0;

	virtual bool					IsUsingFBTexture(const Model* model, int nSkin, int nBody, void /*IClientRenderable*/* pClientRenderable) const = 0;

	// Obsolete methods. These are left in to maintain binary compatibility with clients using the ModelInfo old version.
	virtual const Model* FindOrLoadModel(const char* name) = 0;
	virtual void					InitDynamicModels() = 0;
	virtual void					ShutdownDynamicModels() = 0;
	virtual void					AddDynamicModel(const char* name, int nModelIndex = -1) = 0;
	virtual void					ReferenceModel(int modelindex) = 0;
	virtual void					UnreferenceModel(int modelindex) = 0;
	virtual void					CleanupDynamicModels(bool bForce = false) = 0;

	virtual MDLHandle_t				GetCacheHandle(const Model* model) const = 0;

	// Returns planes of non-nodraw brush model surfaces
	virtual int						GetBrushModelPlaneCount(const Model* model) const = 0;
	virtual void					GetBrushModelPlane(const Model* model, int nIndex, Plane& plane, Vector3* pOrigin) const = 0;
	virtual int						GetSurfacepropsForVirtualTerrain(int index) = 0;

	// Poked by engine host system
	virtual void					OnLevelChange() = 0;

	virtual int						GetModelClientSideIndex(const char* name) const = 0;

	// Returns index of model by name, dynamically registered if not already known.
	virtual int						RegisterDynamicModel(const char* name, bool bClientSide) = 0;

	virtual bool					IsDynamicModelLoading(int modelIndex) = 0;

	virtual void					AddRefDynamicModel(int modelIndex) = 0;
	virtual void					ReleaseDynamicModel(int modelIndex) = 0;

	// Registers callback for when dynamic model has finished loading.
	// Automatically adds reference, pair with ReleaseDynamicModel.
	virtual bool					RegisterModelLoadCallback(int modelindex, void* pCallback, bool bCallImmediatelyIfLoaded = true) = 0;
	virtual void					UnregisterModelLoadCallback(int modelindex, void* pCallback) = 0;
};