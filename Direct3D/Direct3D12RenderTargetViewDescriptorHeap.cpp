#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace PipelineObject {
		RenderTargetViewDescriptorHeap::RenderTargetViewDescriptorHeap(const Device Dx12Device) {
			D3D12_DESCRIPTOR_HEAP_DESC Desc{};
			Desc.NumDescriptors = FrameCount;
			Desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			Desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			DescriptorHeap(Dx12Device, &Desc, "render target view descriptor heap");
			this->RenderTargetViewDescriptorSize = Dx12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
	}
}
