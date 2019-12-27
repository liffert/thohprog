#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <thread>
#include <vector>
#include <mutex>

HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
std::mutex mut;

typedef struct point {
	int x;
	int y;
}point_t;


static void gotoxy(int X, int Y) {
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}

std::string strRand(int len) {
	std::string temp;
	for (int i = 0; i < len; i++) {
		int a = std::rand() % 91;
		while (a < 65) {
			a = a + 10;
		}
		temp = temp + static_cast<char>(a);
	}
	return temp;
}

void print_word(std::string word, const point_t point) {
	for (int i = 0; i < word.size(); i++) {
		gotoxy(point.x, point.y + i);
		std::cout << word[i];
	}
}
void make_animation(const point_t start, const point_t end, int id, int sleepTime, int len) {
	std::srand(id);
	point_t now = start;
	point_t prew_now = start;
	prew_now.y--;
	std::string clear;
	for (int i = 0; i < len; i++) {
		clear = clear + " ";
	}

	bool flag = false;
	while (1) {
		while (now.y != end.y) {
			mut.lock();
			print_word(clear, prew_now);
			print_word(strRand(len), now);
			prew_now.y++;
			if (flag) {
				prew_now = now;
				flag = false;
			}
			now.y++;
			mut.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		}
		now = start;
		flag = true;
	}
}
int main() {
	std::vector <std::pair<point_t, point_t>> points;
	point_t end{10, 10};
	point_t start{ 10, 0 };
	points.push_back(std::make_pair(start, end));
	end.x = end.x + 10;
	end.y = end.y + 20;
	start.x = start.x + 10;
	start.y = start.y + 10;
	points.push_back(std::make_pair(start, end));
	end.x = end.x + 10;
	end.y = end.y + 20;
	start.x = start.x + 10;
	start.y = start.y + 20;
	points.push_back(std::make_pair(start, end));

	std::thread thread1(make_animation, points[0].first, points[0].second, 1, 1000, 3);
	std::thread thread2(make_animation, points[1].first, points[1].second, 2, 500, 4);
	std::thread thread3(make_animation, points[2].first, points[2].second, 3, 350, 1);

	thread1.join();
	thread2.join();
	thread3.join();
}