#pragma once
#include "../../math/vector.hpp"
#include "../datatypes/movedata.hpp"

struct UserCmd;

class PredictionBase
{
public:
	virtual			~PredictionBase(void) {};

	virtual void	Init(void) = 0;
	virtual void	Shutdown(void) = 0;

	// Run prediction
	virtual void	Update
	(
		int startframe,				// World update ( un-modded ) most recently received
		bool validframe,			// Is frame data valid
		int incoming_acknowledged,	// Last command acknowledged to have been run by server (un-modded)
		int outgoing_command		// Last command (most recent) sent to server (un-modded)
	) = 0;

	// We are about to get a network update from the server.  We know the update #, so we can pull any
	//  data purely predicted on the client side and transfer it to the new from data state.
	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void	PostEntityPacketReceived(void) = 0;
	virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;

	virtual void	OnReceivedUncompressedPacket(void) = 0;

	// The engine needs to be able to access a few predicted values
	virtual void	GetViewOrigin(Vector3& org) = 0;
	virtual void	SetViewOrigin(Vector3& org) = 0;
	virtual void	GetViewAngles(Vector3& ang) = 0;
	virtual void	SetViewAngles(Vector3& ang) = 0;
	virtual void	GetLocalViewAngles(Vector3& ang) = 0;
	virtual void	SetLocalViewAngles(Vector3& ang) = 0;
};

class Prediction : public PredictionBase {
	virtual			~Prediction(void);

	virtual void	Init(void);
	virtual void	Shutdown(void);

	// Implement IPrediction
public:

	virtual void	Update
	(
		int startframe,		// World update ( un-modded ) most recently received
		bool validframe,		// Is frame data valid
		int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command	// Last command (most recent) sent to server (un-modded)
	);

	virtual void	OnReceivedUncompressedPacket(void);

	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet);
	virtual void	PostEntityPacketReceived(void);
	virtual void	PostNetworkDataReceived(int commands_acknowledged);

	virtual bool	InPrediction(void) const;
	virtual bool	IsFirstTimePredicted(void) const;


	virtual int		GetIncomingPacketNumber(void) const;

	// The engine needs to be able to access a few predicted values
	virtual void	GetViewOrigin(Vector3& org);
	virtual void	SetViewOrigin(Vector3& org);
	virtual void	GetViewAngles(Vector3& ang);
	virtual void	SetViewAngles(Vector3& ang);

	virtual void	GetLocalViewAngles(Vector3& ang);
	virtual void	SetLocalViewAngles(Vector3& ang);

	virtual void	RunCommand(BasePlayer* player, UserCmd* ucmd, void* moveHelper);


	virtual void	SetupMove(BasePlayer* player, UserCmd* ucmd, void* pHelper, MoveData* move);
	virtual void	FinishMove(BasePlayer* player, UserCmd* ucmd, MoveData* move);
	virtual void	SetIdealPitch(BasePlayer* player, const Vector3& origin, const Vector3& angles, const Vector3& viewheight);

	virtual void	_Update
	(
		bool received_new_world_update,
		bool validframe,		// Is frame data valid
		int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command	// Last command (most recent) sent to server (un-modded)
	);


	// Last object the player was standing on
	uintptr_t m_hLastGround;
	bool			m_bInPrediction;
	bool			m_bFirstTimePredicted;
	bool			m_bOldCLPredictValue;
	bool			m_bEnginePaused;

	// Last network origin for local player
	int				m_nPreviousStartFrame;

	int				m_nCommandsPredicted;
	int				m_nServerCommandsAcknowledged;
	int				m_bPreviousAckHadErrors;
	int				m_nIncomingPacketNumber;

	float			m_flIdealPitch;
};
