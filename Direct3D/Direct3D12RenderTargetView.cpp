#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace PipelineObject {
		RenderTargetView::RenderTargetView(const Device Dx12Device, const SwapChain DxgiSwapChain, const RenderTargetViewDescriptorHeap RTVDescHeap) {
			CD3DX12_CPU_DESCRIPTOR_HANDLE RTVHandle(RTVDescHeap->GetCPUDescriptorHandleForHeapStart());
			for (unsigned int i = 0; i < FrameCount; i++) {
				ExceptionImpl::ThrowExceptionIfFailed(
					DxgiSwapChain->GetBuffer(i, IID_PPV_ARGS(this->Dx12RenderTargetView[i].Ref())),
					"Failed to get RTV Buffer"
				);
				Dx12Device->CreateRenderTargetView(this->Dx12RenderTargetView[i].Get().Get(), nullptr, RTVHandle);
				RTVHandle.Offset(1, RTVDescHeap.RenderTargetViewDescriptorSize);
			}
		}
	}
}
