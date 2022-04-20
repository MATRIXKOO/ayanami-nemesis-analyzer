#ifndef BORROW_CHECK_H_
#define BORROW_CHECK_H_
#include <concepts>
#include <string>
#include <type_traits>
namespace ANA
{
  template<typename Type>
  class CouldNotBeAdressedType
  {
   public:
    CouldNotBeAdressedType() = default;
    ~CouldNotBeAdressedType() = default;
    CouldNotBeAdressedType(const CouldNotBeAdressedType &) = delete;
    CouldNotBeAdressedType &operator=(const CouldNotBeAdressedType &) = delete;
    Type wrapper;
    inline void __SHOULD_NOT_BE_ADDRESSED();
  };

  template<typename Type>
  concept CouldNotBeAdressed = requires(Type t)
  {
    {
      t.__SHOULD_NOT_BE_ADDRESSED()
      } -> std::same_as<void>;
  };

  template<typename Type>
  concept GetAdressable = !CouldNotBeAdressed<Type> && requires(Type t)
  {
    { &t };
  };

  // concept means can be used as pointee
  template<typename Type>
  concept Pointee = std::destructible<Type> && GetAdressable<Type>;

  // concept means can be used as pointer
  // TODO: reimplement the helper function
  template<typename Type>
  constexpr bool IsPointee(Type t)
  {
    if constexpr (Pointee<Type>)
    {
      if constexpr (requires { *t; })
      {
        return IsPointee<decltype(t)>(t);
      }
      return true;
    }
    else
    {
      return false;
    }
  }
  template<class Type>
  concept PointerAble = requires(Type pointer)
  {
    IsPointee(*pointer) == true;
  };

  namespace BasicType
  {
    using CouldNotBeAdressedInt = CouldNotBeAdressedType<int>;
    using CouldNotBeAdressedString = CouldNotBeAdressedType<std::u32string>;
    using CouldNotBeAdressedChar = CouldNotBeAdressedType<char>;
    using CouldNotBeAdressedFloat = CouldNotBeAdressedType<float>;
    using CouldNotBeAdressedDouble = CouldNotBeAdressedType<double>;
    using CouldNotBeAdressedLong = CouldNotBeAdressedType<long>;
    using CouldNotBeAdressedLongLong = CouldNotBeAdressedType<long long>;
    using CouldNotBeAdressedShort = CouldNotBeAdressedType<short>;
    using CouldNotBeAdressedUnsignedInt = CouldNotBeAdressedType<unsigned int>;
    using CouldNotBeAdressedUnsignedLong = CouldNotBeAdressedType<unsigned long>;
    using CouldNotBeAdressedUnsignedLongLong = CouldNotBeAdressedType<unsigned long long>;
    using CouldNotBeAdressedUnsignedShort = CouldNotBeAdressedType<unsigned short>;
    using CouldNotBeAdressedBool = CouldNotBeAdressedType<bool>;
    using CouldNotBeAdressedVoid = CouldNotBeAdressedType<void>;
    using CouldNotBeAdressedWchar = CouldNotBeAdressedType<wchar_t>;
    using CouldNotBeAdressedChar16 = CouldNotBeAdressedType<char16_t>;
    using CouldNotBeAdressedChar32 = CouldNotBeAdressedType<char32_t>;
    using CouldNotBeAdressedUnsignedChar = CouldNotBeAdressedType<unsigned char>;
  }  // namespace BasicType
}  // namespace ANA

#endif
