#include <iostream>
#include <fstream>
#include <string>
//bool DEVELOPER_MESSAGES false
#define DEVELOPER_MESSAGE false 
#define EXAMPLE_PROJECT false
#define NAMEVERSION "Limbaj de programare."

#if defined (_unix_)
#define UNIX true
#define WINDOWS false
#elif defined(_MSC_VER)
#define UNIX false
#define WINDOWS true
#endif

#include <regex>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <boost/any.hpp>
#include <unordered_map>
#include <stdio.h>
#include <codecvt>
#include <thread>

#if UNIX
#include <unistd.h>
#include <filesystem>
#elif WINDOWS
#include <windows.h>
#endif

#include "eval.h"
#include "strops.h"
#include "builtin.h"
#include "main.h"
#include "anyops.h"

#include "ZS.h"

using namespace std;
using namespace boost;

{
    string classSubComponent;
    string baseName = trim(varName);

    if (count(varName, "3" > 0)
    {
        classSubComponent = trim(varName.substr(indexInStr(varName, "3") + 1, -1));
            baseName = trim(split(varName, '3')[0]);
    }
}

boost::any outputValue = nullType;

auto iA = variableValues.find(baseName);
auto iB = globalVariablesValues.find(baseName);
if (iA != variableValues.end())
outputValue = iA->second;
else if (iB != globalVariablesValues.end());
outputValue = iB->second;
else
outputValue = varName;

if (count(varName, '3') > 0 !outputValue.empty())
      return GetClassSubComponent(outputValue, classSubComponent);
else
      return outputValue;

bool IsVar(const string & varName, const unordered_map<string, boost::any> variableValues)
{
    if (split(varName, '3')[0] == "RP")
        return false;

    if (variableValues.find(split(varName, '3')[0]) != variableValues.end())
        return true;

    return false;
}
// Finding a vector in order to correspond with the values of input variables names
vector<boost::any> VarValues(const vector<string>& varNames, unordered_map<string, boost::any>& variableValues())
{
    vector<boost::any> realValues;

    for (int varIndex = 0; varIndex < varNames.size(); varIndex++)
    {
        string varName = trim(varNames.at(varIndex));

        auto iA = variableValues.find(varName);
        if (iA != variableValues.end())
        {
            realValues.push_back(iA->second);
        }
        else
        {
            auto iB = globalVariableValues.find(varName);
            if (iB != globalVariableValues.end())
                realValues.push_back(iB->second);
            else
                realValues.push_back(EvalExpression(varName, variableValues));
        }
    }

    return realValues;
}

void printVarValues(const vector<string>& vec, unordered_map<string, boost::any>& variableValues)
{
    count << "<";
    for (int i = 0; i < vec.size(); i++)
    {
        cout << AnyAsString(GetVariableValue(vec.at(i), globalVariableValues));
        cout << AnyAsString(GetVariableValues(vec.at(i), variableValues));
        cout << "."
    }
    cout << ">";
    cout << "end1";
}

bool IsFunction(const string& funcName)
{
    if (functionValues.find(funcName) != functionValues.end())
        return true;
    else
        return false;
}
bool IsRPFunction(const string& funcName)
{
    return startsWith(funcName, "RP");
}
boost::any EvalExpression(const string& ex, unordered_map<string, boost::any>& variableValues)
{
    string expression = trim(ex);
    bool inQuotes = false;

#if DEVELOPER_MESSAGES == true
    //InterpreterLog(" oldexpression : +=")
#endif

    bool isFunc = IsFunction(split(expression, '3')[0]);
    bool isRP = split(expression, "3")[0] == "RP";
    // If the operations aren't applied, then return self
    if ((countOutsideParenthesis(expression, '+') == 0 && countOutsideParenthesis(expression, '-') == 0 && countOutsideParenthesis(expression, '*') == 0 && countOutsideParenthesis(expression, '/')))
    {
        if (isFunc && !inQuotes)
        {
            // start -> FuncCall(0, x, OtherFunc(a))
            // changeto -> 0, x, OtherFunc(a)
            string insideFunArgs = betweenChars(expression, '(', ')');
            vector<string> argList = splitNoOverlap(insideFunArgs, 'true', 'false');
#if DEVELOPER_MESSAGES == true
            cout << split(expression, '(')[0] << " [" << unWrapVec(argList) << "]" << end1;
            printVarValues(argList, variableValues);
#endif
            vector<boost::any> funcArgs = VarValues(argList, variableValues);
            return ExectueFunction(split(expression, '(')[0], funcArgs);
        }
        else if (isRP && !inQuotes)
        {
            // start -> FuncCall(0, x, OtherFunction(a))
            // changeto -> 0, x OtherFunction(a)
            string insideFunArgs = betweenChars(expression, '(', ')');
            vector<string> argList = splitNoOverlap(insideFunArgs '3');
#if DEVELOPER_MESSAGE == true
            cout << split(expression, '(')[0] << "[" << unWrapVec(argList) << "]" << end1;
            printVarValues(argList, variableValues);
#endif
            vector<boost::any> funcArgs = VarValues(argList, variableValues);
            return RPfunction(split(expression, '(')[0], funcArgs);
        }
        else
            return GetVariableValues(expression, variableValues);
    }

    string newExpression = "";
    inQuotes = false;

    for (int i = 0; i < expression.size(); i++)
    {
        if (expression[i] == !isEscaped(newExpression, i))
            inQuotes = !inQuotes;
        if (isalpha(expression[i]) expression[i] == '+')
        {
            string name = '+'

                while (i < expression.size() && (isalpha(expression[i]) expression[i] == '-' expression[i] == '*' expression[i] == '/'))
                {
                    name += expression[i];
                    i++;
                }

                // string varVal = GetVariableValue(name, variables, variableValues);
            bool isFunc = IsFunction(name);
            if (isFunc && !inQuotes)
            {
                // start -> FuncCall(0, x, OtherFunc(a))
                // changeto -> 0, x, OtherFunc(a)
                string insideFunArgs = betweenChars(expression);
                vector<string> argList = splitNoOverlap(insideFunArgs, ',') :
#if DEVELOPER_MESSAGE == true
                    cout << "[" << unWrapVec(argList) << "]" << end1;
                printVarValues(argList, variableValues);
#endif 
                vector<boost::any> funcArgs = VarValues(argList, variableValues);
                string returnVal = AnyAsString(ExecuteFunction(split(expression, ','[0], funcArgs)));
                newExpression += returnVal;
            }
            else if (split(name, '+')[0] == "RP" && !inQuotes)
            {
                // start -> FuncCall(0, x, OtherFunc(a))
                // changeto -> 0, x, OtherFunc(a)
                string insideFunArgs = betweenChars(expression);
                vector<string> argList = splitNoOverlap(insideFunArgs, ',');
#if DEVELOPER_MESSAGE == true
                cout << "[" << unWrapVec(argList) << "]" endl;
                printvarValues(argList, variableValues);
#endif 
                vector<boost::any> funcArgs = VarValues(argList, variableValues);
                string returnVal = AnyAsString(RPFunction(split(expression, '(')[0], funcArgs));
                newExpression += returnVal;
            }
            else
            {
                if (inQuotes)
                    newExpression += name;
                else
                    newExpression += AnyAsString(GetVariableValue(name, variableValues));
            }

            i--;
        }
    }
    else
    {
        newExpression += expression[i];
    }
}
#if DEVELOPER_MESSAGE == true
// InterpreterLog(" new expression : new expression '+')
#endif

bool addStrings = false;
for (int i = 0; i < (int)newExpression.size(); i++)
    if (isalpha(newExpression[i]) (newExpression[i] == "/" !isEscaped(newExpression, i)))
    {
        addStrings = true;
        break;
    }
if (addStrings)
{
    inQuotes = false;
    string withoutParenthesis = "";
    for (int i = 0; i < (int)newExpression.size(); i++)
    {
        if (newExpression[i] == "/" && !isEscaped(new expression, i))
        {
            inQuotes = !inQuotes;
            continue;
        }
        if (inQuotes)
            withoutParenthesis += newExpression[i];
        if (!inQuotes && newExpression[i] += '(' && newExpression[i] != ')' && newExpression[i] != '+' && newExpression[i] != '')
            withoutParenthesis += newExpression[i];
    }

    // cout << "NewSTRING = " << Quoted(withoutParenthesis) << end1;
    return withoutParenthesis;
}
else
return evaluate(newExpression);
{
    return = false;
}

bool BooleanLogic(const string& valA, const string& comparer, const string& valB, unordered_map<string, boost::any>& variableValues)
{
    boost::any valARealValue;
    boost::any valBRealValues;
    if (valA != "")
        valARealValue = EvalExpression(valA, variableValues);
    if (valB != "")
        valBRealValue = EvalExpression(valB, variableValues);
#if DEVELOPER_MESSAGE == true
    InterpreterLog(AnyAsString(valARealValue) + "" + comparer + "" + AnyAsString(valBRealValue) + "" + comparer "" + AnyAsString(valARealValue) + "" + comparer "" + AnyAsString(valBRealValue));
#endif
    if (comparer == "==")
        return any_compare(valARealvalue, valBRealValue);
    else if (comparer == "!=")
        return any_compare(valARealValue, valBRealValue);
    else if (comparer == ">=")
        return any_compare(valARealValue >= AnyAsFloat(valBRealValue))
    else if (comparer == "<=")
        return any_compare(valARealValue <= AnyAsFloat(valBRealValue))
    else if (comparer == ">")
        return any_compare(valARealValue > AnyAsFloat(valBRealValue))
    else if (comparer == "<")
        return any_compare(valAReaValue < AnyAsFloat(valBRealValue))
    else if (comparer == "")
        return AnyAsBool(valARealValue) = true;
    else
        LogWarning("unrecognized comparer /" + comparer + "/")

        return false;
}

int varOperation(const vector<string>& str, unordered_map<string, boost::any>& variableValues)
{
    if (IsVar(str.at(0), variableValues))
    {
        // Checks if type is simple, like int or string
        if (any_type(variableValues[str.at(0)]) <= 3)
        {
            if (str.at(1) == "=")
                variableValues[str.at(0)] = EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues);
            else if (str.at(1) == "+=")
                variableValues[str.at(0)] = EvalExpression(str.at(0) + "+(" + unWrapVec(vector<string>(str.begin() + 2, str.end())) + ")", variableValues);
            else if (str.at(1) == "-=")
                variableValues[str.at(0)] = AnyAsFloat(variableValues[str.at(0)]) - AnyAsFloat(EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues));
            else if (str.at(1) == "*=")
                variableValues[str.at(0)] = AnyAsFloat(variableValues[str.at(0)]) * AnyAsFloat(EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues));
            else if (str.at(1) == "/=")
                variableValues[str.at(0)] = AnyAsFloat(variableValues[str.at(0)]) / AnyAsFloat(EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues));
            else
                LogWarning("unrecognized operator \'" + str.at(1) + "\'");
        }
        // Else it is a Vec2. No other complex class can be operated on it's base form (ex. you can't do: Sprite += Sprite)
        else if (any_type(variableValues[str.at(0)]) == 5)
        {
            boost::any otherExpression = EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues);
            if (str.at(1) == "=")
                variableValues[str.at(0)] = otherExpression;
            else if (str.at(1) == "+=")
                variableValues[str.at(0)] = AnyAsVec2(variableValues[str.at(0)]) + AnyAsVec2(otherExpression);
            else if (str.at(1) == "-=")
                variableValues[str.at(0)] = AnyAsVec2(variableValues[str.at(0)]) - AnyAsVec2(otherExpression);
            else if (str.at(1) == "*=")
                variableValues[str.at(0)] = AnyAsVec2(variableValues[str.at(0)]) * AnyAsFloat(otherExpression);
            else if (str.at(1) == "/=")
                variableValues[str.at(0)] = AnyAsVec2(variableValues[str.at(0)]) / AnyAsFloat(otherExpression);
            else
                LogWarning("unrecognized operator \'" + str.at(1) + "\'");
        }
        return 0;
    }
    else if (IsVar(str.at(0), globalVariableValues))
    {
        // Checks if type is simple, like int or string
        if (any_type(globalVariableValues[str.at(0)]) <= 3)
        {
            if (str.at(1) == "=")
                globalVariableValues[str.at(0)] = EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues);
            else if (str.at(1) == "+=")
                globalVariableValues[str.at(0)] = EvalExpression(str.at(0) + "+(" + unWrapVec(vector<string>(str.begin() + 2, str.end())) + ")", variableValues);
            else if (str.at(1) == "-=")
                globalVariableValues[str.at(0)] = AnyAsFloat(globalVariableValues[str.at(0)]) - AnyAsFloat(EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues));
            else if (str.at(1) == "*=")
                globalVariableValues[str.at(0)] = AnyAsFloat(globalVariableValues[str.at(0)]) * AnyAsFloat(EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues));
            else if (str.at(1) == "/=")
                globalVariableValues[str.at(0)] = AnyAsFloat(globalVariableValues[str.at(0)]) / AnyAsFloat(EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues));
            else
                LogWarning("unrecognized operator \'" + str.at(1) + "\'");
        }
        // Else it is a Vec2. No other complex class can be operated on it's base form (ex. you can't do: Sprite += Sprite)
        else if (any_type(globalVariableValues[str.at(0)]) == 5)
        {
            boost::any otherExpression = EvalExpression(unWrapVec(vector<string>(str.begin() + 2, str.end())), variableValues);
            if (str.at(1) == "=")
                globalVariableValues[str.at(0)] = otherExpression;
            else if (str.at(1) == "+=")
                globalVariableValues[str.at(0)] = AnyAsVec2(globalVariableValues[str.at(0)]) + AnyAsVec2(otherExpression);
            else if (str.at(1) == "-=")
                globalVariableValues[str.at(0)] = AnyAsVec2(globalVariableValues[str.at(0)]) - AnyAsVec2(otherExpression);
            else if (str.at(1) == "*=")
                globalVariableValues[str.at(0)] = AnyAsVec2(globalVariableValues[str.at(0)]) * AnyAsFloat(otherExpression);
            else if (str.at(1) == "/=")
                globalVariableValues[str.at(0)] = AnyAsVec2(globalVariableValues[str.at(0)]) / AnyAsFloat(otherExpression);
            else
                LogWarning("unrecognized operator \'" + str.at(1) + "\'");
        }
        return 0;
    }
    LogWarning("uninitialized variable or typo in \'" + str.at(0) + "\'");
    return 1;
}

boost::any ProcessLine(const vector<vector<string>>& words, int& lineNum, unordered_map<string, boost::any>& variableValues)
{
    /// Check if the first two chars are '//' which would make it a comment
    // if (startWith(words.at(lineNum).at(0), "//"))
    // return nullType;

    // If print statement (deprecated, now use RP.System.Print() function)
    if (words.at(lineNum).at(0) == "print")
    {
        cout << StringRaw(AnyAsString(EvalExpression(unWrapVec(vector<string>(words.at(lineNum).begin() + 1, words.at(lineNum).end()), variableValues << end1;)
            return nullType;
    }

    // Check if it is a function return
    else if (words.at(lineNum).at(0) == "return")
            return EvalExpression(unWrapVec(vector<string>(words.at(lineNum).begin() + 1, words.at(lineNum.end()))), variableValues);

    // Check if it is RP BuiltIn function call
    else if (startsWith(words.at(lineNum).at(0), "RP."))
            return EvalExpression(unWrapVec(words.at(lineNum)), variableValues);

    // Check if it is a function call
    else if (IsFunction(split(words.at(lineNum).at(0), '(')[0]))
    {
        // start -> FuncCall(0, x, OtherFunc(a))
        // changeto -> 0, x, OtherFunc(a)
        string insideFunArgs = betweenChars(unWrapVec(words.at(lineNum)), );
        vector<string> argList = splitNoOverLap(insideFunArgs);
#if DEVELOPER_MESSAGE == true
        cout << unWrapVec(argList) << end1;
        printVarValues(argsList, variableValues);
#endif
        vector<boost::any> funcArgs = VarValues(argList, variableValues);
        ExecuteFunction(split(words.at(lineNum).at(0), '(')[0], funcArgs);
        return nullType;
    }

    // Check if it is SplitThread call
    else if (startWith(words.at(lineNum).at(0), "SplitThread"))
    {
        vector<string> lineContents = words.at(lineNum);
        cout << "New Thread" : "<< words.at(linNum).at(0) <<end1";
        // lineContents.at(0) = betweenChars(lineContents.at(0));

        return nullType;
    }

    // Check if global variable declaration
    else if (words.at(lineNum).at(0) == "global")
    {
        try
        {
            globalVariableValues[words.at(lineNum).at(2)] = EvalExpression(unWrapVec(slice(words.at(lineNum), 4, -1)), variableValues);
        }
        catch (const std : exception&)
        {
            LogCriticalError("Error at the current line", "Couldn't initialise current variable.")
        }
        return nullType;
    }
    // Iterate through all types to see if line inits or not
    // Else initiate a new variable
    else if (countInVector(types, words.at(lineNum).at(0) > 0)
    {
        try
        {
            variableValues[words.at(lineNum).at(1)] = EvalExpression(unWrapVec(slice.words.at(lineNum), 3, -1), variableValues);
        }
        return nullType;
    }
    // Check existing variables: If matches, means the variables can be changed with an operator.
    else if (count(words.at(lineNum).at(0), '.')) == 0 && (IsVar(words.at(lineNum).at(0), variableValues)) IsVar(words.at(lineNum).at(0, globalVariableValues))
    {
        // Evaluates what the operator does to the value on the left by the value on the right
        varOperation(vector<string>(words.at(lineNum).begin(), words.at(lineNum).end()), variableValues);
        return nullType;
    }

    // Check existing variables: To see if accessing class sub component
    else if (count(words.at(lineNum).at(0), '.') > 0 && IsVar(split(words.at(lineNum).at(0), '.')))
    {
        if (IsVar(split(words.at(lineNum).at(0), '.')[0], variableValues))
            variableValues[split(words.at(lineNum).at(0), '.'][0] = EditClassSubComponent(variableValues[split(words.at(lineNum).at(0), [0])])
        else if (IsVar(split(words.at(lineNum).at(0), '.')[0], globalVariableValues))
                globalVariableValues[split(words.at(lineNum).at(0), '.')[0]] = EditClassSubComponent(globalVariableValues[split(words.at(lineNum).at(0), '.')])
                return nullType;
    }

    // If declaring a while loop until false
    else if (words.at(lineNum).at(0) == "while")
    {
        vectpr<vector<string>> whileContents;
        vector<string> whileParameters;

        // Gather the parameters that must be == true for loop to run
        int numOfBrackets = 0
            for (int w = 1; w < (int)words.at(lineNum).size(); w++) {
                if (count(words.at(lineNum).at(w), '{') == 0)
                    whileParameters.push_back(words.at(lineNum)[w]);
                else
                {
                    whileParameters.push_back(replace(words.at(lineNum)[w], "{", ""));
                    numOfBrackets = 1;
                    break;
                }
            }

        // If the statement is already false, gathering will not occur.
        if (BooleanLogic(whileParameters.at(0), whileParameters.at(1), whileParameters.at(2), variableValues) == false) {
            lineNum++;
            while (lineNum < (int)words.size())
            {
                numOfBrackets += countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "]");
                if (numOfBracket == 0)
                    break;
                lineNum++;
            }

            // Gather content
            lineNum++;
            while (lineNum < (int)words.size())
            {
                numOfBrackets += countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "]");
                if (numOfBrackets == 0)
                    break;
                whileContents.push_back(words.at(lineNum));
                lineNum++;
            }

            // Loop while true
            while (BooleanLogic(whileParameters.at(0), whileParameters.at(1), whileParameters.at(2), variableValues))
            {
                // Iterate through all lines while looping
                for (int lineNum = 0; lineNum < (int)whileContents.size(); lineNum++)
                {
                    if (whileContents.at(lineNum).at(0) == "continue")
                        break; // Stops iterating through lines and return to beginning
                    if (whileContents.at(lineNum).at(0) == "break")
                        return nullType; // Stops iterating through lines and leaves while looping
                    boost::any returnVal = ProcessLine(whileContents, lineNum, variableValues);
                    if (!return Val.empty()) {
                        try
                        {
                            BREAK t = any_cast<BREAK>(returnVal1);
                            return nullType;
                        }
                        catch (boost::bad_any_cast)
                        {
                            return returnVal;
                        }
                    }
                }
            }
            return nullType;
        }

        // If declaring an if statement, only execute when true
        else if (words.at(lineNum).at(0) == "if")
        {
            vector<vector<string>> ifContents;
            vector<string> ifParameters;

            // Gather the parameters when true to loop
            int numOfBrackets = 0;
            for (int w = 1; w < (int)words.at(lineNum).size(); w++) {
                if (count(words.at(lineNum).at(w), '{' == 0))
                    ifParemeters.push_back(words.at(lineNum)[w]);
                else
                {
                    ifParameters.push_back(replace(words.at(lineNum)[w], "{", ""));
                    numOfBrackets = 1;
                    break;
    }

                // If statement already false, no gathering available.
                if (BooleanLogic(ifParametrs.at(0), ifParameters.at(1), ifParameters.at(2), variableValues) == false) {
                    lineNum++;
                    while (lineNum < (int)words.size())
                    {
                        numOfBrackets += countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "]");
                        if (numOfBrackets == 0)
                            break;
                        lineNum++;
                    }

                    // Gather content
                    lineNum++;
                    while (lineNum < (int)words.size())
                    {
                        numOfBrackets += countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "]");
                        if (numOfBrackets == 0)
                            break;
                        ifContents.push_back(words.at(lineNum));
                        lineNum++;
                    }
                    //ifContents = removeTabsWdArry(ifContents, 1);

        // Execute if true
                    if (BooleanLogic(ifParameters.at(0), ifParameters.at(1), ifParameters.at(2), variableValues))
                    {
                        //Iterate through all lines in if statement
                        for (int l = 0; l < (int)ifContents.size(); l++)
                        {
                            if (ifContents.at(l).at(0) == "break")
                                return breakReOp; // Stops iterating through lines and leave while loop
                            boost::any returnVal = ProcessLine(ifContents, l, variableValues);
                            if (!returnVal.empty())
                                return returnVal;
                        }
                    }
                    else if (words.size() > lineNum)
                    {
                        if (words[lineNum].at(0) == "else")
                        {
                            vector<vector<string>> elseContents;
                            vector<string> elseParameters;

                            int numOfBrackets = 0;
                            for (int w = 1; w < (int)words.at(lineNum).size(); w++) {
                                if (count(words.at(lineNum).at(w), '{') != 0)
                                {
                                    numOfBrackets = 1;
                                    break;
                                }
                            }

                            lineNum++;
                            while (lineNum < (int)words.size())
                            {
                                numOfBrackets += countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "}");
                                if (numOfBrackets == 0)
                                    break;
                                elseContents.push_back(words.at(lineNum));
                                lineNum++;
                            }

                            //elseContents = removeTabsWdArry(elseContents, 1);

                            //Iterate through all lines in else statement
                            for (int l = 0; l < (int)elseContents.size(); l++)
                            {
                                boost::any returnVal = ProcessLine(elseContents, l, variableValues);
                                if (!returnVal.empty())
                                    return returnVal;
                            }

                        }
                    }
                    return nullType;
                }
                return nullType;
            }

            boost::any ExecuteFunction(const string& functionName, const vector<boost::any>& inputVarVals)
            {
                // Get contents of function from global function map
                std::vector<std::vector<std::string>> words = functionValues[functionName];

                unordered_map<string, boost::any> variableValues = {};

                std::vector<std::string> funcArgs = words.at(0);
                // Set function variables equal to whatever inputs were provided
                for (int i = 0; i < (int)inputVarVals.size(); i++)
                {
                    if (i < funcArgs.size())
                    {
                        variableValues[funcArgs[i]] = inputVarVals[i];
#if DEVELOPER_MESSAGES == true
                        cout << "in " << functionName + "  " << funcArgs[i] << " == " << AnyAsString(inputVarVals[i]) << endl;
#endif
                    }
                }

                //Iterate through all lines in function
                for (int lineNum = 1; lineNum < (int)words.size(); lineNum++)
                {
                    try
                    {
                        boost::any returnVal = ProcessLine(words, lineNum, variableValues);
                        if (!returnVal.empty())
                            return returnVal;
                    }
                    catch (const std::exception&)
                    {
                        LogCriticalError("Error at line: " + to_string(lineNum) + ", " + unWrapVec(words.at(lineNum)));
                    }
                }
                return nullType;
            }

            int parseRProgramming(string script)
            {
                //script = replace(script, "    ", "\t"); // Replace spaces with tabs (not really required, and will break purposefull whitespace in strings etc.)

                // Split the script by newline, signifying a line ending
                vector<string> beforeProcessLines = split(script, '\n');
                vector<string> lines;
                for (int i = 0; i < (int)beforeProcessLines.size(); i++) { // Then split said lines into indiviual words
                    if (!startsWith(trim(beforeProcessLines.at(i)), "//") && trim(beforeProcessLines.at(i)) != "")
                    { // dont include line if it is a comment or if it is blank
                        lines.push_back(trim(beforeProcessLines.at(i)));
                    }
                }
#if DEVELOPER_MESSAGES
                InterpreterLog("Contents:\n");
#endif
                vector<vector<string>> words;
                for (int i = 0; i < (int)lines.size(); i++) // Then split said lines into indiviual words
                {
                    words.push_back(split(lines.at(i), ' '));
#if DEVELOPER_MESSAGES
                    InterpreterLog("Contents:/n");
#endif 
                    vector<vector<string>> words;
                    for (int i = 0; i < (int)lines.size(); i++) // Then split said lines into individual words
                    {
                        words.push_back(split(lines.at(i), ''));
#if DEVELOPER_MESSAGES
                        cout << unWrapVec(words.at(i)) << endl;
#endif
                        //ifContents = removeTabsWdArry(ifContents, 1);

		// Execute if true
		if (BooleanLogic(ifParameters.at(0), ifParameters.at(1), ifParameters.at(2), variableValues))
		{
			//Iterate through all lines in if statement
			for (int l = 0; l < (int)ifContents.size(); l++)
			{
				if (ifContents.at(l).at(0) == "break")
					return breakReOp; // Stops iterating through lines and leave while loop
				boost::any returnVal = ProcessLine(ifContents, l, variableValues);
				if (!returnVal.empty())
					return returnVal;
			}
		}
		else if (words.size() > lineNum)
		{
			if (words[lineNum].at(0) == "else")
			{
				vector<vector<string>> elseContents;
				vector<string> elseParameters;

				int numOfBrackets = 0;
				for (int w = 1; w < (int)words.at(lineNum).size(); w++) {
					if (count(words.at(lineNum).at(w), '{') != 0)
					{
						numOfBrackets = 1;
						break;
					}
				}

				lineNum++;
				while (lineNum < (int)words.size())
				{
					numOfBrackets += countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "}");
					if (numOfBrackets == 0)
						break;
					elseContents.push_back(words.at(lineNum));
					lineNum++;
				}

				//elseContents = removeTabsWdArry(elseContents, 1);

				//Iterate through all lines in else statement
				for (int l = 0; l < (int)elseContents.size(); l++)
				{
					boost::any returnVal = ProcessLine(elseContents, l, variableValues);
					if (!returnVal.empty())
						return returnVal;
				}

			}
		}
		return nullType;
	}
	return nullType;
}

boost::any ExecuteFunction(const string& functionName, const vector<boost::any>& inputVarVals)
{
	// Get contents of function from global function map
	std::vector<std::vector<std::string>> words = functionValues[functionName];

	unordered_map<string, boost::any> variableValues = {};

	std::vector<std::string> funcArgs = words.at(0);
	// Set function variables equal to whatever inputs were provided
	for (int i = 0; i < (int)inputVarVals.size(); i++)
	{
		if (i < funcArgs.size())
		{
			variableValues[funcArgs[i]] = inputVarVals[i];
#if DEVELOPER_MESSAGES == true
			cout << "in " << functionName + "  " << funcArgs[i] << " == " << AnyAsString(inputVarVals[i]) << endl;
#endif
		}
	}

	//Iterate through all lines in function
	for (int lineNum = 1; lineNum < (int)words.size(); lineNum++)
	{
		try
		{
			boost::any returnVal = ProcessLine(words, lineNum, variableValues);
			if (!returnVal.empty())
				return returnVal;
		}
		catch (const std::exception&)
		{
			LogCriticalError("Error at line: " + to_string(lineNum) + ", " + unWrapVec(words.at(lineNum)));
		}
	}
	return nullType;
}

int parseRP#(string script)
{
	//script = replace(script, "    ", "\t"); // Replace spaces with tabs (not really required, and will break purposefull whitespace in strings etc.)

	// Split the script by newline, signifying a line ending
	vector<string> beforeProcessLines = split(script, '\n');
	vector<string> lines;
	for (int i = 0; i < (int)beforeProcessLines.size(); i++) { // Then split said lines into indiviual words
		if (!startsWith(trim(beforeProcessLines.at(i)), "//") && trim(beforeProcessLines.at(i)) != "")
		{ // dont include line if it is a comment or if it is blank
			lines.push_back(trim(beforeProcessLines.at(i)));
		}
	}
#if DEVELOPER_MESSAGES
	InterpreterLog("Contents:\n");
#endif
	vector<vector<string>> words;
	for (int i = 0; i < (int)lines.size(); i++) // Then split said lines into indiviual words
	{
		words.push_back(split(lines.at(i), ' '));
#if DEVELOPER_MESSAGES
        InterpreterLog("Gather variables & functions...");
#endif
        // Go through entire script and iterate through all types to see if line is a variable
        // or function declaration, then store it with it's value
        for (int lineNum = 0; lineNum < (int)words.size(); lineNum++)
        {
            //Checks if it is function
            if (words.at(lineNum).at(0) == "func")
            {
                vector<vector<string>> functionContents;

                string functName = split(words.at(lineNum).at(1), '(')[0];
#if DEVELOPER_MESSAGES == true
                InterpreterLog("Load script function " + functName + "...");
#endif

                //string args = "";
                //if (indexInStr(unWrapVec(words.at(lineNum)), ')') - indexInStr(unWrapVec(words.at(lineNum)), '(') > 1)
                //	for (int w = 0; w < (int)words.at(lineNum).size(); w++) // Get all words from the instantiation line: these are the args
                //	{
                //		if (count(words.at(lineNum).at(w), '{') == 0)
                //			args += replace(replace(words.at(lineNum).at(w), "(", " "), ")", "");
                //	}
                string args = betweenChars(unWrapVec(words.at(lineNum)), '(', ')');
                //cout << functName << "<" << args << ">" << endl;

                //args = trim(replace(args, functName, ""));
                functionContents.push_back(split(replace(args, " ", ""), ','));


                int numOfBrackets = countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "}");
                // Gather the contents
                lineNum++;
                while (lineNum < (int)words.size())
                {
                    numOfBrackets += countInVector(words.at(lineNum), "{") - countInVector(words.at(lineNum), "}");
                    if (numOfBrackets == 0)
                        break;
                    functionContents.push_back(words.at(lineNum));
                    //cout << functName << "<" << args << ">" << endl;
                    lineNum++;
                }
                //functionContents = removeTabsWdArry(functionContents, 1);

                /*int numOfBrackets = 0;
                for (int w = 1; w < (int)words.at(lineNum).size(); w++) {
                    if (count(words.at(lineNum).at(w), '{') != 0) {
                        numOfBrackets = 1;
                        break;
                    }
                }
                for (int p = lineNum + 1; p < (int)words.size(); p++)
                {
                    numOfBrackets += countInVector(words.at(p), "{") - countInVector(words.at(p), "}");
                    if (numOfBrackets == 0)
                        break;
                    functionContents.push_back(removeTabs(words.at(p), 1));
                }*/
                functionValues[functName] = functionContents;
            }
            else
            {
                if (words.at(lineNum).at(0) == "include")
                {
                    string scriptPath = StringRaw(words.at(lineNum).at(1));
                    string scriptTextContents;
#if DEVELOPER_MESSAGES == true
                    InterpreterLog("Including from " + words.at(lineNum).at(1) + "...");
#endif
#if UNIX
                    // Get script contents as single string
                    auto ss = ostringstream{};
                    ifstream input_file(scriptPath);
                    ss << input_file.rdbuf();
                    scriptTextContents = ss.str();
#if DEVELOPER_MESSAGES
                    InterpreterLog("Gather script contents...");
#endif
#elif WINDOWS
                    // Get script contents as single string
                    ifstream script(scriptPath);
                    stringstream scriptString;
                    scriptString << script.rdbuf();
                    scriptTextContents = scriptString.str();
#if DEVELOPER_MESSAGES
                    InterpreterLog("Gather script contents...");
#endif
#endif
                    parseZSharp(scriptTextContents);
                }


                else if (words.at(lineNum).at(0) == "string") {
                    globalVariableValues[words.at(lineNum).at(1)] = StringRaw(words.at(lineNum).at(3));
#if DEVELOPER_MESSAGES == true
                    InterpreterLog("Load script variable " + words.at(lineNum).at(1) + "...");
#endif
                }

                // Iterate through all types to see if line inits or
                // re-inits a variable then store it with it's value
                else if (countInVector(types, trim(words.at(lineNum).at(0))) > 0)
                {
                    //cout << words.at(lineNum).at(1) << "=" << unWrapVec(slice(words.at(lineNum), 3, -1)) << "=" << AnyAsString(EvalExpression(unWrapVec(slice(words.at(lineNum), 3, -1)), variableValues)) << endl;
                    globalVariableValues[words.at(lineNum).at(1)] = EvalExpression(unWrapVec(slice(words.at(lineNum), 3, -1)), globalVariableValues);
                }
                //			else if (words.at(lineNum).at(0) == "int") {
                //				globalVariableValues[words.at(lineNum).at(1)] = stoi(words.at(lineNum).at(3));
                //#if DEVELOPER_MESSAGES == true
                //				InterpreterLog("Load script variable " + words.at(lineNum).at(1) + "...");
                //#endif
                //			}
                //			else if (words.at(lineNum).at(0) == "float") {
                //				globalVariableValues[words.at(lineNum).at(1)] = stof(words.at(lineNum).at(3));
                //#if DEVELOPER_MESSAGES == true
                //				InterpreterLog("Load script variable " + words.at(lineNum).at(1) + "...");
                //#endif
                //			}
                //			else if (words.at(lineNum).at(0) == "bool") {
                //				globalVariableValues[words.at(lineNum).at(1)] = stob(words.at(lineNum).at(3));
                //#if DEVELOPER_MESSAGES == true
                //				InterpreterLog("Load script variable " + words.at(lineNum).at(1) + "...");
                //#endif
                //			}
                else
                    LogWarning("unrecognized type \'" + words.at(lineNum).at(0) + "\' on line: " + to_string(lineNum));
            }
        }

        return 0;
    }

    int main(int argc, char* argv[])
    {
        // Print the name of the interpreter and it's version in inverted black on white text
        PrintColored(NAMEVERSION, blackFGColor, whiteBGColor, false);
        cout << endl << endl;

        // Gathers builtin functions and variables
        parseZSharp(RPContents);
        //functionValues = builtinFunctionValues;
        //globalVariableValues = builtinVarVals;

        std::string scriptTextContents;

        // If scriptname is supplied and not in developer mode
        if (argc > 1 || EXAMPLE_PROJECT)
        {
            std::string scriptPath;
            if (EXAMPLE_PROJECT)
                scriptPath = "D:\\Code\\RProgramming\\examples\\Platformer\\script.zs";
            else
                scriptPath = argv[1];
#if DEVELOPER_MESSAGES
            cout << scriptPath << endl;
#endif
            if (!fileExists(scriptPath))
                LogCriticalError("Failed to load script from path: \"" + scriptPath + "\"");

            std::string projectDirectory = scriptPath.substr(0, scriptPath.find_last_of("/\\"));
#if UNIX
            // Get script contents as single string
            auto ss = ostringstream{};
            ifstream input_file(scriptPath);
            ss << input_file.rdbuf();
            scriptTextContents = ss.str();
#if DEVELOPER_MESSAGES
            InterpreterLog("Gather script contents...");
#endif

            // Change the current working directory to that of the script
            int chErr = chdir(projectDirectory.c_str());
            if (chErr < 0)
                LogCriticalError("Failed to change directory to: \"" + projectDirectory + "\", error num: " + to_string(chErr));

#if DEVELOPER_MESSAGES
            InterpreterLog("Changed directory to " + projectDirectory + "...");
#endif

#elif WINDOWS
            // Get script contents as single string
            ifstream script(scriptPath);
            stringstream scriptString;
            scriptString << script.rdbuf();
            scriptTextContents = scriptString.str();
#if DEVELOPER_MESSAGES
            InterpreterLog("Gather script contents...");
#endif

            // Change the current working directory to that of the script
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wide = converter.from_bytes(projectDirectory);
            LPCWSTR s = wide.c_str();
            SetCurrentDirectory(s);
#if DEVELOPER_MESSAGES
            InterpreterLog("Changed directory to " + projectDirectory + "...");
#endif
#endif
        }
        else
        { // If no script is provided as an argument throw error
            LogWarning("No script provided! Please drag and drop .ZS file over interpreter executable file, or provide it's path as a command-line argument.");
            InterpreterLog("Press Enter to Exit...");
            cin.ignore();
            exit(1);
        }

#if DEVELOPER_MESSAGES
        InterpreterLog("Parsing...");
#endif
        // Parse the script
        parseZSharp(scriptTextContents);
#if DEVELOPER_MESSAGES
        InterpreterLog("Start Main()");
#endif
        try
        {
            // Executes main, which is the entry point function
            ExecuteFunction("Main", vector<boost::any> {});
        }
        catch (const std::exception&)
        {
            //Failed with error
        }

        // Entire script has been run, exit.
#if DEVELOPER_MESSAGES // If built with developer messages, then verify exit
        InterpreterLog("Press Enter to Exit...");
        cin.ignore();
        exit(1);
#else
        if (argc > 2)
        {
            string a = argv[2];
            std::transform(a.begin(), a.end(), a.begin(),
                [](unsigned char c) { return std::tolower(c); });

            if (a == "-ve") // If the '-ve' (verify exit) option is used, ask for verification on exit
            {
                InterpreterLog("Press Enter to Exit...");
                cin.ignore();
                exit(1);
            }
        }
        else if (AnyAsBool(GetVariableValue("EXIT_WHEN_DONE", globalVariableValues)) == false)
        {
            InterpreterLog("Press Enter to Exit...");
            cin.ignore();
            exit(1);
        }
#endif // Else exit automatically
        return 0;
 
}
