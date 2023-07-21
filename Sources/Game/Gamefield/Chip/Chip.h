#pragma once
#include "Gamefield/Chip/ChipBehaviour.h"
#include "Gamefield/Chip/ChipColor.h"
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class Cell;

// ---------------------------------------------------------
// Game field chip. Has state, has behaviours, can fall down
// ---------------------------------------------------------
class Chip: public Component
{
public:
	enum class State { Standing, Falling, CheckFallingNext, Swapping, Destroying };

public:
	// Called when component is created, collects behaviours
	void OnStart();

	// Processes chip logic
	void Process(float dt);

	// Initializes fall speed parameters
	void SetFallSpeed(float maxSpeed, float acceleration);

	// Returns chip color
	ChipColor GetColor() const;

	// Sets chip state
	void SetState(State state);

	// Returns chip state
	State GetState() const;

	// Sets cell
	void SetCell(Cell*);

	// Returns cell
	Cell* GetCell();

	// Returns true if chip is falling
	bool IsFalling() const;

	// Checks if chip can fall down
	void CheckFallingDown();

	// Checks if chip can fall size
	void CheckFallingSide();

	// First step of falling, updates speed and current position. Stops at target cells and gets ready for second step
	void UpdateFallingStep1(float dt);

	// Second step of falling, continues falling thru target cells
	void UpdateFallingStep2(float dt);

	// Returns category of component
	static String GetCategory() { return "Gamefield"; }

	SERIALIZABLE(Chip);

private:
	ChipColor mColor; // Chip color @SERIALIZABLE @EDITOR_PROPERTY

	State mState = State::Standing; // Current state @EDITOR_PROPERTY

	Vector<Ref<ChipBehaviour>> mBehaviours; // List of behaviour @EDITOR_PROPERTY

	Cell* mCell = nullptr; // Owner cell

	float mFallSpeedMax = 0.0f;     // Max falling speed
	float mFallAcceleration = 0.0f; // Falling acceleration
	float mFallSpeed = 0.0f;        // Current falling speed

	float mAccumulatedFallDistance = 0.0f; // Accumulated fall distance, used to continue falling after stopping at target cell

private:
	// Moves position down by distance
	void UpdateFalling(float distance);

	// Continues falling
	void ContinueFalling();

	// Stops falling
	void StopFalling();

	// Updates swapping
	void UpdateSwapping(float dt);
};
// --- META ---

PRE_ENUM_META(Chip::State);

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
	FIELD().PRIVATE().DEFAULT_VALUE(0.0f).NAME(mAccumulatedFallDistance);
}
END_META;
CLASS_METHODS_META(Chip)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
	FUNCTION().PUBLIC().SIGNATURE(void, SetFallSpeed, float, float);
	FUNCTION().PUBLIC().SIGNATURE(ChipColor, GetColor);
	FUNCTION().PUBLIC().SIGNATURE(void, SetState, State);
	FUNCTION().PUBLIC().SIGNATURE(State, GetState);
	FUNCTION().PUBLIC().SIGNATURE(void, SetCell, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(Cell*, GetCell);
	FUNCTION().PUBLIC().SIGNATURE(bool, IsFalling);
	FUNCTION().PUBLIC().SIGNATURE(void, CheckFallingDown);
	FUNCTION().PUBLIC().SIGNATURE(void, CheckFallingSide);
	FUNCTION().PUBLIC().SIGNATURE(void, UpdateFallingStep1, float);
	FUNCTION().PUBLIC().SIGNATURE(void, UpdateFallingStep2, float);
	FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
	FUNCTION().PRIVATE().SIGNATURE(void, UpdateFalling, float);
	FUNCTION().PRIVATE().SIGNATURE(void, ContinueFalling);
	FUNCTION().PRIVATE().SIGNATURE(void, StopFalling);
	FUNCTION().PRIVATE().SIGNATURE(void, UpdateSwapping, float);
}
END_META;
// --- END META ---
