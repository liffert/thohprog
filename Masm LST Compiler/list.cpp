#include "list.h"

list* head = NULL;
void add_to_list(std::string name, int off) {
	list* temp = new list;
	if (head == NULL) {
		head = temp;
		head->identificator = name;
		head->offset = off;
		head->prew = NULL;
	}
	else {
		temp->prew = head;
		head = temp;
		head->identificator = name;
		head->offset = off;
	}
}
bool chek_ava(std::string name) {
	list* temp = head;
	while (temp != NULL) {
		if (name == temp->identificator) {
			return true;
		}
		temp = temp->prew;
	}
	return false;
}
list* get_pointer(std::string name) {
	list* temp = head;
	while (temp != NULL) {
		if (name == temp->identificator) {
			return temp;
		}
		temp = temp->prew;
	}
	return NULL;
}