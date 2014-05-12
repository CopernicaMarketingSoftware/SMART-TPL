/**
 *  Boolean.h
 *
 *  Class that represents a boolean
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class BooleanValue : public Value
{
public:
    static BooleanValue *get(bool b)
    {
        if (b) return &_true;
        return &_false;
    }
private:
    /**
     *  Static instances of BooleanValue, we really only need 2 you know
     */
    static BooleanValue _true;
    static BooleanValue _false;

    /**
     *  The boolean value
     */
    const bool _boolean;
public:
    /**
     *  Constructor
     */
    BooleanValue(bool b) : _boolean(b) {};

    /**
     *  Deconstructor
     */
    virtual ~BooleanValue() {};
    /**
     *  Convert the variable to a string
     *  @return const char *
     */
    virtual const char *toString() const override
    {
        return "";
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() const override
    {
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        return _boolean;
    }

    /**
     *  Get access to a member variable
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Variant member(const char *name, size_t size) const override
    {
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() const override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Variant member(int position) const override
    {
        return nullptr;
    }

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Variant key(int position) const override
    {
        return nullptr;
    }

    /**
     *  String length of the variable
     *
     *  @return int
     */
    virtual size_t size() const override
    {
        return 0;
    }
};

/**
 *  End namespace
 */
}