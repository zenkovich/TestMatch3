#include "o2/stdafx.h"
#include "Chip.h"

#include "o2/Scene/Scene.h"
#include "o2/Render/Render.h"


void Chip::OnStart()
{
	mBehaviours = mOwner->GetComponents<ChipBehaviour>().Cast<Ref<ChipBehaviour>>();
}

void Chip::Process(float dt)
{
	for (auto& behaviour : mBehaviours)
		behaviour->Process(dt);
}

DECLARE_TEMPLATE_CLASS(Ref<Chip>);
// --- META ---

ENUM_META(Chip::State)
{
	ENUM_ENTRY(Destroying);
	ENUM_ENTRY(Falling);
	ENUM_ENTRY(Standing);
	ENUM_ENTRY(Swapping);
}
END_ENUM_META;

DECLARE_CLASS(Chip);
// --- END META ---
