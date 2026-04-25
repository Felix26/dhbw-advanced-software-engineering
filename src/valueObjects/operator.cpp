#include "valueObjects/operator.h"

Operator::Operator(int id, const std::string &name) : operatorId(id), mName(name)
{

}

std::string Operator::getName() const
{
    return mName;
}

bool Operator::operator==(const Operator &other) const
{
    return this->operatorId == other.operatorId;
}

std::string Operator::getKeyTypeName()
{
    return "Betreiber";
}
