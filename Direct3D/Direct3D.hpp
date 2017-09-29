#ifndef __DIRECT3D_HPP__
#define __DIRECT3D_HPP__
#include "Window.hpp"
#include <d3d12.h>
#include <d3d12shader.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>
template<typename T> using Ptr = Microsoft::WRL::ComPtr<T>;

enum class D3DFeatureLevel : int {
	Level12_1 = 0xc100,
	Level12_0 = 0xc000,
	Level11_1 = 0xb100,
	Level11_0 = 0xb000,
	Null = 0x000
};

class Factory {
private:
	Ptr<IDXGIFactory4> DxgiFactory;
public:
	Factory();
	Ptr<IDXGIFactory4> operator -> () const { return this->DxgiFactory; }
};

class Device {
private:
	Ptr<ID3D12Device> Dx12Device;
	D3DFeatureLevel UseFeatureLevel;
	HRESULT CreateDevice(const Ptr<IDXGIAdapter> Adapter, const D3DFeatureLevel FeatureLevel);
	HRESULT CreateDevice(const Ptr<IDXGIAdapter1> Adapter, const D3DFeatureLevel FeatureLevel);
public:
	Device() = default;
	Device(const Factory fac, const bool UseWarpDevice = true);
	Device(const Factory fac, const D3DFeatureLevel FeatureLevel, const bool UseWarpDevice = true);
	D3DFeatureLevel GetUseFeatureLevel() const { return this->UseFeatureLevel; }
	Ptr<ID3D12Device> operator -> () const { return this->Dx12Device; }
	ID3D12Device* Get() const { return this->Dx12Device.Get(); }
};

class CommandQueue {
private:
	Ptr<ID3D12CommandQueue> Dx12CommandQueue;
public:
	CommandQueue() = default;
	CommandQueue(const Device dev);
	Ptr<ID3D12CommandQueue> operator -> () const { return this->Dx12CommandQueue; }
	ID3D12CommandQueue* Get() const { return this->Dx12CommandQueue.Get(); }
};

class SwapChain {
private:
	Ptr<IDXGISwapChain3> DxgiSwapChain;
	unsigned int FrameBufferIndex;
public:
	SwapChain() = default;
	SwapChain(HWND hWnd, const Factory fac, const CommandQueue com, const int WindowWidth, const int WindowHeight, const int RefreshRate);
	Ptr<IDXGISwapChain3> operator -> () const { return this->DxgiSwapChain; }
	unsigned int GetFrameBufferIndex() const { return this->FrameBufferIndex; }
};

//class RenderTargetView {
//private:
//	Ptr<ID3D12DescriptorHeap> RenderTargetViewHeap;
//	D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetViewHandle[2];
//	Ptr<ID3D12Resource> RenderTarget[2];
//	unsigned int RTVDescriptorSize;
//public:
//	RenderTargetView(const Device Dev, const SwapChain Chain);
//};

class RenderTargetDescriptorHeap {
private:
	Ptr<ID3D12DescriptorHeap> RenderTargetViewHeap;
	size_t DescriptorSize;
public:
	RenderTargetDescriptorHeap() = default;
	RenderTargetDescriptorHeap(const UINT FrameCount, const Device Dev);
	Ptr<ID3D12DescriptorHeap> operator -> () const { return this->RenderTargetViewHeap; }
	size_t size() const { return this->DescriptorSize; }
};

class RenderTargetView {
private:
	Ptr<ID3D12Resource>* RenderTarget;
public:
	RenderTargetView() = default;
	RenderTargetView(const UINT FrameCount, const D3D12_RENDER_TARGET_VIEW_DESC Desc, RenderTargetDescriptorHeap RTDesc, const SwapChain Sc, const Device Dev);
};

class CommandAllocator {
private:
	Ptr<ID3D12CommandAllocator> Dx12CommandAllocator;
public:
	CommandAllocator() = default;
	CommandAllocator(const Device Dev);
	Ptr<ID3D12CommandAllocator> operator -> () const { return this->Dx12CommandAllocator; }
	ID3D12CommandAllocator* Get() const { return this->Dx12CommandAllocator.Get(); }
};

class CommandList {
private:
	Ptr<ID3D12CommandList> Dx12CommandList;
public:
	CommandList() = default;
	CommandList(const Device Dev, const CommandAllocator Allocator);
	Ptr<ID3D12CommandList> operator ->() const { return this->Dx12CommandList; }
};

class Fence {
private:
	Ptr<ID3D12Fence> Dx12Fence;
	size_t FenceValue;
public:
	Fence() = default;
	Fence(const Device Dev);
	Ptr<ID3D12Fence> operator -> () const { return this->Dx12Fence; }
	size_t GetFenceValue() const { return this->FenceValue; }
};

class Direct3D {
private:
	Factory Fac;
	Device Dev;
	CommandAllocator CmdAlloc;
	CommandQueue ComQueue;
	SwapChain SwpChain;
	RenderTargetDescriptorHeap RTVHeap;
	CommandList CmdList;
	RenderTargetView RTV;
	Fence Fnc;
public:
	Direct3D(const MainWindow Window, const int WindowWidth, const int WindowHeight, const unsigned int FrameCount);
	void Clear();
};
#endif
