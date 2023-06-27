
void DrawBox(float X, float Y, float W, float H, const ImU32& color, int thickness)
{
	ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();

	Drawlist->AddRect(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), ImGui::GetColorU32(color), thickness);
	Drawlist->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();

	//black outlines
	Drawlist->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	Drawlist->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	Drawlist->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	Drawlist->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	Drawlist->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	Drawlist->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	Drawlist->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	Drawlist->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	Drawlist->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	Drawlist->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

void DrawFilledRect(int x, int y, int w, int h, ImU32 color)
{
	ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();
	Drawlist->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}
void DrawCorneredTriangle(int x, int y, int w, int h, ImColor color, int thickness) {
	ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();
	float half_w = w / 2;
	Drawlist->AddLine(ImVec2(x, y + h), ImVec2(x + half_w, y), color, thickness);
	Drawlist->AddLine(ImVec2(x + half_w, y), ImVec2(x + w, y + h), color, thickness);
	Drawlist->AddLine(ImVec2(x, y + h), ImVec2(x + w, y + h), color, thickness);
}
void DrawCorneredBox(int x, int y, int w, int h, ImColor color, int thickness) {

	ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();

	float line_w = (w / 3);
	float line_h = (h / 3);
	Drawlist->AddLine(ImVec2(x, y), ImVec2(x, y + line_h), color, thickness);
	Drawlist->AddLine(ImVec2(x, y), ImVec2(x + line_w, y), color, thickness);
	Drawlist->AddLine(ImVec2(x + w - line_w, y), ImVec2(x + w, y), color, thickness);
	Drawlist->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + line_h), color, thickness);
	Drawlist->AddLine(ImVec2(x, y + h - line_h), ImVec2(x, y + h), color, thickness);
	Drawlist->AddLine(ImVec2(x, y + h), ImVec2(x + line_w, y + h), color, thickness);
	Drawlist->AddLine(ImVec2(x + w - line_w, y + h), ImVec2(x + w, y + h), color, thickness);
	Drawlist->AddLine(ImVec2(x + w, y + h - line_h), ImVec2(x + w, y + h), color, thickness);
}

void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();
	Drawlist->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}
