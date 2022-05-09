#include "borrow_checker/borrow.hpp"

#include <gtest/gtest.h>

#include <stdexcept>
using namespace ANA;
TEST(borrow_checker, UseCheck)
{
  own_ptr<int> owner;
  owner.reset(new int(5));
  auto x = borrow_mut(owner);
  try
  {
    auto y = borrow_mut(owner);
  }
  catch (std::runtime_error& e)
  {
    EXPECT_EQ(e.what(), std::string("borrow_verify failed"));
    EXPECT_EQ(owner.cnt_, -1);
  }
}

TEST(borrow_checker, UseCheck2)
{
  own_ptr<int> owner;
  owner.reset(new int(5));
  {
    auto x = borrow_mut(owner);
    EXPECT_EQ(owner.cnt_, -1);
  }
  auto y = borrow_mut(owner);
  {
    try
    {
      auto y = borrow_mut(owner);
    }
    catch (std::runtime_error& e)
    {
      EXPECT_EQ(e.what(), std::string("borrow_verify failed"));
      EXPECT_EQ(owner.cnt_, -1);
    }
  }
}

TEST(borrow_checker, UseCheck3)
{
  own_ptr<int> owner;
  owner.reset(new int(5));
  auto x = borrow_const(owner);
  auto y = borrow_const(owner);
  try
  {
    auto z = borrow_mut(owner);
  }
  catch (const std::exception& e)
  {
    EXPECT_EQ(e.what(), std::string("borrow_verify failed"));
    EXPECT_FALSE(owner.cnt_ == 0);
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
