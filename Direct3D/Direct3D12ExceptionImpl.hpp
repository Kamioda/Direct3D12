#ifndef __DIRECT3D12EXCEPTIONIMPL_HPP__
#define __DIRECT3D12EXCEPTIONIMPL_HPP__
#include <Windows.h>
#include <string>

namespace DirectX12 {
	namespace ExceptionImpl {
		void ThrowExceptionIfFailed(const HRESULT hr, const std::string ExceptionMessage) {
			if (FAILED(hr)) throw std::runtime_error(ExceptionMessage + "\nErrorCode : " + std::to_string(hr));
		}
	}
}
#endif
