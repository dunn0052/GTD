#pragma once

namespace GTD
{
	template <class DelegateType>
	class Dispatcher
	{

	public:

		Dispatcher() {}
		~Dispatcher() {}

		template <typename ... EventArgs>
		void Invoke(EventArgs&& ... args)
		{
			for (DelegateType&& del)
			{
				del(std::forward<Args>(args)...)
			}
		}
		void Clear()
		{
			m_Delegates.empty
		}

		void operator +=(DelegateType&& inDel)
		{
			m_Delegates.push_back(std::forward<DelegateType>(inDel));
		}

	private:
		const std::vector<DelegateType> m_Delegates;
	};


	/* EXAMPLE */

	/*
	struct EventArgsTest
	{
		int m_Param;
		int m_Other;
	};

	void ExampleDelegateFunctor(void* obj, const EventArgsTest&& e)
	{
		std::cout << e.m_Other << std::endl;
	}

	typedef void (*DelegateFunctor)(void*, const EventArgsTest&&);



	void TestScope()
	{
		Ref<Dispatcher<DelegateFunctor>> d = CreateRef<Dispatcher<DelegateFunctor>>();
		*d += &ExampleDelegateFunctor;
		d->Invoke(EventArgsTest());
	}
	*/
	
}