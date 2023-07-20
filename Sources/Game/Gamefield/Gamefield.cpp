#include "o2/stdafx.h"
#include "Gamefield.h"
#include "ChipsSpawner.h"
#include "o2/Scene/Scene.h"

void Gamefield::OnStart()
{
	GenerateField(Math::Random(mFieldMinSize, mFieldMaxSize), 
				  Math::Random(mFieldMinSize, mFieldMaxSize));
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

void Gamefield::SwapChips(const Ref<Chip>& chipA, const Ref<Chip>& chipB)
{

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

			if (y == 0)
			{
				auto spawner = Ref<ChipSpawner>(newCellActor->AddComponent<ChipSpawner>());
				auto beh = Ref<CellBehaviour>(spawner.Get());
				newCell->AddBehaviour(beh);

				mChipSpawners.Add(spawner);
			}
		}
	}

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
}

void Gamefield::UpdateSpawn()
{
	for (auto& spawner : mChipSpawners)
	{
		if (!spawner->CanSpawn())
			continue;

		auto& chipProto = mChipProtos[Math::Random(0, mChipProtos.Count() - 1)];
		auto newChip = spawner->SpawnChip(chipProto);

		newChip->SetFallSpeed(mChipsFallingMaxSpeed, mChipsFallingAcceleration);

		mChips.Add(newChip);
		mChipsByColor[newChip->GetColor()].Add(newChip);
	}
}

DECLARE_TEMPLATE_CLASS(Ref<Gamefield>);
// --- META ---

DECLARE_CLASS(Gamefield);
// --- END META ---
