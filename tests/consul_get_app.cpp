//  Copyright (c) 2014 Andrey Upadyshev <oliora@gmail.com>
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "ppconsul/ppconsul.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " url-to-fetch" << std::endl;
        return 2;
    }
        
    try
    {
        ppconsul::http::Status s;
        auto r = ppconsul::Consul().get(s, argv[1]);
        std::cout
            << s.code() << ' ' << s.message() << '\n';
        if (r.headers())
        {
            std::cout
                << "Index: " << r.headers().index() << '\n'
                << "Known leader: " << (r.headers().knownLeader() ? "true" : "false") << '\n'
                << "Lastcontact: " << r.headers().lastContact().count() << "\n\n";
        }
        else
        {
            std::cout << '\n';
        }

        std::cout << r.value() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
