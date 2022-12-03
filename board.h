#pragma once

#include <vector>
#include <iostream>

using namespace std;

enum class board_state 
{
	EMPTY = '-',
	SNAKE = 'S',
	FOOD = 'O',
};

class board 
{
private:
	int x;
	int y;
	vector<vector<int>> food_tiles;
	vector<vector<board_state>> arr;
	
	vector<vector<int>> get_clear_tiles()
	{
		vector<vector<int>> clear_tiles;
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				if (arr[i][j] == board_state::EMPTY)
					clear_tiles.push_back(vector<int>{j, i});
			}
		}
		return clear_tiles;
	}
	
public:

	vector<board_state> operator[](int index) { return this->arr[index]; }

	board(int x, int y) : x(x), y(y), arr(vector<vector<board_state>>(y, vector<board_state>(x, board_state::EMPTY))) {};

	void print()
	{
		cout << string(25, '\n');
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
				cout << char(arr[i][j]) << " ";
			if (i < y)
				cout << endl;
		}
	}

	vector<int> get_dimensions()
	{
		return vector<int>{x, y};
	}

	vector<int> get_middle()
	{
		return vector<int>{x / 2, y / 2};
	}

	void clear_snake_tiles()
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				if (arr[i][j] == board_state::SNAKE)
					arr[i][j] = board_state::EMPTY;
			}
		}
	}

	bool point_exists(vector<int> point)
	{
		int x = point[0], y = point[1];
		if (x < 0 || x >= this->x)
			return false;
		if (y < 0 || y >= this->y)
			return false;
		return true;
	}

	void spawn_food()
	{
		vector<vector<int>> clear_tiles = get_clear_tiles();
		int index = rand() % clear_tiles.size();
		vector<int> point = clear_tiles[index];
		arr[point[1]][point[0]] = board_state::FOOD;
		food_tiles.push_back(point);
	}

	void remove_food(vector<int> point)
	{
		for (int i = 0; i < food_tiles.size(); i++)
		{
			if (food_tiles[i] == point)
			{
				food_tiles.erase(food_tiles.begin() + i);
				break;
			}
		}
	}

	bool has_food()
	{
		return !food_tiles.empty();
	}

	void set(int x, int y, board_state state)
	{
		arr[y][x] = state;
	}

};