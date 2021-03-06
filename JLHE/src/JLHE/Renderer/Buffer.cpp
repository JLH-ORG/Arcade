#include "jlhepch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace JLHE {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				JLHE_CORE_ASSERT(false, "Renderer API None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(size);
		}

		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				JLHE_CORE_ASSERT(false, "Renderer API None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				JLHE_CORE_ASSERT(false, "Renderer API None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		JLHE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}