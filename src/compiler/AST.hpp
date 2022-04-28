#include <string>
#include <memory>
#include <vector>

namespace AST {
    class ExprAST {
        public:
            virtual ~ExprAST() = default;
    };

    class NumberExprAST: public ExprAST {
        double Val;

        public:
            NumberExprAST(double Val): Val(Val) {}
    };

    class VariableExprAST: public ExprAST {
        std::string Name;

        public:
            VariableExprAST(std::string Name): Name(Name) {}
    };

    class BinaryExprAST: public ExprAST {
        char Op;
        std::unique_ptr<ExprAST> RHS, LHS;

        public:
            BinaryExprAST(char Op, std::unique_ptr<ExprAST> RHS, std::unique_ptr<ExprAST> LHS): Op(Op), RHS(std::move(RHS)), LHS(std::move(LHS)) {}
    };

    class CallExprAST: public ExprAST {
        std::string CallName;
        std::vector<std::unique_ptr<ExprAST>> Args;

        public:
            CallExprAST(std::string CallName, std::vector<std::unique_ptr<ExprAST>> Args): CallName(CallName), Args(std::move(Args)) {}
    };

    class PrototypeAST {
        std::string Name;
        std::vector<std::string> Args;

        public:
            PrototypeAST(const std::string &Name, std::vector<std::string> Args): Name(Name), Args(std::move(Args)) {};
            const std::string &getName() { return Name; };
    };

    class FunctionAST {
        std::unique_ptr<PrototypeAST> Prototype;
        std::unique_ptr<ExprAST> Body;

        public:
            FunctionAST(std::unique_ptr<PrototypeAST> Prototype, std::unique_ptr<ExprAST> Body): Prototype(std::move(Prototype)), Body(std::move(Body)) {}
    };
}