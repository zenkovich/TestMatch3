#include "o2/stdafx.h"
#include "Chip.h"

#include "o2/Scene/Scene.h"
#include "o2/Render/Render.h"
#include "Cell.h"

#undef DrawText

void Chip::OnStart()
{
	mBehaviours = mOwner->GetComponents<ChipBehaviour>().Cast<Ref<ChipBehaviour>>();
}

void Chip::Process(float dt)
{
	for (auto& behaviour : mBehaviours)
		behaviour->Process(dt);

	if (mState == State::Swapping)
		UpdateSwapping(dt);

	o2Debug.DrawText(GetOwnerActor()->transform->worldPosition, o2Reflection.GetEnumName(mState));
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

bool Chip::IsFalling() const
{
	return mState == State::Falling || mState == State::CheckFallingNext;
}

void Chip::CheckFallingDown()
{
	auto downCell = mCell->GetNeighborDown();
	if (!downCell)
		StopFalling();
	else
	{
		if (!downCell->GetChip())
		{
			mCell->SetChip(nullptr);
			downCell->SetChip(this, false);

			ContinueFalling();
		}
	}
}

void Chip::CheckFallingSide()
{
	auto downCell = mCell->GetNeighborDown();
	if (!downCell)
		StopFalling();
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
			ContinueFalling();
		}
		else
		{
			StopFalling();
		}
	}
}

void Chip::UpdateFallingStep1(float dt)
{
	float targetDistance = GetOwnerActor()->transform->GetPosition().Length();

	mFallSpeed = Math::Min(mFallSpeedMax, mFallSpeed + mFallAcceleration*dt);
	float moveDistance = mFallSpeed * dt;

	if (moveDistance > targetDistance)
	{
		mState = State::CheckFallingNext;

		mAccumulatedFallDistance = moveDistance - targetDistance;
		moveDistance = targetDistance;
	}

	UpdateFalling(moveDistance);

	o2Debug.DrawLine(GetOwnerActor()->transform->worldPosition, mCell->GetOwnerActor()->transform->worldPosition);
}

void Chip::UpdateFalling(float distance)
{
	GetOwnerActor()->transform->position += GetOwnerActor()->transform->position.Get().Normalized()*(-distance);
}

void Chip::UpdateFallingStep2(float dt)
{
	UpdateFalling(mAccumulatedFallDistance);
	mAccumulatedFallDistance = 0.0f;

	if (mState == State::CheckFallingNext)
		StopFalling();
}

void Chip::ContinueFalling()
{
	mState = State::Falling;
}

void Chip::StopFalling()
{
	mState = State::Standing;
	mFallSpeed = 0.0f;
	mAccumulatedFallDistance = 0.0f;

	GetOwnerActor()->transform->position = Vec2F();
}

void Chip::UpdateSwapping(float dt)
{
	GetOwnerActor()->transform->position = Math::Lerp(GetOwnerActor()->transform->position.Get(), Vec2F(), 20.0f*dt);

	if (GetOwnerActor()->transform->position.Get().Length() < 1.0f)
	{
		mState = State::Standing;
		GetOwnerActor()->transform->position = Vec2F();
	}
}

DECLARE_TEMPLATE_CLASS(Ref<Chip>);
// --- META ---

ENUM_META(Chip::State)
{
	ENUM_ENTRY(CheckFallingNext);
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
