#include "GameApplication.h"
#include "o2/O2.h"

#include "CheckupTypes.h"

extern void InitializeTypesGameLib();

int main()
{
	INITIALIZE_O2;
	InitializeTypesGameLib();

	CheckupTypes();

	GameApplication* app = mnew GameApplication();
	app->Initialize();
	app->Launch();
	delete app;

	return 0;
}
