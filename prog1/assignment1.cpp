//
// assignment1.cpp (Version 1.0)
//
// Kusdavletov Ernar, 20152008, kusdavletov@gmail.com

/* getPriority function
 * The getPriority function takes the token of the operator and returns its priority.
 * Also, the function throws errors when token is not operator or ')'
 * The higher the priority of an operator is, the smaller the number this function returns.
 */

/* getInStackPriority function
 * The getInStackPriority function takes the token of the operator and returns its priority.
 * Also, the function throws errors when token is not operator or ')'
 * It returns the in-stack priority, which gives '(' lowest priority.
 */

/* postfix function
 * The postfix function takes the expression and convert it from infix notation into an expression in postfix notation.
 * The expressions are stored as a vector of tokens.
 */

/* eval function
 * The eval function takes the expression (vector of tokens) in the postfix notation and evaluates it to integer.
 */

#include "assignment1.h"
#include "Token.h"
#include "tokenizer.h"
#include "LinkedStack.h"
#include "CircularList.h"

#include <iostream>
#include <stdexcept>

using namespace std;

int getPriority(Token token) {
    if (!token.isOperator() || token.getOperator() == Token::CLOSE_PARENTHESIS_OPERATOR) throw runtime_error("Token is not operator or close parenthesis");
    if (token.getOperator() == Token::OPEN_PARENTHESIS_OPERATOR)
        return 0;
    else if (token.getOperator() == Token::MULTIPLICATION_OPERATOR || token.getOperator() == Token::DIVISION_OPERATOR)
        return 1;
    else
        return 2;
}

int getInStackPriority(Token token) {
    if (!token.isOperator() || token.getOperator() == Token::CLOSE_PARENTHESIS_OPERATOR) throw runtime_error("Token is not operator or close parenthesis");
    if (token.getOperator() == Token::MULTIPLICATION_OPERATOR || token.getOperator() == Token::DIVISION_OPERATOR)
        return 1;
    else if (token.getOperator() == Token::ADDITION_OPERATOR || token.getOperator() == Token::SUBTRACTION_OPERATOR)
        return 2;
    else
        return 3;
}

vector<Token> postfix(const vector<Token>& expression) {
    vector<Token> post;
    LinkedStack<Token> temp;
    Token x;
    for (int i = 0; i < expression.size(); i++){
        x = expression[i];
        if (x.isConstant())
            post.push_back(x);
        else if (x.getOperator() == Token::OPEN_PARENTHESIS_OPERATOR){
            temp.push(x);
        }
        else if (x.getOperator() == Token::CLOSE_PARENTHESIS_OPERATOR){
            while (true){
                if (temp.top().isOperator() && temp.top().getOperator() == Token::OPEN_PARENTHESIS_OPERATOR){
                    temp.pop();
                    break;
                }
                else{
                    post.push_back(temp.top());
                    temp.pop();
                }
            }
        }
        else {
            while (!temp.empty() && getInStackPriority(temp.top()) <= getInStackPriority(x)) {
                post.push_back(temp.top());
                temp.pop();
            }
            temp.push(x);
        }
    }
    while(!temp.empty()){
        post.push_back(temp.top());
        temp.pop();
    }
    return post;
}


int eval(const vector<Token>& expression) {
    LinkedStack<Token> temp;
    Token x;
    int result = 0;

    if (expression.empty()) throw runtime_error("Cannot evaluate an empty expression.");
    if (expression.size() == 1){
        x = expression[0];
        if (x.isConstant()){
            result = x.getConstant();
            return result;
        }
        else
            throw runtime_error("Cannot apply an operator to an empty stack.");
    }
    bool check = false;
    for (int i = 0; i < expression.size(); i++){
        x = expression[i];
        if (x.isConstant()){
            temp.push(x);
            check = true;
        }
        else{
            if (temp.empty()){
                if (check == false) throw runtime_error("Cannot apply an operator to an empty stack.");
                else throw runtime_error("Cannot apply an operator to a stack with one integer only.");
            }
            int val1 = temp.top().getConstant();
            temp.pop();
            if (temp.empty()){
                if (check == false) throw runtime_error("Cannot apply an operator to an empty stack.");
                else throw runtime_error("Cannot apply an operator to a stack with one integer only.");
            }
            int val2 = temp.top().getConstant();
            temp.pop();
            if (x.getOperator() == Token::ADDITION_OPERATOR)
                result = val2 + val1;
            else if (x.getOperator() == Token::SUBTRACTION_OPERATOR)
                result = val2 - val1;
            else if (x.getOperator() == Token::DIVISION_OPERATOR)
                result = val2 / val1;
            else if (x.getOperator() == Token::MULTIPLICATION_OPERATOR)
                result = val2 * val1;
            temp.push(result);
        }
    }
    if (temp.size() > 1) throw runtime_error("Unfinished evaluation due to missing operators.");
    return result;
}
