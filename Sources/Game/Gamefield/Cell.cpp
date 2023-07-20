#include "o2/stdafx.h"
#include "Cell.h"

#include "Gamefield.h"

void Cell::OnStart()
{
	mBehaviours = mOwner->GetComponents<CellBehaviour>().Cast<Ref<CellBehaviour>>();
	for (auto& beh : mBehaviours)
		beh->SetCell(this);
}

void Cell::Draw()
{
	DrawableComponent::Draw();
	CursorAreaEventsListener::OnDrawn();
}

void Cell::Process(float dt)
{
	for (auto& behaviour : mBehaviours)
		behaviour->Process(dt);
}

void Cell::SetGamefield(Gamefield* gamefield)
{
	mGamefield = gamefield;
}

void Cell::SetChip(const Ref<Chip>& chip, bool resetPosition /*= true*/)
{
	mChip = chip;

	if (mChip)
	{
		mChip->SetCell(this);
		mChip->GetOwnerActor()->SetParent(GetOwnerActor(), !resetPosition);
	}
}

const Ref<Chip>& Cell::GetChip() const
{
	return mChip;
}

void Cell::AddBehaviour(Ref<CellBehaviour>& behaviour)
{
	mBehaviours.Add(behaviour);
	behaviour->SetCell(this);
}

void Cell::RemoveBehaviour(const Ref<CellBehaviour>& behaviour)
{
	mBehaviours.Remove(behaviour);
}

void Cell::SetNeighborLeft(Cell* neighbor)
{
	mNeighborLeft = neighbor;
}

void Cell::SetNeighborRight(Cell* neighbor)
{
	mNeighborRight = neighbor;
}

void Cell::SetNeighborTop(Cell* neighbor)
{
	mNeighborTop = neighbor;
}

void Cell::SetNeighborDown(Cell* neighbor)
{
	mNeighborDown = neighbor;
}

Cell* Cell::GetNeighborLeft() const
{
	return mNeighborLeft;
}

Cell* Cell::GetNeighborRight() const
{
	return mNeighborRight;
}

Cell* Cell::GetNeighborTop() const
{
	return mNeighborTop;
}

Cell* Cell::GetNeighborDown() const
{
	return mNeighborDown;
}

Cell::FallAvoidDirection Cell::GetFallAvoidDirection() const
{
	return mAvoidDirection;
}

void Cell::SwapFallAvoidDirection()
{
	if (mAvoidDirection == FallAvoidDirection::Left)
		mAvoidDirection = FallAvoidDirection::Right;
	else
		mAvoidDirection = FallAvoidDirection::Left;
}

bool Cell::IsUnderPoint(const Vec2F& point)
{
	return GetOwnerActor()->transform->worldBasis.Get().IsPointInside(point);
}

void Cell::OnCursorRightMouseReleased(const Input::Cursor& cursor)
{
	if (mChip)
		mGamefield->DestroyChip(mChip);
}

DECLARE_TEMPLATE_CLASS(Ref<Cell>);
// --- META ---

ENUM_META(Cell::FallAvoidDirection)
{
	ENUM_ENTRY(Left);
	ENUM_ENTRY(Right);
}
END_ENUM_META;

DECLARE_CLASS(Cell);
// --- END META ---
