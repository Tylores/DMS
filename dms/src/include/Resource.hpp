/*******************************************************************************
Author: Tylor Slay
Project: ECE510 - EV project
Description: This class is build to emulate the EV battery information

Google C++ coding standard
--------------------------
https://google.github.io/styleguide/cppguide.html

General rules:
- Indents are two spaces. No tabs should be used anywhere.
- Each line must be at most 80 characters long.
- Comments can be // or /* but // is most commonly used.
- Avoid Abbreviations
- Type/Function Names: CamelCase
- Variable Names: lowercase_underscores
- Class Data Members: trailing_underscores_
- Constant Names: kName
- Enumerator/Macro Names: ALL_CAPS

Note: Please reference http://en.cppreference.com/w/cpp for additional help
*******************************************************************************/

#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED
#include <string>
#include <vector>
#include <map>

#include "ts_utility.hpp"
#include "CTA2045.hpp"

class Resource {
public :
    // member functions
    Resource (const tsu::config_map& init_map);
    ~Resource ();
    CTA2045 cta_module_;
    void Control ();
    std::map<std::string, unsigned int> GetProperties ();

private :
    // internal functions
    // - These functions are only for internal use and should not be used by
    //   outside classes.

private :
    // static member variables
    // - This is where you should put configuration variables

private :
    // dynamic member variables
    // - this is where you should put variables that will be updated within the
    //   control loops.

private :
    // distributed energy resource properties
    // - you must conform to the naming convention set for these properties and
    //   thier corresponding value types.
    std::map<std::string, unsigned int> properties_;
}; // end Resource

#endif // RESOURCE_H_INCLUDED
