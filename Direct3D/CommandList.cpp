#include "Direct3D.hpp"
#include "KgWinException.hpp"

CommandList::CommandList(const Device Dev, const CommandAllocator Allocator) {
	const HRESULT hr = Dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, Allocator.Get(), nullptr, IID_PPV_ARGS(this->Dx12CommandList.GetAddressOf()));
	if (FAILED(hr)) throw KgWinException("Failed Create Command List");
}
