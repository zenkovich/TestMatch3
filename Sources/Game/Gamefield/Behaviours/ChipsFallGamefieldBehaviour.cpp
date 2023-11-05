#include "o2/stdafx.h"
#include "ChipsFallGamefieldBehaviour.h"

#include "Gamefield/Chip/Chip.h"
#include "Gamefield/Gamefield.h"

void ChipsFallGamefieldBehaviour::Process(float dt)
{
    mGamefield->ForEachChip([&](Chip* chip, int x, int y)
                {
                    if (!chip->IsFalling())
                        return;

                    chip->UpdateFallingStep1(dt);
                });

    mGamefield->ForEachChip([&](Chip* chip, int x, int y)
                {
                    if (chip->GetState() == Chip::State::Standing || chip->GetState() == Chip::State::CheckFallingNext)
                        chip->CheckFallingDown();
                });

    mGamefield->ForEachChip([&](Chip* chip, int x, int y)
                {
                    if (!chip->IsFalling())
                        return;

                    chip->UpdateFallingStep2(dt);
                });
}

void ChipsFallGamefieldBehaviour::OnChipCreated(Chip* chip)
{
    chip->SetFallSpeed(mChipsFallingMaxSpeed, mChipsFallingAcceleration);
}
// --- META ---

DECLARE_CLASS(ChipsFallGamefieldBehaviour);
// --- END META ---
