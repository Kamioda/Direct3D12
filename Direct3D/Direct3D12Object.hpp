#ifndef __DIRECT3D12OBJECT_HPP__
#define __DIRECT3D12OBJECT_HPP__
#include "ComPtr.hpp"

namespace DirectX12 {
	namespace CommonObject {
		template<typename Object> class ObjectInstance {
		private:
			using ComPtrRef = Microsoft::WRL::Details::ComPtrRef<ComPtr<Object>>;
		protected:
			ComPtr<Object> Obj;
		public:
			Object* operator -> () const noexcept { return this->Obj.Get(); }
			ComPtr<Object> Get() const noexcept { return this->Obj; }
			Object* GetPtr() const noexcept { return this->Obj.Get(); }
			ComPtrRef Ref() const noexcept { return &this->Obj; }
		};
	}
}
#endif
