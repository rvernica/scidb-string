#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>
#include <boost/lexical_cast.hpp>

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

// string + int/uint 8/16/32/64
#define STRCAT_S_RHS(RHS_T, RHS)                                        \
  void strcat_s_##RHS(const Value** arguments, Value* result, void*)    \
  {                                                                     \
    if (arguments[0]->isNull() || arguments[1]->isNull()) {             \
      result->setNull();                                                \
    } else {                                                            \
      const std::string lhs = std::string(arguments[0]->getString());   \
      const RHS_T rhs = arguments[1]->get##RHS();                       \
      result->setString(                                                \
        (lhs + boost::lexical_cast<std::string>(rhs)).c_str());         \
    }                                                                   \
  }

// int/uint 8/16/32/64 + string
#define STRCAT_LHS_S(LHS_T, LHS)                                        \
  void strcat_##LHS##_s(const Value** arguments, Value* result, void*)  \
  {                                                                     \
    if (arguments[0]->isNull() || arguments[1]->isNull()) {             \
      result->setNull();                                                \
    } else {                                                            \
      const LHS_T lhs = arguments[0]->get##LHS();                       \
      const std::string rhs = std::string(arguments[1]->getString());   \
      result->setString(                                                \
        (boost::lexical_cast<std::string>(lhs) + rhs).c_str());         \
    }                                                                   \
  }

// Use "(u)int16_t" for "(U)Int8" so lexical_cast does not treat it as char
STRCAT_S_RHS(int16_t,  Int8)
STRCAT_S_RHS(int16_t,  Int16)
STRCAT_S_RHS(int32_t,  Int32)
STRCAT_S_RHS(int64_t,  Int64)
STRCAT_S_RHS(uint16_t, Uint8)
STRCAT_S_RHS(uint16_t, Uint16)
STRCAT_S_RHS(uint32_t, Uint32)
STRCAT_S_RHS(uint64_t, Uint64)
STRCAT_S_RHS(float,    Float)
STRCAT_S_RHS(double,   Double)
STRCAT_LHS_S(int16_t,  Int8)
STRCAT_LHS_S(int16_t,  Int16)
STRCAT_LHS_S(int32_t,  Int32)
STRCAT_LHS_S(int64_t,  Int64)
STRCAT_LHS_S(uint16_t, Uint8)
STRCAT_LHS_S(uint16_t, Uint16)
STRCAT_LHS_S(uint32_t, Uint32)
STRCAT_LHS_S(uint64_t, Uint64)
STRCAT_LHS_S(float,    Float)
STRCAT_LHS_S(double,   Double)

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

REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_INT8),   TID_STRING, strcat_s_Int8 );
REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_INT16),  TID_STRING, strcat_s_Int16);
REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_INT32),  TID_STRING, strcat_s_Int32);
REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_INT64),  TID_STRING, strcat_s_Int64);

REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_UINT8) , TID_STRING, strcat_s_Uint8 );
REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_UINT16), TID_STRING, strcat_s_Uint16);
REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_UINT32), TID_STRING, strcat_s_Uint32);
REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_UINT64), TID_STRING, strcat_s_Uint64);

REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_FLOAT),  TID_STRING, strcat_s_Float);
REGISTER_FUNCTION(+, list_of(TID_STRING)(TID_DOUBLE), TID_STRING, strcat_s_Double);

REGISTER_FUNCTION(+, list_of(TID_INT8)  (TID_STRING), TID_STRING, strcat_Int8_s );
REGISTER_FUNCTION(+, list_of(TID_INT16) (TID_STRING), TID_STRING, strcat_Int16_s);
REGISTER_FUNCTION(+, list_of(TID_INT32) (TID_STRING), TID_STRING, strcat_Int32_s);
REGISTER_FUNCTION(+, list_of(TID_INT64) (TID_STRING), TID_STRING, strcat_Int64_s);

REGISTER_FUNCTION(+, list_of(TID_UINT8) (TID_STRING), TID_STRING, strcat_Uint8_s );
REGISTER_FUNCTION(+, list_of(TID_UINT16)(TID_STRING), TID_STRING, strcat_Uint16_s);
REGISTER_FUNCTION(+, list_of(TID_UINT32)(TID_STRING), TID_STRING, strcat_Uint32_s);
REGISTER_FUNCTION(+, list_of(TID_UINT64)(TID_STRING), TID_STRING, strcat_Uint64_s);

REGISTER_FUNCTION(+, list_of(TID_FLOAT) (TID_STRING), TID_STRING, strcat_Float_s );
REGISTER_FUNCTION(+, list_of(TID_DOUBLE)(TID_STRING), TID_STRING, strcat_Double_s);

REGISTER_FUNCTION(strlower, list_of(TID_STRING), TID_STRING, strlower);
REGISTER_FUNCTION(strupper, list_of(TID_STRING), TID_STRING, strupper);
REGISTER_FUNCTION(strtrim, list_of(TID_STRING), TID_STRING, strtrim);
