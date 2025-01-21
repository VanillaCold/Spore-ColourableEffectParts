#include "stdafx.h"
#include "Detours.h"
#include "ColourableEffectsSystem.h"

Simulator::cCreatureAnimal* CreatureCreateDetour::DETOUR(const Vector3& pPosition, Simulator::cSpeciesProfile* pSpecies, int age = 1, Simulator::cHerd* pHerd = nullptr, bool bIsAvatar = false, bool unk = false)
{
	auto a = original_function(pPosition, pSpecies, age, pHerd, bIsAvatar, unk);
	ColourableEffectsSystem::Get()->mResetClock = 3;
	return a;
}

void CommitEditHistoryDetour::DETOUR(bool arg1, Editors::EditorStateEditHistory* pStateHistory = nullptr)
{
	original_function(this, arg1, pStateHistory);
	ColourableEffectsSystem::Get()->mResetClock = 3;
}

void UndoDetour::DETOUR(bool arg1, bool arg2)
{
	original_function(this, arg1, arg2);
	ColourableEffectsSystem::Get()->mResetClock = 3;
}

void SetEditorModeDetour::DETOUR(Editors::Mode mode, bool unk)
{
	original_function(this, mode, unk);
	ColourableEffectsSystem::Get()->mResetClock = 3;
}