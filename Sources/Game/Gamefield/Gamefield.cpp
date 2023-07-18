#include "o2/stdafx.h"
#include "Gamefield.h"

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
}

void Gamefield::SwapChips(const Ref<Chip>& chipA, const Ref<Chip>& chipB)
{

}

Ref<Cell> Gamefield::GetCell(int x, int y) const
{
	return mCells[x][y];
}

void Gamefield::GenerateField(int width, int heigth)
{
	Vec2F fieldSize = Vec2F(width, heigth) * mCellSize;

	for (int x = 0; x < width; x++)
	{
		float xCenter = x*mCellSize.x - fieldSize.x/2.0f;
		mCells.Add(Vector<Ref<Cell>>());

		for (int y = 0; y < heigth; y++)
		{
			float yCenter = y*mCellSize.y - fieldSize.y/2.0f;

			auto newCell = mCellProto->Instantiate();
			newCell->SetParent(mCellsContainer.Get(), false);
			newCell->transform->position = Vec2F(xCenter, yCenter);

			mCells[x].Add(newCell->GetComponent<Cell>());
		}
	}
}

DECLARE_TEMPLATE_CLASS(Ref<Gamefield>);
// --- META ---

DECLARE_CLASS(Gamefield);
// --- END META ---
