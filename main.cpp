#include <iostream>   //I/O
#include <fstream>    //File Input handling
#include <string>     //String convenience

#include "TwoThreeTree.h"	              //2-3 Tree

//Load a TwoThreeTree from a (.txt) file
TwoThreeTree loadTwoThreeTree(std::string fName) {
  std::ifstream file(fName);
  int num;
  std::cout << "\n\nAttempting to create a 2-3 tree from table from file " << fName << "...";
  if (file.is_open()) {
    TwoThreeTree* tree = new TwoThreeTree();
    while(file >> num) tree->insert(num); //Load numbers to table.
    file.close();
    return *tree;
  } else return TwoThreeTree();
}

//Main function
int main(int argc, char* argv[])
{
  if (!argv[1]) std::cout << "\nNo file arguments provided. Defaulting to 'data.txt'.";
	std::string fileName = (argv[1]) ? argv[1] : "data.txt"; //File name assignment

	TwoThreeTree tree = loadTwoThreeTree(fileName);


  //Main IO loop - controls interaction with 2-3 Tree.
	int choice = 0;
	do {
    std::cout << "\n\n................................................................"
									<< "\nPlease choose one of the following commands:"
									<< "\n1-	Insert"
                  << "\n2-	DeleteMin"
                  << "\n3-	DeleteMax"
                  << "\n4-	FindMin"
                  << "\n5-	FindMax"
                  << "\n6-	Find"
                  << "\n7-	Delete"
                  << "\n8-	Level order"
                  << "\n9-	Exit"
									<< "\n> ";
    std::cin >> choice;
		int num = 0; //Contains I/O responses
    switch(choice) {
      case 1: //Handle Insert
        std::cout << "\nEnter a number to be inserted: \n> ";
				std::cin >> num;
        tree.insert(num);
        break;
      case 2: //Handle DeleteMin
        std::cout << "\nDeleting the minimum value...";
        tree.deleteMin();
        break;
      case 3: //Handle DeleteMax
        std::cout << "\nDeleting the maximum value...";
        tree.deleteMax();
        break;
      case 4: //Handle FindMin
        std::cout << "\nFinding the minimum value...";
        tree.findMin();
        break;
      case 5: //Handle FindMax
        std::cout << "\nFinding the maximum value...";
        tree.findMax();
        break;
      case 6: //Handle Find
        std::cout << "\nEnter a number to find: \n";
        std::cin >> num;
        tree.find(num);
        break;
      case 7: //Handle Delete
        std::cout << "\nEnter a number to be deleted: \n> ";
        std::cin >> num;
        tree.erase(num);
        break;
      case 8: //Handle Level order
        std::cout << "Level order traversal";
        tree.levelorder();
        break;
      case 9: break; //Handle Exit
      default:
        std::cout << "\nThat option was not found. Please try again.";
        break;
    }

} while (choice != 9);
  std::cout << "\n\nExiting - dumping tree...\n";
}
