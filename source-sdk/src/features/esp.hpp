#pragma once

class BaseEntity;
struct Box;

namespace src::features::esp {
	void Draw2DBoundingBox(Box* box);
	void DrawName(BaseEntity* entity, Box* box);

	void Run();
}