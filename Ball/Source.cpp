#include "Header.h"
#include "Map.h"
#include <iostream>
#include <Windows.h>
#include <sstream> //для використання ostringstream (для конвертування чисел в строку)
#include "View.h"
#include <conio.h>
#pragma warning (disable: 4996)
#define MENU_FUNC 4
HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace sf;// підключення простору імен SFML
int lvl = 1;//поточний рівень
int point = 0; // кількість балів
bool viewFlag = 0;// перевірка чи увімкнена опція слідкування за м’ячем
int goldP = 10;//бонуси за за золото. серебро та бронзу
int silverP = 5;
int bronzeP = 3;
class ballhero {// клас м’яча
public:
	float w;
	float h;
	float x;
	float y;
	float dx;
	float dy;
	float speed = 0;
	int dir = 0;
	bool flag = 0;
	Texture Balltexture;
	Sprite Ball;
	SoundBuffer Buf;
	SoundBuffer TBuf;
	Sound teleport;
	Sound pointer;
	ballhero(float X, float Y, float W, float H) {//конструктор класу з заданням текстури для м’яча, розімірів та позиції початкового виводу на екран
		w = W;
		h = H;
		Balltexture.loadFromFile("Ball.png");
		Ball.setTexture(Balltexture);
		x = X;
		y = Y;
		TBuf.loadFromFile("Tp.ogg");
		teleport.setBuffer(TBuf);
		Buf.loadFromFile("Pointer.ogg");
		pointer.setBuffer(Buf);
	}
	void update(float time) {//функція оновлення стану м’яча(руху) в залежності з залежністю від часу, що робить швидкодію гри одноковою незалежно від навантаження на процессор
		switch (dir) {
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x = x + dx * time;
		y = y + dy * time;
		Ball.setPosition(x, y);
		interactionWithMap();
	}
	void interactionWithMap() {//функція взаємодії з картою
		for (int i = y / 32; i < (y + h) / 32; i++) {
			for (int j = x / 32; j < (x + w) / 32; j++) {
				if (TileMap[i][j] == '0' || TileMap[i][j] == 's' || TileMap[i][j] == 'w') {
					if (dy > 0) {
						y = i * 32 - h;
						speed = 0;
					}
					if (dy < 0) {
						y = i * 32 + 32;
						speed = 0;
					}
					if (dx > 0) {
						x = j * 32 - w;
						speed = 0;
					}
					if (dx < 0) {
						x = j * 32 + 32;
						speed = 0;
					}
				}
				if (TileMap[i][j] == 'g') {
					int k = j;
					bool flag = 0;
					int o = 0;
					while (1) {
						if (TileMap[o][k] == 'g') {
							TileMap[o][k] = ' ';
							flag = 1;
						}
						else if (flag == 1 && TileMap[o][k] != 'g') {
							break;
						}
						o++;
					}
				}
				if (TileMap[i][j] == 'z') {
					int k = i;
					bool flag = 0;
					int o = 0;
					while (1) {
						if (TileMap[k][o] == 'z') {
							TileMap[k][o] = ' ';
							flag = 1;
						}
						else if (flag == 1 && TileMap[k][o] != 'z') {
							break;
						}
						o++;
					}
				}
				if (TileMap[i][j] == 'p') {
					TileMap[i][j] = ' ';
					point++;
					pointer.play();
				}
				if (TileMap[i][j] == 'f') {
					if (lvl == 1) {
						for (int i = 0; i < HEIGHT_MAP; i++) {
							for (int j = 0; j < WIDTH_MAP; j++) {
								TileMap[i][j] = Level_2[i][j];
							}
						}
						x = 72.7956;
						y = 933.116;
						lvl++;
					}
					else if (lvl == 2) {
						if (dy > 0) {
							y = i * 32 - h;
							speed = 0;
						}
						if (dy < 0) {
							y = i * 32 + 32;
							speed = 0;
						}
						if (dx > 0) {
							x = j * 32 - w;
							speed = 0;
						}
						if (dx < 0) {
							x = j * 32 + 32;
							speed = 0;
						}
						flag = 1;
					}
				}
				if (TileMap[i][j] == 't') {
					teleport.play();
					x = 841.053;
					y = 326.076;
					for (int r = 16; r < 20; r++) {
						for (int j = 14; j < 46; j++) {
							TileMap[r][j] = 'w';
						}
					}
					speed = 0;
				}
			}
		}
	}
};
class End {//клас закінчення гри
private:
	Texture Finishtexture;
	std::ostringstream Goldens;
	std::ostringstream Silvers;
	std::ostringstream Bronzes;
	std::ostringstream Timestr;
	std::ostringstream Pointsstr;
public:
	Font font;
	Sprite finish;
	Text Bronze;
	Text Golden;
	Text silver;
	Text myTime;
	Text myPoints;

	End(int time, int points) {//конструктор, що задає значення для філнального виводу в залежності від часу та набраних балів
		Finishtexture.loadFromFile("finish.jpg");
		finish.setTexture(Finishtexture);
		font.loadFromFile("ARIAL.TTF");
		myTime.setStyle(Text::Underlined);
		Bronze.setFont(font);
		Bronze.setCharacterSize(20);
		silver.setFont(font);
		silver.setCharacterSize(20);
		Golden.setFont(font);
		Golden.setCharacterSize(20);
		myTime.setFont(font);
		myTime.setCharacterSize(20);
		myTime.setStyle(Text::Underlined);
		myPoints.setFont(font);
		myPoints.setCharacterSize(20);
		myPoints.setStyle(Text::Bold);
		Goldens << 35;
		Silvers << 45;
		Bronzes << 55;
		Timestr << time;
		Pointsstr << points;
		Golden.setString("1. Gold: " + Goldens.str() + " Seconds");
		Golden.setPosition(50, 25);
		silver.setPosition(50, 75);
		Bronze.setPosition(50, 125);
		myTime.setPosition(50, 175);
		myPoints.setPosition(50, 225);
		silver.setString("2. Silver: " + Silvers.str() + " Seconds");
		Bronze.setString("3. Bronze: " + Bronzes.str() + " Seconds");
		myTime.setString("Your Time: " + Timestr.str() + " Seconds");
		myPoints.setString("Points: " + Pointsstr.str());
	}
};
void game() {//запуск гри
	int GameTime;
	Texture Maptexture;
	Sprite Map;
	Font font;
	font.loadFromFile("ARIAL.TTF");
	Text text("", font, 20);
	text.setStyle(Text::Bold);
	Text timeGame("", font, 20);
	timeGame.setStyle(Text::Underlined);
	Maptexture.loadFromFile("map2.png");
	Map.setTexture(Maptexture);
	RenderWindow window(VideoMode(1920, 1080), "Game test 2", Style::None);
	if (viewFlag == 1) {
		view.reset(FloatRect(0, 0, 1920, 1080));//встановлення виду на м’яч ящо ввідмкнено слідкування за м’ячем
	}
	Clock clock;
	Clock Gameclock;
	ballhero ball(35.81071, 399.542, 85, 85);//створення об’єкту ball  через конструктор класу ballhero
	
	while (window.isOpen()) {

		GameTime = Gameclock.getElapsedTime().asSeconds();
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;

		while (window.pollEvent(event)) {
			if (event.type == event.KeyPressed) {
				if (event.key.code == Keyboard::Escape) {//закриття гри на клавішу esc
					window.close();
					for (int i = 0; i < HEIGHT_MAP; i++) {
						for (int j = 0; j < WIDTH_MAP; j++) {
							TileMap[i][j] = stock[i][j];
						}
					}
					lvl = 1;
					point = 0;
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {//керування м’ячем за допомоги стрілок
			ball.dir = 1;
			ball.speed = 0.3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			ball.dir = 0;
			ball.speed = 0.3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			ball.dir = 3;
			ball.speed = 0.3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			ball.dir = 2;
			ball.speed = 0.3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			ball.speed = 0;
		}
		ball.update(time);

		if (viewFlag == 1) {//переменіщення камери на м’яч в кожен момент часу
			camera(ball.x, ball.y);
			window.setView(view);
		}
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++) {//вивід певної частини тукстури (тайл) в залежності від символа, що зустрічається на мапі
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == ' ') {
					Map.setTextureRect(IntRect(0, 0, 32, 32));
				}
				if (TileMap[i][j] == 's') {
					Map.setTextureRect(IntRect(32, 0, 32, 32));
				}
				if (TileMap[i][j] == '0') {
					Map.setTextureRect(IntRect(64, 0, 32, 32));
				}
				if (TileMap[i][j] == 'g') {
					Map.setTextureRect(IntRect(96, 0, 32, 32));
				}
				if (TileMap[i][j] == 'w') {
					Map.setTextureRect(IntRect(128, 0, 32, 32));
				}
				if (TileMap[i][j] == 'p') {
					Map.setTextureRect(IntRect(0, 0, 32, 32));
				}
				if (TileMap[i][j] == 'z') {
					Map.setTextureRect(IntRect(96, 0, 32, 32));
				}
				if (TileMap[i][j] == 'f') {
					Map.setTextureRect(IntRect(160, 0, 32, 32));
				}
				if (TileMap[i][j] == 't') {
					Map.setTextureRect(IntRect(192, 0, 32, 32));
				}
				Map.setPosition(j * 32, i * 32);//встановлення потрібної позиції з урахуванням розміру тайлів 32х32
				window.draw(Map);
			}
		}
		std::ostringstream pointsString;
		std::ostringstream TimeString;
		pointsString << point;
		TimeString << GameTime;
		text.setString("Points:" + pointsString.str());
		text.setPosition(0, 0);
		timeGame.setString("Time:" + TimeString.str());
		timeGame.setPosition(1800, 0);
		if (viewFlag == 1) {
			timeGame.setPosition(ball.x + 200, ball.y - 200);
			text.setPosition(ball.x - 200, ball.y - 200);
		}
		window.draw(text);
		window.draw(timeGame);
		window.draw(ball.Ball);
		Text closewindow("Press Escape for Back to main menu", font, 20);
		closewindow.setPosition(100, 300);
		if (ball.flag == 1) {//Закінчення гри та виввід рузультатів
			Text record("", font, 20);
			if (viewFlag == 1) {
				view.reset(FloatRect(0, 0, 1920, 1080));
				view.zoom(1.5);
				window.setView(view);
			}
			if (GameTime <= 35 ) {
				if (point == 20) {
					point = point + goldP;
					record.setString("You beat gold time and got a bonus - 10 points");
				}
				else {
					record.setString("You not pick up all pointers - no bonus");
				}
			}
			else if (GameTime <= 45) {
				if (point == 20) {
					point = point + silverP;
					record.setString("You beat silver time and got a bonus - 5 points");
				}
				else {
					record.setString("You not pick up all pointers - no bonus");
				}
			}
			else if (GameTime <= 55) {
				if (point == 20) {
					point = point + bronzeP;
					record.setString("You beat bronze time and got a bonus - 3 points");
				}
				else {
					record.setString("You not pick up all pointers - no bonus");
				}
			}
			else {
				record.setString("You not beat any record");
			}
			record.setPosition(100, 275);
			End end(GameTime, point);
			window.draw(end.finish);
			window.draw(end.Golden);
			window.draw(end.silver);
			window.draw(end.Bronze);
			window.draw(end.myTime);
			window.draw(end.myPoints);
			window.draw(record);
			window.draw(closewindow);
		}
		window.display();
		if (ball.flag == 1) {//зупинка гри для перегляду результатів та фиходу з гри. повернення карти першого рівня, для рестарту
			while (1) {
				while (window.pollEvent(event)) {
					if (event.type == event.KeyPressed) {
						if (event.key.code == Keyboard::Escape) {
							window.close();
							for (int i = 0; i < HEIGHT_MAP; i++) {
								for (int j = 0; j < WIDTH_MAP; j++) {
									TileMap[i][j] = stock[i][j];
								}
							}
							lvl = 1;
							point = 0;
						}
					}
				}
				if (point == 0) {
					break;
				}
			}
		}
	}
}
void rules() {//вивід правил
	system("cls");
	printf("%s\n%s\n%s\n%s\n", "!!! Якщо у вас монітор розширенням меньше ніж FULL HD(1920x1080) - увімкніть в налаштуваннях слідкування за м’ячем !!!\n",
		"Правила гри:\n Потрібно проїзжати м’ячем через зелені ворота. Вони подвійні. нарахування балів відбувається після проїзду через обідві частини воріт.",
		"Керування здійснюється стрілками на клавіатурі. Зупинка м’яча відбувається при нажатті клавіші ПРОБІЛ. Вихід на клавішу Escape. Гра складається з двох рівней.",
		"Якщо вихід з програми не відбувається на Escape - клікніть мишкою по вікну програми та спробуйсте ще раз");
	system("pause");
}
void gotoxy(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}
//меню програми
void draw_menu(int selection) {
	system("cls");
	char options[MENU_FUNC][255] = { "Запуск гри", "Налаштування", "Прочитай перед грою", "Вихід" };
	for (int i = 0; i < MENU_FUNC; i++) {
		gotoxy(40, 10 + i);
		if (i == selection) {
			SetConsoleTextAttribute(hStdOut, 5);
			printf("%d. %s", i + 1, options[i]);
		}
		else {
			SetConsoleTextAttribute(hStdOut, 7);
			printf("%d. %s", i + 1, options[i]);
		}
	}
}
void settings_menu() {
	system("cls");
	gotoxy(40, 10);
	char options[2][255] = { "Слідкування за м’ячем - увімкнено", "Слідкування за м’ячем - вимкнено" };
	if (viewFlag == 0) {
		SetConsoleTextAttribute(hStdOut, 5);
		printf("%d. %s", 1, options[1]);
	}
	if (viewFlag == 1) {
		SetConsoleTextAttribute(hStdOut, 5);
		printf("%d. %s", 1, options[0]);
	}
	gotoxy(30, 20);
	SetConsoleTextAttribute(hStdOut, 7);
	printf("Для зміни параметра натисніть Enter, для виходу в головне меню Escape");
}
void settings_loop() {
	int zinderg = 0;

	while (1) {
		settings_menu();
		int nextchar = getch();
		switch (nextchar) {
		case 13: {
			if (viewFlag == 0) {
				viewFlag = 1;
			}
			else if (viewFlag == 1) {
				viewFlag = 0;
			}
			break;
		}
		case 27: return;
		}
	}
}
void control_loop() {
	int zinderg = 0;

	while (1) {
		draw_menu(zinderg);
		int nextchar = getch();
		switch (nextchar) {
		case 224: {
			int t = getch();
			if (t == 80 && zinderg < MENU_FUNC - 1) { zinderg++; }
			else if (t == 72 && zinderg > 0) { zinderg--; }
			break;
		}
		case 13: {
			switch (zinderg) {
			case 0: game(); break;
			case 1: settings_loop(); break;
			case 2: rules(); break;
			case 3: exit(1);
			}
		}
		}
	}
}
int main() {
	system("chcp 1251");
	control_loop();
	return 0;
}