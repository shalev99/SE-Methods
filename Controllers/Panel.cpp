#include "Panel.h"
#include <iostream>

void Panel::updateFocusedControler(Control* controler) {
    if(getFocus() == nullptr && controler->canGetFocus()) {
        setFocus(*controler);
    }
}

void Panel::addToPanel(Control* controler) {
    if (controler != nullptr)
        Controlers.push_back(controler);
        try {
            updateFocusedControler(controler); 
        }
        catch(...) {}
}

void Panel::draw(Graphics& g, int x, int y, size_t z) {
    int controlerX, controlerY;
    if (!z){
        Control::draw(g, x, y, z);
        for (int index = 0; Controlers.size() > index; index++) {
            controlerX = Controlers[index]->getLeft();
            controlerY = Controlers[index]->getTop();
            g.setBackground(Controlers[index]->getBackgroundColor());
            g.setForeground(Controlers[index]->getTextColor());
            Controlers[index]->draw(g, controlerX + x + 1, controlerY + y + 1, z);
        }
    }
}

Panel::~Panel(){
    while (!Controlers.empty()) {
        Controlers.pop_back();
    }
}

int Panel::findFocusIndex() {
    Control* tempFocus = getFocus();
    if (getFocus() != nullptr) {
        for (int i = 0; i < Controlers.size(); i++) {
            if (Controlers[i] == tempFocus) {
                focusedControlCell = i;
                return i;
            }
            else if(Controlers[i]->findFocusIndex() != -1) {
                focusedControlCell = i;
                return i;
            }
        }
    }
    focusedControlCell = -1;
    return -1;
}

void Panel::mousePressed(int x, int y, bool isLeft) {    
    if(isInside(x,y, getLeft(), getTop(), getWidth(), getHeight())) {
        if (getVisability()) {
            for (int i = 0; i < Controlers.size(); i++) {
                Controlers[i]->mousePressed(x,y,isLeft);
            }
        }
         else if (findFocusIndex() != -1) {
             Controlers[focusedControlCell]->mousePressed(x, y, isLeft);
         }
    }
}

bool Panel::keyDown(int keyCode, char character) {
    if (findFocusIndex() != -1)
        Controlers[focusedControlCell]->keyDown(keyCode, character);
    return true;
}

void Panel::getAllControls(vector<Control*>* controls) {
    for(int i = 0; i < this->Controlers.size(); ++i) {
        controls->push_back(this->Controlers[i]);
        this->Controlers[i]->getAllControls(controls);
    }
}

Control * Panel::getFirstControl()
	{
	if (Controlers.size() > 0) {
		if (Controlers[0]->canGetFocus()) {
			return &(*Controlers[0]);
		}
	}
	return NULL;
}