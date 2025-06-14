#ifndef MYLIST_H
#define MYLIST_H

#include <memory>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <ostream>
#include <iterator>

#define IMPLEMENTED_constructorOfEmptyList
#define IMPLEMENTED_pushingAndPopingElementsFront
#define IMPLEMENTED_nodesStoredAsUniquePtrs
#define IMPLEMENTED_popFromWhenEmptyList
#define IMPLEMENTED_copyingDisabled
#define IMPLEMENTED_removingElements
#define IMPLEMENTED_iteratorOperations
#define IMPLEMENTED_iteratorWithRangedForLoop
#define IMPLEMENTED_iteratorWithStlAlgorithm
#define IMPLEMENTED_ostreamOperator

class MyListTester_nodesStoredAsUniquePtrs_Test;

template <typename U> class MyListTestWrapper;
template <typename T> class MyList;

template <typename T_ListElement_FwdDecl>
void mySort(MyList<T_ListElement_FwdDecl>& list);

template <typename T> class MyList{
	public:

		friend class MyListTestWrapper<T>;

		friend void mySort<>(MyList<T>& list);

		using value_type = T;

		class Node {
			public:

				friend class MyListTestWrapper<T>;

				explicit Node(const T& data_val) : data_(data_val), next_(nullptr) {}
				explicit Node(T&& data_val) : data_(std::move(data_val)), next_(nullptr) {}
				void setData(const T& data){ data_ = data; };
				T& getData() { return data_; }
				const T& getData() const { return data_; }
				void setNext(std::unique_ptr<Node>&& next){ next_ = std::move(next); }
				Node* getNext() const { return next_.get(); }
				std::unique_ptr<Node> releaseNext() { return std::move(next_); }

			private:
				T data_;
				std::unique_ptr<Node> next_;
				friend class ::MyListTester_nodesStoredAsUniquePtrs_Test;
		};

	struct ListIterator {

		private:
			Node* current_node_ptr_;

		public:
			using iterator_category = std::forward_iterator_tag;
	        using value_type = T;
	        using difference_type = std::ptrdiff_t;
	        using reference = const T&;
	        using pointer = const T*;

	        ListIterator() : current_node_ptr_(nullptr) {}
	        explicit ListIterator(Node* p_node) : current_node_ptr_(p_node) {}

	        T& operator*() {
	            return current_node_ptr_->getData();
	        }
	        T* operator->(){
	            return &(current_node_ptr_->getData());
	        }

	        ListIterator& operator++() {
	            if (current_node_ptr_) {
	                current_node_ptr_ = current_node_ptr_->getNext();
	            }
	            return *this;
	        }

	        ListIterator operator++(int) {
	            ListIterator temp = *this;
	            ++(*this);
	            return temp;
	        }

	        bool operator==(const ListIterator& other) const {
	            return current_node_ptr_ == other.current_node_ptr_;
	        }

	        bool operator!=(const ListIterator& other) const {
	            return current_node_ptr_ != other.current_node_ptr_;
	        }
	    };

	struct ConstListIterator {
		private:
			const Node* current_node_ptr_;
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using reference = const T&;
			using pointer = const T*;

			ConstListIterator() : current_node_ptr_(nullptr) {}
			explicit ConstListIterator(const Node* p_node) : current_node_ptr_(p_node) {}

			const T& operator*() const {
				return current_node_ptr_->getData();
			}
			const T* operator->() const {
				return &(current_node_ptr_->getData());
			}

			ConstListIterator& operator++() {
				if (current_node_ptr_) {
					current_node_ptr_ = current_node_ptr_->getNext();
				}
				return *this;
			}
			ConstListIterator operator++(int) { ConstListIterator temp = *this; ++(*this); return temp; }
			bool operator==(const ConstListIterator& other) const { return current_node_ptr_ == other.current_node_ptr_; }
			bool operator!=(const ConstListIterator& other) const { return current_node_ptr_ != other.current_node_ptr_; }
		};


        MyList();
		MyList(const MyList& other) = delete;
		MyList& operator=(const MyList& other) = delete;
		MyList(MyList&& other) noexcept = default;
		MyList& operator=(MyList&& other) noexcept = default;
		~MyList() = default;

		size_t size() const;
		void push_front(const T& data);
		void push_front(T&& data);
		T pop_front();
		const T& front() const;

		void remove(const T& element);

		using iterator = ListIterator;
		iterator begin() const;
		iterator end() const;



    private:

		std::unique_ptr<Node> head_;
		size_t size_;

};

template<typename T>
MyList<T>::MyList():head_{}, size_{0}{}

template<typename T>
size_t MyList<T>::size() const {
	return size_;
}

template<typename T>
void MyList<T>::push_front(const T& data) {
	auto new_node = std::make_unique<Node>(data);
	new_node->setNext(std::move(head_));
	head_ = std::move(new_node);
	size_++;
}

template<typename T>
void MyList<T>::push_front(T&& data) { // Overload for rvalue data
	auto new_node = std::make_unique<Node>(std::move(data)); // Use Node(T&&) constructor
	new_node->setNext(std::move(head_));
	head_ = std::move(new_node);
	size_++;
}

template<typename T>
T MyList<T>::pop_front() {
	if (size_ <= 0) {
		throw std::out_of_range("Empty list");
	}
	T data = head_->getData();
	std::unique_ptr<Node> old_head = std::move(head_);
	head_ = old_head->releaseNext();
	size_--;
	return data;
}

template<typename T>
const T& MyList<T>::front() const {
	return head_->getData();
}

template<typename T>
MyList<T>::iterator MyList<T>::begin() const {
	return ListIterator(head_.get());
}
template<typename T>
MyList<T>::iterator MyList<T>::end() const {
	return ListIterator(nullptr);
}

template<typename T>
void MyList<T>::remove(const T& element) {
	while (head_ && head_->getData() == element) {
		std::unique_ptr<Node> old_head = std::move(head_);
		head_ = old_head->releaseNext();
		size_--;
	}

	if (!head_) return;

	Node* current_node_raw_ptr = head_.get();
	while (current_node_raw_ptr && current_node_raw_ptr->getNext()) {
		if (current_node_raw_ptr->getNext()->getData() == element) {
			std::unique_ptr<Node> node_b_to_delete = current_node_raw_ptr->releaseNext();
			std::unique_ptr<Node> node_c_ptr = node_b_to_delete->releaseNext();
			current_node_raw_ptr->setNext(std::move(node_c_ptr));
			size_--;
		} else {
			current_node_raw_ptr = current_node_raw_ptr->getNext();
		}
	}
}

template<typename T_> // Use T_ to avoid conflict with class template parameter T
std::ostream& operator<<(std::ostream& os, const MyList<T_>& list) {
	os << "[";
	bool first = true;
	for (const auto& item : list) { // Relies on working iterators
		if (!first) {
			os << ", ";
		}
		os << item;
		first = false;
	}
	os << "]";
	return os;
}

#endif //MYLIST_H
