// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "board.h"
#include "snake.h"
#include <thread>
#include <chrono>
#include <conio.h>
#include <atomic>

using namespace std;

atomic<char> last_pressed;
atomic<bool> cont{ true };

void get_input()
{
	while (cont)
	{
		last_pressed = _getch();
	}
}

move_direction process_input()
{
	switch (last_pressed)
	{
	case 'w':
		return move_direction::UP;
		break;
	case 'a':
		return move_direction::LEFT;
		break;
	case 's':
		return move_direction::DOWN;
		break;
	case 'd':
		return move_direction::RIGHT;
		break;
	}
}

int main()
{
	srand(time(NULL));
	board test(15, 15);
	snake snk(test);
	thread input(get_input);
	while (true)
	{
		snk.change_direction(process_input());
		if (!snk.game_loop())
		{
			cont = false;
			input.join();
			break;
		}
		if (!test.has_food())
			test.spawn_food();
		test.print();
		this_thread::sleep_for(500ms);
	}
}