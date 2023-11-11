#include "o2/stdafx.h"
#include "CheckMatchesGamefieldBehaviour.h"

#include "Gamefield/Chip/Chip.h"
#include "Gamefield/Gamefield.h"

void CheckMatchesGamefieldBehaviour::Process(float dt)
{
    CheckMatches();
}

bool CheckMatchesGamefieldBehaviour::CheckMatches()
{
    bool hasMatches = false;

    // Search matches while there are any
    // Finidng biggest match and applygin it. And repeating
    while (true)
    {
        bool foundMatch = false;
        Vector<Chip*> biggestMatch;
        int biggestMatchSizeSum = 0;

        Vector<Chip*> chipsToCheck;
        for (int x = 0; x < mGamefield->GetFieldSize().x; x++)
        {
            for (int y = 0; y < mGamefield->GetFieldSize().y; y++)
            {
                auto chip = mGamefield->GetCell(x, y)->GetChip();
                if (!chip || chip->GetState() != Chip::State::Standing)
                    continue;

                chipsToCheck.Clear();
                chipsToCheck.Add(chip.Get());
                RectI bounds(x, y, x, y);

                // Run recursive search for matches with 4 directions
                FindChipsMatch(Vec2I(x, y), Vec2I(1, 0), bounds, chipsToCheck, chip->GetColor());
                FindChipsMatch(Vec2I(x, y), Vec2I(0, 1), bounds, chipsToCheck, chip->GetColor());
                FindChipsMatch(Vec2I(x, y), Vec2I(-1, 0), bounds, chipsToCheck, chip->GetColor());
                FindChipsMatch(Vec2I(x, y), Vec2I(0, -1), bounds, chipsToCheck, chip->GetColor());

                if (bounds.Width() + 1 >= 3 || bounds.Height() + 1 >= 3)
                {
                    int sizeSum = bounds.Width() + bounds.Height();
                    if (sizeSum > biggestMatchSizeSum)
                    {
                        biggestMatchSizeSum = sizeSum;
                        biggestMatch = chipsToCheck;
                    }

                    foundMatch = true;
                    hasMatches = true;
                }
            }
        }

        if (!foundMatch)
            break;

        for (auto chip : biggestMatch)
        {
            auto refChip = Ref<Chip>(chip);
            mGamefield->DestroyChip(refChip);
        }
    }

    return hasMatches;
}

void CheckMatchesGamefieldBehaviour::FindChipsMatch(const Vec2I& pos, const Vec2I& dir, RectI& bounds, Vector<Chip*>& chips, ChipColor color)
{
    Vec2I newPos = pos + dir;
    if (newPos.x < 0 || newPos.x >= mGamefield->GetFieldSize().x || newPos.y < 0 || newPos.y >= mGamefield->GetFieldSize().y)
        return;

    auto chip = mGamefield->GetCell(newPos.x, newPos.y)->GetChip();
    if (!chip || chip->GetState() != Chip::State::Standing || chip->GetColor() != color)
        return;

    chips.Add(chip.Get());

    bounds.left = Math::Min(newPos.x, bounds.left);
    bounds.right = Math::Max(newPos.x, bounds.right);
    bounds.top = Math::Max(newPos.y, bounds.top);
    bounds.bottom = Math::Min(newPos.y, bounds.bottom);

    FindChipsMatch(newPos, dir, bounds, chips, color);
}
// --- META ---

DECLARE_CLASS(CheckMatchesGamefieldBehaviour, CheckMatchesGamefieldBehaviour);
// --- END META ---
