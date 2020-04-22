#include "ParserMyMenu.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

using namespace menuentity;

int menuentity::sumReqCodeAttr(OBJECT_T object) {
    if ((object == OBJ_MENU) || (object == OBJ_WINDOW))
        return OP_BEGIN + OP_COLOR + OP_FRAME + OP_NAME + OP_END;
    if (object == OBJ_BUTTON)
        return OP_BEGIN + OP_COLOR + OP_FRAME + OP_NAME + OP_END + OP_HIGHLIGHT;
    return 0;
}


bool menuentity::errorInObjOrder(OBJECT_T prev, OBJECT_T next) {
    if ((prev < 0) || (next < 0))
        return 0;
    if ((int(next) - int(prev) == 1) || (prev == next))
        return 0;
    else
        return 1;
}


OBJECT_T menuentity::parseToObject(const string& line) {
    if (findSubstr(line, "//"))
        return OBJ_COMMENT;
    if (findSubstr(line, "menu."))
        return OBJ_MENU;
    if (findSubstr(line, "window."))
        return OBJ_WINDOW;
    if (findSubstr(line, "button."))
        return OBJ_BUTTON;
    return OBJ_NONE;
}


OPERATION_T menuentity::parseToOperation(const string& line) {
    if (findSubstr(line, "begin:"))
        return OP_BEGIN;
    if (findSubstr(line, "end"))
        return OP_END;
    if (findSubstr(line, "color"))
        return OP_COLOR;
    if (findSubstr(line, "highlight"))
        return OP_HIGHLIGHT;
    if (findSubstr(line, "name"))
        return OP_NAME;
    if (findSubstr(line, "frame"))
        return OP_FRAME;
    return OP_NONE;
}


bool findSubstr(const string& line, string substr) {
    return (line.find(substr) != string::npos);
}


string getBracketsPart(const string& line) {
    size_t pos1 = line.find_first_of('(');
    size_t pos2 = line.find_last_of(')');
    return line.substr(pos1 + 1, pos2 - pos1 - 1);
}


void replaceTrashToSpace(string& line) {
    string trash = "(),;";
    for (char chr : trash)
        replace(line.begin(), line.end(), chr, ' ');
}
