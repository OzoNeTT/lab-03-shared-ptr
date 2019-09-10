// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "../include/Shared.hpp"


TEST(SharedPtr, FromPointer)
{
    auto sourcePtr = new int{789};
    auto ptr = SharedPtr<int>{sourcePtr};

    EXPECT_EQ(static_cast<bool>(ptr), true);
    EXPECT_EQ(ptr.use_count(), 1u);
    EXPECT_EQ(ptr.get(), sourcePtr);
    EXPECT_EQ(*ptr, 789);
}