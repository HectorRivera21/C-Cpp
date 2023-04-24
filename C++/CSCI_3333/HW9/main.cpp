
#include <iostream>
#include <cstdlib>
#include <vector>
#include "tiling.h"

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
	string floor;


	floor = "";
	floor += "######\n";
	floor += "#    #\n";
	floor += "######\n";
	test(has_tiling(floor));

	floor = "";
	floor += "#######\n";
	floor += "#     #\n";
	floor += "#######\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "########\n";
	floor += "#      #\n";
	floor += "########\n";
	test(has_tiling(floor));

	floor = "";
	floor += "###\n";
	floor += "# #\n";
	floor += "# #\n";
	floor += "###\n";
	test(has_tiling(floor));

	floor = "";
	floor += "###\n";
	floor += "# #\n";
	floor += "# #\n";
	floor += "# #\n";
	floor += "###\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "###\n";
	floor += "# #\n";
	floor += "# #\n";
	floor += "# #\n";
	floor += "# #\n";
	floor += "###\n";
	test(has_tiling(floor));

	floor = "";
	floor += "####\n";
	floor += "#  #\n";
	floor += "#  #\n";
	floor += "####\n";
	test(has_tiling(floor));

	floor = "";
	floor += "####\n";
	floor += "#  #\n";
	floor += "# ##\n";
	floor += "####\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "#####\n";
	floor += "# # #\n";
	floor += "# # #\n";
	floor += "#####\n";
	test(has_tiling(floor));

        floor = "";
        floor += "########\n";
        floor += "## ## ##\n";
        floor += "#      #\n";
        floor += "## ## ##\n";
        floor += "########\n";
        test(!has_tiling(floor));

	floor = "";
	floor += "#####\n";
	floor += "## ##\n";
	floor += "#   #\n";
	floor += "## ##\n";
	floor += "#####\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "######\n";
	floor += "###  #\n";
	floor += "##  ##\n";
	floor += "#  ###\n";
	floor += "######\n";
	test(has_tiling(floor));

	floor = "";
	floor += "######\n";
	floor += "# #  #\n";
	floor += "#    #\n";
	floor += "#  # #\n";
	floor += "######\n";
	test(has_tiling(floor));

	floor = "";
	floor += "######\n";
	floor += "###  #\n";
	floor += "#    #\n";
	floor += "#  # #\n";
	floor += "######\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "#######\n";
	floor += "#     #\n";
	floor += "###  ##\n";
	floor += "#### ##\n";
	floor += "#######\n";
	test(has_tiling(floor));

	floor = "";
	floor += "#######\n";
	floor += "##   ##\n";
	floor += "###  ##\n";
	floor += "##   ##\n";
	floor += "#######\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "#######\n";
	floor += "##   ##\n";
	floor += "## # ##\n";
	floor += "##   ##\n";
	floor += "#######\n";
	test(has_tiling(floor));

	floor = "";
	floor += "##########\n";
	floor += "##      ##\n";
	floor += "#  #  #  #\n";
	floor += "##      ##\n";
	floor += "##########\n";
	test(has_tiling(floor));

	floor = "";
	floor += "#########\n";
	floor += "##     ##\n";
	floor += "#  # #  #\n";
	floor += "##     ##\n";
	floor += "#########\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "##########\n";
	floor += "##      ##\n";
	floor += "## #  # ##\n";
	floor += "##      ##\n";
	floor += "##########\n";
	test(has_tiling(floor));

	floor = "";
	floor += "############\n";
	floor += "##   #   # #\n";
	floor += "## # # # # #\n";
	floor += "#  #   #   #\n";
	floor += "############\n";
	test(has_tiling(floor));

	floor = "";
	floor += "############\n";
	floor += "##   #   ###\n";
	floor += "## # # # # #\n";
	floor += "#  #   #   #\n";
	floor += "############\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "############\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "############\n";
	test(has_tiling(floor));

	floor = "";
	floor += "############\n";
	floor += "##         #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#         ##\n";
	floor += "############\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "############\n";
	floor += "##         #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "##         #\n";
	floor += "############\n";
	test(has_tiling(floor));

	floor = "";
	floor += "############\n";
	floor += "#####  #####\n";
	floor += "####    ####\n";
	floor += "###      ###\n";
	floor += "##        ##\n";
	floor += "#          #\n";
	floor += "#          #\n";
	floor += "##        ##\n";
	floor += "###      ###\n";
	floor += "####    ####\n";
	floor += "#####  #####\n";
	floor += "############\n";
	test(has_tiling(floor));

	floor = "";
	floor += "############\n";
	floor += "#####  #####\n";
	floor += "####    ####\n";
	floor += "###      ###\n";
	floor += "##        ##\n";
	floor += "##         #\n";
	floor += "#         ##\n";
	floor += "##        ##\n";
	floor += "###      ###\n";
	floor += "####    ####\n";
	floor += "#####  #####\n";
	floor += "############\n";
	test(!has_tiling(floor));

	floor = "";
	floor += "##########\n";
	floor += "#   ######\n";
	floor += "#    #####\n";
	floor += "#      ###\n";
	floor += "## #    ##\n";
	floor += "##      ##\n";
	floor += "###     ##\n";
	floor += "####   ###\n";
	floor += "##########\n";
	test(!has_tiling(floor));

        // Try some random mazes
        for (int trial = 0; trial < 500; ++trial)
        {
                bool ok = static_cast<bool>(rand() % 2);
                int height = 6 + (rand() % 10);
                int width = 7 + (rand() % 10);
                floor = "";
                for (int i = 0; i < height; ++i)
                {
                        string row;
                        for (int j = 0; j < width; ++j)
                                row += "#";
                        if (i != 0 && i != height-1)
                        {
                                int ko = 1 + (rand() % (width-3));
                                row[ko] = ' ';
                                row[ko+1] = ' ';
                        }
                        floor += row + '\n';
                }

                if (ok)
                {
                        test(has_tiling(floor));
                        continue;
                }

                int bad_row = 1 + (rand() % (height-3));
                int start = bad_row * (width + 1) + 1;
                while (floor[start] == ' ')
                        ++start;
                floor[start] = ' ';
                int end = bad_row * (width + 1) + width - 2;
                while (floor[end] == ' ')
                        --end;
                floor[end] = ' ';
                test(!has_tiling(floor));
        }


	cout << "Assignment complete." << endl;
}



