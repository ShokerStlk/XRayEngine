#pragma once
#include "..\XrECore\stdafx.h"
#include "..\XrECore\Editor\device.h"
#include "..\XrECore\Editor\UI_MainCommand.h"
#include "..\XrECore\Editor\UI_ToolsCustom.h"
#include "..\XrECore\Editor\ui_main.h"
#include "..\XrECore\Editor\EditorPreferences.h"
#include "..\XrECore\Editor\render.h"
#include "..\XrECore\Editor\UIRenderForm.h"
#include "..\XrECore\Editor\ELog.h"
#include "UI\UITopBarForm.h"
#include "UI\UIMainMenuForm.h"
#include "UI\UILeftBarForm.h"
#include "UI\UILPropertiesFrom.h"
#include "UI\UIMainForm.h"
#include "Edit/UI_LevelMain.h"
#include "Edit/UI_LevelTools.h"

#include "motion.h"
#include "../XrECore/Editor/EditObject.h"
#include "../XrECore/Editor/EditMesh.h"
#include "../XrECore/Editor/D3DUtils.h"
#include "scene.h"
inline void not_implemented_low()
{
}
inline void not_implemented()
{
	return ;
	if (IsDebuggerPresent())
		DebugBreak();
	R_ASSERT(0);
}