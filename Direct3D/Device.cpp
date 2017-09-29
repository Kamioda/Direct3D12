#include "Direct3D.hpp"
#include "KgWinException.hpp"
#include <stdexcept>

Device::Device(const Factory fac, const bool UseWarpDevice) : UseFeatureLevel(D3DFeatureLevel::Null){
	const D3DFeatureLevel Arr[4] = {
		D3DFeatureLevel::Level12_1,
		D3DFeatureLevel::Level12_0,
		D3DFeatureLevel::Level11_1,
		D3DFeatureLevel::Level11_0
	};
	if (UseWarpDevice) {
		Ptr<IDXGIAdapter> WarpAdapter;
		if (SUCCEEDED(fac->EnumWarpAdapter(IID_PPV_ARGS(&WarpAdapter)))) {
			for (int i = 0; i < 4; i++) {
				if (SUCCEEDED(this->CreateDevice(WarpAdapter, Arr[i]))) continue;
				this->UseFeatureLevel = Arr[i];
				break;
			}
		}
	} // UseWarpDevice
	else {
		Ptr<IDXGIAdapter1> HardwareAdapter;
		for (int i = 0; i < 4; i++) {
			for (unsigned int AdapterIndex = 0; DXGI_ERROR_NOT_FOUND != fac->EnumAdapters1(AdapterIndex, &HardwareAdapter); AdapterIndex++) {
				DXGI_ADAPTER_DESC1 desc;
				if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
				if (SUCCEEDED(D3D12CreateDevice(HardwareAdapter.Get(), static_cast<D3D_FEATURE_LEVEL>(Arr[i]), _uuidof(ID3D12Device), nullptr))) break;
			} // グラフィックアクセラレータ検索のループ
			HRESULT hr = this->CreateDevice(HardwareAdapter, Arr[i]);
			if (SUCCEEDED(hr)) {
				this->UseFeatureLevel = Arr[i];
				break;
			}
		} // FeatureLevelのループ
	} // !UseWarpDevice
	if (D3DFeatureLevel::Null == this->UseFeatureLevel) throw KgWinException("Direct3D 12に対応したグラフィックアクセラレータが見つかりませんでした。");
}

Device::Device(const Factory fac, const D3DFeatureLevel FeatureLevel, const bool UseWarpDevice) : UseFeatureLevel(FeatureLevel){
	if (UseWarpDevice) {
		Ptr<IDXGIAdapter> WarpAdapter;
		if (SUCCEEDED(fac->EnumWarpAdapter(IID_PPV_ARGS(&WarpAdapter)))) {
			HRESULT hr = this->CreateDevice(WarpAdapter, FeatureLevel);
			if (FAILED(hr)) throw KgWinException("Failed Create Device");
		}
	}
	else {
		Ptr<IDXGIAdapter1> HardwareAdapter;
		for (unsigned int AdapterIndex = 0; DXGI_ERROR_NOT_FOUND != fac->EnumAdapters1(AdapterIndex, &HardwareAdapter); AdapterIndex++) {
			DXGI_ADAPTER_DESC1 desc;
			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
			if (SUCCEEDED(D3D12CreateDevice(HardwareAdapter.Get(), static_cast<D3D_FEATURE_LEVEL>(FeatureLevel), _uuidof(ID3D12Device), nullptr))) break;
		}
		HRESULT hr = this->CreateDevice(HardwareAdapter, FeatureLevel);
		if (FAILED(hr)) throw KgWinException("Failed Create Device");
	}
}

HRESULT Device::CreateDevice(const Ptr<IDXGIAdapter> Adapter, const D3DFeatureLevel FeatureLevel) {
	return D3D12CreateDevice(Adapter.Get(), static_cast<D3D_FEATURE_LEVEL>(FeatureLevel), IID_PPV_ARGS(&this->Dx12Device));
}

HRESULT Device::CreateDevice(const Ptr<IDXGIAdapter1> Adapter, const D3DFeatureLevel FeatureLevel) {
	return D3D12CreateDevice(Adapter.Get(), static_cast<D3D_FEATURE_LEVEL>(FeatureLevel), IID_PPV_ARGS(&this->Dx12Device));
}
