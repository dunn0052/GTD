#pragma once

#include <any>
#include <utility>

namespace GTD
{
	/* Tool to make generic interfaces play nice */

	/* Usage:
		
		IBaseClass -- IFunction1(), IFunction2
		DerivedClass1 : IBaseClass -- Must implement at least IBaseClass
		DerivedClass2 : IBaseClass -- Must implement at least IBaseClass

		using BaseClass = Implementation<IBaseClass>

		std::vector<BaseClass> baseClassVector;

		baseClassVector.push_back(DerivedClass1);
		baseClassVector.push_back(DerivedClass2);

		for(BaseClass& ent : baseClassVector)
		{
			ent.IFunction1();
			ent.IFunction2();
		}
	*/

	template<typename Interface>
	struct Implementation
	{
	public:
		template<typename ConcreteType>
		Implementation(ConcreteType&& derived) : 
			m_Storage{std::forward<ConcreteType>(derived)},
			m_Getter{ [](std::any& storage) -> Interface& { return std::any_cast<ConcreteType&>(storage} } {}

		~Implementation() { delete m_Getter; }

		Interface* operator->() { return &m_Getter(m_Storage); }

	private:
		std::any m_Storage;
		Interface& (*m_Getter)(std::any&);
	};


}