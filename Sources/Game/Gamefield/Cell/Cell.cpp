#include "o2/stdafx.h"
#include "Cell.h"

#include "Gamefield/Gamefield.h"

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

Ref<Chip>& Cell::GetChip()
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

bool Cell::IsUnderPoint(const Vec2F& point)
{
    return GetOwnerActor()->transform->worldBasis.Get().IsPointInside(point);
}

void Cell::OnCursorExit(const Input::Cursor& cursor)
{
    if (!mChip)
        return;

    if (mIsPressed)
    {
        Vec2F delta = cursor.position - GetOwnerActor()->transform->worldPosition;
        if (Math::Abs(delta.x) > Math::Abs(delta.y))
        {
            if (delta.x < 0)
            {
                if (mNeighborLeft && mNeighborLeft->GetChip())
                    mGamefield->TrySwapChips(this, mNeighborLeft);
            }
            else
            {
                if (mNeighborRight && mNeighborRight->GetChip())
                    mGamefield->TrySwapChips(this, mNeighborRight);
            }
        }
        else
        {
            if (delta.y < 0)
            {
                if (mNeighborDown && mNeighborDown->GetChip())
                    mGamefield->TrySwapChips(this, mNeighborDown);
            }
            else
            {
                if (mNeighborTop && mNeighborTop->GetChip())
                    mGamefield->TrySwapChips(this, mNeighborTop);
            }
        }
    }
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

DECLARE_CLASS(Cell, Cell);
// --- END META ---
