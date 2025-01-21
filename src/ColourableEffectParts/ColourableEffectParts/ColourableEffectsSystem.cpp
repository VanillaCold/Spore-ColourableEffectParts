#include "stdafx.h"
#include "ColourableEffectsSystem.h"
#include <Spore/Swarm/cEffectsManager.h>
#include <Spore/Swarm/cEffectsWorld.h>
#include <Spore/Swarm/cVisualEffect.h>

ColourableEffectsSystem::ColourableEffectsSystem()
{
	sInstance = this;
}


ColourableEffectsSystem::~ColourableEffectsSystem()
{
}

void ColourableEffectsSystem::UpdateEffects()
{
	if (GameModeManager.GetActiveModeID() == GameModeIDs::kEditorMode)
	{
		if (!Editor.GetSkin())
		{
			return;
		}


		//Editor.mpEditorModel->mColors;
		vector<Vector3> skinColours;

		skinColours.push_back((Math::Vector3&)Editor.mpEditorModel->mColors[0]);
		skinColours.push_back((Math::Vector3&)Editor.mpEditorModel->mColors[1]);
		skinColours.push_back((Math::Vector3&)Editor.mpEditorModel->mColors[2]);

		for (auto rigblock : Editor.GetEditorModel()->mRigblocks)
		{
			auto model = (Graphics::cMWModelInternal*)rigblock->mpModel.get();
			
			vector<ResourceKey> modelEffectsList;
			App::Property::GetArrayKey(model->mpPropList.get(), 0x02A907B5, modelEffectsList);
			for (int i = 0; i < modelEffectsList.size(); i++)
			{
				SetEffectColour(model->mEffects[i].mpEffect, skinColours);
			}
		}

		if (auto animCrt = Editor.GetAnimWorld()->mpAnimWorld->GetCreatures()[0])
		{
			for each (auto model in animCrt->p_cid->field_2C0->models)
			{
				if (model.pModel != nullptr)
				{
					auto inModel = (Graphics::cMWModelInternal*)model.pModel.get();

					vector<ResourceKey> modelEffectsList;
					App::Property::GetArrayKey(inModel->mpPropList.get(), 0x02A907B5, modelEffectsList);
					for (int i = 0; i < modelEffectsList.size(); i++)
					{
						SetEffectColour(inModel->mEffects[i].mpEffect, skinColours);
					}
				}
			}
		}
	}
	else
	{
		Swarm::cEffectsWorld* world = (Swarm::cEffectsWorld*)EffectsManager.DefaultWorld();
		for each (IVisualEffectPtr effect in world->field_30)
		{
			auto offset = effect->GetSourceTransform().GetOffset();
			for (cCreatureBasePtr crt : Simulator::GetDataByCast<Simulator::cCreatureBase>())
			{
				auto radius = crt->GetBoundingRadius();
				const auto& origin = crt->GetPosition();
				auto newOffset = offset - origin;
				if (newOffset.Length() < radius)
				{
					vector<Vector3> skinColours;
					ResourceObjectPtr res;
					ResourceKey crtKey = crt->mSpeciesKey;
					if (ResourceManager.GetResource(crtKey, &res))
					{
						cEditorResourcePtr creatureResource = object_cast<Editors::cEditorResource>(res);
						if (creatureResource != nullptr)
						{
							skinColours.push_back((Math::Vector3&)creatureResource->mProperties.mSkinColor1);
							skinColours.push_back((Math::Vector3&)creatureResource->mProperties.mSkinColor2);
							skinColours.push_back((Math::Vector3&)creatureResource->mProperties.mSkinColor3);
						}
					}
					SetEffectColour(effect, skinColours);
					break;
				}
			}
		}
	}
}

void ColourableEffectsSystem::UpdateSingleCreature(Simulator::cCreatureBase* pCreature)
{
	
}

void ColourableEffectsSystem::SetEffectColour(IVisualEffectPtr effect, const vector<Vector3> colours)
{
	PropertyListPtr propList;
	auto visEffect = ((Swarm::cVisualEffect*)effect.get());
	SporeDebugPrint("0x%x", visEffect->mInstanceID);
	if (PropManager.GetPropertyList(visEffect->mInstanceID, id("ColourableEffectsData"), propList))
	{
		uint32_t channel;
		App::Property::GetUInt32(propList.get(), id("colourableEffectChannel"), channel);
		if (channel <= 2)
		{
			effect->SetVectorParams(Swarm::FloatParams::kParamColor, &colours[channel], 1);
		}
	}
	return;
}

ColourableEffectsSystem* ColourableEffectsSystem::Get()
{
	return sInstance;
}

ColourableEffectsSystem* ColourableEffectsSystem::sInstance = nullptr;

// For internal use, do not modify.
int ColourableEffectsSystem::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int ColourableEffectsSystem::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* ColourableEffectsSystem::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(ColourableEffectsSystem);
	return nullptr;
}
