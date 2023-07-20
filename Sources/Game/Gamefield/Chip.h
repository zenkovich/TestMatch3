#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "ChipBehaviour.h"

using namespace o2;

class Cell;

class Chip: public Component
{
public:
	enum class State { Standing, Falling, Swapping, Destroying };
	enum class Color { Red, Green, Blue, Yellow, Violet };

public:
	void OnStart();

	void Process(float dt);

	void SetFallSpeed(float maxSpeed, float acceleration);

	Color GetColor() const;

	void SetState(State state);
	State GetState() const;

	void SetCell(Cell*);
	Cell* GetCell();

	SERIALIZABLE(Chip);

private:
	Color mColor; // @SERIALIZABLE @EDITOR_PROPERTY

	State mState = State::Standing; // @EDITOR_PROPERTY

	Vector<Ref<ChipBehaviour>> mBehaviours; // @EDITOR_PROPERTY

	Cell* mCell = nullptr;
	float mFallSpeedMax = 0.0f;
	float mFallAcceleration = 0.0f;
	float mFallSpeed = 0.0f;

private:
	void UpdateFalling(float dt);

	void CheckFallDown();

	void UpdateStanding(float dt);
};
// --- META ---

PRE_ENUM_META(Chip::State);

PRE_ENUM_META(Chip::Color);

CLASS_BASES_META(Chip)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(Chip)
{
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mColor);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(State::Standing).NAME(mState);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mBehaviours);
	FIELD().PRIVATE().DEFAULT_VALUE(nullptr).NAME(mCell);
	FIELD().PRIVATE().DEFAULT_VALUE(0.0f).NAME(mFallSpeedMax);
	FIELD().PRIVATE().DEFAULT_VALUE(0.0f).NAME(mFallAcceleration);
	FIELD().PRIVATE().DEFAULT_VALUE(0.0f).NAME(mFallSpeed);
}
END_META;
CLASS_METHODS_META(Chip)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
	FUNCTION().PUBLIC().SIGNATURE(void, SetFallSpeed, float, float);
	FUNCTION().PUBLIC().SIGNATURE(Color, GetColor);
	FUNCTION().PUBLIC().SIGNATURE(void, SetState, State);
	FUNCTION().PUBLIC().SIGNATURE(State, GetState);
	FUNCTION().PUBLIC().SIGNATURE(void, SetCell, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(Cell*, GetCell);
	FUNCTION().PRIVATE().SIGNATURE(void, UpdateFalling, float);
	FUNCTION().PRIVATE().SIGNATURE(void, CheckFallDown);
	FUNCTION().PRIVATE().SIGNATURE(void, UpdateStanding, float);
}
END_META;
// --- END META ---
