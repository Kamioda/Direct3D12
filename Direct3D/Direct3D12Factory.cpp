#include "Direct3D12PipelineObject.hpp"

namespace DirectX12{
	namespace PipelineObject {
		Factory::Factory() {
			unsigned int DxgiFactoryFlags = 0;
#ifdef _DEBUG
			ComPtr<ID3D12Debug> DebugInterface;
			ExceptionImpl::ThrowExceptionIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugInterface)), "Failed to get debug interface");
			DebugInterface->EnableDebugLayer();
			DxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
			ExceptionImpl::ThrowExceptionIfFailed(CreateDXGIFactory2(DxgiFactoryFlags, IID_PPV_ARGS(&this->Obj)), "Failed to create factory.");
		}
		boost::optional<ComPtr<IDXGIAdapter1>> Factory::GetHardwareAdapter(const unsigned int AdapterNum, const D3D_FEATURE_LEVEL FeatureLevel) const {
			ComPtr<IDXGIAdapter1> HardwareAdapter;
			const HRESULT hr = this->Obj->EnumAdapters1(AdapterNum, &HardwareAdapter);
			if (DXGI_ERROR_NOT_FOUND == hr) return boost::none;
			return HardwareAdapter;
		}
		bool Factory::IsSoftwareAdapter(const ComPtr<IDXGIAdapter1> HardwareAdapter) const {
			DXGI_ADAPTER_DESC1 Desc{};
			ExceptionImpl::ThrowExceptionIfFailed(
				HardwareAdapter->GetDesc1(&Desc),
				"Failed to get hardware description"
				);
			return Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE;
		}
		bool Factory::SupportedDirect3D12HardwareGraphicsMode(const ComPtr<IDXGIAdapter1> HardwareAdapter, const D3D_FEATURE_LEVEL FeatureLevel) const noexcept {
			return SUCCEEDED(D3D12CreateDevice(HardwareAdapter.Get(), FeatureLevel, __uuidof(ID3D12Device), nullptr));
		}
		ComPtr<IDXGIAdapter> Factory::GetWarpAdapter() const {
			ComPtr<IDXGIAdapter> WarpAdapter;
			ExceptionImpl::ThrowExceptionIfFailed(this->Obj->EnumWarpAdapter(IID_PPV_ARGS(&WarpAdapter)), "Failed to enum warp adapter");
		}
		ComPtr<IDXGIAdapter1> Factory::GetFirstHardwareAdapterSupportedReservedFeatureLevel(const D3D_FEATURE_LEVEL FeatureLevel) const {
			boost::optional<ComPtr<IDXGIAdapter1>> HardwareAdapter;
			for (unsigned int i = 0; (HardwareAdapter = this->GetHardwareAdapter(i, FeatureLevel)) != boost::none; i++) {
				if (this->IsSoftwareAdapter(HardwareAdapter.get())) continue;
				if (this->SupportedDirect3D12HardwareGraphicsMode(HardwareAdapter.get(), FeatureLevel)) return HardwareAdapter.get();
			}
			throw std::runtime_error("This computer is not found graphics device supported Direct3D 12 use hardware adapter");
		}
	}
}