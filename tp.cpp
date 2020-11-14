#include "tp.h"

#include <iostream>


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


