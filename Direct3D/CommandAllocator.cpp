#include "Direct3D.hpp"
#include "KgWinException.hpp"

CommandAllocator::CommandAllocator(const Device Dev) {
	const HRESULT hr = Dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&this->Dx12CommandAllocator));
	if (FAILED(hr)) throw KgWinException("Failed Create Command Allocator");
}
