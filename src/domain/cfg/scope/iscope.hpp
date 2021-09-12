#pragma once

#include "domain/core/aggregator.hpp"
#include <map>
#include <optional>
#include <vector>

#include "../../core/types.hpp"

namespace cfg {

using namespace core;

template<class Concrete, class ConcreteBlock>
class IScope : public Entity {
public:
	using Parent = Concrete const*;
	using Blocks = core::Aggregator<ConcreteBlock>;
	using Childs = core::Aggregator<Concrete>;

	IScope() : Entity(){};
	explicit IScope(core::Uuid uuid) : Entity(std::move(uuid)){};
	[[nodiscard]] virtual auto is_root() const -> bool = 0;
	[[nodiscard]] virtual auto has_childs() const -> bool = 0;
	[[nodiscard]] virtual auto get_blocks() const -> Blocks = 0;
	[[nodiscard]] virtual auto get_childs() const -> Childs = 0;
	[[nodiscard]] virtual auto get_parent() const -> Parent = 0;

	class IBuilder {
	public:
		// virtual ~IBuilder() = default;
		virtual auto set_uuid(Uuid uuid) -> result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> = 0;
		virtual auto add_child(Concrete* child) -> result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>> = 0;
		virtual auto set_parent(Concrete* parent) -> result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>> = 0;
		virtual auto add_block(ConcreteBlock* block) -> result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>> = 0;
		virtual auto set_childs(Aggregator<Concrete>* childs) -> result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> = 0;
		virtual auto set_blocks(Aggregator<ConcreteBlock>* blocks) -> result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> = 0;
		[[nodiscard]] virtual auto build() -> Concrete = 0;
	};
};

}  // namespace cfg
