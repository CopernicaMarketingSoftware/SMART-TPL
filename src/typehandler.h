/**
 *  TypeHandler.h
 * 
 *  Class that keeps track of the types of the variables that have been assigned
 * 
 *  @author     David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright  2019 Copernica BV
 */

/**
 *  Dependencies
 */
#include "expressions/expression.h"

/**
 *  Set up namespaces
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class TypeHandler {
private:
    /**
     *  Internal map that keeps track of token => type assigns
     *  @var std::map<string, Type>
     */
    std::map<std::string, Expression::Type> _map;

public:

    /**
     *  Store the type of a newly assigned variable
     *  @param std::string
     *  @param Expression::Type
     */
    void store(const std::string &key, Expression::Type type) 
    {
        // Insert into the map (or overwrite if it already exists)
        _map[key] = type;
    }

    /**
     *  Fetch the type of an assigned variable. If the variable is not known,
     *  this will return the Value (unknown) type
     *  @param  std::string
     *  @return Expression::Type
     */
    Expression::Type get(const std::string &key) 
    {
        // If we know the key, return the type of variable
        if (_map.find(key) != _map.end()) return _map[key];

        // Not found, return Value type
        return Expression::Type::Value;
    }
};

/**
 *  End of namespaces
 */
}}