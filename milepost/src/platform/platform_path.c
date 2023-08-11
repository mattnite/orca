/************************************************************//**
*
*	@file: platform_path.c
*	@author: Martin Fouilleul
*	@date: 24/05/2023
*
*****************************************************************/

#include"platform_path.h"

str8 path_slice_directory(str8 fullPath)
{
	i64 lastSlashIndex = -1;

	for(i64 i = fullPath.len-1; i >= 0; i--)
	{
		if(fullPath.ptr[i] == '/')
		{
			lastSlashIndex = i;
			break;
		}
	}
	str8 directory = str8_slice(fullPath, 0, lastSlashIndex+1);
	return(directory);
}

str8 path_slice_filename(str8 fullPath)
{
	i64 lastSlashIndex = -1;

	for(i64 i = fullPath.len-1; i >= 0; i--)
	{
		if(fullPath.ptr[i] == '/')
		{
			lastSlashIndex = i;
			break;
		}
	}

	str8 basename = str8_slice(fullPath, lastSlashIndex+1, fullPath.len);
	return(basename);
}

str8_list path_split(mem_arena* arena, str8 path)
{
	mem_arena_scope tmp = mem_scratch_begin_next(arena);
	str8_list split = {0};
	str8_list_push(tmp.arena, &split, STR8("/"));
	str8_list res = str8_split(arena, path, split);
	mem_scratch_end(tmp);
	return(res);
}

str8 path_join(mem_arena* arena, str8_list elements)
{
	//TODO: check if elements have ending/begining '/' ?
	str8 res = str8_list_collate(arena, elements, STR8("/"), STR8("/"), (str8){0});
	return(res);
}

str8 path_append(mem_arena* arena, str8 parent, str8 relPath)
{
	str8 result = {0};

	if(parent.len == 0)
	{
		result = str8_push_copy(arena, relPath);
	}
	else if(relPath.len == 0)
	{
		result = str8_push_copy(arena, parent);
	}
	else
	{
		mem_arena_scope tmp = mem_scratch_begin_next(arena);

		str8_list list = {0};
		str8_list_push(tmp.arena, &list, parent);
		if( (parent.ptr[parent.len-1] != '/')
	  	  &&(relPath.ptr[relPath.len-1] != '/'))
		{
			str8_list_push(tmp.arena, &list, STR8("/"));
		}
		str8_list_push(tmp.arena, &list, relPath);

		result = str8_list_join(arena, list);

		mem_scratch_end(tmp);
	}
	return(result);
}

str8 path_executable_relative(mem_arena* arena, str8 relPath)
{
	str8_list list = {0};
	mem_arena_scope scratch = mem_scratch_begin_next(arena);

	str8 executablePath = path_executable(scratch.arena);
	str8 dirPath = path_slice_directory(executablePath);

	str8 path = path_append(arena, dirPath, relPath);

	mem_scratch_end(scratch);
	return(path);
}