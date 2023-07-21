#include "o2/stdafx.h"
#include "Chipbehaviour.h"

#include "Gamefield/Cell/Cell.h"

void ChipBehaviour::SetChip(Chip* chip)
{
	mChip = chip;
}

DECLARE_TEMPLATE_CLASS(Ref<ChipBehaviour>);
// --- META ---

DECLARE_CLASS(ChipBehaviour);
// --- END META ---
