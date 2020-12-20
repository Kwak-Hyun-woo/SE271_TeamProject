#include <iostream>

#include "model.h"
#include "control.h"
#include "view.h"

int main() {

	/// 독서실 생성, 좌석 세팅
	StudyRoom E7(10);
	Pos temp_pos(1, 2);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	temp_pos(1, 3);
	E7.add_seat(Seat(&E7, 2, temp_pos));
	temp_pos(2, 3);
	E7.add_seat(Seat(&E7, 3, temp_pos));
	temp_pos(2, 4);
	E7.add_seat(Seat(&E7, 4, temp_pos));
	temp_pos(2, 5);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	///

	UI main_interface;

	main_interface.show_studyroom(&E7);
	
	system("cls");

	main_interface.user_interface();

	return 0;
}