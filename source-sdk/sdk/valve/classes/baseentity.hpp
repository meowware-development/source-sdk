#pragma once
#include "cliententity.hpp"
#include "../../math/vector.hpp"
#include "../structures/firebulletsinfo.hpp"
#include "../structures/takedamageinfo.hpp"
#include "collideable.hpp"
#include "trace.hpp"
#include "../structures/studio.hpp"
#include "../misc/color.hpp"

enum class ShadowType : int
{
	SHADOWS_NONE = 0,
	SHADOWS_SIMPLE,
	SHADOWS_RENDER_TO_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC,	// the shadow is always changing state
	SHADOWS_RENDER_TO_DEPTH_TEXTURE,
};

enum class RenderGroup : int
{
	RENDER_GROUP_OPAQUE_STATIC_HUGE = 0,		// Huge static prop
	RENDER_GROUP_OPAQUE_ENTITY_HUGE = 1,		// Huge opaque entity
	RENDER_GROUP_OPAQUE_STATIC = RENDER_GROUP_OPAQUE_STATIC_HUGE + 6,
	RENDER_GROUP_OPAQUE_ENTITY,					// Opaque entity (smallest size, or default)

	RENDER_GROUP_TRANSLUCENT_ENTITY,
	RENDER_GROUP_TWOPASS,						// Implied opaque and translucent in two passes
	RENDER_GROUP_VIEW_MODEL_OPAQUE,				// Solid weapon view models
	RENDER_GROUP_VIEW_MODEL_TRANSLUCENT,		// Transparent overlays etc

	RENDER_GROUP_OPAQUE_BRUSH,					// Brushes

	RENDER_GROUP_OTHER,							// Unclassfied. Won't get drawn.

	// This one's always gotta be last
	RENDER_GROUP_COUNT
};

struct Model;
struct Team;

class BaseEntity : public ClientEntity {
public:
	virtual ~BaseEntity() = 0;

	virtual void					FireBullets(const FireBulletsInfo& info);
	virtual void					ModifyFireBulletsDamage(TakeDamageInfo* dmgInfo);
	virtual bool					ShouldDrawUnderwaterBulletBubbles();
	virtual bool					ShouldDrawWaterImpacts(void) { return true; }
	virtual bool					HandleShotImpactingWater(const FireBulletsInfo& info,
		const Vector3& vecEnd, TraceFilter* pTraceFilter, Vector3* pVecTracerDest);
	virtual TraceFilter* GetBeamTraceFilter(void);
	virtual void					DispatchTraceAttack(const TakeDamageInfo& info, const Vector3& vecDir, GameTrace* ptr, bool* pAccumulator = NULL);
	virtual void					TraceAttack(const TakeDamageInfo& info, const Vector3& vecDir, GameTrace* ptr, bool* pAccumulator = NULL);
	virtual void					DoImpactEffect(GameTrace& tr, int nDamageType);
	virtual void					MakeTracer(const Vector3& vecTracerSrc, const GameTrace& tr, int iTracerType);
	virtual int						GetTracerAttachment(void);
	virtual int						BloodColor();
	virtual const char* GetTracerType();

	virtual void					Spawn(void);
	virtual void					SpawnClientEntity(void);
	virtual void					Precache(void);
	virtual void					Activate();

	virtual void					ParseMapData(void* mapData);
	virtual bool					KeyValue(const char* szKeyName, const char* szValue);
	virtual bool					KeyValue(const char* szKeyName, float flValue);
	virtual bool					KeyValue(const char* szKeyName, const Vector3& vecValue);
	virtual bool					GetKeyValue(const char* szKeyName, char* szValue, int iMaxLen);

	virtual bool					Init(int entnum, int iSerialNum);

	//@TODO: Add BaseAnimating to the SDK.
	virtual void* GetBaseAnimating() { return NULL; }
	virtual void					SetClassname(const char* className);

	virtual void SetRefEHandle(const EHANDLE& handle);
	virtual const EHANDLE& GetRefEHandle() const;

	virtual void			RecordToolMessage();

	virtual void					Release();
	virtual Collideable* GetCollideable() = 0;
	virtual ClientNetworkable* GetClientNetworkable() { return this; }
	virtual ClientRenderable* GetClientRenderable() { return this; }
	virtual ClientEntity* GetIClientEntity() { return this; }
	virtual BaseEntity* GetBaseEntity() { return this; }
	virtual ClientThinkable* GetClientThinkable() { return this; }

	virtual const Vector3& GetRenderOrigin(void);
	virtual const Vector3& GetRenderAngles(void);
	virtual Vector3					GetObserverCamOrigin(void) { return GetRenderOrigin(); }	// Return the origin for player observers tracking this target
	virtual const Matrix3x4& RenderableToWorldTransform();
	virtual bool					IsTransparent(void);
	virtual bool					IsTwoPass(void);
	virtual bool					UsesPowerOfTwoFrameBufferTexture();
	virtual bool					UsesFullFrameBufferTexture();
	virtual bool					IgnoresZBuffer(void) const;
	virtual const Model* GetModel(void) const;
	virtual int						DrawModel(int flags);
	virtual void					ComputeFxBlend(void);
	virtual int						GetFxBlend(void);
	virtual bool					LODTest() { return true; }   // NOTE: UNUSED
	virtual void					GetRenderBounds(Vector3& mins, Vector3& maxs);
	virtual void* GetPVSNotifyInterface();
	virtual void					GetRenderBoundsWorldspace(Vector3& absMins, Vector3& absMaxs);

	virtual void					GetShadowRenderBounds(Vector3& mins, Vector3& maxs, ShadowType shadowType);

	// Determine the color modulation amount
	virtual void					GetColorModulation(float* color);

	virtual void OnThreadedDrawSetup() {}
	virtual bool					TestCollision(const Ray& ray, unsigned int fContentsMask, GameTrace& tr);
	virtual bool					TestHitboxes(const Ray& ray, unsigned int fContentsMask, GameTrace& tr);

	// This function returns a value that scales all damage done by this entity.
	// Use CDamageModifier to hook in damage modifiers on a guy.
	virtual float					GetAttackDamageScale(void);

	virtual void					NotifyShouldTransmit(ShouldTransmitState state);

	// save out interpolated values
	virtual void					PreDataUpdate(DataUpdateType updateType);
	virtual void					PostDataUpdate(DataUpdateType updateType);
	virtual void					OnDataUnchangedInPVS();

	virtual void					ValidateModelIndex(void);

	// pvs info. NOTE: Do not override these!!
	virtual void					SetDormant(bool bDormant);
	virtual bool					IsDormant(void);

	// Tells the entity that it's about to be destroyed due to the client receiving
	// an uncompressed update that's caused it to destroy all entities & recreate them.
	virtual void					SetDestroyedOnRecreateEntities(void);

	virtual int				GetEFlags() const;
	virtual void			SetEFlags(int iEFlags);

	virtual int						EntityIndex(void) const;

	// typeof(msg) == bf_read, got lazy lmao
	virtual void					ReceiveMessage(int classID, int& msg);

	virtual void* GetDataTableBasePtr();
	virtual void					ClientThink();

	virtual void*		GetThinkHandle();
	virtual void					SetThinkHandle(void* hThink);

	virtual bool					ShouldSavePhysics();

	// save/restore stuff
	virtual void					OnSave();
	virtual void					OnRestore();
	// capabilities for save/restore
	virtual int						ObjectCaps(void);
	// only overload these if you have special data to serialize
	virtual int						Save(int& save);
	virtual int						Restore(int& restore);

	virtual bool	CreateVPhysics();

	virtual void	VPhysicsDestroyObject(void);

	// Purpose: My physics object has been updated, react or extract data
	virtual void					VPhysicsUpdate(void* pPhysics);
	virtual int						VPhysicsGetObjectList(void** pList, int listMax);
	virtual bool					VPhysicsIsFlesh(void);

	virtual bool					SetupBones(Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	virtual void					SetupWeights(const Matrix3x4* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights);
	virtual bool					UsesFlexDelayedWeights() { return false; }
	virtual void					DoAnimationEvents(void);

	// Add entity to visible entities list?
	virtual void					AddEntity(void);

	virtual const Vector3& GetAbsOrigin(void) const;
	virtual const Vector3& GetAbsAngles(void) const;
	virtual const Vector3& GetPrevLocalOrigin() const;
	virtual const Vector3& GetPrevLocalAngles() const;

	virtual int						CalcOverrideModelIndex() { return -1; }

	virtual const Vector3& WorldAlignMins() const;
	virtual const Vector3& WorldAlignMaxs() const;

	virtual const Vector3& WorldSpaceCenter() const;

	virtual void					ComputeWorldSpaceSurroundingBox(Vector3* pVecWorldMins, Vector3* pVecWorldMaxs);
	virtual float						GetHealthBarHeightOffset() const { return 0.f; }

	virtual void* GetMouth(void);

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool					GetSoundSpatialization(int& info);

	// Attachments
	virtual int						LookupAttachment(const char* pAttachmentName) { return -1; }
	virtual bool					GetAttachment(int number, Matrix3x4& matrix);
	virtual bool					GetAttachment(int number, Vector3& origin);
	virtual	bool					GetAttachment(int number, Vector3& origin, Vector3& angles);
	virtual bool					GetAttachmentVelocity(int number, Vector3& originVel, Vector4& angleVel);

	// Team handling
	virtual Team* GetTeam(void) const = 0;
	virtual int						GetTeamNumber(void) const;
	virtual void					ChangeTeam(int iTeamNum);			// Assign this entity to a team.
	virtual int						GetRenderTeamNumber(void);
	virtual bool					InSameTeam(const BaseEntity* pEntity) const;	// Returns true if the specified entity is on the same team as this one
	virtual bool					InLocalTeam(void);

	virtual bool					IsValidIDTarget(void) = 0;
	virtual const char* GetIDString(void) { return ""; };

	// See CSoundEmitterSystem
	virtual void ModifyEmitSoundParams(int& params);

	virtual bool InitializeAsClientEntity(const char* pszModelName, RenderGroup renderGroup);

	// This function gets called on all client entities once per simulation phase.
	// It dispatches events like OnDataChanged(), and calls the legacy function AddEntity().
	virtual void					Simulate();


	// This event is triggered during the simulation phase if an entity's data has changed. It is 
	// better to hook this instead of PostDataUpdate() because in PostDataUpdate(), server entity origins
	// are incorrect and attachment points can't be used.
	virtual void					OnDataChanged(DataUpdateType type);

	// This is called once per frame before any data is read in from the server.
	virtual void					OnPreDataChanged(DataUpdateType type);

	virtual void* GetClientVehicle() { return NULL; }

	// Returns the aiment render origin + angles
	virtual void					GetAimEntOrigin(ClientEntity* pAttachedTo, Vector3* pAbsOrigin, Vector3* pAbsAngles);

	// get network origin from previous update
	virtual const Vector3& GetOldOrigin();

	virtual RenderGroup			GetRenderGroup();

	virtual void					GetToolRecordingState(void* msg);
	virtual void					CleanupToolRecordingState(void* msg);

	// The value returned by here determines whether or not (and how) the entity
	// is put into the spatial partition.
	virtual CollideType			GetCollideType(void);

	virtual bool					ShouldDraw();
	virtual void					UpdateVisibility();

	// Returns true if the entity changes its position every frame on the server but it doesn't
	// set animtime. In that case, the client returns true here so it copies the server time to
	// animtime in OnDataChanged and the position history is correct for interpolation.
	virtual bool					IsSelfAnimating();

	// Set appropriate flags and store off data when these fields are about to change
	virtual	void					OnLatchInterpolatedVariables(int flags);
	// For predictable entities, stores last networked value
	void							OnStoreLastNetworkedValue();

	// Initialize things given a new model.
	virtual StudioHDR* OnNewModel();
	virtual void					OnNewParticleEffect(const char* pszParticleName, void* pNewParticleEffect);

	virtual void					ResetLatched();

	virtual bool					Interpolate(float currentTime);

	// Did the object move so far that it shouldn't interpolate?
	bool							Teleported(void);
	// Is this a submodel of the world ( *1 etc. in name ) ( brush models only )
	virtual bool					IsSubModel(void);
	// Deal with EF_* flags
	virtual void					CreateLightEffects(void);

	// Reset internal fields
	virtual void					Clear(void);
	// Helper to draw raw brush models
	virtual int						DrawBrushModel(bool bTranslucent, int nFlags, bool bTwoPass);

	// returns the material animation start time
	virtual float					GetTextureAnimationStartTime();
	// Indicates that a texture animation has wrapped
	virtual void					TextureAnimationWrapped();

	// Set the next think time. Pass in CLIENT_THINK_ALWAYS to have Think() called each frame.
	virtual void					SetNextClientThink(float nextThinkTime);

	// anything that has health can override this...
	virtual void					SetHealth(int iHealth) {}
	virtual int						GetHealth() const { return 0; }
	virtual int						GetMaxHealth() const { return 1; }
	virtual bool					IsVisibleToTargetID(void) const { return false; }
	virtual bool					IsHealthBarVisible(void) const { return false; }

	virtual void*			ShadowCastType();

	// Should this object receive shadows?
	virtual bool					ShouldReceiveProjectedTextures(int flags);

	// Shadow-related methods
	virtual bool IsShadowDirty();
	virtual void MarkShadowDirty(bool bDirty);
	virtual ClientRenderable* GetShadowParent();
	virtual ClientRenderable* FirstShadowChild();
	virtual ClientRenderable* NextShadowPeer();

	virtual void					AddDecal(const Vector3& rayStart, const Vector3& rayEnd,
											 const Vector3& decalCenter, int hitbox, int decalIndex, bool doTrace, GameTrace& tr, int maxLODToDecal = -1);

	virtual void					AddColoredDecal(const Vector3& rayStart, const Vector3& rayEnd,
													const Vector3& decalCenter, int hitbox, int decalIndex, bool doTrace, GameTrace& tr, Color cColor, int maxLODToDecal = -1);

	virtual bool					IsClientCreated(void) const;

	virtual void					UpdateOnRemove(void);

	virtual void					SUB_Remove(void);

	virtual void					SetPredictable(bool state);

	virtual int						RestoreData(const char* context, int slot, int type);

	virtual char const* DamageDecal(int bitsDamageType, int gameMaterial);
	virtual void					DecalTrace(GameTrace* pTrace, char const* decalName);
	virtual void					ImpactTrace(GameTrace* pTrace, int iDamageType, const char* pCustomImpactName);

	virtual bool					ShouldPredict(void) { return false; };

	virtual void					Think(void) = 0;

	virtual bool			IsCurrentlyTouching(void) const;

	virtual void			StartTouch(BaseEntity* pOther);
	virtual void			Touch(BaseEntity* pOther);
	virtual void			EndTouch(BaseEntity* pOther);

	virtual unsigned int	PhysicsSolidMaskForEntity(void) const;

	virtual void					PhysicsSimulate(void);
	virtual bool					IsAlive(void);

	bool							IsInWorld(void) { return true; }

	bool							IsWorld() { return EntityIndex() == 0; }
	

	virtual bool					IsPlayer(void) const { return false; };
	virtual bool					IsBaseCombatCharacter(void) { return false; };
	virtual void* MyCombatCharacterPointer(void) { return NULL; }
	virtual bool					IsNPC(void) { return false; }
	virtual bool					IsNextBot() { return false; }

	// Returns the eye point + angles (used for viewing + shooting)
	virtual Vector3			EyePosition(void);
	virtual const Vector3& EyeAngles(void);		// Direction of eyes
	virtual const Vector3& LocalEyeAngles(void);	// Direction of eyes in local space (pl.v_angle)

	// position of ears
	virtual Vector3		EarPosition(void);

	virtual bool		ShouldCollide(int collisionGroup, int contentsMask) const;

	virtual const Vector3& GetViewOffset() const;
	virtual void		  SetViewOffset(const Vector3& v);


	// For shadows rendering the correct body + sequence...
	virtual int GetBody() { return 0; }
	virtual int GetSkin() { return 0; }

	virtual void* GetModelInstance() = 0;
	virtual void* GetShadowHandle() const = 0;
	virtual void* RenderHandle() = 0;

	virtual bool ShouldInterpolate();

	virtual void BoneMergeFastCullBloat(Vector3& localMins, Vector3& localMaxs, const Vector3& thisEntityMins, const Vector3& thisEntityMaxs) const;

	virtual bool					OnPredictedEntityRemove(bool isbeingremoved, BaseEntity* predicted);

	virtual bool					GetShadowCastDistance(float* pDist, ShadowType shadowType) const;
	virtual bool					GetShadowCastDirection(Vector3* pDirection, ShadowType shadowType) const;
	virtual BaseEntity* GetShadowUseOtherEntity(void) const;
	virtual void					SetShadowUseOtherEntity(BaseEntity* pEntity);

	virtual bool					AddRagdollToFadeQueue(void) { return true; }

	virtual bool					IsDeflectable() { return false; }

	virtual void PerformCustomPhysics(Vector3* pNewPosition, Vector3* pNewVelocity, Vector3* pNewAngles, Vector3* pNewAngVelocity);
};