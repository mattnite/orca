/************************************************************//**
*
*	@file: orca.c
*	@author: Martin Fouilleul
*	@date: 13/02/2021
*	@revision:
*
*****************************************************************/

//---------------------------------------------------------------
// platform implementations
//---------------------------------------------------------------
#include"platform/platform.h"

#if OC_PLATFORM_WINDOWS
	#include"platform/native_debug.c"
	#include"platform/win32_memory.c"
	#include"platform/win32_clock.c"
	#include"platform/win32_string_helpers.c"
	#include"platform/win32_path.c"
	#include"platform/win32_io.c"
	#include"platform/win32_thread.c"
	//TODO
#elif OC_PLATFORM_MACOS
	#include"platform/native_debug.c"
	#include"platform/unix_memory.c"
	#include"platform/osx_clock.c"
	#include"platform/posix_io.c"
	#include"platform/posix_thread.c"

	/*
	#include"platform/unix_rng.c"
	#include"platform/posix_socket.c"
	*/

#elif PLATFORM_LINUX
	#include"platform/native_debug.c"
	#include"platform/unix_base_memory.c"
	#include"platform/linux_clock.c"
	#include"platform/posix_io.c"
	#include"platform/posix_thread.c"
	/*
	#include"platform/unix_rng.c"
	#include"platform/posix_socket.c"
	*/
#elif OC_PLATFORM_ORCA
	#include"platform/orca_debug.c"
	#include"platform/orca_clock.c"
	#include"platform/orca_memory.c"
	#include"platform/orca_malloc.c"
	#include"platform/platform_io_common.c"
	#include"platform/orca_io_stubs.c"
#else
	#error "Unsupported platform"
#endif

//---------------------------------------------------------------
// utilities implementations
//---------------------------------------------------------------
#include"util/memory.c"
#include"util/strings.c"
#include"util/utf8.c"
#include"util/hash.c"
#include"util/ringbuffer.c"
#include"util/algebra.c"

//---------------------------------------------------------------
// app/graphics layer
//---------------------------------------------------------------

#if OC_PLATFORM_WINDOWS
	#include"app/win32_app.c"
	#include"graphics/graphics_common.c"
	#include"graphics/graphics_surface.c"

	#if OC_COMPILE_GL || OC_COMPILE_GLES
		#include"graphics/gl_loader.c"
	#endif

	#if OC_COMPILE_GL
		#include"graphics/wgl_surface.c"
	#endif

	#if OC_COMPILE_CANVAS
		#include"graphics/gl_canvas.c"
	#endif

	#if OC_COMPILE_GLES
		#include"graphics/egl_surface.c"
	#endif

#elif OC_PLATFORM_MACOS
	//NOTE: macos application layer and graphics backends are defined in orca.m
#elif OC_PLATFORM_ORCA
	#include"app/orca_app.c"
	#include"graphics/graphics_common.c"
	#include"graphics/orca_surface_stubs.c"
#else
	#error "Unsupported platform"
#endif

#include"ui/input_state.c"
#include"ui/ui.c"