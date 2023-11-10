#pragma once





const struct PREDIFINED_COMMANDS
{
	const char* HELP_CHAR = "?";
	const char* EXIT_CHAR = "`";
};



struct SortingData
{
	int field_id;

	int order;

};


static void SetSortingData(SortingData* sortingData, int _id, int _order)
{
	sortingData->field_id = _id;

	sortingData->order = _order;

}
