#pragma once
#include "Gamefield/Cell/CellBehaviour.h"

using namespace o2;

// ---------------------
// Spawns chip into cell
// ---------------------
class ChipSpawner : public CellBehaviour
{
public:
	// Returns true if can spawn chip, that means that cell is empty
	bool CanSpawn() const;

	// Spawns chip into cell
	void SpawnChip(Chip* chip);

	// Returns category of component
	static String GetCategory() { return "Gamefield"; }

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
	FUNCTION().PUBLIC().SIGNATURE(void, SpawnChip, Chip*);
	FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
}
END_META;
// --- END META ---
