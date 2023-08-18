/************************************************************//**
*
*	@file: unix_memory.c
*	@author: Martin Fouilleul
*	@date: 10/09/2021
*	@revision:
*
*****************************************************************/
#include<sys/mman.h>
#include"platform_memory.h"

/*NOTE(martin):
	Linux and MacOS don't make a distinction between reserved and committed memory, contrary to Windows
*/
void oc_base_nop(oc_base_allocator* context, void* ptr, u64 size) {}

void* oc_base_reserve_mmap(oc_base_allocator* context, u64 size)
{
	return(mmap(0, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, 0, 0));
}

void oc_base_release_mmap(oc_base_allocator* context, void* ptr, u64 size)
{
	munmap(ptr, size);
}

oc_base_allocator* oc_base_allocator_default()
{
	static oc_base_allocator base = {};
	if(base.reserve == 0)
	{
		base.reserve = oc_base_reserve_mmap;
		base.commit = oc_base_nop;
		base.decommit = oc_base_nop;
		base.release = oc_base_release_mmap;
	}
	return(&base);
}
