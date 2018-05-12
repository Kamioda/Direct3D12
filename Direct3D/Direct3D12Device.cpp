#include "Direct3D12PipelineObject.hpp"

namespace DirectX12 {
	namespace PipelineObject {
		Device::Device(const HardwareAdapterInfo HardwareAdapter, const D3D_FEATURE_LEVEL FeatureLevel) {
			ExceptionImpl::ThrowExceptionIfFailed(
				D3D12CreateDevice(HardwareAdapter.Get(), FeatureLevel, IID_PPV_ARGS(&this->Obj)),
				"Failed to create device use reserved hardware adapter."
			);
		}

		Device::Device(const WarpAdapterInfo WarpAdapter) {
			ExceptionImpl::ThrowExceptionIfFailed(
				D3D12CreateDevice(WarpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&this->Obj)),
				"Failed to create device use reserved warp adapter."
			);
		}
	}
}