#pragma once

#include <entt/entity/registry.hpp>
#include "Components/Components.h"

void updateColliders(entt::registry& registry);
void checkPlayerCollision(entt::registry& registry);