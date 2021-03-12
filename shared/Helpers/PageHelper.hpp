#pragma once
#include <vector>

namespace GorillaUI::PageHelper
{
    template<class T>
    std::vector<T&> GetPage(std::vector<T>& vector, int pageSize, int pagenum)
    {
        static_assert(pagenum > 0);
        static_assert(pageSize > 0);
        std::vector<T&> page = {};
        int size = vector.size();
        
        int start = pageSize * pagenum;

        if (start > size) return page;
        int end = start + pageSize;
        end = end > size ? size : end;
        
        for (int i = start; i < end; i++)
        {
            page.push_back(vector[i]);
        }

        return page;
    }

    template<class T>
    int GetPageAmount(std::vector<T>& vector, int pageSize)
    {
        static_assert(pageSize > 0);
        int size = vector.size();
        int count = 0;
        while(size > 0)
        {
            size -= pageSize;
            count++;
        }
        return count;
    }
}