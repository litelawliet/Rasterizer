#pragma once

#include <list>
#include <memory>
#include "Rasterizer/Resources/Entity.h"

namespace Rasterizer::Managers
{
	class Scene final
	{
	public:
		Scene() = default;

		const std::list<Resources::Entity>& GetEntities() const noexcept;
		void AddEntity(std::string && p_modelEntity);

		static std::unique_ptr<Scene>& GetInstance();

	private:
		std::list<Resources::Entity> m_entities;
		static std::unique_ptr<Scene> m_instance;
	};
}
