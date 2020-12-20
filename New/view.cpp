#include <iostream>
#include <windows.h>

#include "model.h"
#include "control.h"
#include "view.h"

void UI::user_interface() {
	while (true) {
		int sel;
		std::cout << "\n---------------     독서실 통합 관리 프로그램     ---------------" << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "1. 학생 로그인\t\t2. 관리자 로그인\t\t3. 종료" << "\n\n입력: ";
		std::cin >> sel;
		if (std::cin.fail() || sel < 0 || sel > 3) {
			std::cout << "\n\n잘못된 입력입니다";
			Sleep(500);
			std::cin.clear();
			std::cin.ignore(100, '\n');
			system("cls");
			continue;
		}
		else if (sel == 1) {
			std::cout << "1 선택" << std::endl;
			break;
		}
		else if (sel == 2) {
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
}

void UI::show_studyroom(StudyRoom* studyroom) {
	// 전체 좌석들 중 서로 다른 y coordinate 탐색
	int size = studyroom->get_cur_using_num();
	int* distinct_y = new int[size];
	int y_count = 0;
	int seat_num = 0;

	for (int i = 0; i < size; i++) {
		if (i == 0) {
			distinct_y[y_count] = studyroom->get_seat(i)->pos.y;
			y_count++;
			continue;
		}
		bool existing = false;
		for (int j = 0; j < y_count; j++) {
			if (studyroom->get_seat(i)->pos.y == distinct_y[j]) {
				existing = true;
				break;
			}
		}
		if (!existing) {
			distinct_y[y_count] = studyroom->get_seat(i)->pos.y;
			y_count++;
		}
	}
	// y coordinate 별로 x coordinate 분류해서 저장, 0번째 index는 해당 y coordinate에 대응하는 x coordinate의 개수
	IntList* coordinates = new IntList[y_count];
	for (int i = 0; i < y_count; i++) {
		coordinates[i].append(0);
	}
	for (int i = 0; i < size; i++) {
		for (int y_index = 0; y_index < y_count; y_index++) {
			if (studyroom->get_seat(i)->pos.y == distinct_y[y_index]) {
				coordinates[y_index].append(studyroom->get_seat(i)->pos.x);
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
					if ((studyroom->get_seat(seat_num - 1))->is_reserved()) {
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
	delete[] distinct_y;
	delete[] coordinates;
}

void UI::show_seat_status(Seat* seat) {
	std::cout << "좌석 번호 : " << seat->get_seat_num() << std::endl;
	std::cout << "예약 상태 : ";
	if (seat->is_reserved()) {
		std::cout << "예약됨" << std::endl;
		std::cout << "예약자(Student Number) : " << seat->get_res_student()->get_student_num() << std::endl;
		std::cout << "예약 시각 : 미구현" << std::endl;
	}
	else {
		std::cout << "예약되어 있지 않음 (예약 가능)" << std::endl;
	}
}