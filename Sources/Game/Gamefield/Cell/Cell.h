#pragma once
#include "Gamefield/Cell/CellBehaviour.h"
#include "Gamefield/Chip/Chip.h"
#include "o2/Events/CursorAreaEventsListener.h"
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "o2/Scene/DrawableComponent.h"

using namespace o2;

class Gamefield;

// --------------------------------------------
// Gamefield cell. Contains chip and behaviours
// --------------------------------------------
class Cell : public DrawableComponent, public CursorAreaEventsListener
{
public:
	enum class FallAvoidDirection { Left, Right };

public:
	// Called when cells are created, initializes behaviours
	void OnStart();

	// Draws content of cell, used to handle events
	void Draw() override;

	// Process behaviours
	void Process(float dt);

	// Sets gamefield for cell
	void SetGamefield(Gamefield* gamefield);

	// Sets chip for cell. Can reset position of chip to center
	void SetChip(const Ref<Chip>& chip, bool resetPosition = true);

	// Returns chip of cell
	Ref<Chip>& GetChip();

	// Returns chip of cell
	const Ref<Chip>& GetChip() const;

	// Adds behaviour to cell
	void AddBehaviour(Ref<CellBehaviour>& behaviour);

	// Removes behaviour from cell
	void RemoveBehaviour(const Ref<CellBehaviour>& behaviour);

	// Sets neighbor cells
	void SetNeighborLeft(Cell* neighbor);
	void SetNeighborRight(Cell* neighbor);
	void SetNeighborTop(Cell* neighbor);
	void SetNeighborDown(Cell* neighbor);

	// Returns neighbor cells
	Cell* GetNeighborLeft() const;
	Cell* GetNeighborRight() const;
	Cell* GetNeighborTop() const;
	Cell* GetNeighborDown() const;

	// Returns true if cell is under point
	bool IsUnderPoint(const Vec2F& point) override;

	// Returns category of component
	static String GetCategory() { return "Gamefield"; }

	SERIALIZABLE(Cell);

private:
	Gamefield* mGamefield = nullptr;

	Ref<Chip> mChip; // Containing chip @EDITOR_PROPERTY

	Cell* mNeighborLeft = nullptr;  // Left cached neighbor
	Cell* mNeighborRight = nullptr; // Right cached neighbor
	Cell* mNeighborTop = nullptr;   // Top cached neighbor
	Cell* mNeighborDown = nullptr;  // Down cached neighbor

	Vector<Ref<CellBehaviour>> mBehaviours; // List of behaviours @EDITOR_PROPERTY

private:
	// Called when cursor exits from cell area
	void OnCursorExit(const Input::Cursor& cursor) override;

	// Called when cursor enters cell area
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
	FIELD().PRIVATE().DEFAULT_VALUE(nullptr).NAME(mNeighborLeft);
	FIELD().PRIVATE().DEFAULT_VALUE(nullptr).NAME(mNeighborRight);
	FIELD().PRIVATE().DEFAULT_VALUE(nullptr).NAME(mNeighborTop);
	FIELD().PRIVATE().DEFAULT_VALUE(nullptr).NAME(mNeighborDown);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mBehaviours);
}
END_META;
CLASS_METHODS_META(Cell)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Draw);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
	FUNCTION().PUBLIC().SIGNATURE(void, SetGamefield, Gamefield*);
	FUNCTION().PUBLIC().SIGNATURE(void, SetChip, const Ref<Chip>&, bool);
	FUNCTION().PUBLIC().SIGNATURE(Ref<Chip>&, GetChip);
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
	FUNCTION().PUBLIC().SIGNATURE(bool, IsUnderPoint, const Vec2F&);
	FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
	FUNCTION().PRIVATE().SIGNATURE(void, OnCursorExit, const Input::Cursor&);
	FUNCTION().PRIVATE().SIGNATURE(void, OnCursorRightMouseReleased, const Input::Cursor&);
}
END_META;
// --- END META ---
