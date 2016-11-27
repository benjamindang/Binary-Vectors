/** @file BinaryVectors.cpp
 @author [Benjamin Dang]
 @date [October 14, 2016]
 
 [This program is designed to fully implement a class called Integer. The Integer class is designed to store user inputed integers as vectors of boolean's to represent their binary equivalence in sign and magnitude form. The class relies on operator overloading to allow more convient access to performing addition, mulitplication, and subtraction with Integer objects, which is all done through bitwise arithmetic. Furthermore, these objects can be input as a negtive or positive integer. The class also overloads many of the comparison operators, pre and post fix increment/decrement, as well as bitwise operations. Nonmember functions featured in the program are a base addition and multiplicaiton function, as well as operator overaloading for comparison operators.]
 
 */
#include <iostream>
#include <vector>
#include <cmath>

class Integer {
public:
    Integer();
    Integer (int a);
    Integer(std::vector<bool> v);
    
    void operator += (const Integer& rhs);
    void operator -= (const Integer& rhs);
    void operator *= (const Integer& rhs);
    
    Integer operator + (const Integer& rhs) const;
    Integer operator - (const Integer& rhs) const;
    Integer operator * (const Integer& rhs) const;
    
    Integer operator++();
    Integer  operator++(int);
    Integer operator--();
    Integer  operator--(int);
    
    Integer operator+();
    Integer operator-();
    
    bool operator<(const Integer& rhs) const;
    bool operator==(const Integer& rhs) const;
    
    void print_as_bits() const;
    std::vector<bool> acess_bit() const;
    void same_size(Integer& rhs);
    void same_size_complement(const Integer& rhs);
    std::vector<bool> twos_complement() const;
    std::vector<bool> complement_to_magnitude() const;
private:
    std::vector<bool> bit;
    void clean_up();
    
};

//These non-member functions are the addition and multiplication functions solely implemented for positive integers.
Integer plus(const Integer& lhs, const Integer& rhs);
Integer multiply(const Integer& lhs, const Integer& rhs);

//The following functions allow for comparison of two Integer objects by utilizing the Integer class member functions.
bool operator > (const Integer& lhs, const Integer& rhs){return rhs < lhs;}
bool operator >= (const Integer& lhs, const Integer& rhs){return !(lhs < rhs);}
bool operator <= (const Integer& lhs, const Integer& rhs){return !(lhs > rhs);}
bool operator != (const Integer& lhs, const Integer& rhs){return !(lhs == rhs);}

int main(){
    int int_value;
    
    std::cout << "Please input an integer a: ";
    std::cin >> int_value;
    Integer a = int_value;
    
    std::cout << "The base-2 representaion of a is: "; a.print_as_bits(); std::cout << std::endl;
    
    std::cout << "Please input an integer b: ";
    std::cin >> int_value ;
    Integer b = int_value;
    
    std::cout << "The base-2 representaion of b is: "; b.print_as_bits(); std::cout << std::endl;
    
    Integer plusequals = a; plusequals += b;
    plusequals.print_as_bits(); std::cout << std::endl;
    
    Integer minusequals = a; minusequals -= b;
    minusequals.print_as_bits(); std::cout << std::endl;
    
    Integer timesequals = a; timesequals *= b;
    timesequals.print_as_bits(); std::cout << std::endl;
    
    Integer plus = a+b; plus.print_as_bits(); std::cout << std::endl;
    Integer minus = a-b; minus.print_as_bits(); std::cout << std::endl;
    Integer times = a*b; times.print_as_bits(); std::cout << std::endl;
    
    Integer prefix_increment = ++a; prefix_increment.print_as_bits(); std::cout << std::endl;
    Integer postfix_increment = a++;  postfix_increment.print_as_bits(); std::cout << std::endl;
    Integer prefix_decrement = --a; prefix_decrement.print_as_bits (); std::cout << std::endl;
    Integer postfix_decrement = a--  ; postfix_decrement.print_as_bits () ; std::cout << std::endl;
    
    Integer negative = -a ; negative.print_as_bits();std::cout << std::endl ;
    Integer positive = +b ; positive.print_as_bits();std::cout << std::endl ;
    
    std::cout << "Please input an integer c: ";
    std::cin >> int_value;
    Integer c = int_value;
    
    std::cout << "The base-2 representaion of c is: "; c.print_as_bits(); std::cout << std::endl;
    
    std::cout << "Please input an integer d: ";
    std::cin >> int_value ;
    Integer d = int_value;
    
    std::cout << "The base-2 representaion of d is: "; d.print_as_bits(); std::cout << std::endl;
    
    if(c<d) std::cout<<"c<d"<<std::endl;
    if(c<=d) std::cout<<"c<=d"<<std::endl;
    if(c>d) std::cout<<"c>d"<<std::endl;
    if(c>=d) std::cout<<"c>=d"<<std::endl;
    if(c==d) std::cout<<"c==d"<<std::endl;
    if(c!=d) std::cout<<"c!=d"<<std::endl;

    return 0;
}

/**Default Constructor, Constructs an Integer variable equal to 0
 */
Integer::Integer()
{
    std::vector<bool> bit;
}

/**Constructor with a vector of booleans parameter
 @param v is any vector of booleans that represent a binary number to be stored in an Integer object
 */
Integer::Integer(std::vector<bool> v)
{
    bit = v;
}

/**Constructor with an unsigned int parameter
 @param a is any unsigned int to be converted into binary and stored in a boolean vector
 */
Integer::Integer(int a)
{
    if(a < 0)
    {
        a = a * -1;
        while(a > 0)
        {
            bit.push_back(a%2);
            a/= 2;
        }
        bit.push_back(1);
    }
    else if(a == 0)
        bit.push_back(0);
    else if(a > 0)
    {
        while(a > 0)
        {
            bit.push_back(a%2);
            a/= 2;
        }
        bit.push_back(0);
    }
}

/**Plus equals operator for two Integer objects. Modifies the left hand side of the operator to equal the sum of the two objects. Utilies many if and else if statements to account for different combinations of negative numbers.
 @param rhs right hand side of the plus equals function
 */
void Integer::operator+=(const Integer& rhs)
{
    Integer sum;
    std::vector<bool> lefths = bit;
    std::vector<bool> righths = rhs.acess_bit();
    if(!lefths[lefths.size()-1] && !righths[righths.size()-1])
    {
        lefths.pop_back(); righths.pop_back();
        Integer left(lefths); Integer right(righths);
        sum = plus(left,right);
        bit = sum.bit;
        bit.push_back(0);
    }
    
    else if(lefths[lefths.size()-1] && !righths[righths.size()-1])
    {
        Integer left(lefths);
        std::vector<bool> lhs_complement = left.twos_complement();
        righths.pop_back(); lefths.pop_back();
        Integer right(righths); Integer left_complement(lhs_complement);
        left_complement.same_size_complement(right);
        sum = plus(left_complement,right);
        bit = sum.bit;
        Integer comparison_left(lefths); Integer comparison_right(righths);
        if(comparison_left < comparison_right)
        {
            bit.pop_back();
            Integer cleaner(bit);
            cleaner.clean_up();
            bit = cleaner.acess_bit();
            bit.push_back(0);
        }
        else if(comparison_right < comparison_left)
        {
            Integer needs_to_convert(bit);
            std::vector<bool> converted = needs_to_convert.complement_to_magnitude();
            Integer needs_to_clean(converted);
            needs_to_clean.clean_up();
            bit = needs_to_clean.acess_bit();
            bit.push_back(1);
        }
        else if(comparison_right == comparison_left)
        {
            while(bit.size() > 0)
            {
                bit.pop_back();
            }
            bit.push_back(0); bit.push_back(0);
        }
    }
    
    else if(!lefths[lefths.size()-1] && righths[righths.size()-1])
    {
        Integer right(righths);
        std::vector<bool> rhs_complement = right.twos_complement();
        lefths.pop_back(); righths.pop_back();
        Integer left(lefths); Integer right_complement(rhs_complement);
        right_complement.same_size_complement(left);
        sum = plus(left,right_complement);
        bit = sum.bit;
        Integer comparison_left(lefths); Integer comparison_right(righths);
        if(comparison_right < comparison_left)
        {
            bit.pop_back();
            Integer cleaner(bit);
            cleaner.clean_up();
            bit = cleaner.acess_bit();
            bit.push_back(0);
        }
        else if(comparison_left < comparison_right)
        {
            Integer needs_to_convert(bit);
            std::vector<bool> converted = needs_to_convert.complement_to_magnitude();
            Integer needs_to_clean(converted);
            needs_to_clean.clean_up();
            bit = needs_to_clean.acess_bit();
            bit.push_back(1);
        }
        else if(comparison_right == comparison_left)
        {
            while(bit.size() > 0)
            {
                bit.pop_back();
            }
            bit.push_back(0); bit.push_back(0);
        }
    }
    
    else if(lefths[lefths.size()-1] && righths[righths.size()-1])
    {
        Integer lhs(bit);
        Integer lhs_complement(lhs.twos_complement()); Integer rhs_complement(rhs.twos_complement());
        lhs_complement.same_size_complement(rhs_complement);
        rhs_complement.same_size_complement(lhs_complement);
        sum = plus(lhs_complement,rhs_complement);
        bit = sum.bit;
        Integer needs_to_convert(bit);
        std::vector<bool> converted = needs_to_convert.complement_to_magnitude();
        Integer needs_to_clean(converted);
        needs_to_clean.clean_up();
        bit = needs_to_clean.acess_bit();
        bit.push_back(1);
        
    }
}
/** Minus equals operator for two Integer objects. Modifies the left hand side of the operator to equal the difference of the two objects. Utilizes the mathametical property that a - b = a + -b
 @param rhs right hand side of the minus equals function
 */
void Integer::operator -=(const Integer& rhs)
{
    std::vector<bool> righths = rhs.acess_bit();
    if(righths[righths.size()-1])
    {
        righths.pop_back(); righths.push_back(0);
        Integer lefthand(bit); Integer righthand(righths);
        lefthand += righthand;
        bit = lefthand.bit;
    }
    else if(!righths[righths.size()-1])
    {
        righths.pop_back(); righths.push_back(1);
        Integer lefthand(bit); Integer righthand(righths);
        lefthand += righthand;
        bit = lefthand.bit;
    }
}
/**Times equals operator for two Integer objects. Modifies the left hand side of the operator to equal the product of the two objects. Utilizes non-member function multiply.
 @param rhs right hand side of the *= operator
 */
void Integer::operator *=(const Integer& rhs)
{
    std::vector<bool> sign_magnitude_left = bit;
    std::vector<bool> sign_magnitude_right = rhs.acess_bit();
    bool left = sign_magnitude_left[sign_magnitude_left.size()-1];
    bool right = sign_magnitude_right[sign_magnitude_right.size()-1];
    sign_magnitude_left.pop_back(); sign_magnitude_right.pop_back();
    Integer lefths(sign_magnitude_left); Integer righths(sign_magnitude_right);
    Integer product = multiply(lefths,righths);
    bit = product.acess_bit();
    bit.push_back(left^right);
}

/**Addition operator for any two Integer objects. Creates a copy of the left hand side of the addition operator and uses the += function on the copy, returning the sum in the copy of the left hand side. Neither of the Interger object inputs get modified.
 @param rhs right hand side of the + operator
 */
Integer Integer::operator+(const Integer& rhs) const
{
    Integer lefths(bit);
    lefths += rhs;
    return lefths;
}
/**Subtraction operator for any two Integer objects. Creates a copy of the lef thand side of the subtraction operator and uses the -= function on the copy, returning the difference in the copy of the left hand side.
 @param rhs right hand side of the - operator
 */
Integer Integer::operator-(const Integer& rhs) const
{
    std::vector<bool> righths = rhs.acess_bit();
    bool sign = righths[righths.size()-1];
    righths.pop_back();
    righths.push_back(!sign);
    Integer left(bit); Integer right(righths);
    left += right;
    return left;
}
/**Multiplication operator for any two Integer objects. Creates a copy of the left hand side of the subtraction operator and uses the *= function on the copy, returning the product in the copy of the left hand side.
 @param rhs right hand side of the * operator
 */
Integer Integer::operator*(const Integer& rhs) const
{
    Integer lefths(bit);
    lefths *= rhs;
    return lefths;
}

/**Prefix increment for any Integer object. Increment's an Integer object's private boolean vector by one.
 @return incremented new integer object containing increment of the input object
 */
Integer Integer::operator++()
{
    Integer value(bit);
    Integer increment(1);
    Integer incremented = value + increment;
    bit = incremented.bit;
    return incremented;
}
/**Postfix increment for any Integer object. Increment's an Integer object's private boolean vector by one.
 @param int dummy input used to separate between pre and postfix
 
 @return value the original value of the Integer object, before the increment
 */
Integer Integer::operator++(int)
{
    Integer value(bit);
    Integer increment(1);
    Integer incremented = value + increment;
    bit = incremented.bit;
    return value;
}

/**Prefix decrement for any Integer object. Decrement's an Integer object's private boolean vector by one.
 @return decremented new Integer object containing decrement of the input object
 */
Integer Integer::operator--()
{
    Integer value(bit);
    Integer decrement(-1);
    Integer decremented = value + decrement;
    bit = decremented.bit;
    return decremented;
    
}

/**Postfix decrement for any Integer object. Decrement's an Integer object's private boolean vector by one.
 @param int dummy input used to separate between pre and postfix
 @return value the original value of the Integer object, before the decrement
 */
Integer Integer::operator--(int)
{
    Integer value(bit);
    Integer increment(-1);
    Integer incremented = value + increment;
    bit = incremented.bit;
    return value;
}
/**Positive operator which effectively multiplies any Integer object by 1. Coincidentally, nothing is modified in this function.
 @return absolute Integer object times positive 1;
 */
Integer Integer::operator+()
{
    Integer positive(bit);
    return positive;
}

/**Negative operator which effectively multiplies any Integer object by 1. As Integer objects are stored in sign and magnitude form, this just switches the last bit.
 @return negative Integer object times negative 1;
 */
Integer Integer::operator-()
{
    bool sign = bit[bit.size()-1];
    bit.pop_back();
    bit.push_back(!sign);
    Integer negative(bit);
    return negative;
}

/**Less than operator for two Integer objects, returns a boolean value determined by comparing the two Integer objects.
 @param rhs right hand side of the less than operator
 @return less_than is a boolean true/false value stating whether it is true or not if the first, or left hand side, object is less than the rhs object.
 */
bool Integer::operator<(const Integer& rhs) const
{
    bool less_than = false;
    std::vector<bool> righths = rhs.acess_bit();
    
    if(bit[bit.size()-1] & !righths[righths.size()-1])
        less_than = true;
    if(!bit[bit.size()-1] & righths[righths.size()-1])
        less_than = false;
    else if(bit.size() < righths.size())
        less_than = true;
    else if(bit.size() == righths.size())
    {
        for(int i = bit.size()-1; i >= 0; i--)
        {
            if(bit[i] == false & righths[i] == true)
            {
                less_than = true;
                break;
            }
            else if(bit[i] == true & righths[i] == false)
            {
                break;
            }
        }
    }
    return less_than;
}

/**Equal to operator for two Integer objects, returns a boolean value determined by comparing the two Integer objects
 @param rhs right hand side of the is equal to operator
 @return equal_to is a boolean value that determines whether the first, or left hand side, object is equal to the rhs object.
 */
bool Integer::operator==(const Integer&rhs) const
{
    std::vector<bool> righths = rhs.acess_bit();
    bool equal_to = false;
    int counter = 0;
    if(bit.size() == righths.size())
    {
        for(int i = 0; i < bit.size(); i++)
        {
            if(bit[i] == righths[i])
                counter ++;
        }
        if(counter == bit.size())
            equal_to = true;
    }
    return equal_to;
}


/**This member function takes any Integer object and prints it as a the base_2 number it is equal to
 */
void Integer::print_as_bits() const
{
    std::vector<bool> copy = bit;
    std::vector<bool> temp_bit;
    std::vector<bool>::iterator first;
    if(copy[copy.size()-1] == 1)
    {
        std::cout << "-";
        copy.pop_back();
    }
    else
    {
        std::cout << " ";
        copy.pop_back();
    }
    std::cout<<"(";
    for(int i=0; i < copy.size(); i++)
    {
        first = temp_bit.begin();
        temp_bit.insert(first,copy[i]);
    }
    for(int i=0; i < temp_bit.size(); i++)
    {
        if(i == temp_bit.size()-1)
            std::cout << temp_bit[i];
        else
            std::cout << temp_bit[i] << " ";
    }
    std::cout << ")_2";
}

/**This member function takes any Integer object and allows access to its private variable
 @return returns the private variable bit for any Integer object without changing it
 */
std::vector<bool> Integer::acess_bit() const
{
    return bit;
}

/**This member function ensures that two Integer objects are the same size. However, these integer objects must both be positive numbers.
 @param rhs the second Integer object, who's size is to be compared to the first one.
 */
void Integer::same_size(Integer& rhs)
{
    std::vector<bool> lefths = bit;
    std::vector<bool> righths = rhs.acess_bit();
    if(lefths.size() > righths.size())
    {
        bool not_same_size = true;
        lefths.push_back(0);
        while (not_same_size)
        {
            righths.push_back(0);
            if (lefths.size() == righths.size())
                not_same_size = false;
        }
        rhs = righths;
    }
    else if(righths.size() > lefths.size())
    {
        bool not_same_size = true;
        while (not_same_size)
        {
            lefths.push_back(0);
            if (righths.size() == lefths.size())
                not_same_size = false;
        }
        bit = lefths;
    }
}
/**This member function ensures that an Integer object stored in two's compliment form and another object stored in any form are the same size. This function pushes back 1's to the two's compliment as opposed to the normal zeros to account for the conversion difference.
 @param rhs Integer object that must be in sign and magnitude form
 */
void Integer::same_size_complement(const Integer& rhs)
{
    std::vector<bool> righths = rhs.acess_bit();
    bool same_size = true;
    if(bit.size() < righths.size())
        same_size = false;
    while(!same_size)
    {
        bit.push_back(1);
        if(bit.size() == righths.size())
            same_size = true;
    }
}
/**This member function takes any Integer object and turns it into its two's compliment. This is done through the use of the same principles of negation.
 @return final_complement.bit returns the vector of booleans already converted into two's compliment form.
 */
std::vector<bool> Integer::twos_complement() const
{
    std::vector<bool> complement;
    for(int i = 0; i < bit.size(); i++)
    {
        if(bit[i])
            complement.push_back(0);
        if(!bit[i])
            complement.push_back(1);
    }
    complement.pop_back();
    complement.push_back(1);
    Integer plus_one(complement);
    Integer one(1);
    Integer final_complement = plus(plus_one,one);
    return final_complement.bit;
}

/**This member function takes any Integer object already in two's compliment form and changes it back into sign and magnitude form.
 @return magnitude vector of boolean values already converted back into sign and magnitude form
 */
std::vector<bool> Integer::complement_to_magnitude() const
{
    std::vector<bool> need_to_negate, magnitude;
    Integer needs_minus_one(bit);
    Integer negative_one(-1);
    Integer complement_negative_one(negative_one.twos_complement());
    std::vector<bool> acess_cnegative_one = complement_negative_one.acess_bit();
    if(bit.size() > acess_cnegative_one.size())
    {
        bool same_size = false;
        while(!same_size)
        {
            acess_cnegative_one.push_back(1);
            if(bit.size() == acess_cnegative_one.size())
                same_size = true;
        }
    }
    Integer sizing(acess_cnegative_one);
    Integer sum = plus(sizing, needs_minus_one);
    need_to_negate = sum.acess_bit();
    for(int i =0; i < need_to_negate.size(); i++)
    {
        if(need_to_negate[i])
            magnitude.push_back(0);
        if(!need_to_negate[i])
            magnitude.push_back(1);
    }
    return magnitude;
}

/**This functions use is to clear any extra zeros made through any form of changes on any Integer object. This is the only private member function in the whole class.
 */
void Integer::clean_up()
{
    bool leading_zero = false;
    if(!bit[bit.size()-1])
        leading_zero = true;
    
    while(leading_zero)
    {
        bit.pop_back();
        if(bit[bit.size()-1])
            leading_zero = false;
        if(bit.size()==2)
            leading_zero = false;
    }
}


/**This function computes the addition of two binary numbers stored in the Integer class
 
 @param lhs is the first Integer passed to the function, not to be modified but to be added with rhs
 @param rhs is the second Integer passed to the function, not to be modified but to be added with lhs
 @return Integer that is equal to lhs + rhs
 */
Integer plus(const Integer& lhs, const Integer& rhs)
{
    std::vector<bool> lefths = lhs.acess_bit();
    std::vector<bool> righths = rhs.acess_bit();
    if(lefths.size() > righths.size())
    {
        bool not_same_size = true;
        lefths.push_back(0);
        while (not_same_size)
        {
            righths.push_back(0);
            if (lefths.size() == righths.size())
                not_same_size = false;
        }
    }
    else if(righths.size() > lefths.size())
    {
        bool not_same_size = true;
        righths.push_back(0);
        while (not_same_size)
        {
            lefths.push_back(0);
            if (righths.size() == lefths.size())
                not_same_size = false;
        }
    }
    else
    {
        lefths.push_back(0);
        righths.push_back(0);
    }
    std::vector<bool> result;
    bool carry = false;
    for(int i =0; i < lefths.size(); i++)
    {
        if(!((lefths[i]^righths[i])^carry))
        {
            result.push_back(0);
            if((lefths[i] ^ righths[i]))
                carry = true;
            else if(lefths[i] & righths[i])
                carry = true;
        }
        else if(((lefths[i]^righths[i])^carry))
        {
            result.push_back(1);
            if(!lefths[i] & !righths[i])
                carry = false;
            else if(lefths[i] & righths[i])
                carry = true;
        }
        
    }
    if(!result[result.size()-1])
        result.pop_back();
    Integer final_result(result);
    return final_result;
}

/**This function computes the multiplication of two Integers by utilizing the properties that relate binary addition to multiplication
 @param lhs the first Integer to be multiplied, again not modified
 @param rhs the second Integer to be multiplied, again not modified
 @return returns an Integer that is equal to lhs*rhs
 */
Integer multiply(const Integer& lhs, const Integer& rhs)
{
    std::vector<bool>::iterator first;
    std::vector<bool> lefths = lhs.acess_bit();
    std::vector<bool> righths = rhs.acess_bit();
    std::vector<bool> additions;
    Integer final_result;
    for(int i = 0; i < lefths.size(); i++)
    {
        if(lefths[i])
        {
            std::vector<bool> temprighths = righths;
            for(int j = 0; j <= i-1; j++)
            {
                first = temprighths.begin();
                temprighths.insert(first,0);
            }
            additions = temprighths;
            Integer temporary_additions(additions);
            final_result = plus(final_result,temporary_additions);
        }
    }
    std::vector<bool> product = final_result.acess_bit();
    if(product.size() < 1)
        product.push_back(0);
    final_result = product;
    
    return final_result;
}
