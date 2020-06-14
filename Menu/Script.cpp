#include "Script.h"

#include <algorithm>
#include <sstream>
#include <fstream>
#include <iterator>
#include <stack>


struct objectWSumAttr {
    OBJECT_T object;
    int sumCodeAttributes;
};


ScriptLine::ScriptLine(const string& line, OBJECT_T curObject) {
    error = ERROR_OK;
    object = parseToObject(line);
    operation = parseToOperation(line);

    if (object == OBJ_COMMENT)
        operation = OP_NONE;
    if ((object != OBJ_COMMENT) && (operation == OP_NONE))
        error = ERROR_SYNTAX;
    if (object == OBJ_NONE)
        object = curObject;

    if (object == OBJ_COMMENT) {
        name = line.substr(2, line.size() - 2);
    }
    string insideBrackets = getBracketsPart(line);
    if (operation == OP_NAME) {
        name = insideBrackets;
    }
    if ((operation == OP_COLOR) || (operation == OP_HIGHLIGHT) || (operation == OP_FRAME)) {
        replaceTrashToSpace(insideBrackets);
        istringstream streamLine(insideBrackets);
        copy(istream_iterator<int>(streamLine), {}, back_inserter(numbers));
    }
}


Script::Script(const string& fileName) {
    string filename = fileName;
    ifstream file(filename);
    string line;
    stack<objectWSumAttr> stackObjects;
    stackObjects.push({ OBJ_NONE, 0 });

    while (getline(file, line)) {
        if ((line.empty()) || (line.find_first_not_of('\t') == string::npos))
            continue;
        ScriptLine curScript(line, stackObjects.top().object);

        if (curScript.GetOperation() == OP_BEGIN) {
            stackObjects.push({ curScript.GetObject(), 0 });
        }

        stackObjects.top().sumCodeAttributes += curScript.GetOperation();
        script.push_back(shared_ptr<ScriptLine>(new ScriptLine(curScript)));

        if (curScript.GetOperation() == OP_END) {
            if (stackObjects.top().sumCodeAttributes != sumReqCodeAttr(stackObjects.top().object))
                curScript.SetError(ERROR_ATTRIBUTES);
            stackObjects.pop();
        }
        if (errorInObjOrder(stackObjects.top().object, curScript.GetObject()))
            curScript.SetError(ERROR_ORDER);

        if (curScript.GetError() != ERROR_OK)
            isError = 1;
    }
    if (!((stackObjects.size() == 1) && (stackObjects.top().object == OBJ_NONE))) {
        script[0]->SetError(ERROR_NOSCRIPT);
        isError = 1;
    }
}


vector<shared_ptr<const ScriptLine>> Script::GetScript() const {
    vector<shared_ptr<const ScriptLine>> res(script.begin(), script.end());
    return res;
}


shared_ptr<const ScriptLine> Script::FindMatchFromBeginToEnd(OBJECT_T object, OPERATION_T operation, int posStart) const { //needs to be refactored
    int i = posStart;
    if (((script[i]->GetObject() == object) && (script[i]->GetOperation() == OP_BEGIN)) == false)
        return nullptr;
    else
        i++;

    while (((script[i]->GetObject() == object) && (script[i]->GetOperation() == operation)) == false) {
        i++;
        if (i == script.size())
            return nullptr;
        if ((script[i]->GetObject() == object) && (script[i]->GetOperation() == OP_END))
            return nullptr;
    }
    return script[i];
}


vector<int> Script::GetIndexesLinesWObjOp(OBJECT_T object, OPERATION_T operation) const {
    vector<int> res;
    int i = 0;
    for (auto& curScript : script) {
        if (((curScript->GetObject() == object) || (object == OBJ_NONE)) && (((curScript->GetOperation() == operation) || (operation == OP_NONE))))
            res.push_back(i);
        i++;
    }
    return res;
}


vector<int> Script::GetIndexesErrorLines() const {
    vector<int> res;
    int i = 0;
    for (auto& curScrupt : script) {
        if (curScrupt->GetError() != ERROR_OK)
            res.push_back(i);
    }
    return res;
}


shared_ptr<MyMenu> Script::InitMyMenu() const {
    shared_ptr<MyMenu> myMyMenu = nullptr;
    if (isError)
        return myMyMenu;
    vector<int> indexesOfBegin = GetIndexesLinesWObjOp(OBJ_NONE, OP_BEGIN);
    for (auto& i : indexesOfBegin) {
        OBJECT_T curObject = script[i]->GetObject();
        switch (curObject) {
        case OBJ_MENU:
            myMyMenu = shared_ptr<MyMenu>(new MyMenu(MyRectangle(FindMatchFromBeginToEnd(curObject, OP_FRAME, i)->GetNumbers()), FindMatchFromBeginToEnd(curObject, OP_NAME, i)->GetName(),
                MyColor(FindMatchFromBeginToEnd(curObject, OP_COLOR, i)->GetNumbers())));
            break;
        case OBJ_WINDOW:
            myMyMenu->CreateMyWindow(MyRectangle(FindMatchFromBeginToEnd(curObject, OP_FRAME, i)->GetNumbers()), FindMatchFromBeginToEnd(curObject, OP_NAME, i)->GetName(),
                MyColor(FindMatchFromBeginToEnd(curObject, OP_COLOR, i)->GetNumbers()));
            break;
        case OBJ_BUTTON:
            myMyMenu->GetIthMutableWindow(-1)->CreateMyButton(MyRectangle(FindMatchFromBeginToEnd(curObject, OP_FRAME, i)->GetNumbers()), FindMatchFromBeginToEnd(curObject, OP_NAME, i)->GetName(),
                MyColor(FindMatchFromBeginToEnd(curObject, OP_COLOR, i)->GetNumbers()), MyColor(FindMatchFromBeginToEnd(curObject, OP_HIGHLIGHT, i)->GetNumbers()));
            break;
        }
    }
    return myMyMenu;
}