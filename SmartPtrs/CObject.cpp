#include "CObject.h"

std::string CObject::foo() const
{
    return "foo";
}

std::string DerivedObject::foo() const
{
    return "derived foo";
}
