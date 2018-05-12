#include "Direct3D12Asset.hpp"
#include <d3dcompiler.h>
#include "Win32LetterConvert.hpp"

namespace DirectX12 {
	namespace Asset {
		PipelineState::PipelineState(const std::string ShaderPath, const PipelineObject::Device Dx12Device, const RootSignature Dx12RootSignature) 
			: PipelineState(StringToWString(ShaderPath), Dx12Device, Dx12RootSignature) {}

		PipelineState::PipelineState(const std::wstring ShaderPath, const PipelineObject::Device Dx12Device, const RootSignature Dx12RootSignature) {
			ComPtr<ID3DBlob> VertexShader, PixelShader;
#ifdef _DEBUG
			unsigned int compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
			unsigned int compileFlags = 0;
#endif
			ExceptionImpl::ThrowExceptionIfFailed(
				D3DCompileFromFile(ShaderPath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &VertexShader, nullptr),
				"Failed to compile vertex shader"
			);
			ExceptionImpl::ThrowExceptionIfFailed(
				D3DCompileFromFile(ShaderPath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &PixelShader, nullptr),
				"Failed to compile pixel shader"
			);
			D3D12_INPUT_ELEMENT_DESC InputElementDescs[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
			D3D12_GRAPHICS_PIPELINE_STATE_DESC Desc = {};
			Desc.InputLayout = { InputElementDescs, _countof(InputElementDescs) };
			Desc.pRootSignature = Dx12RootSignature.GetPtr();
			Desc.VS = CD3DX12_SHADER_BYTECODE(VertexShader.Get());
			Desc.PS = CD3DX12_SHADER_BYTECODE(PixelShader.Get());
			Desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
			Desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			Desc.DepthStencilState.DepthEnable = FALSE;
			Desc.DepthStencilState.StencilEnable = FALSE;
			Desc.SampleMask = UINT_MAX;
			Desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			Desc.NumRenderTargets = 1;
			Desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			Desc.SampleDesc.Count = 1;
			ExceptionImpl::ThrowExceptionIfFailed(
				Dx12Device->CreateGraphicsPipelineState(&Desc, IID_PPV_ARGS(&this->Obj)),
				"Failed to create graphics pipeline state"
			);
		}
	}
}
