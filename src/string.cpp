#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>

#include <query/FunctionDescription.h>
#include <query/FunctionLibrary.h>
#include <query/Operator.h>
#include <query/TypeSystem.h>

using namespace scidb;
using namespace boost::assign;

void strcat(const Value** arguments, Value* result, void*)
{
  const std::string lhs = std::string(arguments[0]->getString());
  const std::string rhs = std::string(arguments[1]->getString());
  result->setString((lhs + rhs).c_str());
}

void strlower(const Value** arguments, Value* result, void*)
{
  result->setString(boost::to_lower_copy(std::string(arguments[0]->getString())).c_str());
}

void strupper(const Value** arguments, Value* result, void*)
{
  result->setString(boost::to_upper_copy(std::string(arguments[0]->getString())).c_str());
}

void strtrim(const Value** arguments, Value* result, void*)
{
  result->setString(boost::trim_copy(std::string(arguments[0]->getString())).c_str());
}

REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_STRING), TID_STRING, strcat);
REGISTER_FUNCTION(strlower, list_of(TID_STRING), TID_STRING, strlower);
REGISTER_FUNCTION(strupper, list_of(TID_STRING), TID_STRING, strupper);
REGISTER_FUNCTION(strtrim, list_of(TID_STRING), TID_STRING, strtrim);

