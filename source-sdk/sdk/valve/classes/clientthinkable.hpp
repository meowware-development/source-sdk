#pragma once

class ClientUnknown;

class ClientThinkable {
public:
	// Gets at the containing class...
	virtual ClientUnknown* GetIClientUnknown() = 0;

	virtual void				ClientThink() = 0;

	// Called when you're added to the think list.
	// GetThinkHandle's return value must be initialized to INVALID_THINK_HANDLE.
	virtual void* GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;

	// Called by the client when it deletes the entity.
	virtual void				Release() = 0;
};
