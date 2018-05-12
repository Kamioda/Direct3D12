#include "Direct3D12Asset.hpp"

namespace DirectX12 {
	namespace Asset {
		RootSignature::RootSignature(const PipelineObject::Device Dx12Device) {
			CD3DX12_ROOT_SIGNATURE_DESC Desc{};
			Desc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
			ComPtr<ID3DBlob> Signature, Error;
			ExceptionImpl::ThrowExceptionIfFailed(
				D3D12SerializeRootSignature(&Desc, D3D_ROOT_SIGNATURE_VERSION_1, &Signature, &Error),
				"Failed to serialize root signature"
			);
			ExceptionImpl::ThrowExceptionIfFailed(
				Dx12Device->CreateRootSignature(0, Signature->GetBufferPointer(), Signature->GetBufferSize(), IID_PPV_ARGS(&this->Obj)),
				"Failed to create root signature"
			);
		}
	}
}
