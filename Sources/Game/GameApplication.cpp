#include "o2/stdafx.h"
#include "GameApplication.h"

#include "o2/Render/Render.h"
#include "o2/Scene/Scene.h"
#include "o2/Application/Input.h"
#include "o2/Utils/Debug/Debug.h"
#include "o2/Scripts/ScriptEngine.h"
#include "o2/Utils/FileSystem/FileSystem.h"
#include "o2/Assets/Types/SceneAsset.h"

void GameApplication::OnStarted()
{
    SceneAssetRef scene("Gamefield.scn");
    scene->Load();
    o2Application.SetWindowSize(Vec2I(750, 1334));
}

void GameApplication::OnUpdate(float dt)
{
    o2Application.windowCaption = String("Pet story") +
        "; FPS: " + (String)((int)o2Time.GetFPS()) +
        " Cursor: " + (String)o2Input.GetCursorPos() +
        " JS: " + (String)(o2Scripts.GetUsedMemory() / 1024) + "kb";
}

void GameApplication::OnDraw()
{
}

void GameApplication::DrawScene()
{
    Application::DrawScene();
}

