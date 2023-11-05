#include "o2/stdafx.h"
#include "GamefieldBehaviour.h"

#include "Gamefield/Gamefield.h"

void GamefieldBehaviour::SetGamefield(Gamefield* gamefield)
{
    mGamefield = gamefield;
}

DECLARE_TEMPLATE_CLASS(Ref<GamefieldBehaviour>);
// --- META ---

DECLARE_CLASS(GamefieldBehaviour);
// --- END META ---
