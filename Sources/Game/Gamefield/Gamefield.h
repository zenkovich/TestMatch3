#pragma once
#include "Cell.h"
#include "ChipsSpawner.h"
#include "GamefieldBehaviour.h"
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class Gamefield : public Component
{
public:
	void OnStart() override;
	void Update(float dt) override;

	void SwapChips(const Ref<Chip>& chipA, const Ref<Chip>& chipB);

	Ref<Cell> GetCell(int x, int y) const;

	void DestroyChip(Ref<Chip>& chip);

	SERIALIZABLE(Gamefield);

private:
	Vector<ActorAssetRef> mChipProtos; // @SERIALIZABLE @EDITOR_PROPERTY

	int mFieldMinSize = 3; // @SERIALIZABLE @EDITOR_PROPERTY
	int mFieldMaxSize = 10; // @SERIALIZABLE @EDITOR_PROPERTY

	float mChipsFallingMaxSpeed = 10.0f; // @SERIALIZABLE @EDITOR_PROPERTY
	float mChipsFallingAcceleration = 10.0f; // @SERIALIZABLE @EDITOR_PROPERTY

	Vec2F         mCellSize;       // @SERIALIZABLE @EDITOR_PROPERTY
	ActorRef      mCellsContainer; // @SERIALIZABLE @EDITOR_PROPERTY
	ActorAssetRef mCellProto;      // @SERIALIZABLE @EDITOR_PROPERTY

	Vector<Ref<ChipSpawner>> mChipSpawners; // @EDITOR_PROPERTY

	Vector<Ref<GamefieldBehaviour>> mBehaviours; // @SERIALIZABLE @EDITOR_PROPERTY

	Vector<Vector<Ref<Cell>>> mCells; // @EDITOR_PROPERTY
	Vector<Ref<Chip>>         mChips; // @EDITOR_PROPERTY

	Map<Chip::Color, Vector<Ref<Chip>>> mChipsByColor; // @EDITOR_PROPERTY

private:
	void GenerateField(int width, int heigth);

	void UpdateSpawn();
};
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
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().DEFAULT_VALUE(10.0f).NAME(mChipsFallingMaxSpeed);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().DEFAULT_VALUE(10.0f).NAME(mChipsFallingAcceleration);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellSize);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellsContainer);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellProto);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChipSpawners);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mBehaviours);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mCells);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChips);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChipsByColor);
}
END_META;
CLASS_METHODS_META(Gamefield)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Update, float);
	FUNCTION().PUBLIC().SIGNATURE(void, SwapChips, const Ref<Chip>&, const Ref<Chip>&);
	FUNCTION().PUBLIC().SIGNATURE(Ref<Cell>, GetCell, int, int);
	FUNCTION().PUBLIC().SIGNATURE(void, DestroyChip, Ref<Chip>&);
	FUNCTION().PRIVATE().SIGNATURE(void, GenerateField, int, int);
	FUNCTION().PRIVATE().SIGNATURE(void, UpdateSpawn);
}
END_META;
// --- END META ---