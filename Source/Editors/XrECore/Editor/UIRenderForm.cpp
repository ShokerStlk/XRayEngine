#include "stdafx.h"
#include "UIRenderForm.h"
#include "ui_main.h"
UIRenderForm::UIRenderForm()
{
	m_mouse_down = false;
	m_mouse_move = false;
}

UIRenderForm::~UIRenderForm()
{

}

void UIRenderForm::Draw()
{

	ImGui::Begin("Render");
	if (UI && UI->RT->pSurface)
	{
		int ShiftState = ssNone;

		if (ImGui::GetIO().KeyShift)ShiftState |= ssShift;
		if (ImGui::GetIO().KeyCtrl)ShiftState |= ssCtrl;
		if (ImGui::GetIO().KeyAlt)ShiftState |= ssAlt;


		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))ShiftState |= ssLeft;
		if (ImGui::IsMouseDown(ImGuiMouseButton_Right))ShiftState |= ssRight;
		//VERIFY(!(ShiftState & ssLeft && ShiftState & ssRight));
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
		ImVec2 canvas_size = ImGui::GetContentRegionAvail();
		if (canvas_size.x < 64)canvas_size.x = 64;
		if (canvas_size.y < 64)canvas_size.y = 64;
		if ((ImGui::GetIO().MousePos.x >= canvas_pos.x && ImGui::GetIO().MousePos.y >= canvas_pos.y) &&
			(ImGui::GetIO().MousePos.x <= (canvas_pos.x + canvas_size.x) && ImGui::GetIO().MousePos.y <= (canvas_pos.y + canvas_size.y)))
		{
			if (ImGui::IsWindowFocused())
			{

				if ((ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Right)) && !m_mouse_down)
				{
					UI->MousePress(TShiftState(ShiftState), ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
					m_mouse_down = true;
				}

				else  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) || ImGui::IsMouseReleased(ImGuiMouseButton_Right))
				{
					UI->MouseRelease(TShiftState(ShiftState), ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
					m_mouse_down = false;
					m_mouse_move = false;
				}
				else
				{
					UI->MouseMove(TShiftState(ShiftState), ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
					m_mouse_move = true;
				}
			}
				
			m_mouse_position.set(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
		}
		else  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) || ImGui::IsMouseReleased(ImGuiMouseButton_Right))
		{
			UI->MouseRelease(TShiftState(ShiftState), ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
			m_mouse_down = false;
		}
		
		UI->RTSize.set(canvas_size.x, canvas_size.y);
		if (canvas_size.x < 50.0f) canvas_size.x = 50.0f;
		if (canvas_size.y < 50.0f) canvas_size.y = 50.0f;
		ImGui::InvisibleButton("canvas", canvas_size);
		if (!m_OnContextMenu.empty()&& !m_mouse_move&& !(ShiftState& ssShift))
		{
			if (ImGui::BeginPopupContextItem("Menu"))
			{
				m_OnContextMenu();
				ImGui::EndPopup();
			}
		}
		
		draw_list->AddImage(UI->RT->pSurface, canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y));

	}
	ImGui::End();
}
