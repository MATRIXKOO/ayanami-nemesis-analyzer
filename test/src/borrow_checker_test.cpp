#include "borrow_checker/borrow_checker.hpp"

#include <__utility/integer_sequence.h>
#include <gtest/gtest.h>

#include <concepts>
#include <memory>
#include <type_traits>

#include "project/concept_checker.h"

using namespace ANA;
using namespace tmp;

TEST(borrow_checker, ConceptPointee)
{
  // check concept pointee
  ASSERT_EQ(true, Pointee<int>);
  ASSERT_EQ(true, Pointee<std::string>);
  ASSERT_EQ(true, Pointee<std::unique_ptr<int>>);

  // const
  ASSERT_EQ(true, Pointee<const int>);
  ASSERT_EQ(true, Pointee<const std::string>);

  class UnDestoriedType
  {
    ~UnDestoriedType()
    {
      throw std::runtime_error("UnDestoriedType");
    }
  };  // Cannot be destroyed
  ASSERT_EQ(false, std::destructible<UnDestoriedType>);
  ASSERT_EQ(false, Pointee<UnDestoriedType>);

  //
  ASSERT_EQ(true, Pointee<int *>);
  ASSERT_EQ(true, Pointee<std::unique_ptr<int>>);
  ASSERT_EQ(true, Pointee<nullptr_t>);

  // Not addressable
  class UnAddressableType : public CouldNotBeAdressedType<int>
  {
  };
  class UnAddressableWithSpecialType
  {
   public:
    inline void __SHOULD_NOT_BE_ADDRESSED();
  };

  ASSERT_EQ(true, CouldNotBeAdressed<UnAddressableType>);
  ASSERT_EQ(false, Pointee<UnAddressableType>);
  ASSERT_EQ(true, CouldNotBeAdressed<UnAddressableWithSpecialType>);
  ASSERT_EQ(false, Pointee<UnAddressableWithSpecialType>);
}

TEST(borrow_checker, UseConceptPointee)
{
  ASSERT_EQ(false, Pointee<BasicType::CouldNotBeAdressedInt>);
}

TEST(borrow_checker, ConceptPointer)
{
  //  A pointer to A pointer to a pointee
  ASSERT_EQ(true, PointerAble<int **>);

  // A pointer to a pointer to a non-pointee
  ASSERT_EQ(false, PointerAble<BasicType::CouldNotBeAdressedBool *>);
}

TEST(borrow_checker, UseConceptPointer)
{
  // use as non_Adressble ptr
  ASSERT_EQ(false, PointerAble<CouldNotBeAdressedType<int *>>);

  CouldNotBeAdressedType<int *> ptr;
  int magic = 42;
  ptr.wrapper = &magic;
  // auto a = &ptr; is not allowed

  using NonAdressbleSharedPtr = CouldNotBeAdressedType<std::shared_ptr<int>>;
  ASSERT_EQ(false, PointerAble<NonAdressbleSharedPtr>);
  NonAdressbleSharedPtr a;
  a.wrapper = std::make_shared<int>(42);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
