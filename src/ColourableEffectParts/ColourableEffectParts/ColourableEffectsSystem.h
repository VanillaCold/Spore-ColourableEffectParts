#pragma once

#include <Spore\BasicIncludes.h>

#define ColourableEffectsSystemPtr intrusive_ptr<ColourableEffectsSystem>

class ColourableEffectsSystem 
	: public Object
	, public DefaultRefCounted
{
private:
	static ColourableEffectsSystem* sInstance;
public:
	static const uint32_t TYPE = id("ColourableEffectsSystem");
	
	ColourableEffectsSystem();
	~ColourableEffectsSystem();

	void UpdateEffects();
	void UpdateSingleCreature(Simulator::cCreatureBase* pCreature);
	void SetEffectColour(IVisualEffectPtr effect, const vector<Vector3> colours);

	static ColourableEffectsSystem* Get();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
