#include"Head.h"

int main()
{
	//初始化
	struct MemberList memberlist = initial_MemberList();
	readfile_Member(&memberlist);
	struct RecordList recordlist = initial_RecordList();
	readfile_Record_all(&recordlist);
	import_to_member(&recordlist, memberlist);

	struct displayArray_Record a = initial_display();
	struct Searchinfo search= info_init();
	search.searchmode |= mode_date;
	search.date_top = date_trans("2020.01.01");
	search_Record(&a, memberlist, search);

	UI_initial();
	win_display win1 = initial_window(2, 7, 80, 40);
	strcpy_s(win1.name, 20, "TEST");
	frame_window(win1);
	struct display_info info = display_list_ini(win1, a);
	MouseOP(&info);
}
