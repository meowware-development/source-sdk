#pragma once

struct Model;
class ClientUnknown;

#include "../../math/vector.hpp"
#include "../../math/matrix.hpp"

class ClientRenderable {
public:
	// Gets at the containing class...
	virtual ClientUnknown* GetIClientUnknown() = 0;

	// Data accessors
	virtual Vector3 const& GetRenderOrigin(void) = 0;
	virtual Vector3 const& GetRenderAngles(void) = 0;
	virtual bool ShouldDraw(void) = 0;
	virtual bool IsTransparent(void) = 0;
	virtual bool UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool UsesFullFrameBufferTexture() = 0;

	virtual void* GetShadowHandle() const = 0;

	// Used by the leaf system to store its render handle.
	virtual void* RenderHandle() = 0;

	// Render baby!
	virtual const Model* GetModel() const = 0;
	virtual int						DrawModel(int flags) = 0;

	// Get the body parameter
	virtual int		GetBody() = 0;

	// Determine alpha and blend amount for transparent objects based on render state info
	virtual void	ComputeFxBlend() = 0;
	virtual int		GetFxBlend(void) = 0;

	// Determine the color modulation amount
	virtual void	GetColorModulation(float* color) = 0;

	// Returns false if the entity shouldn't be drawn due to LOD. 
	// (NOTE: This is no longer used/supported, but kept in the vtable for backwards compat)
	virtual bool	LODTest() = 0;

	// Call this to get the current bone transforms for the model.
	// currentTime parameter will affect interpolation
	// nMaxBones specifies how many matrices pBoneToWorldOut can hold. (Should be greater than or
	// equal to studiohdr_t::numbones. Use MAXSTUDIOBONES to be safe.)
	virtual bool	SetupBones(Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;

	virtual void	SetupWeights(const Matrix3x4* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void	DoAnimationEvents(void) = 0;

	// Return this if you want PVS notifications. See IPVSNotify for more info.	
	// Note: you must always return the same value from this function. If you don't,
	// undefined things will occur, and they won't be good.
	virtual void* GetPVSNotifyInterface() = 0;

	// Returns the bounds relative to the origin (render bounds)
	virtual void	GetRenderBounds(Vector3& mins, Vector3& maxs) = 0;

	// returns the bounds as an AABB in worldspace
	virtual void	GetRenderBoundsWorldspace(Vector3& mins, Vector3& maxs) = 0;

	// These normally call through to GetRenderAngles/GetRenderBounds, but some entities custom implement them.
	virtual void	GetShadowRenderBounds(Vector3& mins, Vector3& maxs, void* shadowType) = 0;

	// Should this object be able to have shadows cast onto it?
	virtual bool	ShouldReceiveProjectedTextures(int flags) = 0;

	// These methods return true if we want a per-renderable shadow cast direction + distance
	virtual bool	GetShadowCastDistance(float* pDist, void* shadowType) const = 0;
	virtual bool	GetShadowCastDirection(Vector3* pDirection, void* shadowType) const = 0;

	// Other methods related to shadow rendering
	virtual bool	IsShadowDirty() = 0;
	virtual void	MarkShadowDirty(bool bDirty) = 0;

	// Iteration over shadow hierarchy
	virtual ClientRenderable* GetShadowParent() = 0;
	virtual ClientRenderable* FirstShadowChild() = 0;
	virtual ClientRenderable* NextShadowPeer() = 0;

	// Returns the shadow cast type
	virtual void* ShadowCastType() = 0;

	// Create/get/destroy model instance
	virtual void CreateModelInstance() = 0;
	virtual void* GetModelInstance() = 0;

	// Returns the transform from RenderOrigin/RenderAngles to world
	virtual const Matrix3x4& RenderableToWorldTransform() = 0;

	// Attachments
	virtual int LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool GetAttachment(int number, Vector3& origin, Vector3& angles) = 0;
	virtual bool GetAttachment(int number, Matrix3x4& matrix) = 0;

	// Rendering clip plane, should be 4 floats, return value of NULL indicates a disabled render clip plane
	virtual float* GetRenderClipPlane(void) = 0;

	// Get the skin parameter
	virtual int		GetSkin() = 0;

	// Is this a two-pass renderable?
	virtual bool	IsTwoPass(void) = 0;

	virtual void	OnThreadedDrawSetup() = 0;

	virtual bool	UsesFlexDelayedWeights() = 0;

	virtual void	RecordToolMessage() = 0;

	virtual bool	IgnoresZBuffer(void) const = 0;
};