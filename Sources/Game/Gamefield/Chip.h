#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "ChipBehaviour.h"

using namespace o2;

class Chip: public Component
{
public:
	enum class State { Standing, Falling, Swapping, Destroying };

public:
	void OnStart();

	void Process(float dt);

	SERIALIZABLE(Chip);

private:
	String mType; // @SERIALIZABLE @EDITOR_PROPERTY

	State mState = State::Standing; // @EDITOR_PROPERTY

	Vector<Ref<ChipBehaviour>> mBehaviours; // @EDITOR_PROPERTY
};
// --- META ---

PRE_ENUM_META(Chip::State);

CLASS_BASES_META(Chip)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(Chip)
{
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mType);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(State::Standing).NAME(mState);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mBehaviours);
}
END_META;
CLASS_METHODS_META(Chip)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
}
END_META;
// --- END META ---
