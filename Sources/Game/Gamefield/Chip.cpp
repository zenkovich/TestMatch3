#include "o2/stdafx.h"
#include "Chip.h"

#include "o2/Scene/Scene.h"
#include "o2/Render/Render.h"
#include "Cell.h"


void Chip::OnStart()
{
	mBehaviours = mOwner->GetComponents<ChipBehaviour>().Cast<Ref<ChipBehaviour>>();
}

void Chip::Process(float dt)
{
	for (auto& behaviour : mBehaviours)
		behaviour->Process(dt);

	if (mState == State::Falling)
		UpdateFalling(dt);
	else if (mState == State::Standing)
		UpdateStanding(dt);
}

void Chip::SetFallSpeed(float maxSpeed, float acceleration)
{
	mFallSpeedMax = maxSpeed;
	mFallAcceleration = acceleration;
}

Chip::Color Chip::GetColor() const
{
	return mColor;
}

void Chip::SetState(State state)
{
	mState = state;
}

Chip::State Chip::GetState() const
{
	return mState;
}

void Chip::SetCell(Cell* cell)
{
	mCell = cell;
}

Cell* Chip::GetCell()
{
	return mCell;
}

void Chip::UpdateFalling(float dt)
{
	float targetDistance = GetOwnerActor()->transform->GetPosition().Length();

	mFallSpeed = Math::Min(mFallSpeedMax, mFallSpeed + mFallAcceleration*dt);
	float moveDistance = mFallSpeed * dt;

	bool finishedFalling = false;

	if (moveDistance > targetDistance)
	{
		finishedFalling = true;
		moveDistance = targetDistance;
	}

	GetOwnerActor()->transform->position += GetOwnerActor()->transform->position.Get().Normalized()*(-moveDistance);

	if (finishedFalling)
		CheckFallDown();
}

void Chip::CheckFallDown()
{
	auto downCell = mCell->GetNeighborDown();
	if (!downCell)
		mState = State::Standing;
	else
	{
		if (!downCell->GetChip())
		{
			mCell->SetChip(nullptr);
			downCell->SetChip(this, false);
			mCell = downCell;
			mState = State::Falling;
		}
		else
		{
			Ref<Cell> fallCell;
			if (downCell->GetFallAvoidDirection() == Cell::FallAvoidDirection::Left)
				fallCell = downCell->GetNeighborLeft();
			else
				fallCell = downCell->GetNeighborRight();

			downCell->SwapFallAvoidDirection();

			if (fallCell && !fallCell->GetChip())
			{
				mCell->SetChip(nullptr);
				fallCell->SetChip(this, false);
				mCell = fallCell.Get();
				mState = State::Falling;
			}
			else
			{
				mState = State::Standing;
			}
		}
	}
}

void Chip::UpdateStanding(float dt)
{
	CheckFallDown();
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

ENUM_META(Chip::Color)
{
	ENUM_ENTRY(Blue);
	ENUM_ENTRY(Green);
	ENUM_ENTRY(Red);
	ENUM_ENTRY(Violet);
	ENUM_ENTRY(Yellow);
}
END_ENUM_META;

DECLARE_CLASS(Chip);
// --- END META ---
