#pragma once

#include <Spore\BasicIncludes.h>

class UpdateAllEffectsCheat 
	: public ArgScript::ICommand
{
public:
	UpdateAllEffectsCheat();
	~UpdateAllEffectsCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;
};

