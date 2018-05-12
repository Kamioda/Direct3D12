#include "Direct3D12Asset.hpp"
#include "Win32Exception.hpp"

namespace DirectX12 {
	namespace Asset {
		Fence::Fence(const PipelineObject::Device Dx12Device) {
			ExceptionImpl::ThrowExceptionIfFailed(
				Dx12Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&this->Obj)),
				"Failed to create fence"
			);
			this->FenceValue = 1;
			this->FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (this->FenceEvent) {
				const DWORD ErrorCode = GetLastError();
				throw Win32ExceptionA("Failed to create event", ErrorCode);
			}
		}
		Fence::~Fence() {
			CloseHandle(this->FenceEvent);
		}
	}
}
