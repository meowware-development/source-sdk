#pragma once

struct UserCmd;

namespace src::features {
	void BunnyHop(UserCmd* cmd);

	void EdgeJump(int oldFlags, UserCmd* cmd);
}