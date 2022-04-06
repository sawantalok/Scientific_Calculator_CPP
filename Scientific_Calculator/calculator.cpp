/**************************************************************************
 *
 *       Program         :   calculator.cpp
 *       Purpose         :   Scientific Calculator
 *       Author          :   Alok Sawant
 *       Creation Date   :   26-10-2021
 *       Last Modified   :   Tue 26 Oct 16:36:45 2021
 *
 **************************************************************************/
# include <cmath>
# include "calculator.h"
# include "data_struct.h"


char *reverseString(const char *string, char length)
{
    auto tmp = (char*)malloc((length+1)*sizeof(char));
    if(!tmp)
    {
        return nullptr;
    }
    tmp[length]='\0';
    for(int i = 0; i< length; ++i)
    {
        tmp[i] = string[(length-1) - i];
    }
    return tmp;
}

float calculate(const char* eq, char start, char end, const float* vars)
{
    //first check if the enterd equation is valid
    if(end<=start)
    {
        return std::nan("");
    }

    //creating arrarys to store number and operators 
    Vector<float> numbers;
    Vector<char> plusIndex;
    Vector<char> multIndex;
    Vector<char> powIndex;

    auto tmp = (char*)malloc(max_num_len*sizeof(char));
    if(!tmp)
        return std::nanf("");
    char tmpc=0;
    char* reversed;

    //Parsing input eqation string from left to right 
    for(char i = end-1; i>= start; --i)
    {
        //This is to check if the input character is number or a decimal point
        if((eq[i] > 47 && eq[i] < 58)||(eq[i]==46))
        {
            if(tmpc >= max_num_len)
            {
                return std::nan("");
            }
            tmp[tmpc++] = eq[i];
        }

        else if(eq[i] == '+') //checking for + operator
        {
            if(tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                plusIndex.push(numbers.push(strtof(reversed, nullptr)));
                free(reversed);
                tmpc=0;
            }
            //For calculation like a++--+b is valid and equal to a+b
            else if(plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size() != *plusIndex.at(plusIndex.size() - 1)))
            {
                plusIndex.push(numbers.size());
            }
        }
        else if(eq[i] == '-') //checking for - operator
        {
            if(tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                plusIndex.push(numbers.push(-strtof(reversed, nullptr)));
                free(reversed);
                tmpc=0;
            }
            else if(plusIndex.size() == 0 || (plusIndex.size() > 0 && numbers.size()!= *plusIndex.at(plusIndex.size() - 1)))
            {
                *numbers.at(numbers.size() - 1)*=-1;
                plusIndex.push(numbers.size());
            }
            else
            {
                *numbers.at(numbers.size() - 1)*=-1;
            }
        }
        else if(eq[i] == '*') //checking for * operator
        {
            if(tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                multIndex.push(numbers.push(strtof(reversed, nullptr)));
                free(reversed);
                tmpc=0;
            }
            else if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size())
            {
                plusIndex.pop();
                multIndex.push(numbers.size());
            }
            else
            {
                multIndex.push(numbers.size());
            }
        }
        else if(eq[i] == '/') // checking for '/' operator
        {
            if(tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                multIndex.push(numbers.push((float)1/strtof(reversed, nullptr)));
                free(reversed);
                tmpc=0;
            }
            else if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size())
            {
                plusIndex.pop();
                (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
                multIndex.push(numbers.size());
            }
            else
            {
                (*numbers.at(numbers.size() - 1)) = 1 / (*numbers.at(numbers.size() - 1));
                multIndex.push(numbers.size());
            }
        }
        else if(eq[i] == '^') // checking for '^' operator
        {
            if(tmpc > 0)
            {
                reversed = reverseString(tmp, tmpc);
                multIndex.push(numbers.push(strtof(reversed, nullptr)));
                powIndex.push(numbers.size());
                free(reversed);
                tmpc=0;
            }
            else if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size())
            {
                plusIndex.pop();
                multIndex.push(numbers.size());
                powIndex.push(numbers.size());
            }
            else
            {
                multIndex.push(numbers.size());
                powIndex.push(numbers.size());
            }
        }
               else if(eq[i]==')')
        {
            //find a matching '(':
            char numClosingBrackets=0;
            char foundMatching=0;
            for(char j=i-1; j>=start; --j)
            {
                if(eq[j]==')')
                {
                    ++numClosingBrackets;
                }
                else if(eq[j]=='(' && numClosingBrackets>0)
                {
                    --numClosingBrackets;
                }
                else if(eq[j]=='(' && numClosingBrackets==0)
                {
                    //matching '(' found
                    if(!foundMatching) 
                    {
                        numbers.push(calculate(eq, j+1, i, vars));
                        i = j;         //this is to skip the part between () in parsing
                        foundMatching = 1;
                    }
                }
            }
            if(!foundMatching)
            {
                return std::nanf("");
            }
        }
        else
        {
            if(i>1 && eq[i]=='g' && eq[i-1]=='o' && eq[i-2]=='l')
            {
                if(numbers.size())
                    *numbers.at(numbers.size()-1) = log10(*numbers.at(numbers.size()-1));
                i-=2;
                if(plusIndex.size()>0 && *plusIndex.at(plusIndex.size()-1) == numbers.size()) 
                {
                    plusIndex.pop();
                }
            }
        }

    }
    //push to numbers array one last time
    if(tmpc>0)
    {
        reversed=reverseString(tmp,tmpc);
        if(!reversed)
            return std::nanf("");
        numbers.push(strtof(reversed,nullptr));
        free(reversed);
        tmpc=0;
    }
    if(numbers.size()==0)
        return std::nanf("");

    //we start with power a^b
    if(powIndex.size() > 0) 
    {
        for (char i = powIndex.size()-1; i>=0; --i)
        {
            //check if '^' is associated with two numbers:
            if(*powIndex.at(i)>= numbers.size())
                return std::nanf("");
            (*numbers.at(*powIndex.at(i)-1)) = pow((*numbers.at(*powIndex.at(i))),(*numbers.at(*powIndex.at(i)-1)));
            (*numbers.at(*powIndex.at(i))) = 1;
        }
    }
    if(multIndex.size() > 0) 
    {
        for (char i = multIndex.size()-1; i>=0  ; --i)
        {
            //check if '*' is associated with two numbers:
            if(*multIndex.at(i)>= numbers.size())
                return std::nanf("");
            (*numbers.at(*multIndex.at(i)-1)) *= (*numbers.at(*multIndex.at(i)));
        }
    }

    float result=*numbers.at(0);
    for (char i=0;i< plusIndex.size(); ++i)
    {
        result += *numbers.at(*plusIndex.at(i));
    }
    free(tmp);
    return result;
}
