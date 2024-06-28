#include "esp.hpp"

#include "../../globals.hpp"

struct Box {
	float x, y, width, height;
};

static bool GetBoundings(BaseEntity* entity, Box* box)
{
	Matrix3x4 boneMatrix[MAXSTUDIOBONES];

	if (!entity->SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f))
		return false;

	const Model* model = entity->GetModel();

	if (!model)
		return false;

	StudioHDR* pStudioHdr = sdk::interfaces::modelInfo->GetStudiomodel(model);
	if (!pStudioHdr)
		return false;

	StudioHitboxSet* set = pStudioHdr->HitboxSet(0);
	if (!set || !set->hitboxCount)
		return false;

	float left = FLT_MAX;
	float top = FLT_MIN;
	float right = FLT_MIN;
	float bottom = FLT_MAX;

	for (int i = 0; i < set->hitboxCount; ++i) {
		StudioBox* pbox = set->Hitbox(i);

		if (!pbox)
			continue;

		Vector3 min = pbox->mins;
		Vector3 max = pbox->maxs;

		std::array<Vector3, 8> points = {
			Vector3(min.x, min.y, min.z),
			Vector3(min.x, max.y, min.z),
			Vector3(max.x, max.y, min.z),
			Vector3(max.x, min.y, min.z),
			Vector3(max.x, max.y, max.z),
			Vector3(min.x, max.y, max.z),
			Vector3(min.x, min.y, max.z),
			Vector3(max.x, min.y, max.z)
		};

		for (int j = 0; j < 8; j++) {
			Vector2 screen;
			Vector3 transformed;
			sdk::math::TransformVector(points[j], boneMatrix[pbox->bone], transformed);

			if (!sdk::math::WorldToScreen(transformed, screen))
				return false;

			left = std::min<float>(left, screen.x);
			top = std::max<float>(top, screen.y);
			right = std::max<float>(right, screen.x);
			bottom = std::min<float>(bottom, screen.y);
		}
	}

	box->x = left - 4.f;
	box->y = bottom - 8.f;
	box->width = right - left + 8.f;
	box->height = top - bottom + 16.f;

	if (box->x + box->width < 25.f || box->y + box->height < 25.f)
		return false;

	return true;
}

void src::features::esp::Draw2DBoundingBox(Box* box)
{
	utils::renderer::Rectangle(box->x - 1, box->y - 1, box->width + 2, box->height + 2, Color(0, 0, 0, 150));
	utils::renderer::Rectangle(box->x, box->y, box->width, box->height, Color(255, 255, 255));
	utils::renderer::Rectangle(box->x + 1, box->y + 1, box->width - 2, box->height - 2, Color(0, 0, 0, 150));
}

void src::features::esp::DrawName(BaseEntity* entity, Box* box)
{
	PlayerInfo info = PlayerInfo::Get(entity->EntityIndex());
	auto nameSize = utils::renderer::GetTextSize(utils::renderer::fonts::tahoma13, info.name);
	utils::renderer::Text(box->x + box->width / 2 - nameSize.x / 2, box->y - (nameSize.y + 2.f), utils::renderer::fonts::tahoma13, Color(255, 255, 255), info.name);
}

void src::features::esp::Run()
{
	if (!globals::localPlayer)
		return;

	size_t highestEntIndex = sdk::interfaces::entityList->GetHighestEntityIndex();

	// Entity 0 is DT_World, so we skip that.
	// After that, the 1->64 indexes are reserved for players.
	// This loops over the WHOLE entity list, including the grenades thrown, or whatever is left on the ground
	// If you want to just loop the player list, loop from 1 to 64 inclusive
	for (size_t i = 1; i < highestEntIndex; i++)
	{
		BaseEntity* entity = sdk::interfaces::entityList->GetClientEntity(i)->As<BaseEntity>();

		// You can do alive check, teammate check, whatever here
		if (!entity || entity->IsDormant() || entity == globals::localPlayer)
			continue;

		ClientClass* clientClass = entity->GetClientClass();

		switch (clientClass->classId) {
		case ClassIDS::CCSPlayer: {
			BasePlayer* player = entity->As<BasePlayer>();

			if (!player->IsAlive())
				break;

			Box box{};

			if (!GetBoundings(entity, &box))
				continue;

			Draw2DBoundingBox(&box);
			DrawName(entity, &box);
			break;
		}
		}
	}
}
