#include "RadioBox.h"
#include <fstream>

RadioBox::RadioBox(int left, int top, vector<string> options_lbl) : Panel(left, top, 20, 10, new Single, Color::White, Color::Red),
left(left),top(top),options_lbl(options_lbl), focus(false)
{
    position_t pos = {0,0};
    for (std::vector<string>::iterator lbl = options_lbl.begin() ; lbl != options_lbl.end(); ++lbl)
    {
        options.push_back(Button(*lbl));
    }
    for(int i=0; i < options.size(); i++ )
    {
        options[i].setTop(i);
        options[i].addListener(this);
        this->addToPanel(&options[i]);
        pos.x = getLeft();
        pos.y = getTop()+i+1;
        options_pos.push_back(pos);
    }
}

void RadioBox::draw(Graphics& g, int x, int y, size_t z) {

    if (this == focused && cursor == -1)
        focus = true;
    if (focus && cursor == -1)
        cursor++;

    if (cursor >= 0)
        SelectItemCursor(cursor);

    if (selectedItem >= 0)
        g.write(x - 2, y + selectedItem, "X");

    if (!z)
        Panel::draw(g, x - 1, y - 1, z);
}

bool RadioBox::keyDown(int keyCode, char character)
{
     SelectItemCursor(cursor);
    if (cursor >= 0)
    {
        if (keyCode == VK_UP || keyCode == VK_NUMPAD8)
            if (cursor == 0)
                cursor = cursor == options_pos.size() - 1;

            else
                cursor--;

        if (keyCode == VK_TAB || keyCode == VK_DOWN || keyCode == VK_NUMPAD2)

            if (cursor == options_pos.size()-1)
            {
                cursor = -1;
                focus = false;
                return true;
            }
            else
                cursor++;

        if (keyCode == VK_SPACE || keyCode == VK_RETURN)
        {
            selectedItem = cursor;
        }

        return false;
    }
    return true;
}

void RadioBox::mousePressed(int x, int y, bool isLeft)
{

    if (x >= options_pos[0].x && x <= options_pos[options_pos.size() - 1].x + 20 && y >= options_pos[0].y && y <= options_pos[options_pos.size() - 1].y && isLeft == true)
    {

        if (this != focused || focus == false)
        {
            focus = true;
            focused = this;
        }
        else
            ClearItemCursor();
        cursor = y - options_pos[0].y;
        selectedItem = cursor;
    }
    else {
        if (x >= left && x <= left + width && y >= top && y <= top + width || focus == false)
        {
            if (cursor > -1)
                SelectItemCursor(cursor);
        }
        else
            if (focus == true)
            {
                focus = false;
                SelectItemCursor(cursor);
                cursor = -1;
                focused = NULL;
            }
    }
}

bool RadioBox::SelectItemCursor(int index) {
    Color tempColor = options[index].getBackgroundColor();
    options[index].SetBackgroundColor(options[index].getTextColor());
    options[index].SetTextColor(tempColor);
    this->updateFocusedControler(this);
    cursor=index;
    return true;
}

bool RadioBox::ClearItemCursor() {
    Color tempColor = options[cursor].getBackgroundColor();
    options[cursor].SetBackgroundColor(options[cursor].getTextColor());
    options[cursor].SetTextColor(tempColor);
    this->updateFocusedControler(this);
    cursor = -1;
    return true;
}

void RadioBox::activateListener(int x, int y)
{
    ofstream myfile;
    myfile.open ("activateListener.txt", std::ios_base::app);
    for(int i=0; i < options_pos.size(); i++){
        if(x >= options_pos[i].x && x <= options_pos[i].x + 10 && y >= options_pos[i].y)
        {
            if(cursor>=0)
            ClearItemCursor();
            SelectItemCursor(i);
        }
    }
    myfile.close();
}

bool RadioBox::SelectedItem(int index)
{
    if (index >= 0 && index <= options_pos.size())
    { 
    selectedItem = index;
    return true;
}
    return false;
}

bool RadioBox::ClearSelection(){
    selectedItem = -1;
    return true;
}