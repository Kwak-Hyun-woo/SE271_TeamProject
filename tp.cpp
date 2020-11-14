#include "tp.h"

#include <iostream>


void Seat::init_set(int num) {  // �������� ��ȣ ����
	seat_num = num;
	reserved = false;
	reserved_student_num = NULL;			// ����		
	reserved_student_name = "";			    // ����
	password = NULL;                        // ����
}

void Seat::print_status() {    // �¼� ���� ���
	std::cout << "�¼� ��ȣ : " << seat_num << std::endl;
	std::cout << "���� ���� : ";
	if (reserved) {
		std::cout << "�����" << std::endl;
		std::cout << "������ : " << reserved_student_name << "(" << reserved_student_num << ")" << std::endl;
		std::cout << "���� �ð� : �̱���" << std::endl;
	}
	else {
		std::cout << "����Ǿ� ���� ���� (���� ����)" << std::endl;
	}
}

bool Seat::is_reserved() {						// ���� ���� ����
	return reserved;
}

void Seat::reserve(int num, std::string& name, int pw) {		// ����
	reserved = true;
	reserved_student_name = name;
	reserved_student_num = num;
	password = pw;
}

bool Seat::cancelation() {									// ���� ���, ��� ���� ���θ� bool type���� ����
	int pw;
	std::cout << "��й�ȣ�� �Է��� �ֽʽÿ� : ";
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


