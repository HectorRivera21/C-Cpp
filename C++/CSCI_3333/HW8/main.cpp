#include <iostream>
#include <cstdlib>
#include <string>
#include "solve.h"
// #include "COOL.cpp"
#include "solve2.cpp"

using namespace std;

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


int main()
{
	// Setup
	srand(2023 + 's');
	string maze, soln;


	// Test a few mazes without portals

	maze = "";
	maze += "##### #\n";
	maze += "#     #\n";
	maze += "# #####\n";
	soln = "";
	soln += "#####o#\n";
	soln += "#ooooo#\n";
	soln += "#o#####\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "##### #\n";
	maze += "#   # #\n";
	maze += "# # # #\n";
	maze += "# #   #\n";
	maze += "# #####\n";
	soln = "";
	soln += "#####o#\n";
	soln += "#ooo#o#\n";
	soln += "#o#o#o#\n";
	soln += "#o#ooo#\n";
	soln += "#o#####\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "########\n";
	maze += "#      #\n";
	maze += "# ## ###\n";
	maze += "#      #\n";
	maze += "## ## ##\n";
	maze += "#  ##  #\n";
	maze += "## ### #\n";
	maze += "## ### #\n";
	soln = "";
	soln += "########\n";
	soln += "#      #\n";
	soln += "# ## ###\n";
	soln += "# oooo #\n";
	soln += "##o##o##\n";
	soln += "# o##oo#\n";
	soln += "##o###o#\n";
	soln += "##o###o#\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "########\n";
	maze += "#  #    \n";
	maze += "# ## ###\n";
	maze += "#      #\n";
	maze += "# # # ##\n";
	maze += "# ###  #\n";
	maze += "#  ### #\n";
	maze += "## #####\n";
	soln = "";
	soln += "########\n";
	soln += "#  #oooo\n";
	soln += "# ##o###\n";
	soln += "#oooo  #\n";
	soln += "#o# # ##\n";
	soln += "#o###  #\n";
	soln += "#oo### #\n";
	soln += "##o#####\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "# ######\n";
	maze += "#  #   #\n";
	maze += "# ## ###\n";
	maze += "#      #\n";
	maze += "# # # ##\n";
	maze += "# ###  #\n";
	maze += "#  ###  \n";
	maze += "########\n";
	soln = "";
	soln += "#o######\n";
	soln += "#o #   #\n";
	soln += "#o## ###\n";
	soln += "#ooooo #\n";
	soln += "# # #o##\n";
	soln += "# ###oo#\n";
	soln += "#  ###oo\n";
	soln += "########\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "########\n";
	maze += "#      #\n";
	maze += "#      #\n";
	maze += "#      #\n";
	maze += "## ## ##\n";
	maze += "## ##  #\n";
	maze += "## ### #\n";
	soln = "";
	soln += "########\n";
	soln += "#      #\n";
	soln += "#      #\n";
	soln += "# oooo #\n";
	soln += "##o##o##\n";
	soln += "##o##oo#\n";
	soln += "##o###o#\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "#########################################################\n";
	maze += "#     #        #  #  #     #  #  #        #     #       #\n";
	maze += "  ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##  \n";
	maze += "#  #     #  #           #           #  #     #     #  # #\n";
	maze += "#########################################################\n";
	soln = "";
	//r:2 c:57 Destination r:2 c:0 Start
	soln += "#########################################################\n";
	soln += "#oooo #ooooooo #  #  #oooo #  #  #ooooooo #oooo #ooooooo#\n";
	soln += "oo##o##o## ##o## ## ##o##o## ## ##o## ##o##o##o##o## ##oo\n";
	soln += "#  #oooo #  #oooooooooo #oooooooooo #  #oooo #oooo #  # #\n";
	soln += "#########################################################\n";
	test(solve(maze) == soln);

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
	test(solve(maze) == soln);

	for (int t = 0; t < 100; ++t)
	{
		// Randomized test to prevent hardcoding
		maze = "";
		maze += "##################################################\n";
		maze += "                                                  \n";
		maze += "#                                                #\n";
		maze += "##################################################\n";
		for (int i = 0; i < 4; ++i)
		{
			int offset = rand() % 5;
			maze[58 + 10*i + offset] = '#';
			maze[108 + 10*i + 3 + offset] = '#';
			maze[108 + 10*i - 1 + offset] = '#';
			soln = maze;
			int j = 51;
			while (j < 101)
			{
				if (soln[j] == '#')
				{
					soln[j-1 + 51] = 'o';
					soln[j-1 + 52] = 'o';
					soln[j-1 + 53] = 'o';
				}
				else
					soln[j] = 'o';
				++j;
			}
		}
		test(solve(maze) == soln);
	}



	// Test mazes with portals

	maze = "";
	maze += "### #\n";
	maze += "#1#1#\n";
	maze += "# ###\n";
	soln = "";
	soln += "###o#\n";
	soln += "#o#o#\n";
	soln += "#o###\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += " 1##1 \n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "oo##oo\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += " 1  1 \n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "oo  oo\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += "  1#2 \n";
	maze += "# ####\n";
	maze += "# 2#1#\n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "oo1#oo\n";
	soln += "#o####\n";
	soln += "#oo#1#\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "# ######\n";
	maze += "#  1  2#\n";
	maze += "########\n";
	maze += "#12    #\n";
	maze += "### ####\n";
	soln = "";
	soln += "#o######\n";
	soln += "#ooo  2#\n";
	soln += "########\n";
	soln += "#ooo   #\n";
	soln += "###o####\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += " 5# 3 \n";
	maze += "######\n";
	maze += "#5  3#\n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "oo# oo\n";
	soln += "######\n";
	soln += "#oooo#\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "########\n";
	maze += "  0  0  \n";
	maze += "#      #\n";
	maze += "########\n";
	soln = "";
	soln += "########\n";
	soln += "ooo  ooo\n";
	soln += "#      #\n";
	soln += "########\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "########\n";
	maze += "  9  9  \n";
	maze += "#      #\n";
	maze += "########\n";
	soln = "";
	soln += "########\n";
	soln += "oooooooo\n";
	soln += "#      #\n";
	soln += "########\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "########\n";
	maze += "  9  9  \n";
	maze += "#0    0#\n";
	maze += "########\n";
	soln = "";
	soln += "########\n";
	soln += "oo9  9oo\n";
	soln += "#o    o#\n";
	soln += "########\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += "  98  \n";
	maze += "# 89 #\n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "oooooo\n";
	soln += "# 89 #\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += "1 ## 1\n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "o ## o\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += "0 ## 0\n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "o ## o\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += "6    6\n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "oooooo\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "######\n";
	maze += "4    4\n";
	maze += "######\n";
	soln = "";
	soln += "######\n";
	soln += "o    o\n";
	soln += "######\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "##########\n";
	maze += "# 2#2 6#6#\n";
	maze += "  ######  \n";
	maze += "# 3#3 4#4#\n";
	maze += "##########\n";
	soln = "";
	soln += "##########\n";
	soln += "# 2#2 6#6#\n";
	soln += "oo######oo\n";
	soln += "#oo#ooo#o#\n";
	soln += "##########\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "##########\n";
	maze += "# 2#2 6#6#\n";
	maze += "  ### ##  \n";
	maze += "# 3#3 4#4#\n";
	maze += "##########\n";
	soln = "";
	soln += "##########\n";
	soln += "# 2#2 6#6#\n";
	soln += "oo### ##oo\n";
	soln += "#oo#ooo#o#\n";
	soln += "##########\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "#### ####\n";
	maze += "# 6  ####\n";
	maze += "####   0#\n";
	maze += "#### ## #\n";
	maze += "#### ## #\n";
	maze += "#0     6#\n";
	maze += "#### ####\n";
	soln = "";
	soln += "####o####\n";
	soln += "# 6 o####\n";
	soln += "####o  0#\n";
	soln += "####o## #\n";
	soln += "####o## #\n";
	soln += "#0  o  6#\n";
	soln += "####o####\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "#### ####\n";
	maze += "# 0  ####\n";
	maze += "####   6#\n";
	maze += "#### ## #\n";
	maze += "#### ## #\n";
	maze += "#6   0  #\n";
	maze += "#### ####\n";
	soln = "";
	soln += "####o####\n";
	soln += "# ooo####\n";
	soln += "####   6#\n";
	soln += "#### ## #\n";
	soln += "#### ## #\n";
	soln += "#6  oo  #\n";
	soln += "####o####\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "##############\n";
	maze += "# 3        3 #\n";
	maze += "# ########## #\n";
	maze += "              \n";
	maze += "# ########## #\n";
	maze += "#  0      0  #\n";
	maze += "##############\n";
	soln = "";
	soln += "##############\n";
	soln += "# 3        3 #\n";
	soln += "# ########## #\n";
	soln += "oo          oo\n";
	soln += "#o##########o#\n";
	soln += "#ooo      ooo#\n";
	soln += "##############\n";
	test(solve(maze) == soln);

	maze = "";
	maze += "# ######################################\n";
	maze += "#   ###     ##                      ## #\n";
	maze += "### ### ### #  ###### ######## #  # #  #\n";
	maze += "# #    7# #7##      #        # #### # ##\n";
	maze += "# ####### # ##### # # ###### # #       #\n";
	maze += "#         #     # # #      # # #  ##   #\n";
	maze += "# ### ### ##### # # ######## # #####   #\n";
	maze += "# ### #    5#   ###          # ##    ###\n";
	maze += "#     # ### #4######## #######  # #### #\n";
	maze += "# # # # ### #          ##    ## # ## # #\n";
	maze += "# # # #     ########## #   #### # ## # #\n";
	maze += "# # ##### #    4 5  3# ### #    #      #\n";
	maze += "# #    ## #######  # #3#      #1### ####\n";
	maze += "# #### ##   # # #### # #####  #   # #  #\n";
	maze += "# ## ## ###       ## #  2    ## # # # ##\n";
	maze += "## # #  ###### ## ## ####### ##1# # # ##\n";
	maze += "#  # #       # ##         2            #\n";
	maze += "###################################### #\n";
	soln = "";
	soln += "#o######################################\n";
	soln += "#ooo###     ##                      ## #\n";
	soln += "###o### ### #  ###### ######## #  # #  #\n";
	soln += "# #ooooo# #o##      #        # #### # ##\n";
	soln += "# ####### #o##### # # ###### # #       #\n";
	soln += "#         #ooooo# # #      # # #  ##   #\n";
	soln += "# ### ### #####o# # ######## # #####   #\n";
	soln += "# ### #    5#ooo###          # ##    ###\n";
	soln += "#     # ### #o######## #######  # #### #\n";
	soln += "# # # # ### #          ##    ## # ## # #\n";
	soln += "# # # #     ########## #   #### # ## # #\n";
	soln += "# # ##### #    oooooo# ### #    #      #\n";
	soln += "# #    ## #######  # #o#      #1### ####\n";
	soln += "# #### ##   # # #### #o#####  #   # #  #\n";
	soln += "# ## ## ###       ## #ooo    ## # # # ##\n";
	soln += "## # #  ###### ## ## ####### ##1# # # ##\n";
	soln += "#  # #       # ##         ooooooooooooo#\n";
	soln += "######################################o#\n";
	test(solve(maze) == soln);

	for (int t = 0; t < 100; ++t)
	{
		// Randomized test to prevent hardcoding
		maze = "";
		maze += "##################################################\n";
		maze += "                                                  \n";
		maze += "#                                                #\n";
		maze += "##################################################\n";
		char port = '1' + (rand() % 9);
		maze[70 + rand() % 10] = port;
		maze[100] = port;
		for (int i = 0; i < 4; ++i)
		{
			int offset = rand() % 5;
			int loc = 58 + 10*i + offset;
			if (maze[loc] == port)
				continue;
			maze[loc] = '#';
			maze[loc + 50 + 3] = '#';
			maze[loc + 50 - 1] = '#';
			soln = maze;
			int j = 51;
			while (j < 101)
			{
				if (soln[j] == '#')
				{
					soln[j-1 + 51] = 'o';
					soln[j-1 + 52] = 'o';
					soln[j-1 + 53] = 'o';
					++j;
				}
				else if (soln[j] == ' ')
				{
					soln[j] = 'o';
					++j;
				}
				else
				{
					soln[j] = 'o';
					soln[100] = 'o';
					break;
				}
			}
		}
		test(solve(maze) == soln);
	}

	cout << "Assignment complete." << endl;
}



