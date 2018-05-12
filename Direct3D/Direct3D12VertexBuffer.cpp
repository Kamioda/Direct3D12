#include "Direct3D12Asset.hpp"

namespace DirectX12 {
	namespace Asset {
		void VertexBuffer::CreateBaseResource(const PipelineObject::Device Dx12Device, const unsigned int VertexBufferSize) {
			ExceptionImpl::ThrowExceptionIfFailed(
				Dx12Device->CreateCommittedResource(
					&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
					D3D12_HEAP_FLAG_NONE,
					&CD3DX12_RESOURCE_DESC::Buffer(VertexBufferSize),
					D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&this->Obj)
				),
				"Failed to create vertex buffer"
			);			
		}

		void VertexBuffer::MapResource(unsigned char* pVertexDataBegin) {
			CD3DX12_RANGE ReadRange(0, 0);
			ExceptionImpl::ThrowExceptionIfFailed(
				this->Obj->Map(0, &ReadRange, reinterpret_cast<void**>(pVertexDataBegin)),
				"Failed to map vertex data"
			);
		}

		void VertexBuffer::UnmapResource() {
			this->Obj->Unmap(0, nullptr);
		}
		
		void VertexBuffer::InitializeVertexBufferView(const unsigned int VertexTypeSize, const unsigned int VertexBufferSize) {
			this->VertexBufferView.BufferLocation = this->Obj->GetGPUVirtualAddress();
			this->VertexBufferView.StrideInBytes = VertexTypeSize;
			this->VertexBufferView.SizeInBytes = VertexBufferSize;
		}

	}
}
