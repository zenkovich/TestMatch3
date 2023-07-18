#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "Cell.h"
#include "GamefieldBehaviour.h"

using namespace o2;

class Gamefield : public Component
{
public:
	void OnStart() override;
	void Update(float dt) override;

	void SwapChips(const Ref<Chip>& chipA, const Ref<Chip>& chipB);

	Ref<Cell> GetCell(int x, int y) const;

	SERIALIZABLE(Gamefield);

private:
	Vector<ActorAssetRef> mChipProtos; // @SERIALIZABLE @EDITOR_PROPERTY

	int mFieldMinSize = 3; // @SERIALIZABLE @EDITOR_PROPERTY
	int mFieldMaxSize = 10; // @SERIALIZABLE @EDITOR_PROPERTY

	Vec2F         mCellSize;       // @SERIALIZABLE @EDITOR_PROPERTY
	ActorRef      mCellsContainer; // @SERIALIZABLE @EDITOR_PROPERTY
	ActorAssetRef mCellProto;      // @SERIALIZABLE @EDITOR_PROPERTY

	Vector<Ref<GamefieldBehaviour>> mBehaviours; // @SERIALIZABLE @EDITOR_PROPERTY

	Vector<Vector<Ref<Cell>>> mCells; // @EDITOR_PROPERTY
	Vector<Ref<Chip>>         mChips; // @EDITOR_PROPERTY

private:
	void GenerateField(int width, int heigth);
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
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellSize);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellsContainer);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mCellProto);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().NAME(mBehaviours);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mCells);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChips);
}
END_META;
CLASS_METHODS_META(Gamefield)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Update, float);
	FUNCTION().PUBLIC().SIGNATURE(void, SwapChips, const Ref<Chip>&, const Ref<Chip>&);
	FUNCTION().PUBLIC().SIGNATURE(Ref<Cell>, GetCell, int, int);
	FUNCTION().PRIVATE().SIGNATURE(void, GenerateField, int, int);
}
END_META;
// --- END META ---
