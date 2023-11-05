#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "Gamefield/GamefieldBehaviour.h"

using namespace o2;

// ---------------------------
// Updates chips falling logic
// ---------------------------
class ChipsFallGamefieldBehaviour : public GamefieldBehaviour
{
public:
    // Processes falling
    void Process(float dt) override;

    // Called when chips created, initializes fall speed parameters for them
    void OnChipCreated(Chip* chip) override;

    // Returns category of component
    static String GetCategory() { return "Gamefield"; }

    SERIALIZABLE(ChipsFallGamefieldBehaviour);

private:
    float mChipsFallingMaxSpeed = 10.0f;     // Chip fall max speed @SERIALIZABLE @EDITOR_PROPERTY
    float mChipsFallingAcceleration = 10.0f; // Chip fall acceleration @SERIALIZABLE @EDITOR_PROPERTY
};
// --- META ---

CLASS_BASES_META(ChipsFallGamefieldBehaviour)
{
    BASE_CLASS(GamefieldBehaviour);
}
END_META;
CLASS_FIELDS_META(ChipsFallGamefieldBehaviour)
{
    FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().DEFAULT_VALUE(10.0f).NAME(mChipsFallingMaxSpeed);
    FIELD().PRIVATE().EDITOR_PROPERTY_ATTRIBUTE().SERIALIZABLE_ATTRIBUTE().DEFAULT_VALUE(10.0f).NAME(mChipsFallingAcceleration);
}
END_META;
CLASS_METHODS_META(ChipsFallGamefieldBehaviour)
{

    FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
    FUNCTION().PUBLIC().SIGNATURE(void, OnChipCreated, Chip*);
    FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
}
END_META;
// --- END META ---
