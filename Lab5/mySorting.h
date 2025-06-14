#ifndef MYSORTING_H
#define MYSORTING_H

#include "myList.h"

#include <algorithm>
#include <vector>
#include <cstring>
#include <cctype>
#include <concepts>
#include <type_traits>
#include <array>

template <typename Type>
concept Compare = requires(Type a, Type b) {
	{ a < b } -> std::convertible_to<bool>;
};

template <typename T>
requires Compare<typename T::value_type> && requires(T c) { { c.begin() } -> std::input_or_output_iterator; { c.end() } -> std::input_or_output_iterator; }
void mySort(T& data) {
	std::sort(data.begin(), data.end());
}

template <typename T_ArrayElement, std::size_t N>
requires Compare<T_ArrayElement>
void mySort(T_ArrayElement (&data)[N]) {
	std::sort(data, data + N);
}

template <std::size_t N, std::size_t M>
void mySort(char (&data)[N][M]) {
	if (N < 2) {
		return;
	}

	std::vector<std::array<char, M>> temp_vec;
	temp_vec.reserve(N);

	for (std::size_t i = 0; i < N; ++i) {
		std::array<char, M> current_str_arr;
		strncpy(current_str_arr.data(), data[i], M - 1);
		current_str_arr[M - 1] = '\0';
		temp_vec.push_back(current_str_arr);
	}

	std::sort(temp_vec.begin(), temp_vec.end(), [](const std::array<char, M>& s1_arr, const std::array<char, M>& s2_arr) {
		const char* p1 = s1_arr.data();
		const char* p2 = s2_arr.data();

		while (true) {
			unsigned char u1 = static_cast<unsigned char>(*p1);
			unsigned char u2 = static_cast<unsigned char>(*p2);

			int char1_lower = std::tolower(u1);
			int char2_lower = std::tolower(u2);

			if (u1 == '\0' && u2 == '\0') {
				return false;
			}
			if (u1 == '\0') {
				return true;
			}
			if (u2 == '\0') {
				return false;
			}

			if (char1_lower < char2_lower) {
				return true;
			}
			if (char1_lower > char2_lower) {
				return false;
			}

			++p1;
			++p2;
		}
	});

	for (std::size_t i = 0; i < N; ++i) {
		strncpy(data[i], temp_vec[i].data(), M - 1);
		data[i][M - 1] = '\0';
	}
}


template <typename T_ListElement>
void mySort(MyList<T_ListElement>& list) {
	if (list.size() < 2) {
		return;
	}
	std::vector<T_ListElement> temp_vec;
	temp_vec.reserve(list.size());

	for(const auto& val : list) {
		temp_vec.push_back(val);
	}

	std::sort(temp_vec.begin(), temp_vec.end());

	typename MyList<T_ListElement>::Node* current_node_to_set = list.head_.get();
	for (const T_ListElement& sorted_val : temp_vec) {
		if (current_node_to_set != nullptr) {
			current_node_to_set->setData(sorted_val);
			current_node_to_set = current_node_to_set->getNext();
		} else {
			break;
		}
	}
}

#endif //MYSORTING_H
