#pragma once

#include "board.h"
#include <deque>

enum class move_direction 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class snake 
{
private:
	deque<vector<int>> points;
	move_direction move_dir = move_direction::UP;
	board& brd;

	vector<int> get_next_point()
	{
		vector<int> move_point;
		int x = points[0][0];
		int y = points[0][1];
		switch (move_dir)
		{
		case move_direction::UP:
			move_point = { x, y - 1 };
			break;
		case move_direction::DOWN:
			move_point = { x, y + 1 };
			break;
		case move_direction::LEFT:
			move_point = { x - 1, y };
			break;
		case move_direction::RIGHT:
			move_point = { x + 1, y };
			break;
		}
		return move_point;
	}

	void move()
	{
		vector<int> move_point = get_next_point();
		points.push_front(move_point);
		points.pop_back();
	}

	void grow()
	{
		vector<int> tail = points.back();
		move();
		points.push_back(tail);
	}

	void deploy()
	{
		for (int i = 0; i < points.size(); i++)
		{
			vector<int> point = points[i];
			int x = point[0], y = point[1];
			brd.set(x, y, board_state::SNAKE);
		}
	}

	bool is_opposite_of_move_dir(move_direction dir)
	{
		switch (dir)
		{
		case move_direction::UP:
			if (move_dir == move_direction::DOWN)
				return true;
			break;
		case move_direction::DOWN:
			if (move_dir == move_direction::UP)
				return true;
			break;
		case move_direction::LEFT:
			if (move_dir == move_direction::RIGHT)
				return true;
			break;
		case move_direction::RIGHT:
			if (move_dir == move_direction::LEFT)
				return true;
			break;
		}
		return false;
	}

public:

	snake(board &b) : brd(b) {
		vector<int> middle = brd.get_middle();
		points.push_back(vector<int>{middle[0], middle[1]});
		deploy();
	};

	void change_direction(move_direction dir)
	{
		if (!is_opposite_of_move_dir(dir) && dir != move_dir)
			move_dir = dir;
	}

	bool game_loop()
	{
		vector<int> next_point = get_next_point();
		int x = next_point[0], y = next_point[1];
		if (!brd.point_exists(next_point))
			return false;
		switch (brd[y][x])
		{
		case board_state::EMPTY:
			move();
			break;
		case board_state::FOOD:
			brd.remove_food(next_point);
			grow();
			break;
		case board_state::SNAKE:
			move();
			return false;
		}
		brd.clear_snake_tiles();
		deploy();
		return true;
	}

};