#pragma once
#include "o2/Scene/Component.h"
#include "o2/Scene/ComponentRef.h"
#include "Gamefield/GamefieldBehaviour.h"

using namespace o2;

class ChipsFallGamefieldBehaviour : public GamefieldBehaviour
{
public:
	void Process(float dt) override;

	SERIALIZABLE(ChipsFallGamefieldBehaviour);

private:
};
