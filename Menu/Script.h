#pragma once

#include "MyMenu.h"
#include "ParserMyMenu.h"

#include <vector>
#include <string>
#include <memory>

using namespace std;
using namespace menuentity;


class ScriptLine {

    OBJECT_T object;
    OPERATION_T operation;
    ERROR_T error;

    vector<int> numbers;
    string name;

public:

    ScriptLine(const string& line, OBJECT_T curObject);


    OBJECT_T GetObject() const { return object; }


    OPERATION_T GetOperation() const { return operation; }


    ERROR_T GetError() const { return error; }


    string GetName() const { return name; }


    vector<int> GetNumbers() const { return numbers; }


    void SetError(ERROR_T err) { error = err; }
};


class Script {

    vector<shared_ptr<ScriptLine>> script;
    bool isError;

public:

    Script(const string& fileName);


    vector<shared_ptr<const ScriptLine>> GetScript() const;


    shared_ptr<const ScriptLine> FindMatchFromBeginToEnd(OBJECT_T object, OPERATION_T operation, int posStart) const;


    vector<int> GetIndexesLinesWObjOp(OBJECT_T object, OPERATION_T operation) const;


    vector<int> GetIndexesErrorLines() const;


    shared_ptr<MyMenu> InitMyMenu() const;
};