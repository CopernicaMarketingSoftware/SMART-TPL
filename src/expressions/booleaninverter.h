/**
 *  BinaryInverter.h
 *
 *  Implementation of the boolean inverter, used to implement the not and !
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BooleanInverter : public Expression
{
private:
    /**
     *  The expression we're going to invert
     *  @var    Expression
     */
    std::unique_ptr<Expression> _expression;

    /**
     *  A custom private generator which wraps around an existing Generator and
     *  inverts all the calls. equals becomes notEquals etc.
     */
    class InvertedGenerator : public Generator
    {
    private:
        /**
         *  The underlying Generator
         */
        Generator *_generator;

    public:
        /**
         *  Constructor
         *  @param  generator
         */
        InvertedGenerator(Generator *generator) : _generator(generator) {}

        /**
         *  Destructor
         */
        virtual ~InvertedGenerator() {};

        /**
         *  Generate code to output raw data
         *  @param  data                data to output
         */
        virtual void raw(const std::string &data) override { _generator->raw(data); };

        /**
         *  Generate the code to output a variable
         *  @param  variable           The variable to output
         */
        virtual void output(const Variable *variable) override { _generator->output(variable); };

        /**
         *  Generate the code to output the output of a filter
         *  @param  filter             The filter to eventually output
         */
        virtual void output(const Filter *filter) override { _generator->output(filter); };

        /**
         *  Generate the code to write an expression as a string
         *  @param  expression          the expression to write as a string
         */
        virtual void write(const Expression *expression) override { _generator->write(expression); };

        /**
         *  Generate a conditional statement
         *  @param  expression          the expression to evaluate
         *  @param  ifstatements        the statements in the 'if' part
         *  @param  elsestatements      the statements in the 'else' part
         */
        virtual void condition(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements) override { _generator->condition(expression, ifstatements, elsestatements); }

        /**
         *  Generate the code to get a pointer to a variable
         *  There are three formats, to get a pointer to a literal variable by name,
         *  to get a pointer to a variable inside a table with a literal name, and
         *  to get a pointer to a variable with variable name
         *  @param  parent              parent variable from which the var is retrieved
         *  @param  name                name of the variable
         *  @param  expression          Expression that evaluates to a var name
         */
        virtual void varPointer(const Variable *parent, const std::string &name) override { _generator->varPointer(parent, name); };
        virtual void varPointer(const Variable *parent, const Expression *expression) override { _generator->varPointer(parent, expression); }
        virtual void varPointer(const std::string &name) override { _generator->varPointer(name); }

        /**
         *  Create a string, numeric or boolean literal
         *  @param  value
         */
        virtual void string(const std::string &value) override { _generator->string(value); }
        virtual void numeric(numeric_t value) override { _generator->numeric(!value); }
        virtual void double_type(double value) override { _generator->double_type(!value); }

        /**
         *  Create a string, numeric or boolean constant for a variable
         *  @param  variable
         */
        virtual void stringVariable(const Variable *variable) override { _generator->stringVariable(variable); }
        virtual void numericVariable(const Variable *variable) override { _generator->numericVariable(variable); }
        virtual void doubleVariable(const Variable *variable) override { _generator->doubleVariable(variable); }
        virtual void variable(const Variable *variable) override { _generator->variable(variable); }

        // The boolean one has to be inverted
        virtual void booleanVariable(const Variable *variable) override
        {
            // create a temporary literal boolean
            LiteralBoolean tru(true);

            // our variable shouldn't be equal to this literal boolean
            _generator->notEquals(variable, &tru);
        }

        /**
         *  Arithmetric operations
         *  @param  left
         *  @param  right
         */
        virtual void plus(const Expression *left, const Expression *right) override { _generator->plus(left, right); }
        virtual void minus(const Expression *left, const Expression *right) override { _generator->minus(left, right); }
        virtual void divide(const Expression *left, const Expression *right) override { _generator->divide(left, right); }
        virtual void multiply(const Expression *left, const Expression *right) override { _generator->multiply(left, right); }
        virtual void modulo(const Expression *left, const Expression *right) override { _generator->modulo(left, right); }

        /**
         *  Comparison operators, these are all inverted. equals becomes notEquals, etc.
         *  @param  left
         *  @param  right
         */
        virtual void equals(const Expression *left, const Expression *right) override { _generator->notEquals(left, right); }
        virtual void notEquals(const Expression *left, const Expression *right) override { _generator->equals(left, right); }
        virtual void greater(const Expression *left, const Expression *right) override { _generator->lesser(left, right); }
        virtual void greaterEquals(const Expression *left, const Expression *right) override { _generator->lesserEquals(left, right); }
        virtual void lesser(const Expression *left, const Expression *right) override { _generator->greater(left, right); }
        virtual void lesserEquals(const Expression *left, const Expression *right) override { _generator->greaterEquals(left, right); }

        /**
         *  Boolean operators
         *  @param  left
         *  @param  right
         */
        virtual void booleanAnd(const Expression *left, const Expression *right) override { _generator->booleanAnd(left, right); }
        virtual void booleanOr(const Expression *left, const Expression *right) override { _generator->booleanOr(left, right); }

        /**
         *  Generate the code to apply a set of modifiers on an expression
         *  @param  modifiers          The set of modifiers to apply
         *  @param  variable           The variable to apply to modifers to
         */
        virtual void modifiers(const Modifiers *modifiers, const Variable *variable) override { _generator->modifiers(modifiers, variable); }
        /**
         *  Generate the code to apply a set of modifiers on an expression and turn it into a boolean
         *  @param  modifiers          The set of modifiers to apply
         *  @param  variable           The variable to apply the modifers to
         */
        virtual void modifiersBoolean(const Modifiers *modifiers, const Variable *variable) override { _generator->modifiersBoolean(modifiers, variable); }
        /**
         *  Generate the code to apply a set of modifiers on an expression and turn it into a double
         *  @param  modifiers          The set of modifiers to apply
         *  @param  variable           The variable to apply the modifiers to
         */
        virtual void modifiersDouble(const Modifiers *modifiers, const Variable *variable) override { _generator->modifiersDouble(modifiers, variable); }

        /**
         *  Generate the code to construct the following parameters
         *  @param  parameters         The parameters to construct
         *  @note Construct as in, generate the code so the runtime can construct them
         */
        virtual void parameters(const Parameters *parameters) override { _generator->parameters(parameters); }

        /**
         *  Generate the code to do a foreach loop over variable
         *  @param variable         The variable object to iterate over
         *  @param key              The magic variable name for the keys
         *  @param value            The magic variable name for the values
         *  @param statements       The statements to execute on each iteration
         *  @param else_statements  The statements to execute if there was nothing to loop through
         */
        virtual void foreach(const Variable *variable, const std::string &key, const std::string &value, const Statements *statements, const Statements *else_statements) override { _generator->foreach(variable, key, value, statements, else_statements); }

        /**
         *  Generate the code to assign the output of an expression to a key
         *  @param key                  The key to assign the output to
         *  @param expression           The expression to evaluate
         */
        virtual void assign(const std::string &key, const Expression *expression) override { _generator->assign(key, expression); }
    };

public:
    /**
     *  Constructor
     *  @param  expression
     */
    BooleanInverter(Expression *expression) : _expression(expression) {}

    /**
     *  Destructor
     */
    virtual ~BooleanInverter() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override { return Type::Boolean; };

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        // create an inverted generator
        InvertedGenerator inverted(generator);

        // call the boolean operation with this inverted generator
        _expression->boolean(&inverted);
    }
};

/**
 *  End of namespace
 */
}}