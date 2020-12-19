#pragma once

#include "model.h"

class ControlByStudent {
public:
	void make_reservation(Student* student, Seat* seat);			// 좌석 예약
	void cancel_reservation(Student* student, Seat* seat);			// 예약 취소
	void report_away_from(Seat* seat);								// 자리 비움 신고
	void cancel_away_from(Student* student, Seat* seat);			// 자리 비움 해제
};

class ControlByAdmin : public ControlByStudent {
public:
	void add_studyroom();
	void change_seat_coordinate();
	void force_cancel_reservation(Seat* seat);
};