#pragma once
#include "Gamefield/Chip/Chip.h"
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class Cell;

class CellBehaviour : public Component
{
public:
	void SetCell(Cell* cell);
	virtual void Process(float dt) {}

	// Returns category of component
	static String GetCategory() { return "Gamefield"; }

	SERIALIZABLE(CellBehaviour);

protected:
	Cell* mCell = nullptr;
};
// --- META ---

CLASS_BASES_META(CellBehaviour)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(CellBehaviour)
{
	FIELD().PROTECTED().DEFAULT_VALUE(nullptr).NAME(mCell);
}
END_META;
CLASS_METHODS_META(CellBehaviour)
{

	FUNCTION().PUBLIC().SIGNATURE(void, SetCell, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
	FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
}
END_META;
// --- END META ---
