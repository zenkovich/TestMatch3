#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class ChipBehaviour : public Component
{
public:
	virtual void Process(float dt) {}

	SERIALIZABLE(ChipBehaviour);

private:
};
// --- META ---

CLASS_BASES_META(ChipBehaviour)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(ChipBehaviour)
{
}
END_META;
CLASS_METHODS_META(ChipBehaviour)
{

	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
}
END_META;
// --- END META ---
