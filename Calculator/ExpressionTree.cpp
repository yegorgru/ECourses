#include "pch.h"

#include <stdexcept>

#include "ExpressionTree.h"

ExpressionTree::ExpressionTree(const std::string& str) {
    SetExpression(str);
}

void ExpressionTree::SetExpression(const std::string& str) {
    if (!CheckValidity(str.begin(), str.end())) throw std::logic_error("Incorrect expression");
    root = std::make_shared<Node>(Node(str.begin(), str.end()));
}

Number ExpressionTree::Calculate(){
    this->root->Calculate();
    return this->root->GetValue();
}

bool ExpressionTree::CheckValidity(std::string::const_iterator begin, std::string::const_iterator end) {
    if (end - begin == 0) {
        return false;
    }
    int parenthesisCounter = 0;
    Token last = Token::NONE;
    for (auto it = begin; it != end; ++it) {
        if (*it == '(') {
            if (last == Token::RIGHT || last == Token::DIGIT) return false;
            parenthesisCounter++;
            last = Token::LEFT;
        }
        else if (*it == ')') {
            if (last == Token::OPERATION || last == Token::LEFT || last == Token::NONE) return false;
            last = Token::RIGHT;
            parenthesisCounter--;
            if (parenthesisCounter < 0) return false;
        }
        else if (*it == '*' || *it == '/' || *it == '+') {
            if (last == Token::LEFT || last == Token::OPERATION || last == Token::NONE) return false;
            last = Token::OPERATION;
        }
        else if (*it == '-') {
            if (last == Token::OPERATION) return false;
            last = Token::OPERATION;
        }
        else if (*it >= '0' && *it <= '9') {
            if (last == Token::RIGHT) return false;
            last = Token::DIGIT;
        }
        else return false;
    }
    if (parenthesisCounter != 0 || last == Token::OPERATION) return false;
    return true;
}

ExpressionTree::Node::Node(std::string::const_iterator begin, std::string::const_iterator end) {
    this->negation = false;
    FromString(begin, end);
}

void ExpressionTree::Node::FromString(std::string::const_iterator begin, std::string::const_iterator end) {
    int leftParenthnes = 0;
    auto cur = begin;
    while (*cur == '(') {
        leftParenthnes++;
        cur++;
    }
    int minLeftParenthness = leftParenthnes;
    while (cur < end - leftParenthnes) {
        if (*cur == ')') {
            leftParenthnes--;
        }
        else if (*cur == '(') {
            leftParenthnes++;
        }
        if (leftParenthnes < minLeftParenthness) {
            minLeftParenthness = leftParenthnes;
        }
        cur++;
    }
    if (minLeftParenthness != 0) {
        begin += minLeftParenthness;
        end -= minLeftParenthness;
    }
    bool firstNegation = *begin == '-';
    std::list<std::string::const_iterator> op1;
    std::list<std::string::const_iterator> op2;
    int parenthesisCounter = 0;
    for (auto it = begin; it != end; ++it) {
        if (*it == '(') parenthesisCounter++;
        else if (*it == ')') {
            parenthesisCounter--;
        }
        if (parenthesisCounter == 0 && (*it == '-' || *it == '+') && it-begin > 0) {
            op1.push_back(it);
        }
        else if (parenthesisCounter == 0 && (*it == '*' || *it == '/')) {
            op2.push_back(it);
        }
    }
    if (op1.size() == 0 && op2.size() == 0) {
        if (!firstNegation) {
            this->value = std::optional<Number>(Number(std::string(begin, end)));
        }
        else {
            this->negation = true;
            this->nodes.push_back(std::make_shared<Node>(Node(begin + 1, end)));
        }
    }
    else if (op1.size() > 0) {
        op1.push_back(end);
        this->nodes.push_back(std::make_shared<Node>(Node(begin, op1.front())));
        for (auto it = op1.begin(); *it != end; ++it) {
            this->nodes.push_back(std::make_shared<Node>(Node(std::next(*it), *std::next(it))));
            switch (**it) {
            case '+':
                this->operations.push_back(Operation::PLUS);
                break;
            case '-':
                this->operations.push_back(Operation::MINUS);
                break;
            }
        }
    }
    else {
        op2.push_back(end);
        this->nodes.push_back(std::make_shared<Node>(Node(begin, op2.front())));
        for (auto it = op2.begin(); *it != end; ++it) {
            this->nodes.push_back(std::make_shared<Node>(Node(std::next(*it), *std::next(it))));
            switch (**it) {
            case '*':
                this->operations.push_back(Operation::MULTIPLICATION);
                break;
            case '/':
                this->operations.push_back(Operation::DIVISION);
                break;
            }
        }
    }
}

void ExpressionTree::Node::Calculate() {
    if (this->value == std::nullopt) {
        for (auto node : this->nodes) {
            node->Calculate();
        }
        Number result = *this->nodes.front()->value;
        if (this->negation) {
            this->value = std::optional<Number>(-result);
            return;
        }
        auto op = this->operations.begin();
        for (auto it = std::next(this->nodes.begin()); it != this->nodes.end(); it++, op++) {
            switch (*op) {
            case Operation::MINUS:
                result = result - *(*it)->value;
                break;
            case Operation::PLUS:
                result = result + *(*it)->value;
                break;
            case Operation::MULTIPLICATION:
                result = result * *(*it)->value;
                break;
            case Operation::DIVISION:
                if (*(*it)->value == Number("0")) throw std::logic_error("division by zero");
                result = result / *(*it)->value;
                break;
            }
        }
        this->value = std::optional<Number>(result);
    }
}

Number ExpressionTree::Node::GetValue() {
    return *value;
}