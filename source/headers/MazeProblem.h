#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


class MazeProblem {

private:
	struct Cell {
		int id;
		int parent = -1;
		bool up, right, down, left;
		bool visited = false;
	};

	Cell** maze_status;
	int maze_size = -1;
	int row;
	int column;
	int start;
	int goal;

	friend class MazeSolver;

	void ReadFile(std::string file_addr) {
		std::ifstream maze_file(file_addr);
		if (maze_file.is_open()) {
			std::string temp_line;

			//read first line; maze's row and column
			std::getline(maze_file, temp_line);
			std::stringstream first_line(temp_line);

			//process first line
			std::string temp_row_column;

			std::getline(first_line, temp_row_column, ' ');
			this->row = std::stoi(temp_row_column);

			std::getline(first_line, temp_row_column, ' ');
			this->column = std::stoi(temp_row_column);

			//make maze
			this->maze_size = this->row*this->column;
			this->maze_status = new Cell*[this->maze_size];

			std::string direction;

			//continue reading the file and process the maze's cells line by line.
			for (int i = 0; i<this->maze_size; i++) {

				std::getline(maze_file, temp_line);
				std::stringstream first_line(temp_line);

				Cell* new_maze_cell = new Cell;
				new_maze_cell->id = i + 1;


				std::getline(first_line, direction, ' ');
				new_maze_cell->up = bool(stoi(direction));

				std::getline(first_line, direction, ' ');
				new_maze_cell->right = bool(stoi(direction));

				std::getline(first_line, direction, ' ');
				new_maze_cell->down = bool(stoi(direction));

				std::getline(first_line, direction, ' ');
				new_maze_cell->left = bool(stoi(direction));


				this->maze_status[i] = new_maze_cell;

			}

			std::string temp_string;
			std::getline(maze_file, temp_line);
			std::stringstream last_line(temp_line);
			std::getline(last_line, temp_string, ' ');
			this->start = stoi(temp_string);
			std::getline(last_line, temp_string, ' ');
			this->goal = stoi(temp_string);

		}
	}

public:

	MazeProblem() {

	}

	MazeProblem(std::string file_addr) {
		ReadFile(file_addr);
	}

};