#ifndef TP_H
#define TP_H
#include <Windows.h>
#include <iostream>
// 정수만을 보관하는 리스트. 기존 배열에 원소 하나를 추가하는 것을 간편하게 하기 위해 만듦
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
// Seat : 좌석 클래스
class Seat {
private:
	int seat_num;								// 좌석의 번호
	bool reserved;								// 예약 여부
	int reserved_student_num;					// 예약자 학번
	std::string reserved_student_name;			// 예약자 이름
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
// StudyRoom : 독서실 클래스
class StudyRoom {
private:
	int** seat_coordinate;							// 독서실 내 좌석이 배치된 좌표 (2차원 배열)
	int max_size;									// 전체 좌석의 수
	bool init_setting;								// 독서실의 초기 세팅이 완료되었는지를 나타냄
	int cur_using;									// 현재 사용중인 좌석의 수 (미구현)
	Seat* seat_instance_list;						// 좌석에 대응되는 Seat instance들의 배열

public:
	// 현재 독서실 좌석 상황을 출력
	void print();

	// StudyRoom 초기 설정
	void init_set(int size, int coordinate[][2]);

	// 예약
	void reserve(int num);

	// 예약 취소
	void cancel_reservation(int num);

	// 선택한 좌석의 정보를 출력
	void show_seat_status(int num);
	
	// 예약 후 색상 변경
	void setcolor(int color, int bgcolor);

	StudyRoom();
};

// ------------------------------------------------------------------------------------------------------------

#endif
