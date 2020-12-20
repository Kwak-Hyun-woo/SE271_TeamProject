#include <iostream>

#include "control.h"

// Register
void Register::register_student(StudentDB* db) {
	int st_num;
	std::string pwd;
	std::cout << "학번을 입력해 주세요: ";
	std::cin >> st_num;
	std::cout << std::endl;
	std::cout << "비밀번호를 입력해 주세요: ";
	std::cin >> pwd;
	std::cout << std::endl;;
	Student student(st_num);
	student.set_password(pwd);
	db->add_student(&student);
	std::cout << "회원가입이 완료되었습니다." << std::endl;
}

void Register::register_admin(StudentDB* db) {
	std::string ad_id;
	std::string pwd;
	std::cout << "관리자 ID를 입력해 주세요: ";
	std::cin >> ad_id;
	std::cout << std::endl;
	std::cout << "비밀번호를 입력해 주세요: ";
	std::cin >> pwd;
	std::cout << std::endl;;
	Admin admin(ad_id);
	admin.set_password(pwd);
	db->add_admin(&admin);
	std::cout << "회원가입이 완료되었습니다." << std::endl;
}

// Log in
void LogIn::student_log_in(StudentDB* db, ControlByStudent* student) {
	int st_num;
	std::string pwd;
	Student* st;
	std::cout << "학번을 입력해 주세요: ";
	std::cin >> st_num;
	std::cout << std::endl;
	st = db->get_student(st_num);
	if (st == nullptr) {
		std::cout << "등록되지 않은 학생입니다." << std::endl;
		return;
	}
	else {
		student->set_student(st);
	}
}
void LogIn::admin_log_in(StudentDB* db, ControlByAdmin* admin) {
	std::string adm_id;
	std::string pwd;
	Admin* adm;
	std::cout << "관리자 ID를 입력해 주세요: ";
	std::cin >> adm_id;
	std::cout << std::endl;
	adm = db->get_admin(adm_id);
	if (adm == nullptr) {
		std::cout << "등록되지 않은 관리자입니다." << std::endl;
		return;
	}
	else {
		admin->set_admin(adm);
	}
}

// reservation, cancelation
void ControlByStudent::make_reservation(Seat* seat) {
	if (student->get_is_using()) {
		std::cout << "이미 예약중인 좌석이 있습니다." << std::endl;
		return;
	}
	if (seat->is_reserved()) {
		std::cout << "이미 예약된 좌석입니다." << std::endl;
		return;
	}
	student->set_is_using_reverse();
	student->set_seat_using(seat);

	seat->set_reservation_reverse();
	seat->set_res_student(student);
	seat->get_belong_to()->set_cur_using_num(seat->get_belong_to()->get_cur_using_num() + 1);
	std::cout << seat->get_seat_num() << "번 좌석 예약되었습니다." << std::endl;
}

void ControlByStudent::cancel_reservation() {
	if (!(student->get_is_using())) {
		std::cout << "예약중인 좌석이 없습니다." << std::endl;
		return;
	}

	std::cout << student->get_seat_using()->get_seat_num() << "번 좌석 예약이 취소되었습니다." << std::endl;
	student->set_is_using_reverse();
	student->get_seat_using()->set_res_student(NULL);
	student->get_seat_using()->set_reservation_reverse();
	student->set_seat_using(NULL);
	student->get_seat_using()->get_belong_to()->set_cur_using_num(student->get_seat_using()->get_belong_to()->get_cur_using_num() - 1);
}

void ControlByStudent::report_away_from(Seat* seat) {			// 현재는 그냥 신고하면 바로 예약 취소되도록 함. 타이머를 넣어서 일정 시간 안에 자리에 돌아오면 자리비움 취소할 수 있도록!
	seat->set_away_from_reverse();
}

void ControlByStudent::cancel_away_from() {
	student->get_seat_using()->set_away_from_reverse();
}