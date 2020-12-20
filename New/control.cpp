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
	std::cout << std::endl;
	db->add_student(Student(st_num, pwd));
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
	std::cout << std::endl;
	db->add_admin(Admin(ad_id, pwd));
	std::cout << "회원가입이 완료되었습니다." << std::endl;
}

// Log in
void LogIn::student_log_in(StudentDB* db, ControlByStudent* control_student) {
	int st_num;
	std::string pwd;
	std::cout << "학번을 입력해 주세요: ";
	std::cin >> st_num;
	std::cout << std::endl;

	Student* student = db->get_student(st_num);
	if (!student) {
		std::cout << "존재하지 않는 학번입니다. 회원가입 후 사용해주세요." << std::endl;
		return;
	}

	std::cout << "비밀번호를 입력해 주세요: ";
	std::cin >> pwd;
	std::cout << std::endl;

	if (pwd != student->get_password()) {
		std::cout << "비밀번호가 잘못되었습니다." << std::endl;
		return;
	}

	std::cout << "로그인 되었습니다." << std::endl;
	control_student->set_student(student);
}

void LogIn::admin_log_in(StudentDB* db, ControlByAdmin* control_admin) {
	std::string ad_id;
	std::string pwd;
	std::cout << "관리자 학번을 입력해 주세요: ";
	std::cin >> ad_id;
	std::cout << std::endl;

	Admin* admin = db->get_admin(ad_id);
	if (!admin) {
		std::cout << "등록되지 않은 학번입니다. 프로그램 관리자에게 문의해주세요." << std::endl;
		return;
	}

	std::cout << "비밀번호를 입력해 주세요: ";
	std::cin >> pwd;
	std::cout << std::endl;

	if (pwd != admin->get_password()) {
		std::cout << "비밀번호가 잘못되었습니다." << std::endl;
		return;
	}

	std::cout << "관리자 권한으로 로그인 되었습니다." << std::endl;
	control_admin->set_admin(admin);
}

// ControlByStudent
void ControlByStudent::set_student(Student* controller) {
	student = controller;
}

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
}

void ControlByStudent::cancel_reservation() {
	if (!(student->get_is_using())) {
		std::cout << "예약중인 좌석이 없습니다." << std::endl;
		return;
	}

	std::cout << student->get_seat_using()->get_seat_num() << "번 좌석 예약이 취소되었습니다." << std::endl;
	student->set_is_using_reverse();
	student->get_seat_using()->set_res_student(nullptr);
	student->get_seat_using()->set_reservation_reverse();
	student->set_seat_using(nullptr);
	student->get_seat_using()->get_belong_to()->set_cur_using_num(student->get_seat_using()->get_belong_to()->get_cur_using_num() - 1);
}

void ControlByStudent::report_away_from(Seat* seat) {			// 현재는 그냥 신고하면 바로 예약 취소되도록 함. 타이머를 넣어서 일정 시간 안에 자리에 돌아오면 자리비움 취소할 수 있도록!
	seat->set_away_from_reverse();
}

void ControlByStudent::cancel_away_from() {
	student->get_seat_using()->set_away_from_reverse();
}

// ControlByAdmin
void ControlByAdmin::set_admin(Admin* controller) {
	admin = controller;
}

void ControlByAdmin::add_studyroom() {

}

void ControlByAdmin::change_seat_coordinate() {

}

void ControlByAdmin::force_cancel_reservation(Seat* seat) {
	if (!(seat->is_reserved())) {
		std::cout << "예약중인 좌석이 없습니다." << std::endl;
		return;
	}

	std::cout << seat->get_seat_num() << "번 좌석 예약이 취소되었습니다." << std::endl;
	seat->get_res_student()->set_is_using_reverse();
	seat->get_res_student()->set_seat_using(nullptr);
	seat->get_res_student()->set_studyroom_using(nullptr);

	seat->set_reservation_reverse();
	seat->set_res_student(nullptr);
	seat->set_away_from_reverse();

	seat->get_belong_to()->set_cur_using_num(seat->get_belong_to()->get_cur_using_num() - 1);
}
