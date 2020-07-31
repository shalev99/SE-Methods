#pragma once
#include "Graphics.h"
#include "./Border/Border.h"
#include "Border/None.h"
#include "Border/Single.h"
#include "Border/Double.h"
#include <vector>

using namespace std;

class Control {
	protected:
		short left;
		short top;
		short width;
		short height;
		Border* border;
		Color textColor;
		Color backgroundColor;
		bool visible;
		static Control* focused;
		static bool lockEvent;
	
	public:
		Control();
		Control(short left, short top, short width, short height, Border* border, Color textColor, Color backgroundColor);
		static Control* getFocus() { return focused; }
		static void setFocus(Control& control);

		void setBorder(Border* newBorder);

		virtual short getLeft() { return left; }
		virtual void setLeft(short left) { this->left = left; }

		virtual short getTop() { return top; }
		virtual void setTop(short top) { this->top = top; }

		virtual short getWidth() { return width; }
		virtual void setWidth(short width) { this->width = width; }

		virtual short getHeight() { return height; }
		virtual void setHeight(short height) { this->height = height; }

		virtual Color getTextColor() { return textColor; }
		virtual void SetTextColor(Color textColor) { this->textColor = textColor; }

		virtual Color getBackgroundColor() { return backgroundColor; }
		virtual void SetBackgroundColor(Color backgroundColor) { this->backgroundColor = backgroundColor; }
		
		virtual bool getVisability() { return visible; }
		virtual void SetVisability(bool visibility) { this->visible = visibility; }

		virtual void draw(Graphics& g, int x, int y, size_t z);
		virtual void mousePressed(int x, int y, bool isLeft) {};
		virtual bool keyDown(int keyCode, char charecter) { return true; };
		virtual void getAllControls(vector<Control*>* controls) {};
		virtual bool canGetFocus() { return FALSE; };

		virtual int findFocusIndex() { return -1; };

		static void lock_events() { lockEvent = true; };
		static void enable_events() { lockEvent = false; };

		virtual void flipBgToWhite();
		virtual void flipBgToBlack();
		~Control();
};