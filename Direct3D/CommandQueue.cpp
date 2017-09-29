#include "Direct3D.hpp"
#include "KgWinException.hpp"

CommandQueue::CommandQueue(const Device dev) {
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = 0;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;
	HRESULT hr = dev->CreateCommandQueue(&desc, IID_PPV_ARGS(this->Dx12CommandQueue.GetAddressOf()));
	if (FAILED("Failed Create CommandQueue")) throw KgWinException(hr);
	HANDLE FenceEvent = CreateEventEx(nullptr, NULL, NULL, EVENT_ALL_ACCESS);
	if (FenceEvent == NULL) throw KgWinException("FenceEvent‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
	hr = dev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(this->Dx12CommandQueue.GetAddressOf()));
	if (FAILED(hr)) throw KgWinException("Failed Create Fence");
}
