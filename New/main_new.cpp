#include <iostream>
#include <windows.h>

#include "model.h"
#include "control.h"
#include "view.h"

int main() {

	/// 독서실 생성, 좌석 세팅
	StudyRoom E7("E7", 10);
	std::cout << "DONE" << std::endl;
	
	Pos temp_pos(1, 2);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	temp_pos(1, 3);
	E7.add_seat(Seat(&E7, 2, temp_pos));
	temp_pos(2, 3);
	E7.add_seat(Seat(&E7, 3, temp_pos));
	temp_pos(2, 4);
	E7.add_seat(Seat(&E7, 4, temp_pos));
	temp_pos(2, 5);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	///

	UI main_interface;

	StudentDB database;
	
	system("cls");

	while (true) {
		int sel;
		std::cout << "\n--------------------     독서실 통합 관리 프로그램     --------------------" << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "1. 학생 로그인     2. 관리자 로그인     3.학생 회원가입     4.관리자 회원가입     5. 종료" << "\n\n입력: ";
		std::cin >> sel;
		if (std::cin.fail() || sel < 0 || sel > 5) {
			std::cout << "\n\n잘못된 입력입니다";
			Sleep(500);
			std::cin.clear();
			std::cin.ignore(100, '\n');
			system("cls");
			continue;
		}
		else if (sel == 1) {
			system("cls");
			std::cout << "1 선택" << std::endl;
			break;
		}
		else if (sel == 2) {
			system("cls");
			std::cout << "2 선택" << std::endl;
			break;
		}
		else if (sel == 3) {
			system("cls");
			Register student_reg;
			student_reg.register_student(&database);
		}
		else if (sel == 4) {
			system("cls");
			std::cout << "2 선택" << std::endl;
			break;
		}
		else {
			std::cout << "프로그램을 종료합니다.";
			Sleep(1000);
			system("cls");
			break;
		}
	}
	return 0;
}