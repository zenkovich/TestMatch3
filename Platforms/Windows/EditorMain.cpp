#include "o2/stdafx.h"
#include "o2/O2.h"
#include "o2Editor/Core/EditorApplication.h"
#include "o2Editor/Core/EditorConfig.h"
#include "o2Editor/Core/ToolsPanel.h"
#include "o2Editor/Core/WindowsSystem/WindowsManager.h"

using namespace o2;

DECLARE_SINGLETON(Editor::WindowsManager);
DECLARE_SINGLETON(Editor::EditorConfig);
DECLARE_SINGLETON(Editor::ToolsPanel);

extern void InitializeTypeso2Editor();
extern void InitializeTypesGameLib();

int main()
{
    InitializeTypeso2Editor();
    InitializeTypesGameLib();
	INITIALIZE_O2;

	Editor::EditorApplication* app = mnew Editor::EditorApplication();
	app->Initialize();
	app->Launch();
	delete app;

	return 0;
}
