#include "o2/stdafx.h"
#include "GameMenu.h"

#include "GameManager.h"

void GameMenu::SetGameManager(GameManager* gameManager)
{
    mGameManager = gameManager;
}

void GameMenu::Show()
{
    if (auto widget = dynamic_cast<Widget*>(GetOwnerActor()))
        widget->SetEnabled(true);
}

void GameMenu::Hide()
{
    if (auto widget = dynamic_cast<Widget*>(GetOwnerActor()))
        widget->SetEnabled(false);
}

void GameMenu::OnRestartPressed()
{
    mGameManager->RestartGame();
    Hide();
}

void GameMenu::OnExitPressed()
{
    Hide();
}

DECLARE_TEMPLATE_CLASS(Ref<GameMenu>);
// --- META ---

DECLARE_CLASS(GameMenu);
// --- END META ---
