/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSSetting.h"
#include "GSPickMove.h"
#include "GSEndGame.h"
#include "GSPauseGame.h"
#include "GSRecord.h"
#include "GameStatebase.h"
#include "GSRecord.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		break;
	case StateType::STATE_SETTING:
		gs = std::make_shared<GSSetting>();
		break;
	case StateType::STATE_PICKMOVE:
		gs = std::make_shared<GSPickMove>();
		break;
<<<<<<< HEAD
=======
	case StateType::STATE_ENDGAME:
		gs = std::make_shared<GSEndGame>();
		break;
	case StateType::STATE_PAUSEGAME:
		gs = std::make_shared<GSPauseGame>();
		break;
>>>>>>> af27a35425e16caf1724adfb4a6f212fb07a45e2
	case StateType::STATE_RECORD:
		gs = std::make_shared<GSRecord>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}