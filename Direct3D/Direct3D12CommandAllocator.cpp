#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace PipelineObject {
		CommandAllocator::CommandAllocator(const Device Dx12Device) {
			ExceptionImpl::ThrowExceptionIfFailed(
				Dx12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&this->Obj)),
				"Failed to create command allocator"
			);
		}
	}
}
