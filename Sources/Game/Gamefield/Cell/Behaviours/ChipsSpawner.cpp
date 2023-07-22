#include "o2/stdafx.h"
#include "ChipsSpawner.h"

#include "Gamefield/Cell/Cell.h"

bool ChipSpawner::CanSpawn() const
{
	return !mCell->GetChip();
}

void ChipSpawner::SpawnChip(Chip* chip)
{
	mCell->SetChip(chip);

	chip->SetState(Chip::State::Falling);
	chip->GetOwnerActor()->transform->position = Vec2F(0, 100.0f);
}

DECLARE_TEMPLATE_CLASS(Ref<ChipSpawner>);
// --- META ---

DECLARE_CLASS(ChipSpawner);
// --- END META ---
