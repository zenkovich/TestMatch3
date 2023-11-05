#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class Cell;
class Chip;
class Gamefield;

// ----------------------------------------------------------------------
// Gamefield behaviour interface. Can be used to make some logic on field
// ----------------------------------------------------------------------
class GamefieldBehaviour : public Component
{
public:
    // Sets gamefield for behaviour
    void SetGamefield(Gamefield* gamefield);

    // Process behaviour
    virtual void Process(float dt) {}

    // Called when chip created
    virtual void OnChipCreated(Chip* chip) {}

    // Called when cell created
    virtual void OnCellCreated(Cell* cell) {}

    // Returns category of component
    static String GetCategory() { return "Gamefield"; }

    SERIALIZABLE(GamefieldBehaviour);

protected:
    Gamefield* mGamefield = nullptr; 
};
// --- META ---

CLASS_BASES_META(GamefieldBehaviour)
{
    BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(GamefieldBehaviour)
{
    FIELD().PROTECTED().DEFAULT_VALUE(nullptr).NAME(mGamefield);
}
END_META;
CLASS_METHODS_META(GamefieldBehaviour)
{

    FUNCTION().PUBLIC().SIGNATURE(void, SetGamefield, Gamefield*);
    FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
    FUNCTION().PUBLIC().SIGNATURE(void, OnChipCreated, Chip*);
    FUNCTION().PUBLIC().SIGNATURE(void, OnCellCreated, Cell*);
    FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
}
END_META;
// --- END META ---
