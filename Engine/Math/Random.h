#pragma once
#include <random>

namespace nc {
	float random() {
		return rand() / RAND_MAX;
	}

	float random(float min, float max) {
		if (min > max) {
			std::swap(min, max);
		}

		return min + ((max - min) * random());
	}
}