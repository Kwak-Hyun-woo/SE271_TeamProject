#ifndef TP_H
#define TP_H

#include <iostream>

class Seat {
private:
	int seat_num;								// �¼��� ��ȣ
	bool reserved;								// ���� ����
	int reserved_student_num;					// ������ �й�
	std::string reserved_student_name;			// ������ �̸�
	int password;								// ���� ��й�ȣ

public:
	void init_set(int num);

	void print_status();
	void reserve(int num, std::string& name, int pw);

	bool is_reserved();
	bool cancelation();
};


#endif
