/**
 *  VariantValue.cpp
 *
 *  Implementation of the VariantValue class
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Constructors, one for most scalar types
 */
VariantValue::VariantValue() : _value(new NullValue()) {}
VariantValue::VariantValue(std::nullptr_t value) : _value(new NullValue()) {}
VariantValue::VariantValue(bool value) : _value(new BoolValue(value)) {}
VariantValue::VariantValue(int16_t value) : _value(new NumericValue(value)) {}
VariantValue::VariantValue(int32_t value) : _value(new NumericValue(value)) {}
VariantValue::VariantValue(int64_t value) : _value(new NumericValue(value)) {}
VariantValue::VariantValue(double value) : _value(new DoubleValue(value)) {}
VariantValue::VariantValue(const char* value) : _value(value ? (Value *)new StringValue(value) : (Value *)new NullValue()) {}
VariantValue::VariantValue(const char* value, size_t len) : _value(value ? (Value *)new StringValue(value, len) : (Value *)new NullValue()) {}
VariantValue::VariantValue(std::string value) : _value(new StringValue(std::move(value))) {}
VariantValue::VariantValue(const std::vector<VariantValue>& value) : _value(new VectorValue(value)) {};
VariantValue::VariantValue(std::vector<VariantValue>&& value) : _value(new VectorValue(std::move(value))) {};
VariantValue::VariantValue(const std::initializer_list<VariantValue>& value) : _value(new VectorValue(value)) {};
VariantValue::VariantValue(const std::map<std::string, VariantValue>& value) : _value(new MapValue(value)) {};
VariantValue::VariantValue(std::map<std::string, VariantValue>&& value) : _value(new MapValue(std::move(value))) {};
VariantValue::VariantValue(const std::initializer_list<std::map<std::string, VariantValue>::value_type>& value) : _value(new MapValue(value)) {};

/**
 *  Assignment operators, one for most scalar types just like the constructors
 */
VariantValue& VariantValue::operator=(std::nullptr_t value) { _value.reset(new NullValue()); return *this; }
VariantValue& VariantValue::operator=(bool value) { _value.reset(new BoolValue(value)); return *this; }
VariantValue& VariantValue::operator=(int16_t value) { _value.reset(new NumericValue(value)); return *this; }
VariantValue& VariantValue::operator=(int32_t value) { _value.reset(new NumericValue(value)); return *this; }
VariantValue& VariantValue::operator=(int64_t value) { _value.reset(new NumericValue(value)); return *this; }
VariantValue& VariantValue::operator=(double value) { _value.reset(new DoubleValue(value)); return *this; }
VariantValue& VariantValue::operator=(const char* value) { _value.reset(value ? (Value *)new StringValue(value) : (Value *)new NullValue()); return *this; }
VariantValue& VariantValue::operator=(std::string value) { _value.reset(new StringValue(std::move(value))); return *this; }
VariantValue& VariantValue::operator=(const std::vector<VariantValue>& value) { _value.reset(new VectorValue(value)); return *this; }
VariantValue& VariantValue::operator=(std::vector<VariantValue>&& value) { _value.reset(new VectorValue(std::move(value))); return *this; }
VariantValue& VariantValue::operator=(const std::initializer_list<VariantValue>& value) { _value.reset(new VectorValue(value)); return *this; }
VariantValue& VariantValue::operator=(const std::map<std::string, VariantValue>& value) { _value.reset(new MapValue(value)); return *this; }
VariantValue& VariantValue::operator=(std::map<std::string, VariantValue>&& value) { _value.reset(new MapValue(std::move(value))); return *this; }
VariantValue& VariantValue::operator=(const std::initializer_list<std::map<std::string, VariantValue>::value_type>& value) { _value.reset(new MapValue(value)); return *this; }

/**
 *  End namespace
 */
}
