#include <iostream>
#include <windows.h>

// 정수만을 보관하는 리스트. 기존 배열에 원소 하나를 추가하는 것을 간편하게 하기 위해 만듦
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

	void print() {
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
// ------------------------------------------------------------------------------------------------------------

// Seat : 좌석 클래스
class Seat {

private:
	int seat_num;								// 좌석의 번호
	bool reserved;								// 예약 여부
	int reserved_student_num;					// 예약자 학번
	std::string reserved_student_name;			// 예약자 이름
	int password;								// 예약 비밀번호

public:
	void init_set(int num) {					// 수동으로 번호 지정
		seat_num = num;
		reserved = false;
	}

	void print_status() {						// 좌석 정보 출력
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

	bool is_reserved() {						// 예약 여부 리턴
		return reserved;
	}

	void reserve(int num, std::string& name, int pw) {		// 예약
		reserved = true;
		reserved_student_name = name;
		reserved_student_num = num;
		password = pw;
	}

	bool cancelation() {									// 예약 취소, 취소 성공 여부를 bool type으로 리턴
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
};

// ------------------------------------------------------------------------------------------------------------

// StudyRoom : 독서실 클래스
class StudyRoom {

private:
	int** seat_coordinate;							// 독서실 내 좌석이 배치된 좌표 (2차원 배열)
	int max_size;									// 전체 좌석의 수
	bool init_setting;								// 독서실의 초기 세팅이 완료되었는지를 나타냄
	int cur_using;									// 현재 사용중인 좌석의 수 (미구현)
	Seat* seat_instance_list;						// 좌석에 대응되는 Seat instance들의 배열

public:
	void print() {									// 현재 독서실 좌석 상황을 출력
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
	void init_set(int size, int coordinate[][2]) {
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
	void reserve(int num) {
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
	void cancel_reservation(int num) {
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
	void show_seat_status(int num) {
		seat_instance_list[num - 1].print_status();
	}
	StudyRoom() {
		init_setting = false;
	}
};

// ------------------------------------------------------------------------------------------------------------

int main() {
	StudyRoom e7;
	// 좌석 좌표는 반드시 우하향 순으로 정렬해서 입력해야 함!
	int e7_coordinate[23][2] = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {5, 1}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {5, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {5, 4}, {3, 6}, {4, 6}, {5, 6} };
	e7.init_set(23, e7_coordinate);
	int max_seat = 23;
	int select = 0;
	while (true) {
		system("cls");
		std::cout << "\n---------------     독서실 통합 관리 프로그램     ---------------" << std::endl;
		std::cout << std::endl << "\n현재 선택된 독서실 : E7" << std::endl;
		std::cout << std::endl << "1. 좌석 조회		2. 독서실 선택		3. 종료" << std::endl << "\n입력 : ";
		std::cin >> select;
		if (select == 1) {
			while (true) {
				system("cls");
				e7.print();
				std::cout << "\n\n1. 좌석 선택		2. 뒤로 가기" << std::endl << "\n입력 : ";
				std::cin >> select;
				if (select == 1) {
					std::cout << "\n좌석 번호를 입력해 주십시오 : ";
					std::cin >> select;
					if (select > max_seat || select < 0 || std::cin.fail()) {
						std::cout << "잘못된 입력입니다." << std::endl;
						Sleep(1000);
						continue;
					}
					int selected_seat = select;
					system("cls");
					e7.show_seat_status(select);
					std::cout << std::endl << "1. 예약		2. 예약 취소		3. 뒤로 가기" << std::endl << "\n입력 : ";
					std::cin >> select;
					system("cls");
					if (select == 1) {
						e7.reserve(selected_seat);
						Sleep(1500);
						system("cls");
					}
					else if (select == 2) {
						e7.cancel_reservation(selected_seat);
						Sleep(1500);
						system("cls");
					}
					else if (select == 3) {
						system("cls");
						continue;
					}
					else {
						std::cout << "잘못된 입력입니다." << std::endl;
						Sleep(500);
					}
				}
				else if (select == 2) {
					system("cls");
					break;
				}
				else {
					std::cout << "잘못된 입력입니다." << std::endl;
					Sleep(500);
				}
				continue;
			}
		}
		else if (select == 2) {
			std::cout << "미구현" << std::endl;
			Sleep(500);
			system("cls");
		}
		else if (select == 3) {
			system("cls");
			break;
		}
		else {
			std::cout << "잘못된 입력입니다." << std::endl;
			Sleep(500);
		}
	}
	return 0;
}

// Howoo's ass, beautiful ass