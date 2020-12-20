#pragma once

#include "model.h"

class Register {
public:
	void register_student(StudentDB* db);
	void register_admin(StudentDB* db);
};

class ControlByStudent {
private:
	Student* student = nullptr;
public:
	void set_student(Student* student);
	void make_reservation(Seat* seat);			// 좌석 예약
	void cancel_reservation();					// 예약 취소
	void report_away_from(Seat* seat);			// 자리 비움 신고
	void cancel_away_from();					// 자리 비움 해제
};

class ControlByAdmin : public ControlByStudent {
private:
	Admin* admin = nullptr;
public:
	void set_admin(Admin* admin);
	void add_studyroom();
	void change_seat_coordinate();
	void force_cancel_reservation(Seat* seat);
};

class LogIn {
public:
	void student_log_in(StudentDB* db, ControlByStudent* control_student);
	void admin_log_in(StudentDB* db, ControlByAdmin* control_admin);
};