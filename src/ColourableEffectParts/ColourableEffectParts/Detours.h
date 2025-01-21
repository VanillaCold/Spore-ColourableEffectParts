#pragma once
#include "stdafx.h"
#include <Spore/BasicIncludes.h>

//Simulator::cCreatureAnimal::Create()
//const Vector3& pPosition, cSpeciesProfile* pSpecies, int age = 1, cHerd* pHerd = nullptr, bool bIsAvatar = false, bool = false
static_detour(CreatureCreateDetour, Simulator::cCreatureAnimal* (const Vector3&, Simulator::cSpeciesProfile*, int, Simulator::cHerd*, bool, bool)) {};

//bool arg1, EditorStateEditHistory* pStateHistory = nullptr
//CommitEditHistory
member_detour(CommitEditHistoryDetour, Editors::cEditor, void(bool, Editors::EditorStateEditHistory*)) {};

member_detour(UndoDetour, Editors::cEditor, void(bool, bool)) {};

//Editors::cEditor::OnEnter
member_detour(SetEditorModeDetour, Editors::cEditor, void(Editors::Mode mode, bool unk)) {};
