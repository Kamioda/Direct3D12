#ifndef __COMPTR_HPP__
#define __COMPTR_HPP__
#include <wrl/client.h>

template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
#endif
