#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "Gamefield/Gamefield.h"

using namespace o2;

class GameManager : public Component
{
public:
	void OnStart() override;

	SERIALIZABLE(GameManager);

private:
	Ref<Gamefield> mGamefield; // Gamefield reference @SERIALIZABLE
};
// --- META ---

CLASS_BASES_META(GameManager)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(GameManager)
{
	FIELD().PRIVATE().SERIALIZABLE_ATTRIBUTE().NAME(mGamefield);
}
END_META;
CLASS_METHODS_META(GameManager)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
}
END_META;
// --- END META ---
