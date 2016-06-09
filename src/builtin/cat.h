/**
 *  Cat.h
 *
 *  Built-in "|cat:"string"" modifier
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class CatModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~CatModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // copy the entire string
        std::string output(input.toString());

        // Loop through the parameters and add all of them to the output string
        for (auto &param : params) output.append(param.toString());

        // return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}