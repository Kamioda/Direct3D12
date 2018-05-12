#ifndef __DIRECT3D12ASSET_HPP__
#define __DIRECT3D12ASSET_HPP__
#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace Asset {
		class RootSignature : public CommonObject::ObjectInstance<ID3D12RootSignature> {
		public:
			RootSignature() = default;
			RootSignature(const PipelineObject::Device Dx12Device);
		};
		class PipelineState : public CommonObject::ObjectInstance<ID3D12PipelineState> {
		public:
			PipelineState() = default;
			PipelineState(const std::string ShaderPath, const PipelineObject::Device Dx12Device, const RootSignature Dx12RootSignature);
			PipelineState(const std::wstring ShaderPath, const PipelineObject::Device Dx12Device, const RootSignature Dx12RootSignature);
		};
		class CommandList : public CommonObject::ObjectInstance<ID3D12GraphicsCommandList> {
		public:
			CommandList() = default;
			CommandList(const PipelineObject::Device Dx12Device, const PipelineObject::CommandAllocator Dx12CommandAllocator, const PipelineState Dx12PipelineState);
		};
		class VertexBuffer : public CommonObject::ObjectInstance<ID3D12Resource> {
		private:
			D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
			void CreateBaseResource(const PipelineObject::Device Dx12Device, const unsigned int VertexBufferSize);
			void MapResource(unsigned char* pVertexDataBegin);
			void UnmapResource();
			template<typename Vertex> memorycopy(unsigned char* pVertexDataBegin, const Vertex Vertices[]) {
				memcpy(pVertexDataBegin, Vertices, sizeof(Vertices));
			}
			void InitializeVertexBufferView(const unsigned int VertexTypeSize, const unsigned int VertexBufferSize);
		public:
			VertexBuffer() = default;
			template<typename Vertex> VertexBuffer(const PipelineObject::Device Dx12Device, const Vertex Vertices[]) {
				const unsigned int VertexBufferSize = sizeof(Vertices);
				this->CreateBaseResource(Dx12Device, VertexBufferSize);
				unsigned char* pVertexDataBegin;
				this->MapResource(pVertexDataBegin);
				this->memorycopy<Vertex>(pVertexDataBegin, Vertices);
				this->UnmapResource();
				this->InitializeVertexBufferView(sizeof(Vertex), VertexBufferSize);
			}
		};
		class Fence : public CommonObject::ObjectInstance<ID3D12Fence> {
		public:
			Fence() = default;
			Fence(const PipelineObject::Device Dx12Device);
			~Fence();
			unsigned __int64 FenceValue;
			HANDLE FenceEvent;
		};
	}
}
#endif
