#ifndef STACKANDMETHODS_H
#define STACKANDMETHODS_H

#include <iostream>

using namespace std;

/*
This is a class created for
the number stack. This class's
object holds its number
and next pointer.
*/
class nodeForNumbers
{
 public:
    int number;
    nodeForNumbers * next;
};
/*
This class created for stack
implementation which contains
number. It has a top
attribute and several methods.
 */
class StackForNumbers{

public:
    nodeForNumbers *top;
public:
    StackForNumbers(){
        top = NULL;
    }
/*
This methods pushes new
value into stack.
*/
void push(int value){
    nodeForNumbers *newTop = new nodeForNumbers;
    if (top == NULL) {
        newTop->number = value;
        newTop->next = NULL;
        top = newTop;
    }
    else{
        newTop->number = value;
        newTop->next = top;
        top = newTop;
    }
}

/*
This methods erase the top
value and returns it.
*/
int pop(){
    int returnValue;
    if (top == NULL){
        cout << "The stack is empty";
        return -1;
    }
    else{
        nodeForNumbers * temp = top;
        returnValue = top->number;
        top = top->next;
        delete(temp);
        return returnValue;
    }
}
/*
This method prints the whole stack.
It is used for debugging.
*/
void print(){
    nodeForNumbers * temp;
    temp = top;
    while (temp != NULL){
        cout << temp->number << " -> ";
        temp = temp->next;
    }
    cout << endl;
}
/*
This method clears the whole stack.
*/
void clearStack(){
    while (top != NULL) {
        pop();
    }
}
};
/*
This is a class created for
the operator stack. This class's
object holds its operator as a char
and next pointer.
*/
class nodeForOperators
{
 public:
    nodeForOperators * next;
    char op;
};
/*
This class created for stack
implementation which contains
operators. It has a top
attribute and several methods which
*/
class StackForOperators{

public:
    nodeForOperators *top;
public:
    StackForOperators(){
        top = NULL;
    }
/*
This methods pushes new
operator into stack.
*/
void push(const char givenOperator){
    nodeForOperators *newTop;
    newTop = new nodeForOperators;
    if (top == NULL) {
        newTop->op = givenOperator;
        newTop->next = NULL;
        top = newTop;
    }
    else{
        newTop->op = givenOperator;
        newTop->next = top;
        top = newTop;
    }
}
/*
This methods erase the top
operator and returns it.
*/
char pop(){
    char currentOperator;
    if (top == NULL){
        cout << "The stack is empty";
        return -1;
    }
    else{
        nodeForOperators * temp = top;
        currentOperator = top->op;
        top = top->next;
        delete(temp);
        return currentOperator;
    }
}
/*
This method prints the whole stack.
It is used for debugging.
*/
void print(){
    nodeForOperators * temp;
    temp = top;
    while (temp != NULL){
        cout << temp->op << " -> ";
        temp = temp->next;
    }
    cout << endl;
}
/*
This method clears the whole stack.
*/
void clearStack(){
    while (top != NULL) {
        pop();
    }
}
};

/*
This method convert to int value to
string. We use this method when printing
the number which popped from stack to a string.
*/
string intToString(int value) {
    string result;
    stringstream convert;
    convert << value;
    result = convert.str();
    return result;
}

/*
This method calculates the number of elements in
the expression with respect to 'space' character.
 We used it to detect if there are more
than two elements. Because if there is less than two
elements we don't need to control for parenthesis.
*/
int calculateNumOfElements(string sInfixExpression) {
    int numOfElements = 1;
    size_t pos = 0;
    string token;
    while ((pos = sInfixExpression.find(" ")) != std::string::npos) {
        token = sInfixExpression.substr(0, pos);
        sInfixExpression.erase(0, pos + 1);
        numOfElements++;
    }
    return numOfElements;
}

/*
This method find the index of first operator.
We use it to control the precedence between
first operator in the expression and the operator
we get from the operator stack.
*/
int indexOfFirstOperator (string infixExpression) {

    size_t starIndex = infixExpression.find("*");
    int iStarIndex = 1000;
    size_t slashIndex = infixExpression.find("/");
    int iSlashIndex = 1000;
    size_t powerIndex = infixExpression.find("^");
    int iPowerIndex = 1000;
    size_t plusIndex = infixExpression.find("+");
    int iPlusIndex = 1000;
    size_t minusIndex = infixExpression.find("-");
    int iMinusIndex = 1000;

    if (starIndex == string::npos) {
    }
    else {
        iStarIndex = static_cast<int>(starIndex);
    }

    if (slashIndex == string::npos) {
    }
    else
        iSlashIndex = static_cast<int>(slashIndex);
    if (powerIndex == string::npos) {
    }
    else
        iPowerIndex = static_cast<int>(powerIndex);
    if (plusIndex == string::npos) {
    }
    else
        iPlusIndex = static_cast<int>(plusIndex);
    if (minusIndex == string::npos) {
    }
    else
        iMinusIndex = static_cast<int>(minusIndex);

    if ( (iStarIndex + iSlashIndex + iPowerIndex + iPlusIndex + iMinusIndex)  != 5000) {
        return min(iStarIndex, min(min(iSlashIndex, iPowerIndex),min(iPlusIndex, iMinusIndex)));
    }
    else {
        cout << "The expression doesn't contain any operator!" << endl;
        return -1;
    }
}

/*
This method converts the given expression to prefix expression.
It takes the stacks as parameters, first we get two numbers from
the number stack then we get one operator from operation stack
we add them to a string backwards.
*/
string expressionToPrefix ( StackForNumbers *sForNum, StackForOperators *sForOp ) {
    string numInStack = "";
    string sPrefixExpression = "";
    numInStack = intToString(sForNum->pop());
    sPrefixExpression.append(numInStack);
    sPrefixExpression.insert(0, " ");
    while ( sForNum->top != NULL || sForNum->top != NULL ){
        if (sForNum->top != NULL){
            numInStack = intToString(sForNum->pop());
            sPrefixExpression.insert(0, numInStack);
            sPrefixExpression.insert(0, " ");
        }
        if ( sForOp->top != NULL ){
            string poppedOperator(1, sForOp->pop());
            sPrefixExpression.insert(0, poppedOperator);
            sPrefixExpression.insert(0, " ");
        }
    }
    return sPrefixExpression;
}

/*
This method converts the given expression to infix expression.
It takes the stacks as parameters. First we get a number and an operator
from stack and add them to the expression without any control. After the
number of elements in expression got bigger than 2, we start to control
precedence. We control every operator which we get from operator stack
to add expression, with respect to first operator which we obtain through
indexOfFirstOperator method.
 */
string expressionToInfix ( StackForNumbers *sForNum, StackForOperators *sForOp) {
    string numInStack = "";
    string sInfixExpression = "";
    int opIndex;
    int numOfElementsInExpression;
    while (sForNum->top != NULL || sForOp->top != NULL ){
                if ( sForNum->top != NULL) {
                    numInStack = intToString(sForNum->pop());
                    sInfixExpression.insert(0, numInStack);
                    sInfixExpression.insert(0, " ");
                }
                if (sForOp->top != NULL) {
                    numOfElementsInExpression = calculateNumOfElements(sInfixExpression);
                    if ( numOfElementsInExpression > 2) {
                        opIndex = indexOfFirstOperator(sInfixExpression);
                        if ( sForOp->top->op == '*' ) {
                            if ( sInfixExpression[opIndex] == '-' || sInfixExpression[opIndex] == '+' ) {
                                sInfixExpression.insert(0, " ( ");
                                sInfixExpression.append(" )");
                            }
                        }
                        else if ( sForOp->top->op == '/') {
                            if ( sInfixExpression[opIndex] == '*' ||sInfixExpression[opIndex] == '/' || sInfixExpression[opIndex] == '+' || sInfixExpression[opIndex] == '-' ){
                                sInfixExpression.insert(0, " ( ");
                                sInfixExpression.append(" )");
                            }
                        }
                        else if ( sForOp->top->op == '^' ){
                            sInfixExpression.insert(0, " ( ");
                                sInfixExpression.append(" )");
                        }
                        else if (sForOp->top->op == '-') {
                            if (sInfixExpression[opIndex] == '+' || sInfixExpression[opIndex] == '-' ) {
                                sInfixExpression.insert(0, " ( ");
                                sInfixExpression.append(" )");
                            }
                        }
                    }
                    string b(1, sForOp->pop());
                    sInfixExpression.insert(0, b);
                    sInfixExpression.insert(0, " ");
                }
        }
        return sInfixExpression;
}
/*
This method converts the given expression to postfix expression.
It takes the stacks as parameters, first we reverse the number stack
because in postfix expression, the numbers are in the same order with
the input. After that we add all the numbers to the postfix expression,
then we add operators to the expression reversely with respect to
input order.  */
string expressionToPostfix( StackForNumbers *sForNum,StackForNumbers *tempStack, StackForOperators *sForOp ) {
    string sPostfixExpression = "";
    string numInStack = "";

    while ( sForNum->top != NULL ){
        tempStack->push(sForNum->pop());
    }
    while ( tempStack->top != NULL ){
        numInStack = intToString(tempStack->pop());
        sPostfixExpression.append(numInStack);
        sPostfixExpression.append(" ");
    }
    while ( sForOp->top != NULL ){
        string op(1, sForOp->pop());
        sPostfixExpression.append(op);
        sPostfixExpression.append(" ");
    }
    return sPostfixExpression;
}
/*
This method calculates the expression with respect to
the given procedure. We get two numbers and one operator
from the stacks. We do the operation with respect to operator
and sequency of the numbers. Then push the result into the number
stack. When the number stack reaches to null we return the result
value as a string.
*/
string calculateResult( StackForNumbers *sForNum, StackForOperators *sForOp){
    int firstNumber;
    int secondNumber;
    int result;
    char currentChar;
    string returnVal;
    while( sForNum->top != NULL || sForOp->top != NULL ){
        if( sForNum->top != NULL ){
            firstNumber = sForNum->pop();
            if( sForNum->top != NULL ){
            secondNumber = sForNum->pop();
            }
        }
        if( sForOp->top != NULL ){
            currentChar = sForOp->pop();
        }
        else
            break;
        if(currentChar == '/' && firstNumber == 0) {
            returnVal = "NaN";
            return returnVal;
        }
        else if(currentChar == '+') {
            result = secondNumber + firstNumber;
            sForNum->push(result);
        }
        else if(currentChar == '-') {
            result = secondNumber - firstNumber;
            sForNum->push(result);
        }
        else if(currentChar == '/') {
            result = secondNumber / firstNumber;
            sForNum->push(result);
        }
        else if( currentChar == '*'){
            result = secondNumber * firstNumber;
            sForNum->push(result);
        }
        else if( currentChar == '^' ){
            result = 1;
            while (firstNumber > 0) {
                result = result * secondNumber;
                firstNumber--;
            }
            sForNum->push(result);
        }
    }
    returnVal = intToString(result);
    return returnVal;

}

#endif // STACKANDMETHODS_H
