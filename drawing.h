#pragma once
#include <Windows.h>
#include <string>
#include "dx_renderer.h"
#define PI 3.14159265358979323846f

void DrawLine(forceinline::dx_renderer* renderer, int x1, int y1, int x2, int y2, unsigned long color)
{
	//ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
	renderer->draw_line(x1, y1, x2, y2, color);
}


void draw_cornered_box(forceinline::dx_renderer* renderer, int x, int y, int w, int h, unsigned long color) {
	float line_w = (w / 3);
	float line_h = (h / 3);

	renderer->draw_line(x, y, x, y + line_h, color);
	renderer->draw_line(x, y, x + line_w, y, color);
	renderer->draw_line(x + w - line_w, y, x + w, y, color);
	renderer->draw_line(x + w, y, x + w, y + line_h, color);
	renderer->draw_line(x, y + h - line_h, x, y + h, color);
	renderer->draw_line(x, y + h, x + line_w, y + h, color);
	renderer->draw_line(x + w - line_w, y + h, x + w, y + h, color);
	renderer->draw_line(x + w, y + h - line_h, x + w, y + h, color);
}