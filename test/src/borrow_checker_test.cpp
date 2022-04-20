#include "borrow_checker/borrow_checker.hpp"

#include <gtest/gtest.h>

#include <memory>

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

  // Addressable
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
  using CouldNotBeAdressedInt = CouldNotBeAdressedType<int>;
  ASSERT_EQ(false, Pointee<CouldNotBeAdressedInt>);
}

TEST(borrow_checker, ConceptPointer)
{
  // A pointer to a pointee
  BasicType::CouldNotBeAdressedInt **ptr;
  std::cout << IsPointee(ptr);
  ASSERT_EQ(true, PointerAble<int *>);
  // use concept checker to check if the type is pointer
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
