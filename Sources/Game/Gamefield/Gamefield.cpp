#include "o2/stdafx.h"
#include "Gamefield.h"

#include "o2/Scene/Scene.h"
#include "Behaviours/CheckMatchesGamefieldBehaviour.h"
#include "o2/Utils/Editor/EditorScope.h"

void Gamefield::OnStart()
{
    InitializeBehaviours();
}

void Gamefield::InitializeBehaviours()
{
    mBehaviours = GetOwnerActor()->GetComponents<GamefieldBehaviour>().Cast<Ref<GamefieldBehaviour>>();
    for (auto& behaviour : mBehaviours)
        behaviour->SetGamefield(this);
}

void Gamefield::OnUpdate(float dt)
{
    for (auto& fieldBehaviour : mBehaviours)
        fieldBehaviour->Process(dt);

    for (auto& chip : mChips)
        chip->Process(dt);

    for (auto& cellRow : mCells)
    {
        for (auto& cell : cellRow)
            cell->Process(dt);
    }

    UpdateSpawn();

    for (auto& action : mPostUpdateActions)
        action();

    mPostUpdateActions.Clear();
}

Vec2I Gamefield::GetFieldSize() const
{
    return Vec2I(mFieldWidth, mFieldHeigth);
}

void Gamefield::TrySwapChips(Cell* cellA, Cell* cellB)
{
    Chip* chipA = cellA->GetChip().Get();
    Chip* chipB = cellB->GetChip().Get();

    cellA->SetChip(chipB, false);
    cellB->SetChip(chipA, false);

    chipA->SetState(Chip::State::Swapping);
    chipB->SetState(Chip::State::Swapping);

    chipA->onSwapped = [=]()
    {
        mPostUpdateActions.Add(
            [=]() {
                if (!CheckMatches())
                {
                    cellA->SetChip(chipA, false);
                    cellB->SetChip(chipB, false);

                    chipA->SetState(Chip::State::Swapping);
                    chipB->SetState(Chip::State::Swapping);

                    chipA->onSwapped.Clear();
                }
            });
    };
}

bool Gamefield::CheckMatches()
{
    if (auto checkMatchesbehaviour = GetBehaviour<CheckMatchesGamefieldBehaviour>())
        return checkMatchesbehaviour->CheckMatches();

    return false;
}

void Gamefield::DestroyField()
{
    for (auto& chip : mChips)
        o2Scene.DestroyActor(chip->GetOwnerActor());

    for (auto& cellsRow : mCells)
    {
        for (auto& cell : cellsRow)
            o2Scene.DestroyActor(cell->GetOwnerActor());
    }

    mChips.Clear();
    mChipsByColor.Clear();
    mCells.Clear();
    mChipSpawners.Clear();
    mPostUpdateActions.Clear();
}

void Gamefield::Restart()
{
    DestroyField();
    GenerateField(Math::Random(mFieldMinSize, mFieldMaxSize), Math::Random(mFieldMinSize, mFieldMaxSize));
}

Ref<Cell> Gamefield::GetCell(int x, int y) const
{
    return mCells[x][y];
}

void Gamefield::DestroyChip(Ref<Chip>& chip)
{
    chip->OnDestroy();

    o2Scene.DestroyActor(chip->GetOwnerActor());

    mChips.Remove(chip);
    mChipsByColor[chip->GetColor()].Remove(chip);

    chip->GetCell()->SetChip(nullptr);
}

void Gamefield::GenerateField(int width, int heigth)
{
    Vec2F fieldSize = Vec2F((float)width, (float)heigth) * mCellSize;

    mFieldWidth = width;
    mFieldHeigth = heigth;

    // Generate cells and spawners at top
    for (int x = 0; x < width; x++)
    {
        float xCenter = x*mCellSize.x - fieldSize.x/2.0f + mCellSize.x/2.0f;
        mCells.Add(Vector<Ref<Cell>>());

        for (int y = 0; y < heigth; y++)
        {
            float yCenter = fieldSize.y/2.0f - y*mCellSize.y + mCellSize.y/2.0f;

            auto newCellActor = mCellProto->Instantiate();
            newCellActor->SetParent(mCellsContainer.Get(), false);
            newCellActor->transform->position = Vec2F(xCenter, yCenter);

            auto newCell = newCellActor->GetComponent<Cell>();
            mCells[x].Add(newCell);

            newCell->SetGamefield(this);

            for (auto& beh : mBehaviours)
                beh->OnCellCreated(newCell);

            if (y == 0)
            {
                auto spawner = Ref<ChipSpawner>(newCellActor->AddComponent<ChipSpawner>());
                auto beh = Ref<CellBehaviour>(spawner.Get());
                newCell->AddBehaviour(beh);

                mChipSpawners.Add(spawner);
            }
        }
    }

    // Map cells neighbors
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < heigth; y++)
        {
            auto cell = mCells[x][y];
            if (x > 0)
                cell->SetNeighborLeft(mCells[x - 1][y].Get());
            if (x < width - 1)
                cell->SetNeighborRight(mCells[x + 1][y].Get());
            if (y > 0)
                cell->SetNeighborTop(mCells[x][y - 1].Get());
            if (y < heigth - 1)
                cell->SetNeighborDown(mCells[x][y + 1].Get());
        }
    }

    FillFieldWithChips();
}

void Gamefield::FillFieldWithChips()
{
    Vector<ChipColor> availableColors;

    Map<ChipColor, ActorAssetRef> protosByColors;
    for (auto& proto : mChipProtos)
    {
        auto chip = proto->GetActor()->GetComponent<Chip>();
        protosByColors[chip->GetColor()] = proto;
    }

    for (int x = 0; x < mFieldWidth; x++)
    {
        for (int y = 0; y < mFieldHeigth; y++)
        {
            auto cell = mCells[x][y];

            availableColors = { ChipColor::Red, ChipColor::Green, ChipColor::Blue, ChipColor::Yellow, ChipColor::Violet };

            if (cell->GetNeighborLeft())
                availableColors.Remove(cell->GetNeighborLeft()->GetChip()->GetColor());

            if (cell->GetNeighborTop())
                availableColors.Remove(cell->GetNeighborTop()->GetChip()->GetColor());

            ChipColor randomColor = availableColors[Math::Random(0, availableColors.Count())];
            auto& chipProto = protosByColors[randomColor];

            auto newChip = CreateChip(chipProto);
            cell->SetChip(newChip);
        }
    }
}

void Gamefield::UpdateSpawn()
{
    for (auto& spawner : mChipSpawners)
    {
        if (!spawner->CanSpawn())
            continue;

        auto chipProto = GetSpawnPrototype();
        auto newChip = CreateChip(chipProto);
        spawner->SpawnChip(newChip);
    }
}

Chip* Gamefield::CreateChip(const ActorAssetRef& proto)
{
    auto newChip = proto->Instantiate()->GetComponent<Chip>();

    newChip->SetState(Chip::State::Standing);

    mChips.Add(newChip);
    mChipsByColor[newChip->GetColor()].Add(newChip);

    for (auto& beh : mBehaviours)
        beh->OnChipCreated(newChip);

    return newChip;
}

ActorAssetRef Gamefield::GetSpawnPrototype() const
{
    // Simple randomly select prototype
    return mChipProtos[Math::Random(0, mChipProtos.Count())];
}

void Gamefield::ForEachChip(const Function<void(Chip* chip, int x, int y)>& func)
{
    for (int x = 0; x < mFieldWidth; x++)
    {
        for (int y = mFieldHeigth - 1; y >= 0; y--)
        {
            auto chip = mCells[x][y]->GetChip();
            if (!chip)
                continue;

            func(chip.Get(), x, y);
        }
    }
}

DECLARE_TEMPLATE_CLASS(Ref<Gamefield>);
// --- META ---

DECLARE_CLASS(Gamefield, Gamefield);
// --- END META ---
