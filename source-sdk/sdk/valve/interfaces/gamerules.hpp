#pragma once
#include "../../math/vector.hpp"
#include "../../../utils/memory/memory.hpp"

struct ViewVectors {
	// Height above entity position where the viewer's eye is.
	Vector3 view;

	Vector3 hullMin;
	Vector3 hullMax;

	Vector3 duckHullMin;
	Vector3 duckHullMax;
	Vector3 duckView;

	Vector3 obsHullMin;
	Vector3 obsHullMax;

	Vector3 deadViewHeight;
};

// TODO: If you want to, implement the entire interface
class GameRules {
public:
	ViewVectors* GetViewVectors()
	{
		return utils::memory::CallVirtualFunction<ViewVectors*>(this, 31);
	}
};
