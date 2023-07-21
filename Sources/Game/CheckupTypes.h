#pragma once
#include "GameManager.h"
#include "GameMenu.h"
#include "Gamefield/Behaviours/CheckMatchesGamefieldBehaviour.h"
#include "Gamefield/Behaviours/ChipsFallGamefieldBehaviour.h"
#include "Gamefield/Cell/Cell.h"
#include "Gamefield/Gamefield.h"

void CheckupTypes()
{
	CHECKUP_TYPE(Cell);
	CHECKUP_TYPE(GameMenu);
	CHECKUP_TYPE(GameManager);
	CHECKUP_TYPE(Gamefield);
	CHECKUP_TYPE(Chip);
	CHECKUP_TYPE(ChipsFallGamefieldBehaviour);
	CHECKUP_TYPE(CheckMatchesGamefieldBehaviour);
}
