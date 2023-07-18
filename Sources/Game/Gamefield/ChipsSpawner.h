#pragma once
#include "CellBehaviour.h"

using namespace o2;

class ChipSpawner : public CellBehaviour
{
public:
	void Process(float dt) override;

	SERIALIZABLE(ChipSpawner);

private:
	ActorAssetRef mSpawningChip; // @SERIALIZABLE @EDITOR_PROPERTY
};
// --- META ---

CLASS_BASES_META(ChipSpawner)
{
	BASE_CLASS(CellBehaviour);
}
END_META;
CLASS_FIELDS_META(ChipSpawner)
{
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mSpawningChip);
}
END_META;
CLASS_METHODS_META(ChipSpawner)
{

	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
}
END_META;
// --- END META ---
