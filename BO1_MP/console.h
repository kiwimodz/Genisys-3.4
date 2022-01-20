#ifndef _CONSOLE_H
#define _CONSOLE_H

#define CONSOLE_DEFAULT_ITEM 0
#define CONSOLE_MAX_ITEMS 10
#define CONSOLE_TEXT_MAX_LENGTH 100

class consoleitem
{
public:
	char text[CONSOLE_TEXT_MAX_LENGTH];
	color colour;
	color color1;
	color color2;
	color color3;
	char time;
};
class Console
{
public:
	consoleitem items[CONSOLE_MAX_ITEMS];
public:
	color animationA;
	color animationB;
public:
	void draw();
	void write(const char* text, color&& colour, color&& colour1, color&& colour2, color&& colour3);
	void arrange(int index);
};

extern Console console;

#endif