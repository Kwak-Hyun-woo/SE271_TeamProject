#include "tp.h"

#include <iostream>
#include <windows.h>

// 정수만을 보관하는 리스트. 기존 배열에 원소 하나를 추가하는 것을 간편하게 하기 위해 만듦
// ------------------------------------------------------------------------------------------------------------
IntList::IntList() {
	list = nullptr;
	size = 0;
}

void IntList::append(int n) {
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

void IntList::insert(int index, int n) {
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

void IntList::print() {
	if (size == 0) {
		std::cout << "[]" << std::endl;
		return;
	}
	std::cout << "[";
	for (int i = 0; i < size - 1; i++) {
		std::cout << list[i] << ", ";
	}
	std::cout << list[size - 1] << "]" << std::endl;
}

int IntList::operator[](int index) {
	return list[index];
}
void IntList::set_value(int index, int n) {
	list[index] = n;
}
int IntList::get_size() {
	return size;
}
;
// ------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------
// Seat : 좌석 클래스

void Seat::init_set(int num) {  // 수동으로 번호 지정
	seat_num = num;
	reserved = false;
	reserved_student_num = NULL;			// 수정		
	reserved_student_name = "";			    // 수정
	password = NULL;                        // 수정
}

void Seat::print_status() {    // 좌석 정보 출력
	std::cout << "좌석 번호 : " << seat_num << std::endl;
	std::cout << "예약 상태 : ";
	if (reserved) {
		std::cout << "예약됨" << std::endl;
		std::cout << "예약자 : " << reserved_student_name << "(" << reserved_student_num << ")" << std::endl;
		std::cout << "예약 시각 : 미구현" << std::endl;
	}
	else {
		std::cout << "예약되어 있지 않음 (예약 가능)" << std::endl;
	}
}

bool Seat::is_reserved() {						// 예약 여부 리턴
	return reserved;
}

void Seat::reserve(int num, std::string& name, int pw) {		// 예약
	reserved = true;
	reserved_student_name = name;
	reserved_student_num = num;
	password = pw;
}

bool Seat::cancelation() {									// 예약 취소, 취소 성공 여부를 bool type으로 리턴
	int pw;
	std::cout << "비밀번호를 입력해 주십시오 : ";
	std::cin >> pw;
	std::cout << std::endl;
	if (pw == password) {
		reserved = false;
		reserved_student_name = "";
		reserved_student_num = NULL;
		return true;
	}
	else {
		return false;
	}
}
// ------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------
// StudyRoom : 독서실 클래스

void StudyRoom::print() {									// 현재 독서실 좌석 상황을 출력
	// 전체 좌석들 중 서로 다른 y coordinate 탐색
	int* distinct_y = new int[max_size];
	int y_count = 0;
	int seat_num = 0;
	for (int i = 0; i < max_size; i++) {
		if (i == 0) {
			distinct_y[y_count] = seat_coordinate[i][1];
			y_count++;
			continue;
		}
		bool existing = false;
		for (int j = 0; j < y_count; j++) {
			if (seat_coordinate[i][1] == distinct_y[j]) {
				existing = true;
				break;
			}
		}
		if (!existing) {
			distinct_y[y_count] = seat_coordinate[i][1];
			y_count++;
		}
	}
	// y coordinate 별로 x coordinate 분류해서 저장, 0번째 index는 해당 y coordinate에 대응하는 x coordinate의 개수
	IntList* coordinates = new IntList[y_count];
	for (int i = 0; i < y_count; i++) {
		coordinates[i].append(0);
	}
	for (int i = 0; i < max_size; i++) {
		for (int y_index = 0; y_index < y_count; y_index++) {
			if (seat_coordinate[i][1] == distinct_y[y_index]) {
				coordinates[y_index].append(seat_coordinate[i][0]);
				coordinates[y_index].set_value(0, coordinates[y_index][0] + 1);
			}
		}
	}
	// print
	for (int y_index = 0; y_index < y_count; y_index++) {
		// 좌석이 배치되어 있지 않은 구간의 공백 print (y coordinate 방향)
		if (y_index == 0) {
			for (int blank = 0; blank < distinct_y[0] * 6; blank++) {
				std::cout << std::endl;
			}
		}
		else {
			for (int blank = 0; blank < (distinct_y[y_index] - distinct_y[y_index - 1] - 1) * 6; blank++) {
				std::cout << std::endl;
			}
		}
		// 같은 y coordinate 내에서 서로 다른 좌석들 사이의 간격을 저장하는 gaps 리스트
		IntList gaps;
		for (int i = 1; i <= coordinates[y_index][0]; i++) {
			if (i == 1) {
				gaps.append(coordinates[y_index][i] + 1);
				continue;
			}
			gaps.append(coordinates[y_index][i] - coordinates[y_index][i - 1]);
		}
		// 본격적인 출력, 한 줄씩 출력, 한 좌석당 12x6 크기 차지
		for (int high = 0; high < 6; high++) {
			for (int bing = 0; bing < coordinates[y_index][0]; bing++) {
				// 좌석 번호 계산
				seat_num = 0;
				for (int yi = 0; yi < y_index; yi++) {
					seat_num += coordinates[yi][0];
				}
				seat_num += (bing + 1);
				//  gaps 리스트에서 이전 좌석과 현재 좌석의 간격을 불러와 해당하는 만큼 공백 출력
				for (int i = 0; i < gaps[bing] - 1; i++) {
					std::cout << "            ";
				}
				// 현재 높이에 따라 좌석 모양 출력
				if (high == 0) {
					std::cout << " ---------- ";
				}
				else if (high == 1) {
					std::cout << "|          |";
				}
				else if (high == 2) {
					if (seat_num < 10) {
						std::cout << "|    0" << seat_num << "    |";
					}
					else {
						std::cout << "|    " << seat_num << "    |";
					}
				}
				else if (high == 3) {
					if (seat_instance_list[seat_num - 1].is_reserved()) {
						std::cout << "|  예약됨  |";
					}
					else {
						std::cout << "|          |";
					}
				}
				else if (high == 4) {
					std::cout << "|          |";
				}
				else if (high == 5) {
					std::cout << " ---------- ";
				}
			}
			std::cout << std::endl;
		}
	}
}
// StudyRoom 초기 설정
void StudyRoom::init_set(int size, int coordinate[][2]) {
	max_size = size;
	seat_coordinate = new int* [size];
	seat_instance_list = new Seat[size];
	for (int i = 0; i < size; i++) {
		seat_coordinate[i] = new int[2];
		seat_coordinate[i][0] = coordinate[i][0];
		seat_coordinate[i][1] = coordinate[i][1];
		seat_instance_list[i].init_set(i + 1);
	}
	init_setting = true;
}
	// 예약
void StudyRoom::reserve(int num) {
	if (seat_instance_list[num - 1].is_reserved()) {
		std::cout << "이미 예약되어 있는 좌석입니다. 다른 좌석을 선택해 주십시오." << std::endl;
		return;
	}
	int st_num;
	std::string st_name;
	int pw;
	std::cout << "학번을 입력해 주십시오 : ";
	std::cin >> st_num;
	std::cout << std::endl << "이름을 입력해 주십시오 : ";
	std::cin >> st_name;
	std::cout << std::endl << "예약 취소 비밀번호를 입력해 주십시오 (4자리 숫자) : ";
	std::cin >> pw;
	if (pw > 9999 || pw < 1000 || std::cin.fail()) {
		std::cout << "잘못된 비밀번호입니다." << std::endl;
		Sleep(500);
		return;
	}
	seat_instance_list[num - 1].reserve(st_num, st_name, pw);
	std::cout << std::endl << "예약이 완료되었습니다." << std::endl;
}
	// 예약 취소
void StudyRoom::cancel_reservation(int num) {
	if (!seat_instance_list[num - 1].is_reserved()) {
		std::cout << "예약되어 있지 않은 좌석입니다." << std::endl;
		return;
	}
	bool cancel = seat_instance_list[num - 1].cancelation();
	if (cancel) {
		std::cout << "예약이 취소되었습니다." << std::endl;
		return;
	}
	else {
		std::cout << "비밀번호가 틀렸습니다." << std::endl;
		return;
	}
}
	// 선택한 좌석의 정보를 출력
void StudyRoom::show_seat_status(int num) {
	seat_instance_list[num - 1].print_status();
}
StudyRoom::StudyRoom() {
	init_setting = false;
}

// ------------------------------------------------------------------------------------------------------------
