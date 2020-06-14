#pragma once

#include <string>

using namespace std;


namespace menuentity {

    enum OBJECT_T {
        OBJ_NONE = -2,
        OBJ_COMMENT = -1,
        OBJ_MENU = 1,
        OBJ_WINDOW = 2,
        OBJ_BUTTON = 3,
    };


    enum OPERATION_T {
        OP_NONE = 0,
        OP_BEGIN = 1,
        OP_END = 11,
        OP_COLOR = 101,
        OP_NAME = 10001,
        OP_FRAME = 100001,
        OP_HIGHLIGHT = 1000001
    };


    enum ERROR_T {
        ERROR_OK,
        ERROR_SYNTAX,
        ERROR_ORDER,
        ERROR_NOSCRIPT,
        ERROR_ATTRIBUTES
    };


    int sumReqCodeAttr(OBJECT_T object);

    bool errorInObjOrder(OBJECT_T prev, OBJECT_T next);

    OBJECT_T parseToObject(const string& line);

    OPERATION_T parseToOperation(const string& line);
}


bool findSubstr(const string& line, string substr);

string getBracketsPart(const string& line);

void replaceTrashToSpace(string& line);