#include "Direct3D.hpp"
#include "KgWinException.hpp"

SwapChain::SwapChain(HWND hWnd, const Factory fac, const CommandQueue com, const int WindowWidth, const int WindowHeight, const int RefreshRate) {
	Ptr<IDXGISwapChain> chain;
	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = WindowWidth;
	desc.BufferDesc.Height = WindowHeight;
	desc.OutputWindow = hWnd;
	desc.Windowed = TRUE;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = FrameCount;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.BufferDesc.RefreshRate.Numerator = RefreshRate;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	HRESULT hr = fac->CreateSwapChain(com.Get(), &desc, chain.GetAddressOf());
	if (FAILED(hr)) throw KgWinException("Failed Create Swap Chain");
	hr = chain->QueryInterface(this->DxgiSwapChain.GetAddressOf());
	if (FAILED(hr)) throw KgWinException("Failed Query Interface");
	this->FrameBufferIndex = this->DxgiSwapChain->GetCurrentBackBufferIndex();
}
