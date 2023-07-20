#pragma once
#include "CellBehaviour.h"
#include "Chip.h"
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "o2/Scene/DrawableComponent.h"
#include "o2/Events/CursorAreaEventsListener.h"

using namespace o2;

class Gamefield;

class Cell : public DrawableComponent, public CursorAreaEventsListener
{
public:
	enum class FallAvoidDirection { Left, Right };

public:
	void OnStart();

	void Draw() override;

	void Process(float dt);

	void SetGamefield(Gamefield* gamefield);

	void SetChip(const Ref<Chip>& chip, bool resetPosition = true);
	const Ref<Chip>& GetChip() const;

	void AddBehaviour(Ref<CellBehaviour>& behaviour);
	void RemoveBehaviour(const Ref<CellBehaviour>& behaviour);

	void SetNeighborLeft(Cell* neighbor);
	void SetNeighborRight(Cell* neighbor);
	void SetNeighborTop(Cell* neighbor);
	void SetNeighborDown(Cell* neighbor);

	Cell* GetNeighborLeft() const;
	Cell* GetNeighborRight() const;
	Cell* GetNeighborTop() const;
	Cell* GetNeighborDown() const;

	FallAvoidDirection GetFallAvoidDirection() const;
	void SwapFallAvoidDirection();

	bool IsUnderPoint(const Vec2F& point) override;

	SERIALIZABLE(Cell);

private:
	Gamefield* mGamefield = nullptr;

	Ref<Chip> mChip; // @EDITOR_PROPERTY

	Cell* mNeighborLeft = nullptr;  // @EDITOR_PROPERTY
	Cell* mNeighborRight = nullptr; // @EDITOR_PROPERTY
	Cell* mNeighborTop = nullptr;   // @EDITOR_PROPERTY
	Cell* mNeighborDown = nullptr;  // @EDITOR_PROPERTY

	Vector<Ref<CellBehaviour>> mBehaviours; // @EDITOR_PROPERTY

	FallAvoidDirection mAvoidDirection = FallAvoidDirection::Left; // @EDITOR_PROPERTY

private:
	void OnCursorRightMouseReleased(const Input::Cursor& cursor) override;
};
// --- META ---

PRE_ENUM_META(Cell::FallAvoidDirection);

CLASS_BASES_META(Cell)
{
	BASE_CLASS(DrawableComponent);
	BASE_CLASS(CursorAreaEventsListener);
}
END_META;
CLASS_FIELDS_META(Cell)
{
	FIELD().PRIVATE().DEFAULT_VALUE(nullptr).NAME(mGamefield);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChip);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(nullptr).NAME(mNeighborLeft);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(nullptr).NAME(mNeighborRight);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(nullptr).NAME(mNeighborTop);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(nullptr).NAME(mNeighborDown);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mBehaviours);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(FallAvoidDirection::Left).NAME(mAvoidDirection);
}
END_META;
CLASS_METHODS_META(Cell)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Draw);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
	FUNCTION().PUBLIC().SIGNATURE(void, SetGamefield, Gamefield*);
	FUNCTION().PUBLIC().SIGNATURE(void, SetChip, const Ref<Chip>&, bool);
	FUNCTION().PUBLIC().SIGNATURE(const Ref<Chip>&, GetChip);
	FUNCTION().PUBLIC().SIGNATURE(void, AddBehaviour, Ref<CellBehaviour>&);
	FUNCTION().PUBLIC().SIGNATURE(void, RemoveBehaviour, const Ref<CellBehaviour>&);
	FUNCTION().PUBLIC().SIGNATURE(void, SetNeighborLeft, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(void, SetNeighborRight, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(void, SetNeighborTop, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(void, SetNeighborDown, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(Cell*, GetNeighborLeft);
	FUNCTION().PUBLIC().SIGNATURE(Cell*, GetNeighborRight);
	FUNCTION().PUBLIC().SIGNATURE(Cell*, GetNeighborTop);
	FUNCTION().PUBLIC().SIGNATURE(Cell*, GetNeighborDown);
	FUNCTION().PUBLIC().SIGNATURE(FallAvoidDirection, GetFallAvoidDirection);
	FUNCTION().PUBLIC().SIGNATURE(void, SwapFallAvoidDirection);
	FUNCTION().PUBLIC().SIGNATURE(bool, IsUnderPoint, const Vec2F&);
	FUNCTION().PRIVATE().SIGNATURE(void, OnCursorRightMouseReleased, const Input::Cursor&);
}
END_META;
// --- END META ---
