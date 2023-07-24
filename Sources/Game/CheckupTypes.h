#pragma once
#include "GameManager.h"
#include "GameMenu.h"
#include "Gamefield/Behaviours/CheckMatchesGamefieldBehaviour.h"
#include "Gamefield/Behaviours/ChipsFallGamefieldBehaviour.h"
#include "Gamefield/Cell/Cell.h"
#include "Gamefield/Gamefield.h"
#include "o2/Animation/Tracks/AnimationTrack.h"
#include "o2/Scene/Components/ImageComponent.h"

void CheckupTypes()
{
	CHECKUP_TYPE(Cell);
	CHECKUP_TYPE(GameMenu);
	CHECKUP_TYPE(GameManager);
	CHECKUP_TYPE(Gamefield);
	CHECKUP_TYPE(Chip);
	CHECKUP_TYPE(ChipsFallGamefieldBehaviour);
	CHECKUP_TYPE(CheckMatchesGamefieldBehaviour);
	CHECKUP_TYPE(ImageComponent);
	CHECKUP_TYPE(AnimationTrack<float>);
}
