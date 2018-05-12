#include "Direct3D12Asset.hpp"

namespace DirectX12 {
	namespace Asset {
		CommandList::CommandList(const PipelineObject::Device Dx12Device, const PipelineObject::CommandAllocator Dx12CommandAllocator, const PipelineState Dx12PipelineState) {
			ExceptionImpl::ThrowExceptionIfFailed(
				Dx12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, Dx12CommandAllocator.GetPtr(), Dx12PipelineState.GetPtr(), IID_PPV_ARGS(&this->Obj)),
				"Failed to create command list"
			);
		}
	}
}
