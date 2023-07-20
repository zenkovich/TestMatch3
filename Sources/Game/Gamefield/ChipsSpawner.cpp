#include "o2/stdafx.h"
#include "ChipsSpawner.h"
#include "CellBehaviour.h"
#include "Cell.h"

bool ChipSpawner::CanSpawn() const
{
	return !mCell->GetChip();
}

Ref<Chip> ChipSpawner::SpawnChip(const ActorAssetRef& proto)
{
	auto chipActor = proto->Instantiate();
	auto chip = chipActor->GetComponent<Chip>();
	mCell->SetChip(chip);

	chip->SetState(Chip::State::Falling);
	chip->GetOwnerActor()->transform->position = Vec2F(0, 100.0f);

	return chip;
}

DECLARE_TEMPLATE_CLASS(Ref<ChipSpawner>);
// --- META ---

DECLARE_CLASS(ChipSpawner);
// --- END META ---
