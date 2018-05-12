#ifndef __DIRECT3D12PIPELINEOBJECT_HPP__
#define __DIRECT3D12PIPELINEOBJECT_HPP__
#include "Direct3D12Object.hpp"
#include "Window.hpp"
#include "d3dx12.h"
#include <dxgi1_4.h>
#include "Direct3D12ExceptionImpl.hpp"
#include <boost/optional.hpp>
#include <utility>
constexpr unsigned int FrameCount = 2;

namespace DirectX12 {
	typedef ComPtr<IDXGIAdapter> WarpAdapterInfo;
	typedef ComPtr<IDXGIAdapter1> HardwareAdapterInfo;
	namespace PipelineObject {
		class Factory : public CommonObject::ObjectInstance<IDXGIFactory4> {
		private:
			bool IsSoftwareAdapter(const ComPtr<IDXGIAdapter1> HardwareAdapter) const;
			bool SupportedDirect3D12HardwareGraphicsMode(const ComPtr<IDXGIAdapter1> HardwareAdapter, const D3D_FEATURE_LEVEL FeatureLevel) const noexcept;
		public:
			Factory();
			ComPtr<IDXGIAdapter> GetWarpAdapter() const;
			boost::optional<ComPtr<IDXGIAdapter1>> GetHardwareAdapter(const unsigned int AdapterNum, const D3D_FEATURE_LEVEL FeatureLevel) const;
			ComPtr<IDXGIAdapter1> GetFirstHardwareAdapterSupportedReservedFeatureLevel(const D3D_FEATURE_LEVEL FeatureLevel) const;
		};
		class Device : public CommonObject::ObjectInstance<ID3D12Device> {
		public:
			Device() = default;
			Device(const HardwareAdapterInfo HardwareAdapter, const D3D_FEATURE_LEVEL FeatureLevel);
			Device(const WarpAdapterInfo WarpAdapter);
		};
		class CommandQueue : public CommonObject::ObjectInstance<ID3D12CommandQueue> {
		public:
			CommandQueue() = default;
			CommandQueue(const Device Dx12Device);
		};
		class SwapChain : public CommonObject::ObjectInstance<IDXGISwapChain3> {
		private:
			unsigned int FrameIndex;
		public:
			SwapChain() = default;
			SwapChain(const MainWindow Window, const Factory DxgiFactory, const CommandQueue Dx12CommandQueue);
			void UpdateFrameIndex();
			unsigned int GetFrameIndex() const;
		};
		namespace {
			// Deviceクラスより下にないとビルドエラーになるっぽいのでここに定義

			class DescriptorHeap : public CommonObject::ObjectInstance<ID3D12DescriptorHeap> {
			public:
				DescriptorHeap() = default;
				DescriptorHeap(const Device Dx12Device, const D3D12_DESCRIPTOR_HEAP_DESC* Desc, const std::string DescriptorHeapName) {
					ExceptionImpl::ThrowExceptionIfFailed(
						Dx12Device->CreateDescriptorHeap(Desc, IID_PPV_ARGS(&this->Obj)),
						"Failed to create" + DescriptorHeapName
					);
				}
			};
		}
		class RenderTargetViewDescriptorHeap : public DescriptorHeap {
		public:
			RenderTargetViewDescriptorHeap() : DescriptorHeap() {}
			RenderTargetViewDescriptorHeap(const Device Dx12Device);
			unsigned int RenderTargetViewDescriptorSize;
		};
		class ShaderResourceViewDescriptorHeap : public DescriptorHeap {
		public:
			ShaderResourceViewDescriptorHeap() : DescriptorHeap() {}
			ShaderResourceViewDescriptorHeap(const Device Dx12Device);

		};
		class RenderTargetView {
		private:
			std::array<CommonObject::ObjectInstance<ID3D12Resource>, FrameCount> Dx12RenderTargetView;
		public:
			RenderTargetView() = default;
			RenderTargetView(const Device Dx12Device, const SwapChain DxgiSwapChain, const RenderTargetViewDescriptorHeap RTVDescHeap);
		};
		class CommandAllocator : public CommonObject::ObjectInstance<ID3D12CommandAllocator> {
		public:
			CommandAllocator() = default;
			CommandAllocator(const Device Dx12Device);
		};
	}
}
#endif
