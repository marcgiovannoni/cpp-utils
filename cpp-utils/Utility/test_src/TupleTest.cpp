/*
*  TupleTest.cpp
*
*  Created by Marc Giovannoni on 02/06/2016
*/

#include <iostream>
#include <gtest/gtest.h>
#include <Utility/Tuple.hpp>

namespace
{
    template <typename... _Args>
    class TupleTest
    {
    public:
        std::tuple<_Args...> _tuple;

        template<class... _Args>
        TupleTest(_Args&&... args) : _tuple(std::forward<_Args>(args)...) {}

        const std::tuple<_Args...>& getTuple() const
        {
            return this->_tuple;
        }
    };
}

TEST(Tuple, for_each)
{
    TupleTest<int, float, double> t(1, 2.0f, 3.0);
    unsigned int i = 0;

    Utility::Tuple::for_each(t._tuple,
        [&](auto arg)
    {
        std::cout << arg << std::endl;
        ++i;
    });

    EXPECT_TRUE(i == 3);
}

TEST(Tuple, const_for_each)
{
    TupleTest<int, float, double> t(1, 2.0f, 3.0);
    unsigned int i = 0;

    Utility::Tuple::const_for_each(t.getTuple(),
        [&](auto arg)
    {
        std::cout << arg << std::endl;
        ++i;
    });

    EXPECT_TRUE(i == 3);
}
