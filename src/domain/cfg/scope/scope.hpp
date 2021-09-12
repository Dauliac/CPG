#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../block/block.hpp"
#include "../block/iblock.hpp"
#include "iscope.hpp"

namespace cfg {

using namespace core;

class Scope : public IScope<Scope, Block> {
public:
	auto is_root() const -> bool override;
	auto has_childs() const -> bool override;
	auto get_blocks() const -> Blocks override;
	auto get_childs() const -> Childs override;
	auto get_parent() const -> Parent override;
	friend IBuilder;
	class Builder;

private:
	Scope(Parent parent, Childs childs, Blocks blocks);
	Scope(core::Uuid uuid, Parent parent, Childs childs, Blocks blocks);

	const Parent _parent;
	const Blocks _blocks;
	const Childs _childs;
};

class Scope::Builder : public IScope::IBuilder {
public:
	auto set_uuid(Uuid uuid) -> result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> override;
	auto add_child(Scope* child) -> result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>> override;
	auto set_parent(Scope* parent) -> result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>> override;
	auto add_block(Block* block) -> result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>> override;
	auto set_childs(Aggregator<Scope>* childs) -> result::Result<
		result::Success<IScope<Scope, Block>::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> override;
	auto set_blocks(Aggregator<Block>* blocks) -> result::Result<
		result::Success<IScope<Scope, Block>::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> override;
	[[nodiscard]] auto build() -> Scope override;

private:
	Uuid _uuid;
	Scope* _parent;
	Aggregator<Scope>* _childs;
	Aggregator<Block>* _blocks;
	IScope* _builded;
};

}  // namespace cfg
