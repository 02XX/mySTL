#include"allocator.h"
#include<vector>
#include<iostream>
int main(int argc, char const *argv[])
{
    
    std::vector<int,mtd::allocator<int>> a(5,0);
    std::cout << a[6];
    return 0;
}
