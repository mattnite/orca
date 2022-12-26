/************************************************************//**
*
*	@file: graphics_internal.h
*	@author: Martin Fouilleul
*	@date: 01/08/2022
*	@revision:
*
*****************************************************************/
#ifndef __GRAPHICS_INTERNAL_H_
#define __GRAPHICS_INTERNAL_H_

#include"graphics.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------------------------
// Surfaces
//---------------------------------------------------------------------------------------------
typedef struct mg_surface_info mg_surface_info;

typedef void (*mg_surface_prepare_proc)(mg_surface_info* surface);
typedef void (*mg_surface_present_proc)(mg_surface_info* surface);
typedef void (*mg_surface_resize_proc)(mg_surface_info* surface, u32 width, u32 height);
typedef void (*mg_surface_set_hidden_proc)(mg_surface_info* surface, bool hidden);
typedef vec2 (*mg_surface_get_size_proc)(mg_surface_info* surface);
typedef void (*mg_surface_destroy_proc)(mg_surface_info* surface);
typedef void* (*mg_surface_get_os_resource_proc)(mg_surface_info* surface);

typedef struct mg_surface_info
{
	mg_backend_id backend;
	mg_surface_destroy_proc destroy;
	mg_surface_prepare_proc prepare;
	mg_surface_present_proc present;
	mg_surface_resize_proc resize;
	mg_surface_set_hidden_proc setHidden;
	mg_surface_get_size_proc getSize;
	mg_surface_get_os_resource_proc getOSResource;

} mg_surface_info;

mg_surface mg_surface_alloc_handle(mg_surface_info* surface);
mg_surface_info* mg_surface_ptr_from_handle(mg_surface handle);
//---------------------------------------------------------------------------------------------
// Surface servers
//---------------------------------------------------------------------------------------------
typedef struct mg_surface_server_info mg_surface_server_info;

typedef void (*mg_surface_server_destroy_proc)(mg_surface_server_info* server);
typedef mg_surface_server_id (*mg_surface_server_get_id_proc)(mg_surface_server_info* server);

typedef struct mg_surface_server_info
{
	mg_surface_server_destroy_proc destroy;
	mg_surface_server_get_id_proc getID;

} mg_surface_server_info;

mg_surface_server mg_surface_server_alloc_handle(mg_surface_server_info* server);

//---------------------------------------------------------------------------------------------
// Surface clients
//---------------------------------------------------------------------------------------------
typedef struct mg_surface_client_info mg_surface_client_info;

typedef void (*mg_surface_client_destroy_proc)(mg_surface_client_info* client);
typedef void (*mg_surface_client_attach_proc)(mg_surface_client_info* client);
typedef void (*mg_surface_client_detach_proc)(mg_surface_client_info* client);

typedef struct mg_surface_client_info
{
	mg_surface_client_destroy_proc destroy;
	mg_surface_client_attach_proc attach;
	mg_surface_client_detach_proc detach;

} mg_surface_client_info;

mg_surface_client mg_surface_client_alloc_handle(mg_surface_client_info* client);
//---------------------------------------------------------------------------------------------
// vertex layout
//---------------------------------------------------------------------------------------------
typedef struct mgc_vertex_layout
{
	u32 maxVertexCount;
	u32 maxIndexCount;

	void* posBuffer;
	u32 posStride;

	void* cubicBuffer;
	u32 cubicStride;

	void* uvBuffer;
	u32 uvStride;

	void* colorBuffer;
	u32 colorStride;

	void* zIndexBuffer;
	u32 zIndexStride;

	void* clipsBuffer;
	u32 clipsStride;

	void* indexBuffer;
	u32 indexStride;

} mgc_vertex_layout;

typedef struct mg_canvas_painter mg_canvas_painter;
typedef void (*mgc_painter_destroy_proc)(mg_canvas_painter* painter);
typedef void (*mgc_painter_draw_buffers_proc)(mg_canvas_painter* painter, u32 vertexCount, u32 indexCount, mg_color clearColor);
typedef void (*mgc_painter_set_viewport_proc)(mg_canvas_painter* painter, mp_rect viewPort);
typedef void (*mgc_painter_atlas_upload_proc)(mg_canvas_painter* painter, mp_rect rect, u8* bytes);

typedef struct mg_canvas_painter
{
	mg_surface_info* surface;
	mgc_vertex_layout vertexLayout;
	mgc_painter_destroy_proc destroy;
	mgc_painter_draw_buffers_proc drawBuffers;
	mgc_painter_set_viewport_proc setViewPort;
	mgc_painter_atlas_upload_proc atlasUpload;

} mg_canvas_painter;

#define MG_ATLAS_SIZE 8192

#ifdef __cplusplus
} // extern "C"
#endif

#endif //__GRAPHICS_INTERNAL_H_
