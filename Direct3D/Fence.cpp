#include "Direct3D.hpp"
#include "KgWinException.hpp"

Fence::Fence(const Device Dev) {
	const HRESULT hr = Dev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&this->Dx12Fence));
	if (FAILED(hr)) throw KgWinException(hr);
	this->FenceValue = 1;
}
