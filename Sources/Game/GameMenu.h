#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class GameMenu: public Component
{
public:
	void OnStart() override;

	SERIALIZABLE(GameMenu);

private:
};
// --- META ---

CLASS_BASES_META(GameMenu)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(GameMenu)
{
}
END_META;
CLASS_METHODS_META(GameMenu)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
}
END_META;
// --- END META ---
