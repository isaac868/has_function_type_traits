# has_function_type_traits
Two generator macros that make type traits to check whether a static or member function exists in a class.

## Example
The `MAKE_TYPE_TRAIT_HAS_MEMBER_FUNCTION` and `MAKE_TYPE_TRAIT_HAS_STATIC_FUNCTION` can be used in a project to generate type traits with a given name that check for a given fucntions existence.

For example:
```C++
MAKE_TYPE_TRAIT_HAS_STATIC_FUNCTION(has_create, CREATE)

template <typename T> 
void HasCreate()
{
  if constexpr (has_create<T, char, int, int>::value)
  {
    std::cout<<"Has CREATE, takes two ints and returns a char"<<std::endl;
  }
  
  if constexpr (has_create_v<T, std::string, float, int>)
  {
    std::cout<<"Has CREATE, takes float and an int, returns a string"<<std::endl;
  }
}
```

## Notes
The traits do not support qualifiers such as const, volatile, lvalue ref-qualifier, or rvalue ref-qualifier. however, it shouldn't be hard to implement these in the future.
