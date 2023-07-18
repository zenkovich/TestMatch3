#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class GamefieldBehaviour : public Component
{
public:
	virtual void Process(float dt) {}

	SERIALIZABLE(GamefieldBehaviour);

private:
};
// --- META ---

CLASS_BASES_META(GamefieldBehaviour)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(GamefieldBehaviour)
{
}
END_META;
CLASS_METHODS_META(GamefieldBehaviour)
{

	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
}
END_META;
// --- END META ---
