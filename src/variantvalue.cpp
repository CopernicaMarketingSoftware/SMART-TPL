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
VariantValue::VariantValue(int32_t value) : _value(new NumericValue(value)) {}
VariantValue::VariantValue(int64_t value) : _value(new NumericValue(value)) {}
VariantValue::VariantValue(double value) : _value(new DoubleValue(value)) {}
VariantValue::VariantValue(const char* value) : _value(new StringValue(value)) {}
VariantValue::VariantValue(const char* value, size_t len) : _value(new StringValue(value, len)) {}
VariantValue::VariantValue(const std::string& value) : _value(new StringValue(value)) {}
VariantValue::VariantValue(std::string&& value) : _value(new StringValue(std::move(value))) {}
VariantValue::VariantValue(const std::vector<VariantValue>& value) : _value(new VectorValue(value)) {};
VariantValue::VariantValue(std::vector<VariantValue>&& value) : _value(new VectorValue(std::move(value))) {};
VariantValue::VariantValue(const std::initializer_list<VariantValue>& value) : _value(new VectorValue(value)) {};
VariantValue::VariantValue(const std::map<std::string, VariantValue>& value) : _value(new MapValue(value)) {};
VariantValue::VariantValue(std::map<std::string, VariantValue>&& value) : _value(new MapValue(std::move(value))) {};
VariantValue::VariantValue(const std::initializer_list<std::map<std::string, VariantValue>::value_type>& value) : _value(new MapValue(value)) {};

/**
 *  End namespace
 */
}