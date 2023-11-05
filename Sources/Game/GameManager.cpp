#include "o2/stdafx.h"
#include "GameManager.h"

void GameManager::OnStart()
{
    mMenu->SetGameManager(this);
    mMenu->Hide();

    mGamefield->Restart();
}

void GameManager::RestartGame()
{
    mGamefield->Restart();
}
// --- META ---

DECLARE_CLASS(GameManager);
// --- END META ---
