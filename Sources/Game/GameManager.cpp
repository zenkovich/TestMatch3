#include "o2/stdafx.h"
#include "GameManager.h"

void GameManager::OnStart()
{
	mMenu->SetGameManager(this);
	mMenu->Hide();
}

void GameManager::RestartGame()
{

}
// --- META ---

DECLARE_CLASS(GameManager);
// --- END META ---
