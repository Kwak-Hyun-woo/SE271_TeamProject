#pragma once

#include "model.h"

class ControlByStudent {
public:
	void make_reservation(Student* student, Seat* seat);			// �¼� ����
	void cancel_reservation(Student* student, Seat* seat);			// ���� ���
	void report_away_from(Seat* seat);								// �ڸ� ��� �Ű�
	void cancel_away_from(Student* student, Seat* seat);			// �ڸ� ��� ����
};

class ControlByAdmin : public ControlByStudent {
public:
	void add_studyroom();
	void change_seat_coordinate();
	void force_cancel_reservation(Seat* seat);
};