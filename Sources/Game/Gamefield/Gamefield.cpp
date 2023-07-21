#include "o2/stdafx.h"
#include "Gamefield.h"

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
	UpdateFalling(dt);
	CheckMatches();
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

	mFieldWidth = width;
	mFieldHeigth = heigth;
}

void Gamefield::UpdateSpawn()
{
	for (auto& spawner : mChipSpawners)
	{
		if (!spawner->CanSpawn())
			continue;

		auto& chipProto = mChipProtos[Math::Random(0, mChipProtos.Count())];
		auto newChip = spawner->SpawnChip(chipProto);

		newChip->SetFallSpeed(mChipsFallingMaxSpeed, mChipsFallingAcceleration);

		mChips.Add(newChip);
		mChipsByColor[newChip->GetColor()].Add(newChip);
	}
}

void Gamefield::UpdateFalling(float dt)
{
	ForEachChip([&](Chip* chip, int x, int y)
				{
					if (!chip->IsFalling())
						return;

					chip->UpdateFallingStep1(dt);
				});

	ForEachChip([&](Chip* chip, int x, int y)
				{
					if (chip->GetState() == Chip::State::Standing || chip->GetState() == Chip::State::CheckFallingNext)
						chip->CheckFallingDown();
				});

	ForEachChip([&](Chip* chip, int x, int y)
				{
					if (chip->GetState() == Chip::State::Standing || chip->GetState() == Chip::State::CheckFallingNext)
						chip->CheckFallingSide();
				});

	ForEachChip([&](Chip* chip, int x, int y)
				{
					if (!chip->IsFalling())
						return;

					chip->UpdateFallingStep2(dt);
				});
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


void Gamefield::CheckMatches()
{
	while (true)
	{
		bool foundMatch = false;
		Vector<Chip*> biggestMatch;
		int biggestMatchSizeSum = 0;

		Vector<Chip*> chipsToCheck;
		for (int x = 0; x < mFieldWidth; x++)
		{
			for (int y = 0; y < mFieldHeigth; y++)
			{
				auto chip = mCells[x][y]->GetChip();
				if (!chip || chip->GetState() != Chip::State::Standing)
					continue;

				chipsToCheck.Clear();
				chipsToCheck.Add(chip.Get());
				RectI bounds(x, y, x, y);

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
				}
			}
		}

		if (!foundMatch)
			break;

		for (auto chip : biggestMatch)
		{
			auto refChip = Ref<Chip>(chip);
			DestroyChip(refChip);
		}
	}
}

void Gamefield::FindChipsMatch(const Vec2I& pos, const Vec2I& dir, RectI& bounds, Vector<Chip*>& chips, Chip::Color color)
{
	Vec2I newPos = pos + dir;
	if (newPos.x < 0 || newPos.x >= mFieldWidth || newPos.y < 0 || newPos.y >= mFieldHeigth)
		return;

	auto chip = mCells[newPos.x][newPos.y]->GetChip();
	if (!chip || chip->GetState() != Chip::State::Standing || chip->GetColor() != color)
		return;

	chips.Add(chip.Get());

	bounds.left = Math::Min(newPos.x, bounds.left);
	bounds.right = Math::Max(newPos.x, bounds.right);
	bounds.top = Math::Max(newPos.y, bounds.top);
	bounds.bottom = Math::Min(newPos.y, bounds.bottom);

	FindChipsMatch(newPos, dir, bounds, chips, color);
}

DECLARE_TEMPLATE_CLASS(Ref<Gamefield>);
// --- META ---

DECLARE_CLASS(Gamefield);
// --- END META ---
