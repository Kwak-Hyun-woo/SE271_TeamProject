#pragma once

#include "model.h"
#include "control.h"

class UI {
private:
	Student* cur_log_in_student;
public:
	void user_interface();
	void show_studyroom(StudyRoom* studyroom);
	void show_seat_status(Seat* seat);
};

class IntList {
private:
	int* list;
	int size;
public:
	IntList() {
		list = nullptr;
		size = 0;
	}

	void append(int n) {
		if (size == 0) {
			list = new int[1]{ n };
			size++;
			return;
		}
		int* temp_list = new int[size];
		for (int i = 0; i < size; i++) {
			temp_list[i] = list[i];
		}
		delete[] list;
		size++;
		list = new int[size];
		for (int i = 0; i < size - 1; i++) {
			list[i] = temp_list[i];
		}
		list[size - 1] = n;
		delete[] temp_list;
	}

	void insert(int index, int n) {
		if (size == 0) {
			list = new int[1]{ n };
			size++;
			return;
		}
		int* temp_list = new int[size];
		for (int i = 0; i < size; i++) {
			temp_list[i] = list[i];
		}
		delete[] list;
		size++;
		list = new int[size];
		for (int i = 0; i < index; i++) {
			list[i] = temp_list[i];
		}
		list[index] = n;
		for (int i = index + 1; i < size; i++) {
			list[i] = temp_list[i];
		}
		delete[] temp_list;
	}

	int operator[](int index) {
		return list[index];
	}

	void set_value(int index, int n) {
		list[index] = n;
	}

	int get_size() {
		return size;
	}
};