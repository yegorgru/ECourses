#include <optional>
#include <list>
#include <string>
#include <memory>

#include "Number.h"

class ExpressionTree {
public:
    enum class Operation {
        PLUS = 0,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        NONE
    };

    enum class Token {
        LEFT = 0,
        DIGIT,
        RIGHT,
        OPERATION,
        NONE
    };

    class Node {
    public:
        Node(std::string::const_iterator begin, std::string::const_iterator end);

        void FromString(std::string::const_iterator begin, std::string::const_iterator end);

        void Calculate();

        Number GetValue();

    private:
        bool negation;
        std::list<Operation> operations;
        std::list<std::shared_ptr<Node>> nodes;
        std::optional<Number> value;
    };

    ExpressionTree(const std::string& str);

    void SetExpression(const std::string& str);

    Number Calculate();

    static bool CheckValidity(std::string::const_iterator begin, std::string::const_iterator end);

private:
    std::shared_ptr<Node> root;
};