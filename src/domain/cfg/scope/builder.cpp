#include "domain/core/guard.hpp"
#include "iscope.hpp"
#include "scope.hpp"

namespace cfg {
auto Scope::Builder::set_uuid(Uuid uuid) -> result::Result<
	result::Success<IScope::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>> {
	auto const result = guard::is_valid_uuid(uuid);
	if (result.is_failure()) {
		return result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
			result.get_failure().value());
	}
	_uuid = uuid;
	return result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::INVALID_UUID>>(
		result::Success<IScope::IBuilder*>{this});
};

auto Scope::Builder::add_child(Scope* child) -> result::Result<
	result::Success<IScope::IBuilder*>,
	result::
		BasicFailure<BasicFailureRegistrar::NO_RESOURCES, BasicFailureRegistrar::ALREADY_INSIDE>> {
	auto const insert_result = _childs->insert(child->get_uuid(), child);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>>(result::Success<IScope::IBuilder*>{this});
};

auto Scope::Builder::set_parent(Scope* parent) -> result::Result<
	result::Success<IScope::IBuilder*>,
	result::
		BasicFailure<BasicFailureRegistrar::NO_RESOURCES, BasicFailureRegistrar::ALREADY_INSIDE>> {
	auto const result = guard::is_null_pointer(parent);
	if (result.is_failure()) {
		return result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>::
				create<BasicFailureRegistrar::NO_RESOURCES>());
	}
	if (_parent == parent) {
		return result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>::
				create<BasicFailureRegistrar::ALREADY_INSIDE>());
	}
	_parent = parent;
	return result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>>(result::Success<IScope::IBuilder*>{this});
};

auto Scope::Builder::add_block(Block* block) -> result::Result<
	result::Success<IScope::IBuilder*>,
	result::
		BasicFailure<BasicFailureRegistrar::NO_RESOURCES, BasicFailureRegistrar::ALREADY_INSIDE>> {
	auto const insert_result = _blocks->insert(block->get_uuid(), block);
	if (insert_result.is_failure()) {
		return result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<
				BasicFailureRegistrar::NO_RESOURCES,
				BasicFailureRegistrar::ALREADY_INSIDE>>(insert_result.get_failure().value());
	}
	return result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<
			BasicFailureRegistrar::NO_RESOURCES,
			BasicFailureRegistrar::ALREADY_INSIDE>>(result::Success<IScope::IBuilder*>{this});
};

auto Scope::Builder::set_childs(Aggregator<Scope>* childs) -> result::Result<
	result::Success<IScope::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
	auto const result = guard::is_null_pointer(childs);
	if (result.is_failure()) {
		return result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>::create());
	}
	_childs = childs;
	return result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
		result::Success<IScope::IBuilder*>{this});
};

auto Scope::Builder::set_blocks(Aggregator<Block>* blocks) -> result::Result<
	result::Success<IScope::IBuilder*>,
	result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>> {
	auto const result = guard::is_null_pointer(blocks);
	if (result.is_failure()) {
		return result::Result<
			result::Success<IScope::IBuilder*>,
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
			result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>::create());
	}
	_blocks = blocks;
	return result::Result<
		result::Success<IScope::IBuilder*>,
		result::BasicFailure<BasicFailureRegistrar::NO_RESOURCES>>(
		result::Success<IScope::IBuilder*>{this});
};

}  // namespace cfg
