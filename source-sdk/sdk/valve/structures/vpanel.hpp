#pragma once
#include "memutil.hpp"

#undef SendMessage
#undef GetClassName

struct SurfacePlat;

struct VPanel {
	virtual ~VPanel() = 0;

	virtual void Init(void* clientPanel) = 0;

	virtual SurfacePlat* Plat() = 0;
	virtual void SetPlat(SurfacePlat* pl) = 0;

	virtual unsigned long GetHPanel() { return hPanel; }
	virtual void SetHPanel(unsigned long  hPanel) { hPanel = hPanel; }

	virtual bool IsPopup() = 0;
	virtual void SetPopup(bool state) = 0;
	virtual bool IsFullyVisible() = 0;

	virtual void SetPos(int x, int y) = 0;
	virtual void GetPos(int& x, int& y) = 0;
	virtual void SetSize(int wide, int tall) = 0;
	virtual void GetSize(int& wide, int& tall) = 0;
	virtual void SetMinimumSize(int wide, int tall) = 0;
	virtual void GetMinimumSize(int& wide, int& tall) = 0;
	virtual void SetZPos(int z) = 0;
	virtual int  GetZPos() = 0;

	virtual void GetAbsPos(int& x, int& y) = 0;
	virtual void GetClipRect(int& x0, int& y0, int& x1, int& y1) = 0;
	virtual void SetInset(int left, int top, int right, int bottom) = 0;
	virtual void GetInset(int& left, int& top, int& right, int& bottom) = 0;

	virtual void Solve() = 0;

	virtual void SetVisible(bool state) = 0;
	virtual void SetEnabled(bool state) = 0;
	virtual bool IsVisible() = 0;
	virtual bool IsEnabled() = 0;
	virtual void SetParent(VPanel* newParent) = 0;
	virtual int GetChildCount() = 0;
	virtual VPanel* GetChild(int index) = 0;
	virtual VPanel* GetParent() = 0;
	virtual void MoveToFront() = 0;
	virtual void MoveToBack() = 0;
	virtual bool HasParent(VPanel* potentialParent) = 0;

	virtual CUtlVector< VPanel* >& GetChildren() = 0;

	virtual const char* GetName() = 0;
	virtual const char* GetClassName() = 0;

	virtual unsigned long GetScheme() = 0;

	// Params is a Keyvalues*...
	virtual void SendMessage(void* params, unsigned int ifromPanel) = 0;

	virtual void* Client() { return clientPanel; }

	// input interest
	virtual void SetKeyBoardInputEnabled(bool state) = 0;
	virtual void SetMouseInputEnabled(bool state) = 0;
	virtual bool IsKeyBoardInputEnabled() = 0;
	virtual bool IsMouseInputEnabled() = 0;

	virtual bool IsTopmostPopup() const = 0;
	virtual void SetTopmostPopup(bool bEnable) = 0;

	virtual void SetSiblingPin(VPanel* newSibling, unsigned char iMyCornerToPin = 0, unsigned char iSiblingCornerToPinTo = 0) = 0;

	virtual void GetInternalAbsPos(int& x, int& y) = 0;
	virtual void TraverseLevel(int val) = 0;

	CUtlVector<VPanel*> children;
	VPanel* parent;
	SurfacePlat* plat;
	unsigned long hPanel;

	void* clientPanel;

	short pos[2];
	short size[2];
	short minimumSize[2];

	short inset[4];
	short clipRect[4];
	short absPos[2];

	short zpos;

	bool visible : 1;
	bool enabled : 1;
	bool popup : 1;
	bool mouseInput : 1;
	bool kbInput : 1;
	bool isTopmostPopup : 1;

	VPanel* pinsibling;
	unsigned char	pinssiblingCorner;
	unsigned char pinsiblingCorner2;

	int	 messageContextId;
	int thinkTraverseLevel;
	unsigned long clientPanelHandle;
};