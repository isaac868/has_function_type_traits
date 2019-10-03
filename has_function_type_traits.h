#pragma once
#include <type_traits>

#define MAKE_TYPE_TRAIT_HAS_STATIC_FUNCTION(TRAIT_NAME, FUNCTION_NAME)              \
namespace TRAIT_TYPE_HELPERS                                                        \
{                                                                                   \
/* Primary Template is false case, this is the default if */                        \
/* SFINAE causes the partial specialization to fail        */                       \
template <typename T, typename ReturnType, typename = void, typename ... ARGS>      \
struct TRAIT_NAME##_helper : std::false_type {};                                    \
                                                                                    \
/* Partially specialized templated is true case, this will*/                        \
/* be instantiated if SFINAE doesnt fail                  */                        \
template <typename T, typename ReturnType, typename ... ARGS>                       \
struct TRAIT_NAME##_helper <T, ReturnType, std::enable_if_t< std::is_same_v< decltype(&T::FUNCTION_NAME), ReturnType(*)(ARGS...)>>, ARGS...> : std::true_type {}; \
}                                                                                   \
                                                                                    \
/* This using directive serves to mask the third template */                        \
/* parameter that is used for the SFINAE implementation   */                        \
template <typename T, typename ReturnType, typename ... ARGS>                       \
using TRAIT_NAME = TRAIT_TYPE_HELPERS::TRAIT_NAME##_helper<T, ReturnType, void, ARGS...>; \
                                                                                    \
/* This templated bool is used as a shortcut for ::value  */                        \
/* This is inline with the STL type traits                */                        \
template <typename T, typename ReturnType, typename ... ARGS>                       \
constexpr bool TRAIT_NAME##_v = TRAIT_NAME<T, ReturnType, ARGS...>::value;

//Creates a type trait definition that has the name TRAIT_NAME and checks for a member function FUNCTION_NAME
#define MAKE_TYPE_TRAIT_HAS_MEMBER_FUNCTION(TRAIT_NAME, FUNCTION_NAME)              \
namespace TRAIT_TYPE_HELPERS                                                        \
{                                                                                   \
/* Primary Template is false case, this is the default if */                        \
/* SFINAE causes the partial specialization to fail       */                        \
template <typename T, typename ReturnType, typename = void, typename ... ARGS>      \
struct TRAIT_NAME##_helper : std::false_type {};                                    \
                                                                                    \
/* Partially specialized templated is true case, this will*/                        \
/* be instantiated if SFINAE doesnt fail                  */                        \
template <typename T, typename ReturnType, typename ... ARGS>                       \
struct TRAIT_NAME##_helper <T, ReturnType, std::enable_if_t< std::is_same_v< decltype(&T::FUNCTION_NAME), ReturnType(T::*)(ARGS...)>>, ARGS...> : std::true_type {}; \
}                                                                                   \
                                                                                    \
/* This using directive serves to mask the third template */                        \
/* parameter that is used for the SFINAE implementation   */                        \
template <typename T, typename ReturnType, typename ... ARGS>                       \
using TRAIT_NAME = TRAIT_TYPE_HELPERS::TRAIT_NAME##_helper<T, ReturnType, void, ARGS...>; \
                                                                                    \
/* This templated bool is used as a shortcut for ::value  */                        \
/* This is inline with the STL type traits                */                        \
template <typename T, typename ReturnType, typename ... ARGS>                       \
constexpr bool TRAIT_NAME##_v = TRAIT_NAME<T, ReturnType, ARGS...>::value;