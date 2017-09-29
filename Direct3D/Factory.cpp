#include "Direct3D.hpp"
#include "KgWinException.hpp"

Factory::Factory() {
	unsigned int Flag{};
	HRESULT hr;
#ifdef _DEBUG
	{
		Ptr<ID3D12Debug> Debug;
		hr = D3D12GetDebugInterface(IID_PPV_ARGS(Debug.GetAddressOf()));
		if (FAILED(hr)) throw KgWinException("Failed Get Debug Interface");
		Debug->EnableDebugLayer();
	}
	Flag |= DXGI_CREATE_FACTORY_DEBUG;
#endif
	hr = CreateDXGIFactory2(Flag, IID_PPV_ARGS(&this->DxgiFactory));
	if (FAILED(hr)) throw KgWinException("Failed Create Factory");
}
