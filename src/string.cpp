#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>

#include <query/FunctionDescription.h>
#include <query/FunctionLibrary.h>
#include <query/Operator.h>
#include <query/TypeSystem.h>

using namespace scidb;
using namespace boost::assign;

void string_add(const Value** arguments, Value* result, void*)
{
  const std::string lhs = std::string(arguments[0]->getString());
  const std::string rhs = std::string(arguments[1]->getString());
  result->setString((lhs + rhs).c_str());
}

void string_len(const Value** arguments, Value* result, void*)
{
  result->setInt64(std::string(arguments[0]->getString()).size());
}

void string_to_lower(const Value** arguments, Value* result, void*)
{
  result->setString(boost::to_lower_copy(std::string(arguments[0]->getString())).c_str());
}

void string_to_upper(const Value** arguments, Value* result, void*)
{
  result->setString(boost::to_upper_copy(std::string(arguments[0]->getString())).c_str());
}

void string_trim(const Value** arguments, Value* result, void*)
{
  result->setString(boost::trim_copy(std::string(arguments[0]->getString())).c_str());
}

REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_STRING), TID_STRING, string_add);
REGISTER_FUNCTION(len, list_of(TID_STRING), TID_INT64, string_len);
REGISTER_FUNCTION(to_lower, list_of(TID_STRING), TID_STRING, string_to_lower);
REGISTER_FUNCTION(to_upper, list_of(TID_STRING), TID_STRING, string_to_upper);
REGISTER_FUNCTION(trim, list_of(TID_STRING), TID_STRING, string_trim);

