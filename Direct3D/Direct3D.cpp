#include "Direct3D.hpp"

Direct3D::Direct3D(const MainWindow Window, const int WindowWidth, const int WindowHeight, const unsigned int FrameCount) {
	this->Fac = Factory();
	this->Dev = Device(this->Fac);
	this->CmdAlloc = CommandAllocator(Dev);
	this->ComQueue = CommandQueue(Dev);
	this->SwpChain = SwapChain(Window.hWnd, Fac, ComQueue, WindowWidth, WindowHeight, 60);
	this->RTVHeap = RenderTargetDescriptorHeap(FrameCount, Dev);
	this->CmdList = CommandList(Dev, CmdAlloc);
	this->RTV = RenderTargetView(
		FrameCount,
		[]() {
		D3D12_RENDER_TARGET_VIEW_DESC Desc;
		Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		Desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		Desc.Texture2D.MipSlice = 0;
		Desc.Texture2D.PlaneSlice = 0;
		return Desc;
	}(),
		RTVHeap, SwpChain, Dev
		);
	this->Fnc = Fence(Dev);
}

void Direct3D::Clear() {

}
