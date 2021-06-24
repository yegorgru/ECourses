#include "CObject.h"

std::string CObject::foo() const
{
    return "foo";
}

DerivedObject::DerivedObject(const std::string& s, int n) {}

std::string DerivedObject::foo() const
{
    return "derived foo";
}
