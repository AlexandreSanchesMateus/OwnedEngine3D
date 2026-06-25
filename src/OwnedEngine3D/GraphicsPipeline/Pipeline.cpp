#include "OwnedEngine3D/GraphicsPipeline/Pipeline.h"
#include "OwnedEngine3D/Engine/GPUDevice.h"
#include "OwnedEngine3D/Engine/Window.h"
#include "OwnedEngine3D/Manager/ResourcesManager.h"
#include "OwnedEngine3D/GraphicsPipeline/Shader.h"
#include "OwnedEngine3D/GraphicsPipeline/Vertex.h"
#include <SDL3/SDL_gpu.h>

Pipeline::Pipeline(GPUDevice* device, Window* window, const PipelineDescriptor& descriptor) : m_device(device)
{
	SDL_GPUGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.vertex_shader = descriptor.vertexShader->GetHandle();
	pipelineInfo.fragment_shader = descriptor.fragmentShader->GetHandle();
	pipelineInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;

	SDL_GPUVertexBufferDescription vertexBufferDesctiptions[1]{};
	vertexBufferDesctiptions[0].slot = 0;
	vertexBufferDesctiptions[0].input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
	vertexBufferDesctiptions[0].instance_step_rate = 0;
	vertexBufferDesctiptions[0].pitch = sizeof(DebugVertex);

	pipelineInfo.vertex_input_state.num_vertex_buffers = 1;
	pipelineInfo.vertex_input_state.vertex_buffer_descriptions = vertexBufferDesctiptions;

	SDL_GPUVertexAttribute vertexAttributes[2]{};
	// position
	vertexAttributes[0].buffer_slot = 0;
	vertexAttributes[0].location = 0;
	vertexAttributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
	vertexAttributes[0].offset = offsetof(DebugVertex, position);
	// color
	vertexAttributes[1].buffer_slot = 0;
	vertexAttributes[1].location = 1;
	vertexAttributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
	vertexAttributes[1].offset = offsetof(DebugVertex, color);

	pipelineInfo.vertex_input_state.num_vertex_attributes = 2;
	pipelineInfo.vertex_input_state.vertex_attributes = vertexAttributes;

	SDL_GPUColorTargetDescription colorTargetDescriptions[1];
	colorTargetDescriptions[0] = {};
	colorTargetDescriptions[0].blend_state.enable_blend = true;
	colorTargetDescriptions[0].blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;
	colorTargetDescriptions[0].blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;
	colorTargetDescriptions[0].blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
	colorTargetDescriptions[0].blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
	colorTargetDescriptions[0].blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
	colorTargetDescriptions[0].blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
	colorTargetDescriptions[0].format = SDL_GetGPUSwapchainTextureFormat(device->GetHandle(), window->GetHandle());

	pipelineInfo.target_info.num_color_targets = 1;
	pipelineInfo.target_info.color_target_descriptions = colorTargetDescriptions;

	m_graphicsPipeline = SDL_CreateGPUGraphicsPipeline(m_device->GetHandle(), &pipelineInfo);
}

Pipeline::~Pipeline()
{
	SDL_ReleaseGPUGraphicsPipeline(m_device->GetHandle(), m_graphicsPipeline);
}

SDL_GPUGraphicsPipeline* Pipeline::GetHandle() const
{
	return m_graphicsPipeline;
}