#include "prediction.hpp"
#include "../../sdk/sdk.hpp"
#include "../../globals.hpp"

void src::helpers::StartPrediction(UserCmd* cmd)
{
	// TODO: Get random seed here
	sdk::interfaces::movement->StartTrackPredictionErrors(globals::localPlayer);
}
