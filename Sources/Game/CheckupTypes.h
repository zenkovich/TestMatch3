#pragma once
#include "GameManager.h"
#include "GameMenu.h"
#include "Gamefield/Cell.h"
#include "Gamefield/Gamefield.h"

void CheckupTypes()
{
	CHECKUP_TYPE(Cell);
	CHECKUP_TYPE(GameMenu);
	CHECKUP_TYPE(GameManager);
	CHECKUP_TYPE(Gamefield);
	CHECKUP_TYPE(Chip);
}
