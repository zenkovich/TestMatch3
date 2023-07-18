#include "o2/stdafx.h"
#include "Cell.h"

void Cell::OnStart()
{
	mBehaviours = mOwner->GetComponents<CellBehaviour>().Cast<Ref<CellBehaviour>>();
}

void Cell::Process(float dt)
{
	for (auto& behaviour : mBehaviours)
		behaviour->Process(dt);
}

const Ref<Chip>& Cell::GetChip() const
{
	return mChip;
}

void Cell::AddBehaviour(const Ref<CellBehaviour>& behaviour)
{
	mBehaviours.Add(behaviour);
}

void Cell::RemoveBehaviour(const Ref<CellBehaviour>& behaviour)
{
	mBehaviours.Remove(behaviour);
}

DECLARE_TEMPLATE_CLASS(Ref<Cell>);
// --- META ---

DECLARE_CLASS(Cell);
// --- END META ---
