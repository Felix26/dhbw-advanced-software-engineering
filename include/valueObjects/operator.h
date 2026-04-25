#pragma once

#include <string>

class Operator
{
    public:
        Operator(int id, const std::string& name);
        ~Operator() = default;

        std::string getName() const;

        bool operator==(const Operator& other) const;

        static std::string getKeyTypeName();
    private:
        int operatorId;
        std::string mName;
};