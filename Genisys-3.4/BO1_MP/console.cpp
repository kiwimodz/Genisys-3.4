#include<Includes.h>

void Console::draw() {
	float x, w, ys, h; x = 14; ys = 625; w = 380; h = 360;//stack
	float start_w = 20, start_h = 20;
	//DrawStaticOutline(x, ys, w, h, menu.skin, 2.1);//outline
	//DrawShaderUI(x, ys, w, h, 0, color(0, 0, 0, 200), white, align_left);//back
	for (int i = 0; i < CONSOLE_MAX_ITEMS; i++) {
		consoleitem item = items[i];
		if (*item.text == 0) continue;

		if (items[i].colour.a > 0) {
			String pszfont = R_GetFontPathFromName(hash("extraSmallFont"));
			int text_w = R_TextWidth(item.text, pszfont, 0.93 * 1.3);
			int text_h = R_TextHeight(pszfont, 0.93) + start_h;
			DrawTextUI(item.text, x + (start_w / 2), ys + (local->consoley[i] + 10) - (start_h / 4) + text_h + 2, 0, 0.93, "extraSmallFont", item.colour, align_left);
		}

		if (items[i].time > 0)
			items[i].time--;

		if (items[i].time <= 0) {
			items[i].colour.a -= 0.001;

			if (items[i].colour.a <= 0)
				arrange(i);
		}
	}
}

void Console::arrange(int index) {
	consoleitem temp[CONSOLE_MAX_ITEMS];// = consoleitem();
	for (uint32_t i = 0, spot = 0; i < CONSOLE_MAX_ITEMS; i++) {
		if (i == index) {
			continue;
		} else {
			temp[i] = items[spot++];
		}
	}
	for (int i = 0; i < CONSOLE_MAX_ITEMS; i++) {
		items[i] = temp[i];
	}
}

void Console::write(const char* text, color&& colour, color&& colour1, color&& colour2, color&& colour3) {
	strcpy(items[CONSOLE_DEFAULT_ITEM].text, text);
	items[CONSOLE_DEFAULT_ITEM].colour = colour;
	items[CONSOLE_DEFAULT_ITEM].time = 255;
	arrange(CONSOLE_DEFAULT_ITEM);
}
