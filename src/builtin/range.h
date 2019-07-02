/**
 *  Range.h
 *
 *  Built-in "|range" modifier, which truncates a list to a certain amount of items
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class RangeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~RangeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // if there are no parameters we're not touching the input
        if (params.size() == 0) throw NoModification();

        // try to retrieve the raw iterator
        auto rawIter = input.iterator();

        // if there's no raw iterator we just return the original input
        if (!rawIter) throw NoModification();

        // get our limits
        integer_t begin = 0;
        integer_t end = 0;

        // get our limits, if we only have 1 parameter we set that to the end
        if (params.size() == 1) end = params[0].toNumeric();
        else if (params.size() >= 2)
        {
            begin = params[0].toNumeric();
            end = params[1].toNumeric();
            end += begin;
        }

        // initialize our output value
        std::map<std::string, VariantValue> output;

        // let's keep a simple counter
        integer_t current = 1;

        // loop over all our values
        for (std::unique_ptr<Iterator> iter(rawIter); iter->valid(); iter->next(), ++current)
        {
            // if we're before our start we just continue
            if (begin > current) continue;
            else if (current > end) break; // if we're past our end we break out

            // and assign to our map
            output[iter->key().toString()] = iter->value();
        }

        // simply return our output, it'll be turned into a VariantValue automatically
        return output;
    }
};

/**
 *  End namespace
 */
}}
