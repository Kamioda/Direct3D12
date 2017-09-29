#include "Direct3D.hpp"
#include "KgWinException.hpp"

RenderTargetDescriptorHeap::RenderTargetDescriptorHeap(const UINT FrameCount, const Device Dev) {
	D3D12_DESCRIPTOR_HEAP_DESC Desc;
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.NumDescriptors = FrameCount;
	Desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	Desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	const HRESULT hr = Dev->CreateDescriptorHeap(&Desc, IID_PPV_ARGS(this->RenderTargetViewHeap.GetAddressOf()));
	if (FAILED(hr)) throw KgWinException("Failed Create Descriptor Heap");
	this->DescriptorSize = Dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

RenderTargetView::RenderTargetView(const UINT FrameCount, const D3D12_RENDER_TARGET_VIEW_DESC Desc, const RenderTargetDescriptorHeap RTDesc, const SwapChain Sc, const Device Dev) {
	this->RenderTarget = new Ptr<ID3D12Resource>[FrameCount];
	D3D12_CPU_DESCRIPTOR_HANDLE Handle = RTDesc->GetCPUDescriptorHandleForHeapStart();
	for (unsigned int i = 0; i < FrameCount; i++) {
		const HRESULT hr = Sc->GetBuffer(i, IID_PPV_ARGS(this->RenderTarget[i].GetAddressOf()));
		if (FAILED(hr)) throw KgWinException("Failed Get Buffer");
		Dev->CreateRenderTargetView(this->RenderTarget[i].Get(), &Desc, Handle);
		Handle.ptr += RTDesc.size();
	}
}
