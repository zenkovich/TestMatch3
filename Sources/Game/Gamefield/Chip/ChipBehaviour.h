#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

class Chip;

// -------------------------------------------------------------
// Chip base logic behaviour. Use it to make some logic for chip
// -------------------------------------------------------------
class ChipBehaviour : public Component
{
public:
    // Initializes chip
    void SetChip(Chip* chip);

    // Process behaviour
    virtual void Process(float dt) {}

    // Called when chip is destroyed
    virtual void OnDestroy() {}

    // Returns category of component
    static String GetCategory() { return "Gamefield"; }

    SERIALIZABLE(ChipBehaviour);

protected:
    Chip* mChip = nullptr; 
};
// --- META ---

CLASS_BASES_META(ChipBehaviour)
{
    BASE_CLASS(Component);
}
END_META;
CLASS_FIELDS_META(ChipBehaviour)
{
    FIELD().PROTECTED().DEFAULT_VALUE(nullptr).NAME(mChip);
}
END_META;
CLASS_METHODS_META(ChipBehaviour)
{

    FUNCTION().PUBLIC().SIGNATURE(void, SetChip, Chip*);
    FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
    FUNCTION().PUBLIC().SIGNATURE(void, OnDestroy);
    FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
}
END_META;
// --- END META ---
