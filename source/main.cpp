#include <iostream>
#include "headers/MazeSolver.h"


char menu(int status) {
	char choice;
	switch (status) {
	case 1:
		std::cout << "\t\t*Maze Problem Solver*\n\n";
		std::cout << "\t\t 1- Solve using BFS\n";
		std::cout << "\t\t 2- Solve using DFS\n";
		std::cout << "\t\t 3- Solve using IDS\n";
		std::cout << "\t\t x- Exit\n";
		std::cout << "\t\t --------------------------\n";
		std::cout << "\t\t Your input: ";
		break;
	case 2:
		std::cout << "\t\t Found the goal.\n\t\t Exported the traceback from the goal point to the start point.\n";
		std::cout << "\t\t Your input: ";
		break;
	case 3:
		std::cout << "\t\t Not found.\n";
		std::cout << "\t\t Your input: ";
		break;
	case 0:
		std::cout << "\t\t Your input was invalid.\n";
		std::cout << "\t\t Your input: ";
		break;
	}

	std::cin >> choice;
	std::cout << std::endl;

	return choice;
}

int main(int argc, char **argv) {
	
	std::string f_str;
	if (argc == 1) {
		std::cerr << "\n\t\tNot enough input agruments.\n\t\tEnter file name: ";
		std::cin >> f_str;
	}
	else if (argc == 2) {
		f_str = argv[1];
	}
	else {
		std::cerr << "Too many input arguments.";
		return -1;
	}
	
	MazeSolver solver(f_str);

	std::string input_text;
	char status = menu(1);
	bool result;
	while (status != 'x') {
		if (status == '1') {
			result = solver.BfsSolution(solver.GetMaze());
			if (result) {
				status = menu(2);
			}
			else {
				status = menu(3);
			}
			continue;
		}
		else if (status == '2') {
			result = solver.DfsSolution(solver.GetMaze());
			if (result) {
				status = menu(2);
			}
			else {
				status = menu(3);
			}
			continue;
		}
		else if (status == '3') {
			result = solver.IdsSolution(solver.GetMaze());
			if (result) {
				status = menu(2);
			}
			else {
				status = menu(3);
			}
			continue;
		}
		else {
			status = menu(0);
		}
	}

	return 0;
}