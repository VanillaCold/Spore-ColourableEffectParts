#include "stdafx.h"
#include "UpdateAllEffectsCheat.h"
#include "ColourableEffectsSystem.h"

UpdateAllEffectsCheat::UpdateAllEffectsCheat()
{
}


UpdateAllEffectsCheat::~UpdateAllEffectsCheat()
{
}


void UpdateAllEffectsCheat::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
	ColourableEffectsSystem::Get()->UpdateEffects();
}

const char* UpdateAllEffectsCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "UpdateAllEffectsCheat: Elaborate description of what this cheat does.";
	}
}
