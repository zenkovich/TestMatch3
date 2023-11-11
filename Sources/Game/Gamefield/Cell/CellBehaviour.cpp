#include "o2/stdafx.h"
#include "CellBehaviour.h"

#include "Gamefield/Cell/Cell.h"


void CellBehaviour::SetCell(Cell* cell)
{
    mCell = cell;
}


DECLARE_TEMPLATE_CLASS(Ref<CellBehaviour>);
// --- META ---

DECLARE_CLASS(CellBehaviour, CellBehaviour);
// --- END META ---
