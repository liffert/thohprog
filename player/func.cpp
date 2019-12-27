#include "Header.h"
#include <iostream>
#include <string.h>
#include <filesystem>
#include <sstream>
#include <bass.h>
#include "menu.h"
#include <iomanip>
#include <Windows.h>
#include <thread>
#include "search.h"

//extentions of files
typedef struct EXT {

	const std::string req_ext = ".mp3";
	const std::string req_ext2 = ".flac";
};
bool scaning = 0;
//count names array
int count;
//filesystem namespace c++17
namespace fs = std::experimental::filesystem;
//names array
std::string *name;
//stream for BASS library
HSTREAM str;
int cur_page = 0;
int Pages;
int search_list_cur_page = 0;
int search_list_pages;
int search_list_counter;
int *s_list;
bool search_flag = 0;

inline void wait() {
	std::cout << "Please wait - scaning\n";
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s", "=========== =         =                      =       =         ", 
					                     "     =      =         =                    =   =     =         ",
		                                 "     =      =         =                  =       =   =         ",
		                                 "     =      ===========                 =         =  ==========",
		                                 "     =      =         = ===========      =       =   =        = ===========",
		                                 "     =      =         = =======            =   =     =        = =======",
		                                 "     =      =         = ===========          =       =        = ===========");
	while (!scaning) {}
	return;
}
inline void print_set() {
	std::cout << "\n\n\n\nControl:\nP - play		S - pause\nD - next track		A - prew track\nQ - rewind 2 sec	E - flash forward 2 sec\nI - input index		R - to rescan\nRight arrow - scroll to the right\nLefr arrow - scroll to le left\nEsc - Back to main menu\n";
}
inline void print(const char *str, double len, int idx) {
	std::cout << "Play:";
	print(idx);
	int min = len / 60;
	int sec = len - min * 60;
	if (sec < 10) {
		std::cout << "\nLen: " << min << " min " << sec << "  seconds\n";
	}
	else {
		std::cout << "\nLen: " << min << " min " << sec << " seconds\n";
	}
}
inline void clear_search_list() {
	for (int i = 0; i < 13; i++) {
		gotoxy(100, i);
		printf("                                                                           ");
	}
}
inline void print_search_list(int i, int song_id) {
	gotoxy(100, 1 + i);
	std::cout << "|" << std::setw(5) << song_id + 1 << "|";
	print(song_id);
	return;
}
inline void search_list(int page, int pages) {
	clear_search_list();
	gotoxy(100, 0);
	std::cout << "|" << std::setw(5) << "Idx" << "|" << "Name\n";

	for (int i = 10 * page; i < 10 * page + 10; i++) {
		if (i == search_list_counter) {
			break;
		}
		print_search_list(i - 10 * page, s_list[i]);
	}
	gotoxy(100, 10 + 2);
	std::cout << page + 1 << "/" << pages << "\t Songs: " << search_list_counter << std::endl;
}
inline int pages() {
	int page = 0;
	int count = ::count;
	while (1) {
		if (count > 10) {
			count = count - 10;
			page++;
		}
		else if (count > 0) {
			page++;
			break;
		}
	}
	return page;
}
void play(int idx = -1) {
	std::string str;
	//stock state ofter start or rescan
	if (idx == -1) {
		scaning = 0;//state scaning
		system("cls");

		std::thread waiting(wait);//waiting thread while scaning
		waiting.detach();
		
		scan();//сканируем
		scaning = 1;
		
		Pages = pages();
		cur_page = 0;
		
		system("cls");
		print(cur_page, Pages);
		std::cout << "Input idx: ";
		std::cin >> idx;
		//std::cin.ignore();

		idx--;
	}

	//state of incorrect idx
	if (idx < 0 || idx > count) {
		std::cout << "Missing index\n";
		idx = 0;
	}
	if (idx > 9) {
		while (idx > (cur_page + 1) * 10 - 1) {
			cur_page++;
		}
		print(cur_page, Pages);
	}
	if (cur_page * 10 > idx) {
		while (cur_page * 10 > idx) {
			cur_page--;
		}
		print(cur_page, Pages);
	}
	//initialisation aiudio device
	BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, NULL);
	//initialisation audio stream 
	::str = BASS_StreamCreateFile(FALSE, name[idx].c_str(), 0, 0, 0);

	//struct of parametres of file
	typedef struct parametres {
		QWORD len;
		double seconds;
		int min;
		int sec;
		std::string LENGTH;
		QWORD pos;
	};
	parametres PR;
	
	//get lenth of song
	PR.len = BASS_ChannelGetLength(::str, BASS_POS_BYTE);
	PR.seconds = BASS_ChannelBytes2Seconds(::str, PR.len);
	
	//print parametres like a song, time witch playing now
	gotoxy(0, 10 + 2);
	printf("                                                                                        ");
	gotoxy(0, 10 + 2);
	print(name[idx].c_str(), PR.seconds, idx);
	
	//play song
	BASS_ChannelPlay(::str, FALSE);
	
	//print set of control
	gotoxy(0, 10 + 3);
	print_set();
	
	//create string array of lenth song
	PR.min = PR.seconds / 60;
	PR.sec = PR.seconds - PR.min * 60;
	PR.LENGTH = std::to_string(PR.min);
	PR.LENGTH = PR.LENGTH + ".";
	PR.LENGTH = PR.LENGTH + std::to_string(PR.sec);
	
	//loop of control
	while (1) {
		//progress
		gotoxy(0, 10 + 6);
		std::cout << "Progress: ";
		PR.pos = BASS_ChannelGetPosition(::str, BASS_POS_BYTE);
		PR.seconds = BASS_ChannelBytes2Seconds(::str, PR.pos);
		PR.min = PR.seconds / 60;
		PR.sec = PR.seconds - PR.min * 60;
		if(PR.sec < 10){
			std::cout << PR.min << ".0" << PR.sec << "/" << PR.LENGTH;
		}
		else {
			std::cout << PR.min << "." << PR.sec << "/" << PR.LENGTH;
		}

		int nextchar;
		if (BASS_ChannelIsActive(::str) == BASS_ACTIVE_STOPPED) {//if song ended
			if (idx == count - 1) {
				idx = 0;
			}
			else {
				idx++;
			}
			BASS_ChannelStop(::str);
			BASS_StreamFree(::str);
			play(idx);
			
			return;
		}
		else if (_kbhit()) {//if press any key
			nextchar = _getch();
			switch (nextchar) {
			case 27: {
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				
				return;
			}
			case (char)'s': {
				BASS_ChannelPause(::str);
				break;
			}
			case (char)'S': {
				BASS_ChannelPause(::str);
				break;
			}
			case (char)'p': {
				BASS_ChannelPlay(::str, FALSE);
				break;
			}
			case (char)'P': {
				BASS_ChannelPlay(::str, FALSE);
				break;
			}
			case (char)'d': {
				if (idx == count - 1) {
					idx = 0;
				}
				else {
					idx++;
				}
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				play(idx);
				;
				return;
			}
			case (char)'D': {
				if (idx == count - 1) {
					idx = 0;
				}
				else {
					idx++;
				}
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				play(idx);
				
				return;
			}
			case (char)'a': {
				if (idx == 0) {
					idx = count - 1;
				}
				else {
					idx--;
				}
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				play(idx);

				return;
			}
			case (char)'A': {
				if (idx == 0) {
					idx = count - 1;
				}
				else {
					idx--;
				}
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				play(idx);
				
				return;
			}
			case (char)'e': {
				PR.pos = BASS_ChannelGetPosition(::str, BASS_POS_BYTE);
				PR.pos = PR.pos + BASS_ChannelSeconds2Bytes(::str, 2.0);
				BASS_ChannelSetPosition(::str, PR.pos, BASS_POS_BYTE);
				break;
			}
			case (char)'E': {
				PR.pos = BASS_ChannelGetPosition(::str, BASS_POS_BYTE);
				PR.pos = PR.pos + BASS_ChannelSeconds2Bytes(::str, 2.0);
				BASS_ChannelSetPosition(::str, PR.pos, BASS_POS_BYTE);
				break;
			}
			case (char)'q': {
				PR.pos = BASS_ChannelGetPosition(::str, BASS_POS_BYTE);
				PR.pos = PR.pos - BASS_ChannelSeconds2Bytes(::str, 2.0);
				BASS_ChannelSetPosition(::str, PR.pos, BASS_POS_BYTE);
				break;
			}
			case (char)'Q': {
				PR.pos = BASS_ChannelGetPosition(::str, BASS_POS_BYTE);
				PR.pos = PR.pos - BASS_ChannelSeconds2Bytes(::str, 2.0);
				BASS_ChannelSetPosition(::str, PR.pos, BASS_POS_BYTE);
				break;
			}
			case (char)'r': {
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				play();
				return;
			}
			case (char)'R': {
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				count = 0;
				play();
				
				return;
			}
			case (char)'l': {
				search_list_counter = 0;
				search_list_cur_page = 0;
				search_list_pages = 0;
				search_flag = 1;
				clear_search_list();
				gotoxy(0, 26);
				std::cout << "Search field: ";
				std::string str;
				getline(std::cin >> std::ws, str);
				gotoxy(0, 26);
				printf("                                                                      ");
				gotoxy(87, 0);
				std::cout << "Search list: ";
				int j = 0;
				for (int i = 0; i < count; i++) {
					bool res = search(str.c_str(), name[i], str.length(), i);
					if (res) {
						s_list[j] = i;
						j++;
					}
				}
				str.clear();
				search_list_counter = j;
				if (j != 0) {
					while (1) {
						if (j > 10) {
							j = j - 10;
							search_list_pages++;
						}
						else if (j > 0) {
							search_list_pages++;
							break;
						}
					}
					search_list(search_list_cur_page, search_list_pages);
				}
				else {
					std::cout << "nothing";
					search_flag = 0;
				}
				gotoxy(100, 14);
				std::cout << "Up arrow - to scroll search list up";
				gotoxy(100, 15);
				std::cout << "Down arrow - to scroll search list down";
				gotoxy(100, 16);
				std::cout << "Delete - clear search list";
				break;
			}
			case (char)'i': {
				gotoxy(0, 26);
				std::cout << "Input Idx: ";
				std::cin >> idx;
				//std::cin.ignore();

				idx--;
	
				gotoxy(0, 26);
				printf("                         ");
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				play(idx);
				return;
			}
			case (char)'I': {
				gotoxy(0, 26);
				std::cout << "Input Idx: ";
				std::cin >> idx;
				//std::cin.ignore();

				idx--;

				gotoxy(0, 26);
				printf("                         ");
				BASS_ChannelStop(::str);
				BASS_StreamFree(::str);
				play(idx);
				return;
			}
			case 224: {
				int t = _getch();
				if (t == 77) {
					cur_page++;
					if (cur_page == Pages) {
						cur_page = 0;
					}
					print(cur_page, Pages);
				}
				else if (t == 75) {
					cur_page--;
					if (cur_page == -1) {
						cur_page = Pages - 1;
					}
					print(cur_page, Pages);
				}
				else if (t == 80 && search_flag ) {
					search_list_cur_page++;
					if (search_list_cur_page == search_list_pages) {
						search_list_cur_page = 0;
					}
					search_list(search_list_cur_page, search_list_pages);
				}
				else if (t == 72 && search_flag) {
					search_list_cur_page--;
					if (search_list_cur_page == -1) {
						search_list_cur_page = search_list_pages - 1;
					}
					search_list(search_list_cur_page, search_list_pages);
				}
				else if (t == 83) {
					search_list_counter = 0;
					search_list_cur_page = 0;
					search_flag = 0;
					clear_search_list();
					gotoxy(87, 0);
					printf("                          ");
					gotoxy(100, 15);
					printf("                                                         ");
					gotoxy(100, 14);
					printf("                                                         ");
					gotoxy(100, 16);
					printf("                                                         ");
				}
				break;
			}
			}
		}
	}
}
inline void create_array() {//читаем папку на наличиче нужных нам файлов, что б узнать размер массива и создаем сам массив

	std::ostringstream oss;
	std::string path = "./music";
	
	
	count = 0;
	EXT ext;
	for (const auto & entry : fs::recursive_directory_iterator(path)) {
		if (!fs::path(entry).extension().compare(ext.req_ext) || !fs::path(entry).extension().compare(ext.req_ext2)) {
			count++;
			oss << entry.path();//name to oss
			oss.str("");//clear oss
		}
	}
	if (count != 0) {
		name = new std::string[count];
		s_list = new int[count];
	}
	else {
		name = NULL;
	}
}
inline int _path(int strlen_path, int idx) {
	char slash = ' ';

	while (slash != '\\') {
		slash = name[idx][strlen_path];
		strlen_path--;
	}
	strlen_path = strlen_path + 2;
	return strlen_path;
}
inline void print(int idx) {
	int strlen_path;//lenth of path to file

	strlen_path = name[idx].length();
	strlen_path = _path(strlen_path, idx);
	
	for (int i = strlen_path; i < name[idx].length(); i++) {//иправить вывод
		std::cout << name[idx][i];
	}
}
inline void print(int page, int pages) {//вывод
	gotoxy(0, 0);
	for (int i = 10 * page; i < 10 * page + 12; i++) {
		printf("                                                                                 \n");
	}
	gotoxy(0, 0);
	std::cout << "|" << std::setw(5) << "Idx" << "|" << "Name\n";
	
	for (int i = 10 * page; i < 10 * page + 10; i++) {
		if (i == count) {
			break;
		}
		std::cout << "|" << std::setw(5) << i + 1 << "|";
		print(i);
		std::cout << "\n";
	}
	gotoxy(0, 10 + 1);
	std::cout << page + 1 << "/" << pages << "\t Songs: " << count << std::endl;
}
void scan() {
	std::ostringstream oss;//для конвертации в стринг элемента полученого из файл систем
	EXT ext;

	create_array();
	system("cls");

	if (name == NULL) {
		std::cout << "Empty folder";
		system("pause");
		exit(1);
	}
	std::string path = "./music";//читаем файлы
	
	int i = 0;
	for (const auto & entry : fs::recursive_directory_iterator(path)) {
		if (!fs::path(entry).extension().compare(ext.req_ext) || !fs::path(entry).extension().compare(ext.req_ext2)) {//условие проверки на .mp3
			oss << entry.path();//name to oss
			name[i] = oss.str();//converted oss to string in name array
			i++;
			oss.str("");//clear oss
		}
	}
}