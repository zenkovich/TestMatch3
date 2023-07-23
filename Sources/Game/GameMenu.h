#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class GameManager;

// ---------------
// Game menu logic
// ---------------
class GameMenu: public Component
{
public:
	// Initializes game manager
	void SetGameManager(GameManager* gameManager);

	// Shows menu
	void Show();

	// Hides menu
	void Hide();

	// Called when restart button is pressed
	void OnRestartPressed();

	// Called when exit button is pressed
	void OnExitPressed();

	SERIALIZABLE(GameMenu);

private:
	GameManager* mGameManager = nullptr; // Game manager
};
// --- META ---

CLASS_BASES_META(GameMenu)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(GameMenu)
{
	FIELD().PRIVATE().DEFAULT_VALUE(nullptr).NAME(mGameManager);
}
END_META;
CLASS_METHODS_META(GameMenu)
{

	FUNCTION().PUBLIC().SIGNATURE(void, SetGameManager, GameManager*);
	FUNCTION().PUBLIC().SIGNATURE(void, Show);
	FUNCTION().PUBLIC().SIGNATURE(void, Hide);
	FUNCTION().PUBLIC().SIGNATURE(void, OnRestartPressed);
	FUNCTION().PUBLIC().SIGNATURE(void, OnExitPressed);
}
END_META;
// --- END META ---
