#include "o2/stdafx.h"
#include "Gamefield.h"

#include "o2/Scene/Scene.h"

void Gamefield::OnStart()
{
	InitializeBehaviours();

	GenerateField(Math::Random(mFieldMinSize, mFieldMaxSize), 
				  Math::Random(mFieldMinSize, mFieldMaxSize));
}

void Gamefield::InitializeBehaviours()
{
	mBehaviours = GetOwnerActor()->GetComponents<GamefieldBehaviour>().Cast<Ref<GamefieldBehaviour>>();
	for (auto& behaviour : mBehaviours)
		behaviour->SetGamefield(this);
}

void Gamefield::Update(float dt)
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
}

Vec2I Gamefield::GetFieldSize() const
{
	return Vec2I(mFieldWidth, mFieldHeigth);
}

void Gamefield::SwapChips(Cell* cellA, Cell* cellB)
{
	Ref<Chip> chipA = cellA->GetChip();
	Ref<Chip> chipB = cellB->GetChip();

	cellA->SetChip(chipB, false);
	cellB->SetChip(chipA, false);

	chipA->SetState(Chip::State::Swapping);
	chipB->SetState(Chip::State::Swapping);
}

Ref<Cell> Gamefield::GetCell(int x, int y) const
{
	return mCells[x][y];
}

void Gamefield::DestroyChip(Ref<Chip>& chip)
{
	o2Scene.DestroyActor(chip->GetOwnerActor());

	mChips.Remove(chip);
	mChipsByColor[chip->GetColor()].Remove(chip);

	chip->GetCell()->SetChip(nullptr);
}

void Gamefield::GenerateField(int width, int heigth)
{
	Vec2F fieldSize = Vec2F(width, heigth) * mCellSize;

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

	mFieldWidth = width;
	mFieldHeigth = heigth;
}

void Gamefield::UpdateSpawn()
{
	for (auto& spawner : mChipSpawners)
	{
		if (!spawner->CanSpawn())
			continue;

		auto chipProto = GetSpawnPrototype();
		auto newChip = spawner->SpawnChip(chipProto);

		mChips.Add(newChip);
		mChipsByColor[newChip->GetColor()].Add(newChip);

		for (auto& beh : mBehaviours)
			beh->OnChipCreated(newChip.Get());
	}
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

DECLARE_CLASS(Gamefield);
// --- END META ---
