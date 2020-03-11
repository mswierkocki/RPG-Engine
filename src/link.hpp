// link standard header
#pragma once
#ifndef _LINK_
#define _LINK_

#include <string>

namespace std
{
template <class L>
	class link
	{
	public:
		L* _Ptr;
		std::string Name;
		int Id;
		int _Ref;
	public:
		link(L* ptr = nullptr):_Ptr(ptr),Name(),Id(-1),_Ref(-1) {}
		link(L* ptr, const std::string& name, int id = 0, int ref = 0):_Ptr(ptr),Name(name),Id(id),_Ref(ref) {}
	public:
		L* operator->() const { return _Ptr; }
		operator L*() const { return _Ptr; }
	};
}

#endif /* _LINK_ */