#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace PipelineObject {
		SwapChain::SwapChain(const MainWindow Window, const Factory DxgiFactory, const CommandQueue Dx12CommandQueue) {
			DXGI_SWAP_CHAIN_DESC1 Desc{};
			Desc.BufferCount = FrameCount;
			Desc.Width = Window.WindowWidth;
			Desc.Height = Window.WindowHeight;
			Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			Desc.SampleDesc.Count = 1;
			ComPtr<IDXGISwapChain1> SwapChain;
			ExceptionImpl::ThrowExceptionIfFailed(
				DxgiFactory->CreateSwapChainForHwnd(Dx12CommandQueue.Get().Get(), Window.hWnd, &Desc, nullptr, nullptr, &SwapChain),
				"Failed to create swap chain"
			);
			ExceptionImpl::ThrowExceptionIfFailed(
				DxgiFactory->MakeWindowAssociation(Window.hWnd, DXGI_MWA_NO_ALT_ENTER),
				"Failed to make window association"
			);
			ExceptionImpl::ThrowExceptionIfFailed(
				SwapChain.As(&this->Obj),
				"Failed to convert SwapChain1 to SwapChain3"
			);
			this->UpdateFrameIndex();
		}

		void SwapChain::UpdateFrameIndex() {
			this->FrameIndex = this->Obj->GetCurrentBackBufferIndex();
		}

		unsigned int SwapChain::GetFrameIndex() const  {
			return this->FrameIndex;
		}
	}
}
