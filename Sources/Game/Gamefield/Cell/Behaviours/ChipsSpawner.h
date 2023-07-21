#pragma once
#include "Gamefield/Cell/CellBehaviour.h"

using namespace o2;

class ChipSpawner : public CellBehaviour
{
public:
	bool CanSpawn() const;
	Ref<Chip> SpawnChip(const ActorAssetRef& proto);

	SERIALIZABLE(ChipSpawner);
};
// --- META ---

CLASS_BASES_META(ChipSpawner)
{
	BASE_CLASS(CellBehaviour);
}
END_META;
CLASS_FIELDS_META(ChipSpawner)
{
}
END_META;
CLASS_METHODS_META(ChipSpawner)
{

	FUNCTION().PUBLIC().SIGNATURE(bool, CanSpawn);
	FUNCTION().PUBLIC().SIGNATURE(Ref<Chip>, SpawnChip, const ActorAssetRef&);
}
END_META;
// --- END META ---
