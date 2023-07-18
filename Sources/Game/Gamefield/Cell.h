#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "Chip.h"
#include "CellBehaviour.h"

using namespace o2;

class Cell : public Component
{
public:
	void OnStart();

	void Process(float dt);

	const Ref<Chip>& GetChip() const;

	void AddBehaviour(const Ref<CellBehaviour>& behaviour);
	void RemoveBehaviour(const Ref<CellBehaviour>& behaviour);

	SERIALIZABLE(Cell);

private:
	Ref<Chip> mChip; // @EDITOR_PROPERTY

	Vector<Ref<CellBehaviour>> mBehaviours; // @EDITOR_PROPERTY
};
// --- META ---

CLASS_BASES_META(Cell)
{
	BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(Cell)
{
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mChip);
	FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().NAME(mBehaviours);
}
END_META;
CLASS_METHODS_META(Cell)
{

	FUNCTION().PUBLIC().SIGNATURE(void, OnStart);
	FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
	FUNCTION().PUBLIC().SIGNATURE(const Ref<Chip>&, GetChip);
	FUNCTION().PUBLIC().SIGNATURE(void, AddBehaviour, const Ref<CellBehaviour>&);
	FUNCTION().PUBLIC().SIGNATURE(void, RemoveBehaviour, const Ref<CellBehaviour>&);
}
END_META;
// --- END META ---
