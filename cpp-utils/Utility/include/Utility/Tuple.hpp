/*
 *  Tuple.hpp
 *
 *  Created by Marc Giovannoni on 02/06/2016
 */

#ifndef     __TUPLE_H__
#define     __TUPLE_H__

//
// System includes
//

#include <utility>

//
// Project includes
//

namespace Utility
{
    namespace Tuple
    {
        template<typename _Lambda, std::size_t _Size = 0, typename... _Args>
        inline typename std::enable_if<_Size == sizeof...(_Args), void>::type
            for_each(std::tuple<_Args...>& /*args*/, _Lambda /*lambda*/)
        {
        }

        template<typename _Lambda, std::size_t _Size = 0, typename... _Args>
        inline typename std::enable_if < _Size < sizeof...(_Args), void>::type
            for_each(std::tuple<_Args...>& args, _Lambda lambda)
        {
            lambda(std::get<_Size>(args));
            for_each<_Lambda, _Size + 1>(args, lambda);
        }
    }
}

#endif  //  __TUPLE_H__
