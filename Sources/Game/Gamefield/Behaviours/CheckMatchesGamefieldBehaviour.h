#pragma once
#include "Gamefield/Chip/ChipColor.h"
#include "Gamefield/GamefieldBehaviour.h"
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"

using namespace o2;

// ---------------------------
// Checks mathces on gamefield
// ---------------------------
class CheckMatchesGamefieldBehaviour : public GamefieldBehaviour
{
public:
    // Calling check matches
    void Process(float dt) override;

    // Checks matches and applies them, returns true if matches found
    bool CheckMatches();

    // Returns category of component
    static String GetCategory() { return "Gamefield"; }

    SERIALIZABLE(CheckMatchesGamefieldBehaviour);

private:
    // Recursively search chips with same color from position with direction
    void FindChipsMatch(const Vec2I& pos, const Vec2I& dir, RectI& bounds, Vector<Chip*>& chips, ChipColor color);
};
// --- META ---

CLASS_BASES_META(CheckMatchesGamefieldBehaviour)
{
    BASE_CLASS(GamefieldBehaviour);
}
END_META;
CLASS_FIELDS_META(CheckMatchesGamefieldBehaviour)
{
}
END_META;
CLASS_METHODS_META(CheckMatchesGamefieldBehaviour)
{

    FUNCTION().PUBLIC().SIGNATURE(void, Process, float);
    FUNCTION().PUBLIC().CONSTRUCTOR();
    FUNCTION().PUBLIC().SIGNATURE_STATIC(String, GetCategory);
    FUNCTION().PRIVATE().SIGNATURE(void, FindChipsMatch, const Vec2I&, const Vec2I&, RectI&, Vector<Chip*>&, ChipColor);
}
END_META;
// --- END META ---
