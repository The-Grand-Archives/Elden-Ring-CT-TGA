#ifndef _TGA_PARAM_CONTAINERS
#define _TGA_PARAM_CONTAINERS

#include <stddef.h>
#include <stdint.h>
#include "dl_types.h"

typedef struct _ParamRowInfo
{
	uint64_t row_id; // ID of param row
	uint64_t param_offset; // Offset of pointer to param data relative to parent table
	uint64_t param_end_offset; // Seems to point to end of ParamTable struct
} ParamRowInfo;

typedef struct _ParamTable
{
	uint8_t pad00[0x00A];
	uint16_t num_rows; // Number of rows in param table

	uint8_t pad01[0x004];
	uint64_t param_type_offset; // Offset of param type string from the beginning of this struct

	uint8_t pad02[0x028];
	ParamRowInfo rows[0]; // Array of row information structs
} ParamTable;

typedef struct _ParamHeader
{
	uint8_t pad00[0x80];
	ParamTable* param_table;
} ParamHeader;

typedef struct _ParamResCap
{
	void** vftable_ptr;

	uint8_t pad00[0x10];
	DLWString param_name;

	uint8_t pad01[0x48];
	ParamHeader* param_header;
} ParamResCap;

typedef struct _CSRegulationManagerImp
{
	void** vftable_ptr;

	uint8_t pad00[0x10];
	ParamResCap** param_list_begin;
	ParamResCap** param_list_end;
} CSRegulationManagerImp;

// Get the param type string for this param table.
inline char* get_param_type(ParamTable* tbl)
{
	return (char*)tbl + tbl->param_type_offset;
}
// Get a pointer to the data of a given row of this param.
inline uint8_t* get_row_data(ParamTable* tbl, int index)
{
	return (uint8_t*)tbl + tbl->rows[index].param_offset;
}

// Compute the size of this param using the difference between the param type offset and last row offset.
// 0 if the param has no rows.
inline uint64_t get_param_size(ParamTable* tbl)
{
	return (tbl->num_rows == 0) ? 0 : tbl->param_type_offset - tbl->rows[tbl->num_rows - 1].param_offset;
}

#endif