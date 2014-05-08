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
     *  Private as you should just use BooleanValue::get(bool) to get one of
     *  the global ones.
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
    virtual const char *toString() override
    {
        return "";
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() override
    {
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() override
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
    virtual Value *member(const char *name, size_t size) override
    {
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Value *member(int position) override
    {
        return nullptr;
    }

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Variant key(int position) override
    {
        return Variant();
    }

    /**
     *  String length of the variable
     *
     *  @return int
     */
    virtual size_t size() override
    {
        return 0;
    }

    /**
     *  Method used to get a instance of this value
     */
    virtual Variant cache() override
    {
        return Variant();
    }
};

/**
 *  End namespace
 */
}