#include "stdafx.h"
#include "ELog.h"
#include "UILogForm.h"

#define MSG_ERROR 	0x00C4C4FF
#define MSG_INFO  	0x00E6FFE7
#define MSG_CONF 	0x00FFE6E7
#define MSG_DEF  	0x00E8E8E8
bool UILogForm::bAutoScroll = true;
xr_vector<xr_string>* UILogForm::List = nullptr;
extern bool bAllowLogCommands;
void UILogForm::AddMessage(TMsgDlgType mt, const xr_string& msg)
{
	xr_string M;
	for (int i = 0; i < msg.size(); i++)
	{
		if (msg[i] == '\r') continue;
		if (msg[i] == '\n') M += " ";
		else M += msg[i];
	}
	GetList()->push_back(M);
}

void UILogForm::AddDlgMessage(TMsgDlgType mt, const xr_string& msg)
{
	GetList()->push_back(msg);
}

void UILogForm::Show()
{
	bAllowLogCommands = true;
}

void UILogForm::Hide()
{
	bAllowLogCommands = false;
}

void UILogForm::Update()
{
	if (bAllowLogCommands)
	{
		if (!ImGui::Begin("Log", &bAllowLogCommands))
		{
			ImGui::End();
			return;
		}
		if (ImGui::Button("Clear")) 
		{
			GetList()->clear();
		}ImGui::SameLine();
		if (ImGui::Button("Flush")) 
		{
			FlushLog();
		}ImGui::SameLine();
		ImGui::Checkbox("Auto Scroll", &bAutoScroll);
		ImGui::Spacing();
		if (ImGui::BeginChild("Log",ImVec2(0,0),true))
		{
			for (int i = 0; i < GetList()->size(); i++)
			{
				ImGui::Text(GetList()->at(i).c_str());
			}
			if (bAutoScroll)ImGui::SetScrollHereY();
			
		}
		ImGui::EndChild();
		ImGui::End();
	}
}

void UILogForm::Destroy()
{
	xr_delete(List);
}

xr_vector<xr_string>* UILogForm::GetList()
{
	if (!List)List = xr_new<xr_vector<xr_string>>();
	return List;
}
