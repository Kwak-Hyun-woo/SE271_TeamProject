#include "tp.h"

#include <iostream>
#include <windows.h>

int main() {
	StudyRoom e7;
	// 좌석 좌표는 반드시 우하향 순으로 정렬해서 입력해야 함!
	int e7_coordinate[23][2] = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {5, 1}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {5, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {5, 4}, {3, 6}, {4, 6}, {5, 6} };
	e7.init_set(23, e7_coordinate);
	int max_seat = 23;
	int select;
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
					if (select > max_seat || select < 0) {
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