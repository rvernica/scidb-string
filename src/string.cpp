#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>

#include <query/FunctionDescription.h>
#include <query/FunctionLibrary.h>
#include <query/Operator.h>
#include <query/TypeSystem.h>

using namespace scidb;
using namespace boost::assign;

void string_to_lower(const Value** args, Value* result, void*)
{
    result->setString(boost::to_lower_copy(std::string(args[0]->getString())).c_str());
}

void string_to_upper(const Value** args, Value* result, void*)
{
    result->setString(boost::to_upper_copy(std::string(args[0]->getString())).c_str());
}

void string_trim(const Value** args, Value* result, void*)
{
    result->setString(boost::trim_copy(std::string(args[0]->getString())).c_str());
}

REGISTER_FUNCTION(to_lower, list_of(TID_STRING), TID_STRING, string_to_lower);
REGISTER_FUNCTION(to_upper, list_of(TID_STRING), TID_STRING, string_to_upper);
REGISTER_FUNCTION(trim, list_of(TID_STRING), TID_STRING, string_trim);

