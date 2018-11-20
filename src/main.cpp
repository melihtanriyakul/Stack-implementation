#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "StackAndMethods.h"


using namespace std;


int main(int argc, char* argv[])
{
    /*
    These stacks created for three different expressions and
    the result.
    */

    StackForNumbers *numStackForInfix = new StackForNumbers();
    StackForOperators *opStackForInfix = new StackForOperators();

    StackForNumbers *numStackForPrefix = new StackForNumbers();
    StackForOperators *opStackForPrefix = new StackForOperators();

    StackForNumbers *numStackForPostfix = new StackForNumbers();
    StackForOperators *opStackForPostfix = new StackForOperators();
    StackForNumbers *tempStack = new StackForNumbers();

    StackForNumbers *numStackForResult= new StackForNumbers();
    StackForOperators *opStackForResult = new StackForOperators();


    ofstream myPrefixFile;
    ofstream myInfixFile;
    ofstream myPostfixFile;
    ofstream myResultFile;

    myPrefixFile.open(argv[2]);
    myInfixFile.open (argv[3]);
    myPostfixFile.open(argv[4]);
    myResultFile.open(argv[5]);

    /*
    In this step, we read the input file,
    parse the numbers and operators, then put them
    into their stacks.
    */
    ifstream infile(argv[1]); //open the file
    if (infile.is_open() && infile.good()) {
        string line;
        string prefixExp = "";
        string infixExp = "";
        string postfixExp= "";
        string result = "";
        while (getline(infile, line)){
            string sLine(line);
            istringstream iss(sLine);
            do
            {
                string subString;
                iss >> subString;
                if (subString.length() != 0) {
                    const char * currentChar = subString.c_str();
                    /*
                    Putting numbers into the number stacks.
                    */
                    if (isdigit(*currentChar)) {
                        stringstream strValue;
                        strValue << currentChar;
                        int intValue;
                        strValue >> intValue;
                        numStackForInfix->push(intValue);
                        numStackForPostfix->push(intValue);
                        numStackForPrefix->push(intValue);
                        numStackForResult->push(intValue);
                    }
                    /*
                    Putting operators into the number stacks.
                    */
                    else if(!isalpha(*currentChar)){
                        opStackForInfix->push(*currentChar);
                        opStackForPostfix->push(*currentChar);
                        opStackForPrefix->push(*currentChar);
                        opStackForResult->push(*currentChar);
                    }
                }
            } while (iss);

            /*
            In this step, we call the methods assign
            the return values to matching strings.
            After that we print the expressions
            into their matching files.
            */
            prefixExp = expressionToPrefix(numStackForPrefix, opStackForPrefix);
            myPrefixFile  << prefixExp << "\n";

            infixExp = expressionToInfix(numStackForInfix, opStackForInfix);
            myInfixFile  << infixExp << "\n";

            postfixExp = expressionToPostfix(numStackForPostfix, tempStack, opStackForPostfix);
            myPostfixFile << postfixExp << "\n";

            result = calculateResult(numStackForResult, opStackForResult);
            myResultFile << result << "\n";

            /*
            After printing the expressions to their matching
            files, we clear the strings and the stacks for
            the new line.
            */
            prefixExp.clear();
            infixExp.clear();
            postfixExp.clear();
            result.clear();

            numStackForPrefix->clearStack();
            opStackForPrefix->clearStack();
            numStackForInfix->clearStack();
            opStackForInfix->clearStack();
            numStackForResult->clearStack();
            opStackForResult->clearStack();

        }

    } else {
        cout << "Failed to open file!";
    }
    infile.close();
    myPrefixFile.close();
    myPostfixFile.close();
    myInfixFile.close();
    myResultFile.close();

    return 0;
}
