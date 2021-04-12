#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <fstream>
#include "headers/MazeProblem.h"

class MazeSolver {

private:
	int expanded = 0;
	int path_length = 0;

	MazeProblem maze;

	struct Node {
		int id, depth;
	};

public:

	MazeSolver(std::string f_str) {
		this->maze = MazeProblem(f_str);
	}

	MazeSolver(MazeProblem maze) {
		this->maze = maze;
	}

	MazeProblem GetMaze() {
		return this->maze;
	}

private:

	bool GoalTest(int id, int goal) {
		if (id == goal)
			return true;
		return false;
	}

	void ExportResult(Node node, MazeProblem maze, int algo) {
		std::string f_str;
		switch (algo) {
		case 1:
			f_str = "maze_bfs_result.txt";
			break;
		case 2:
			f_str = "maze_dfs_result.txt";
			break;
		case 3:
			f_str = "maze_ids_result.txt";
			break;
		}
		std::ofstream maze_result(f_str);
		FindPath(node, maze, maze_result);

	}

	void FindPath(Node node, MazeProblem maze, std::ostream& f) {
		f << node.id << std::endl;
		int parent_id;
		parent_id = maze.maze_status[node.id - 1]->parent;
		while (parent_id != -1)
		{
			f << parent_id << std::endl;
			this->path_length += 1;
			parent_id = maze.maze_status[parent_id - 1]->parent;
		}
		std::cout << std::endl;
	}

	std::vector<int> ActionBfs(int id, MazeProblem maze) {
		/*Actions could be: up = 1, right = 2, down = 3, left = 4.
		process available moves and make the vector.*/
		std::vector<int> actions;
		if (maze.maze_status[id - 1]->up && !(maze.maze_status[id - 1]->visited))
			actions.push_back(1);
		if (maze.maze_status[id - 1]->right && !(maze.maze_status[id - 1]->visited))
			actions.push_back(2);
		if (maze.maze_status[id - 1]->down && !(maze.maze_status[id - 1]->visited))
			actions.push_back(3);
		if (maze.maze_status[id - 1]->left && !(maze.maze_status[id - 1]->visited))
			actions.push_back(4);
		return actions;
	}

	std::vector<int> ActionDFS(int id, MazeProblem maze) {
		/*Actions could be: up = 1, right = 2, down = 3, left = 4.
		process available moves and make the vector.*/
		std::vector<int> actions;

		if (maze.maze_status[id - 1]->up)
			actions.push_back(1);
		if (maze.maze_status[id - 1]->right)
			actions.push_back(2);
		if (maze.maze_status[id - 1]->down)
			actions.push_back(3);
		if (maze.maze_status[id - 1]->left)
			actions.push_back(4);

		return actions;
	}

	Node Result(int id, int action, MazeProblem maze) {
		/*make a move from state "id" by action "action"; make a node
		for the new state. return the new node*/
		Node result;
		if (action == 1 && !(maze.maze_status[id - 2]->visited)) {
			result.id = id - 1;
		}
		else if (action == 2 && !(maze.maze_status[id + maze.row - 1]->visited)) {
			result.id = id + maze.row;
		}
		else if (action == 3 && !(maze.maze_status[id]->visited)) {
			result.id = id + 1;
		}
		else if (action == 4 && !(maze.maze_status[id - maze.row - 1]->visited)) {
			result.id = id - maze.row;
		}
		else {
			result.id = -1;
		}
		return result;
	}

	void Expand(Node  N, std::queue<Node> &my_queue, MazeProblem &maze) {
		std::vector<int> available_moves = ActionBfs(N.id, maze);
		for (int i = 0; i < available_moves.size(); i++) {
			Node new_node = Result(N.id, available_moves[i], maze);
			//add the new node to the frontier
			//new_node.parent = &N;
			new_node.depth = N.depth + 1;
			if (new_node.id != -1) {
				maze.maze_status[new_node.id - 1]->parent = N.id;
				my_queue.push(new_node);
			}
		}

	}

	void Expand(Node N, std::stack<Node> &frontier, MazeProblem &maze) {
		std::vector<int> available_moves = ActionDFS(N.id, maze);
		for (int i = 0; i < available_moves.size(); i++) {
			Node new_node = Result(N.id, available_moves[i], maze);
			new_node.depth = N.depth + 1;
			//add the new node to the frontier
			if (new_node.id != -1) {
				maze.maze_status[new_node.id - 1]->parent = N.id;
				frontier.push(new_node);
			}
		}

	}

	std::stack<Node> InitializeDfs(int start, MazeProblem &maze) {
		std::stack <Node> frontier;
		Node new_node;
		new_node.id = start;
		new_node.depth = 0;
		maze.maze_status[start - 1]->parent = -1;
		frontier.push(new_node);
		return frontier;
	}

	bool BfsSearch(MazeProblem maze, std::queue<Node> my_queue) {
		Node start_n;
		start_n.id = maze.start;
		start_n.depth = 0;
		//	start_n.parent = NULL;
		maze.maze_status[start_n.id - 1]->parent = -1;


		my_queue.push(start_n);
		for (int i = 0; 1; i++) {
			if (my_queue.empty()) {
				return false;
			}
			Node temp_node = my_queue.front();
			my_queue.pop();

			if (GoalTest(temp_node.id, maze.goal)) {
				ExportResult(temp_node, maze, 1);
				return true;
			}
			else {
				this->expanded += 1;
				Expand(temp_node, my_queue, maze);
				maze.maze_status[temp_node.id - 1]->visited = true;
			}
		}
	}

	bool DfsSearch(MazeProblem maze, std::stack<Node> &frontier, int goal) {
		while (true) {
			if (frontier.empty()) {
				return false;
			}

			Node node = frontier.top();
			frontier.pop();
			maze.maze_status[node.id - 1]->visited = true;
			if (GoalTest(node.id, goal)) {
				ExportResult(node, maze, 2);
				return true;
			}

			else {
				this->expanded += 1;
				Expand(node, frontier, maze);
			}
		}

	}

	bool DlsSolution(MazeProblem &maze, int depth_limitation) {
		ResetMaze(maze);
		std::stack<Node> frontier = InitializeDfs(maze.start, maze);

		while (true) {
			if (frontier.empty()) {
				return false;
			}

			Node node = frontier.top();
			frontier.pop();
			maze.maze_status[node.id - 1]->visited = true;

			if (GoalTest(node.id, maze.goal)) {
				ExportResult(node, maze, 3);
				return true;
			}

			else if (node.depth <= depth_limitation - 1) {
				this->expanded += 1;
				Expand(node, frontier, maze);
			}
			else if (frontier.empty()) {
				return false;
			}
		}

	}

	void ResetMaze(MazeProblem &maze) {
		this->expanded = 0;
		for (int i = 0; i < maze.maze_size; i++) {
			maze.maze_status[i]->visited = false;
			maze.maze_status[i]->parent = -1;
		}
	}

public:

	/*void ShowMazeInfo(MazeProblem maze) {
	std::cout << "\t\t" << maze.row << " Row, " << maze.column << "Column\n";
	for (int i = 0; i < maze.maze_size; i++) {
	std::cout << "\t\t" << maze.maze_status[i]->id << ": ";
	std::cout << maze.maze_status[i]->up << ",";
	std::cout << maze.maze_status[i]->right << ",";
	std::cout << maze.maze_status[i]->down << ",";
	std::cout << maze.maze_status[i]->left << "." << "\n";

	}

	std::cout << "\n\t\tStart: " << maze.start << ", Goal: " << maze.goal << std::endl;
	}*/

	bool BfsSolution(MazeProblem &maze) {
		std::queue<Node> my_queue;
		bool result = BfsSearch(maze, my_queue);
		this->ResetMaze(maze);
		return result;
	}

	bool DfsSolution(MazeProblem maze) {
		std::stack<Node> frontier = InitializeDfs(maze.start, maze);
		bool result = DfsSearch(maze, frontier, maze.goal);
		this->ResetMaze(maze);
		return result;
	}

	bool IdsSolution(MazeProblem &maze) {
		int total_expanded = 0;
		for (int i = 0; i < maze.maze_size + 1; i++) {
			this->expanded = 0;
			bool result = DlsSolution(maze, i);
			total_expanded += this->expanded;
			if (result) {
				this->ResetMaze(maze);
				return true;
			}
		}
		this->ResetMaze(maze);
		return false;
	}

};