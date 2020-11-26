#ifndef TP_H
#define TP_H
#include <Windows.h>
#include <iostream>
// �������� �����ϴ� ����Ʈ. ���� �迭�� ���� �ϳ��� �߰��ϴ� ���� �����ϰ� �ϱ� ���� ����
class IntList {
private:
	int* list;
	int size;
public:
	IntList();

	void append(int n);
	void insert(int index, int n);
	void print();
	int operator[](int index);
	void set_value(int index, int n);
	int get_size();
};
// ------------------------------------------------------------------------------------------------------------
// Seat : �¼� Ŭ����
class Seat {
private:
	int seat_num;								// �¼��� ��ȣ
	bool reserved;								// ���� ����
	int reserved_student_num;					// ������ �й�
	std::string reserved_student_name;			// ������ �̸�
	int password;	
	int time_num;
	int time_min;
public:
	void init_set(int num);

	void print_status();
	void reserve(int num, std::string& name, int pw, int time, int min);

	bool is_reserved();
	bool cancelation();
};
// StudyRoom : ������ Ŭ����
class StudyRoom {
private:
	int** seat_coordinate;							// ������ �� �¼��� ��ġ�� ��ǥ (2���� �迭)
	int max_size;									// ��ü �¼��� ��
	bool init_setting;								// �������� �ʱ� ������ �Ϸ�Ǿ������� ��Ÿ��
	int cur_using;									// ���� ������� �¼��� �� (�̱���)
	Seat* seat_instance_list;						// �¼��� �����Ǵ� Seat instance���� �迭

public:
	// ���� ������ �¼� ��Ȳ�� ���
	void print();

	// StudyRoom �ʱ� ����
	void init_set(int size, int coordinate[][2]);

	// ����
	void reserve(int num);

	// ���� ���
	void cancel_reservation(int num);

	// ������ �¼��� ������ ���
	void show_seat_status(int num);
	
	// ���� �� ���� ����
	void setcolor(int color, int bgcolor);

	StudyRoom();
};

// ------------------------------------------------------------------------------------------------------------

#endif
