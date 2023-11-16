#include <iostream>
#include <iomanip>
int main(int argc, char** argv)
{
    if(argc == 1)
    {
        std::cerr<<"No Arguments passed see help for more instructions -h/--help\n";
        return 1;
    }
    if(argc>1){
        for(int i = 0; i<argc; ++i){
            if(argv[i] == "-h"|| argv[i] == "--help")
            {
                std::cout<<"options:\n";
                std::cout<<std::setw(10)<<"-h, --help"<<std::setw(20)<<"show this help message and exit\n";
                std::cout<<std::setw(10)<<"--add"<<std::setw(20)<<"add to table\n";
                std::cout<<std::setw(10)<<"--delete"<<std::setw(20)<<"delete from table\n";
                std::cout<<std::setw(10)<<"--table TABLE"<<std::setw(20)<<"target table\n";
                return 0;
            }
        }   
    }
    return 0;
}
