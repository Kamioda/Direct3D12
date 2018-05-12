#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace PipelineObject {
		CommandQueue::CommandQueue(const Device Dx12Device) {
			D3D12_COMMAND_QUEUE_DESC Desc{};
			Desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			Desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			ExceptionImpl::ThrowExceptionIfFailed(
				Dx12Device->CreateCommandQueue(&Desc, IID_PPV_ARGS(&this->Obj)),
				"Failed to create command queue"
			);
		}
	}
}
