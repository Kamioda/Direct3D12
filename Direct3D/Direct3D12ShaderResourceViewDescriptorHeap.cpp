#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace PipelineObject {
		ShaderResourceViewDescriptorHeap::ShaderResourceViewDescriptorHeap(const Device Dx12Device) {
			D3D12_DESCRIPTOR_HEAP_DESC Desc{};
			Desc.NumDescriptors = 1;
			Desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			Desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			DescriptorHeap(Dx12Device, &Desc, "shader resource view descriptor heap");
		}
	}
}
