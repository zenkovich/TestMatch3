#pragma once
#include "Gamefield/Cell/Behaviours/ChipsSpawner.h"
#include "Gamefield/Cell/Cell.h"
#include "Gamefield/GamefieldBehaviour.h"
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

// -------------------------------------------------------------------------
// Match3 gamefield. Contains cells and chips. Updates whole gamefield logic
// -------------------------------------------------------------------------
class Gamefield : public Component
{
public:
	// Called at start, generates new field
	void OnStart() override;

	// Updates logic
	void OnUpdate(float dt) override;

	// Returns field size
	Vec2I GetFieldSize() const;

	// Returns cell
	Ref<Cell> GetCell(int x, int y) const;

	// Swaps chips in cells
	void TrySwapChips(Cell* cellA, Cell* cellB);

	// Checks matches and returns true if matches found
	bool CheckMatches();

	// Destroys all field
	void DestroyField();

	// Generates new field
	void Restart();

	// Destroys chip
	void DestroyChip(Ref<Chip>& chip);

	// List all chips with function
	void ForEachChip(const Function<void(Chip* chip, int x, int y)>& func);

	template<typename _behaviour_type>
	_behaviour_type* GetBehaviour();

	// Returns category of component
	static String GetCategory() { return "Gamefield"; }

	SERIALIZABLE(Gamefield);

private:
	Vector<ActorAssetRef> mChipProtos; // List of available chips prototypes @SERIALIZABLE @EDITOR_PROPERTY

	int mFieldMinSize = 3;  // Field minimal size @SERIALIZABLE @EDITOR_PROPERTY
	int mFieldMaxSize = 10; // Field max size @SERIALIZABLE @EDITOR_PROPERTY

	Vec2F         mCellSize;       // Size of one cell @SERIALIZABLE @EDITOR_PROPERTY
	ActorRef      mCellsContainer; // Cells objects container @SERIALIZABLE @EDITOR_PROPERTY
	ActorAssetRef mCellProto;      // Cell prototype @SERIALIZABLE @EDITOR_PROPERTY

	Vector<Ref<ChipSpawner>> mChipSpawners; // Chip spawners list @EDITOR_PROPERTY

	Vector<Ref<GamefieldBehaviour>> mBehaviours; // List of field behaviours @EDITOR_PROPERTY

	int mFieldWidth = 0;  // Generated field width @EDITOR_PROPERTY
	int mFieldHeigth = 0; // Generated field height @EDITOR_PROPERTY

	Vector<Vector<Ref<Cell>>> mCells; // List of cell of field @EDITOR_PROPERTY
	Vector<Ref<Chip>>         mChips; // List of chils on field @EDITOR_PROPERTY

	Map<ChipColor, Vector<Ref<Chip>>> mChipsByColor; // Chips sorted by color @EDITOR_PROPERTY

	Vector<Function<void()>> mPostUpdateActions; // List of actions to call after update

private:
	// Gets list of field behaviours, initializes them
	void InitializeBehaviours();

	// Generates new field with size
	void GenerateField(int width, int heigth);

	// Fills gamefield with random chips without matches
	void FillFieldWithChips();

	// Updates spawn
	void UpdateSpawn();

	// Creates chip and registers it
	Chip* CreateChip(const ActorAssetRef& proto);

	// Returns random chip prototype for spawn
	ActorAssetRef GetSpawnPrototype() const;
};

template<typename _behaviour_type>
_behaviour_type* Gamefield::GetBehaviour()
{
	for (auto& beh : mBehaviours)
	{
		if (auto casted = dynamic_cast<_behaviour_type*>(beh.Get()))
			return casted;
	}

	return nullptr;
}
// --- META ---

CLASS_BASES_META(Gamefield)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(Gamefield)
{
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mChipProtos);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().DEFAULT_VALUE(3).NAME(mFieldMinSize);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().DEFAULT_VALUE(10).NAME(mFieldMaxSize);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellSize);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellsContainer);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellProto);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChipSpawners);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mBehaviours);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(0).NAME(mFieldWidth);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().DEFAULT_VALUE(0).NAME(mFieldHeigth);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mCells);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChips);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChipsByColor);
	FIELD().PRIVATE().NAME(mPostUpdateActions);
}
END_META;
CLASS_METHODS_META(Gamefield)
{

	typedef const Function<void(Chip* chip, int x, int y)>& _tmp1;

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, OnUpdate, float);
	FUNCTION().PUBLIC().SIGNATURE(Vec2I, GetFieldSize);
	FUNCTION().PUBLIC().SIGNATURE(Ref<Cell>, GetCell, int, int);
	FUNCTION().PUBLIC().SIGNATURE(void, TrySwapChips, Cell*, Cell*);
	FUNCTION().PUBLIC().SIGNATURE(bool, CheckMatches);
	FUNCTION().PUBLIC().SIGNATURE(void, DestroyField);
	FUNCTION().PUBLIC().SIGNATURE(void, Restart);
	FUNCTION().PUBLIC().SIGNATURE(void, DestroyChip, Ref<Chip>&);
	FUNCTION().PUBLIC().SIGNATURE(void, ForEachChip, _tmp1);
	FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
	FUNCTION().PRIVATE().SIGNATURE(void, InitializeBehaviours);
	FUNCTION().PRIVATE().SIGNATURE(void, GenerateField, int, int);
	FUNCTION().PRIVATE().SIGNATURE(void, FillFieldWithChips);
	FUNCTION().PRIVATE().SIGNATURE(void, UpdateSpawn);
	FUNCTION().PRIVATE().SIGNATURE(Chip*, CreateChip, const ActorAssetRef&);
	FUNCTION().PRIVATE().SIGNATURE(ActorAssetRef, GetSpawnPrototype);
}
END_META;
// --- END META ---
