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

	SERIALIZABLE(CellBehaviour);

protected:
	Cell* mCell = nullptr; // @EDITOR_PROPERTY
};
// --- META ---

CLASS_BASES_META(CellBehaviour)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(CellBehaviour)
{
	FIELD().PROTECTED().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(nullptr).NAME(mCell);
}
END_META;
CLASS_METHODS_META(CellBehaviour)
{

	FUNCTION().PUBLIC().SIGNATURE(void, SetCell, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
}
END_META;
// --- END META ---
