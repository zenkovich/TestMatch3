#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "Gamefield/Gamefield.h"
#include "GameMenu.h"

using namespace o2;

// -----------------
// Game main manager
// -----------------
class GameManager : public Component
{
public:
	// Called on starting, initializes game
	void OnStart() override;

	// Restarts game
	void RestartGame();

	SERIALIZABLE(GameManager);

private:
	Ref<Gamefield> mGamefield; // Gamefield reference @SERIALIZABLE @EDITOR_PROPERTY
	Ref<GameMenu>  mMenu;      // Game menu reference @SERIALIZABLE @EDITOR_PROPERTY
};
// --- META ---

CLASS_BASES_META(GameManager)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(GameManager)
{
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mGamefield);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mMenu);
}
END_META;
CLASS_METHODS_META(GameManager)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, RestartGame);
}
END_META;
// --- END META ---
