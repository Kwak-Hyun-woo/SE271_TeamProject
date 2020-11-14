#ifndef TP_H
#define TP_H

#include <iostream>

class Seat {
private:
	int seat_num;								// 좌석의 번호
	bool reserved;								// 예약 여부
	int reserved_student_num;					// 예약자 학번
	std::string reserved_student_name;			// 예약자 이름
	int password;								// 예약 비밀번호

public:
	void init_set(int num);

	void print_status();
	void reserve(int num, std::string& name, int pw);

	bool is_reserved();
	bool cancelation();
};


#endif
