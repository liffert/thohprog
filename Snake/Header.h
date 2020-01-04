#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>


namespace Game {
	///variables and structures

	static bool end_flag;
	static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	typedef struct results {
		int results;
		int moves;
		int time;
	}results_t;
	typedef struct rect_type {
		int x1;
		int y1;
		int x2;
		int y2;
	}rect;

	static rect field{ 0, 0, 40, 40 };
	static results_t res;

	enum MOVE {
		left,
		right,
		up,
		down
	};

	typedef struct Move {
		bool up = false;
		bool left = false;
		bool down = false;
		bool right = false;
		void clear() {
			up = false;
			left = false;
			down = false;
			right = false;
		}


		int get();
	}move_t;
	//////////////////////////////////////////

	//classes
	class Block {
	public:
		Block(int x, int y);
		Block(int x, int y, bool eat);
		~Block();

		bool compare(Block temp);

		int get_x() const;
		int get_y() const;
		void show(char symb) const;
		bool eat_status() const;
		void eating() { eat_s = false; }

		void add_move(int move);
		void add_move(std::vector <move_t> moves);
		void move();

		int get_size_moves() const;
		std::vector<move_t> get() const;
	private:
		int x;
		int y;

		bool eat_s = false;
		std::vector <move_t> moves;
	};
	Block new_el(rect Square);

	class Snake {
	public:
		Snake(rect field);
		~Snake();
		void show();
		bool move();
		void set_eat(Block* eat);
		void change_status(int m);
		bool check_with_body(Block temp)const;
		rect get_field()const;
		int get_body_size() const;

	private:
		std::vector<Block> body;
		int startX = 10;
		int startY = 10;
		void clear();
		void check_end();
		void add_body_moves(int move);
		move_t state;
		Block* eat;
		rect field;
	};
	////////////////////////////////////
	
	//functions

	void setup_field(rect field);
	void setup_field(int x, int y, int width, int height);
	Block* eat_generator(const Snake g);
	void gotoxy(int X, int Y);
	void end_game(rect field);
	void create_field(rect Square);
	void start();
	const results_t get_results();
}