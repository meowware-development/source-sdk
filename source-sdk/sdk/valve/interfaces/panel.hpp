#pragma once
#include "../datatypes/memutil.hpp"

struct SurfacePlat;

class Panel {
public:
	virtual ~Panel() = 0;

	virtual void Init(unsigned int vguiPanel, void* panel) = 0;

	virtual void SetPos(unsigned int vguiPanel, int x, int y) = 0;
	virtual void GetPos(unsigned int vguiPanel, int& x, int& y) = 0;
	virtual void SetSize(unsigned int vguiPanel, int wide, int tall) = 0;
	virtual void GetSize(unsigned int vguiPanel, int& wide, int& tall) = 0;
	virtual void SetMinimumSize(unsigned int vguiPanel, int wide, int tall) = 0;
	virtual void GetMinimumSize(unsigned int vguiPanel, int& wide, int& tall) = 0;
	virtual void SetZPos(unsigned int vguiPanel, int z) = 0;
	virtual int  GetZPos(unsigned int vguiPanel) = 0;

	virtual void GetAbsPos(unsigned int vguiPanel, int& x, int& y) = 0;
	virtual void GetClipRect(unsigned int vguiPanel, int& x0, int& y0, int& x1, int& y1) = 0;
	virtual void SetInset(unsigned int vguiPanel, int left, int top, int right, int bottom) = 0;
	virtual void GetInset(unsigned int vguiPanel, int& left, int& top, int& right, int& bottom) = 0;

	virtual void SetVisible(unsigned int vguiPanel, bool state) = 0;
	virtual bool IsVisible(unsigned int vguiPanel) = 0;
	virtual void SetParent(unsigned int vguiPanel, unsigned int newParent) = 0;
	virtual int GetChildCount(unsigned int vguiPanel) = 0;
	virtual unsigned int GetChild(unsigned int vguiPanel, int index) = 0;
	virtual CUtlVector< unsigned int >& GetChildren(unsigned int vguiPanel) = 0;
	virtual unsigned int GetParent(unsigned int vguiPanel) = 0;
	virtual void MoveToFront(unsigned int vguiPanel) = 0;
	virtual void MoveToBack(unsigned int vguiPanel) = 0;
	virtual bool HasParent(unsigned int vguiPanel, unsigned int potentialParent) = 0;
	virtual bool IsPopup(unsigned int vguiPanel) = 0;
	virtual void SetPopup(unsigned int vguiPanel, bool state) = 0;
	virtual bool IsFullyVisible(unsigned int vguiPanel) = 0;

	// gets the scheme this panel uses
	virtual unsigned long GetScheme(unsigned int vguiPanel) = 0;
	// gets whether or not this panel should scale with screen resolution
	virtual bool IsProportional(unsigned int vguiPanel) = 0;
	// returns true if auto-deletion flag is set
	virtual bool IsAutoDeleteSet(unsigned int vguiPanel) = 0;
	// deletes the Panel * associated with the unsigned int
	virtual void DeletePanel(unsigned int vguiPanel) = 0;

	// input interest
	virtual void SetKeyBoardInputEnabled(unsigned int vguiPanel, bool state) = 0;
	virtual void SetMouseInputEnabled(unsigned int vguiPanel, bool state) = 0;
	virtual bool IsKeyBoardInputEnabled(unsigned int vguiPanel) = 0;
	virtual bool IsMouseInputEnabled(unsigned int vguiPanel) = 0;

	// calculates the panels current position within the hierarchy
	virtual void Solve(unsigned int vguiPanel) = 0;

	// gets names of the object (for debugging purposes)
	virtual const char* GetName(unsigned int vguiPanel) = 0;
	virtual const char* GetClassName(unsigned int vguiPanel) = 0;

	// delivers a message to the panel
	virtual void SendMessage(unsigned int vguiPanel, void* params, unsigned int ifromPanel) = 0;

	// these pass through to the IClientPanel
	virtual void Think(unsigned int vguiPanel) = 0;
	virtual void PerformApplySchemeSettings(unsigned int vguiPanel) = 0;
	virtual void PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce = true) = 0; //51
	virtual void Repaint(unsigned int vguiPanel) = 0;
	virtual unsigned int IsWithinTraverse(unsigned int vguiPanel, int x, int y, bool traversePopups) = 0;
	virtual void OnChildAdded(unsigned int vguiPanel, unsigned int child) = 0;
	virtual void OnSizeChanged(unsigned int vguiPanel, int newWide, int newTall) = 0;

	virtual void InternalFocusChanged(unsigned int vguiPanel, bool lost) = 0;
	virtual bool RequestInfo(unsigned int vguiPanel, void* outputData) = 0;
	virtual void RequestFocus(unsigned int vguiPanel, int direction = 0) = 0;
	virtual bool RequestFocusPrev(unsigned int vguiPanel, unsigned int existingPanel) = 0;
	virtual bool RequestFocusNext(unsigned int vguiPanel, unsigned int existingPanel) = 0;
	virtual unsigned int GetCurrentKeyFocus(unsigned int vguiPanel) = 0;
	virtual int GetTabPosition(unsigned int vguiPanel) = 0;

	// used by ISurface to store platform-specific data
	virtual SurfacePlat* Plat(unsigned int vguiPanel) = 0;
	virtual void SetPlat(unsigned int vguiPanel, SurfacePlat* Plat) = 0;

	// returns a pointer to the vgui controls baseclass Panel *
	// destinationModule needs to be passed in to verify that the returned Panel * is from the same module
	// it must be from the same module since Panel * vtbl may be different in each module
	virtual void* GetPanel(unsigned int vguiPanel, const char* destinationModule) = 0;

	virtual bool IsEnabled(unsigned int vguiPanel) = 0;
	virtual void SetEnabled(unsigned int vguiPanel, bool state) = 0;

	// Used by the drag/drop manager to always draw on top
	virtual bool IsTopmostPopup(unsigned int vguiPanel) = 0;
	virtual void SetTopmostPopup(unsigned int vguiPanel, bool state) = 0;

	// sibling pins
	virtual void SetSiblingPin(unsigned int vguiPanel, unsigned int newSibling, unsigned char iMyCornerToPin = 0, unsigned char iSiblingCornerToPinTo = 0) = 0;
};