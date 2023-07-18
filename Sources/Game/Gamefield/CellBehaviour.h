#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "Chip.h"

using namespace o2;

class CellBehaviour : public Component
{
public:
	virtual void Process(float dt) {}

	SERIALIZABLE(CellBehaviour);

private:
};
// --- META ---

CLASS_BASES_META(CellBehaviour)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(CellBehaviour)
{
}
END_META;
CLASS_METHODS_META(CellBehaviour)
{

	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
}
END_META;
// --- END META ---
