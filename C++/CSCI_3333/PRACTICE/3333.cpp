#include <iostream>
#include <chrono>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <math.h>
#include "minpriorityqueue.h"
#include "vertex.h"


// void D(int n)
// {
//     int time = 0;
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < i * i; j++)
//             for (int k = 0; k < j*j; k++)
//                 time++;
//     // std::cout<<time<< std::endl;
// }
// void ncubed (int n){
//     int time = 0;
//     for(int i = 0; i < n;i++)
//         for(int j=0;j<n;j++)
//             for(int k = 0; k<n;k++)
//                 time++;
// //    std::cout<<time;
// }
// void showMap(std::unordered_map<std::string, int> &M){
//     std::cout<< "num items: "<< M.size()<<std::endl;
//     std::cout<<"num buckets: "<< M.bucket_count()<<std::endl;
//     std::cout<<"load factor: "<< (M.load_factor()*100)<<std::endl;
//     std:: cout<< "max load: "<< M.max_load_factor()<<std::endl;
// }



string solveMaze(string maze){
    vector<vector<char>> m;
    unordered_map<Vertex*, pair<int,int>> g;
    Vertex* temp;
    int rows = 0, cols = 0;
    for (int i = 0; i < maze.length(); i++) {
        if (maze[i] == '\n') {
            rows++;
            cols = 0;
        }else{
            if (cols == 0) m.push_back(vector<char>());
            m[rows].push_back(maze[i]);
            cols++;
        }
    }

    
    string solution = maze;
    return solution;
}



int main(){

    srand(2023 + 's');
	string maze,  soln;
    maze = "";
	maze += "# ######################################\n";
	maze += "#   ###     ##                      ## #\n";
	maze += "### ### ### #  ###### ######## #  # #  #\n";
	maze += "# #     # # ##      #        # #### # ##\n";
	maze += "# ####### # ##### # # ###### # #       #\n";
	maze += "#         #     # # #      # # #  ##   #\n";
	maze += "# ### ### ##### # # ######## # #####   #\n";
	maze += "# ### #     #   ###          # ##    ###\n";
	maze += "#     # ### # ######## #######  # #### #\n";
	maze += "# # # # ### #          ##    ## # ## # #\n";
	maze += "# # # #     ########## #   #### # ## # #\n";
	maze += "# # ##### #          # ### #    #      #\n";
	maze += "# #    ## #######  # # #      # ### ####\n";
	maze += "# #### ##   # # #### # #####  #   # #  #\n";
	maze += "# ## ## ###       ## #       ## # # # ##\n";
	maze += "## # #  ###### ## ## ####### ## # # # ##\n";
	maze += "#  # #       # ##                      #\n";
	maze += "###################################### #\n";
    soln = "";
	soln += "#o######################################\n";
	soln += "#ooo###ooooo##                      ## #\n";
	soln += "###o###o###o#  ###### ######## #  # #  #\n";
	soln += "# #ooooo# #o##      #        # #### # ##\n";
	soln += "# ####### #o##### # # ###### # #       #\n";
	soln += "#         #ooooo# # #      # # #  ##   #\n";
	soln += "# ### ### #####o# # ######## # #####   #\n";
	soln += "# ### #     #ooo###          # ##    ###\n";
	soln += "#     # ### #o######## #######  # #### #\n";
	soln += "# # # # ### #oooooooooo##    ## # ## # #\n";
	soln += "# # # #     ##########o#   #### # ## # #\n";
	soln += "# # ##### #          #o### #    #      #\n";
	soln += "# #    ## #######  # #o#      # ### ####\n";
	soln += "# #### ##   # # #### #o#####  #   # #  #\n";
	soln += "# ## ## ###       ## #ooooooo## # # # ##\n";
	soln += "## # #  ###### ## ## #######o## # # # ##\n";
	soln += "#  # #       # ##           ooooooooooo#\n";
	soln += "######################################o#\n";

    maze = solveMaze(maze);
    if(maze == soln){
        cout<<'niceeee';
    }
    cout<<"not correct fuck tard";
    // for(auto x: solu){
    //     std::cout<<x;
    // }
    
    







    // MinPriorityQueue<int> Q1;
    // Q1.push(24, 3);
    // Q1.push(7, 23);
    // Q1.push(55, 37);
    // Q1.push(12, 6);
    // Q1.push(31, 15);
    // // 24 12 31 7 55
    // while(Q1.size() != 0){
    //     Q1.pop();
    // }



    //MAP IDEAS//
    // std:: vector<std::pair<std::string, int>> vHeap;
    // std::unordered_map<std::string, int> uMap;
    // uMap.max_load_factor(.10);
    // std::string* cool = new std::string[100000];
    // showMap(uMap);
    // vHeap.push_back({"lol", 23});
    // vHeap.push_back({"nice", 39});
    // vHeap.push_back({"too", 2});
    // vHeap.push_back({"hi", 20000});
    // vHeap.push_back({"boy", 52});
    // vHeap.push_back({"girl", 51});
    // vHeap.push_back({"er", 57});
    // vHeap.push_back({"wqe", 55});
    // vHeap.push_back({"we", 58}); 
    // vHeap.push_back({"ce", 59});
    // vHeap.push_back({"re", 5012});
    // vHeap.push_back({"lov", 5012});
    // vHeap.push_back({"e", 5012});
    // vHeap.push_back({"wwe", 5012});
    // vHeap.push_back({"gen", 5012});
    // auto compare = [](auto a, auto b){return a.second<b.second;};
    // std::sort(vHeap.begin(), vHeap.end(), compare);

    // for(int i = 0; i < vHeap.size();i++){
    //     uMap.insert({vHeap[i].first,i});
    // }

    // showMap(uMap);
    // for(int i = 0; i< vHeap.size();i++){
    //     uMap.erase(vHeap[i].first);
    // }
    // for(auto i: uMap){
    //     std::cout<< i.first<<i.second<<std::endl;
    // }


    // auto start = std::chrono::high_resolution_clock::now();
    // D(10);
    // auto finish = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = finish-start;
    // std::cout<< elapsed.count()<<std::endl;    

    // auto s = std::chrono::high_resolution_clock::now();
    // ncubed(10);
    // auto f = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<long double> nice = f-s;
    // std::cout<< nice.count();

    return 0;
}