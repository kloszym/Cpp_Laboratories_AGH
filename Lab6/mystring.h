#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <random>
#include <ctime>
#include <vector>


class MyString {
public:

	const static size_t initialBufferSize_ = 20;

	class iterator;

	MyString();
	MyString(const char *text);
	MyString(const MyString &text);

	friend std::ostream& operator<<(std::ostream&, const MyString& );
	friend std::istream& operator>>(std::istream&, MyString&);
	char operator[](size_t index) const;
	MyString operator+=(const char);
	bool operator< (const MyString&) const;
	bool operator==(const MyString&) const;
	bool operator!=(const MyString&) const;

	size_t size() const { return size_; }
	size_t capacity() const { return initialBufferSize_+string_.capacity(); }
	bool empty() const { return size_ == 0; }
	void clear();
	void trim();
	std::set<MyString> getUniqueWords() const;
	std::map<MyString, size_t>	countWordsUsageIgnoringCases() const;
	void toLower();
	static MyString generateRandomWord(size_t length);
	bool startsWith(const char* text) const;
	bool endsWith(const char* text) const;
	MyString join(const std::vector<MyString> &texts) const;
	bool all_of(std::function<bool(char)> predicate) const;

	iterator begin();
	iterator end();

	class iterator {

	private:
		MyString* mystring_ptr_;
		char* current_char_ptr_;
		size_t current_index_;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = char;
		using difference_type = std::ptrdiff_t;
		using reference = char&;
		using pointer = char*;

		iterator() : mystring_ptr_(nullptr), current_char_ptr_(nullptr), current_index_(0) {}
		explicit iterator(MyString* my_string) : mystring_ptr_(my_string), current_char_ptr_(&(mystring_ptr_->buffer_[0])), current_index_(0) {}

		reference operator*() {
			return *current_char_ptr_;
		}
		pointer operator->(){
			return &(*current_char_ptr_);
		}

		iterator& operator++() {
			if (current_index_ == initialBufferSize_-1) {
				current_char_ptr_ = &*(mystring_ptr_->string_.begin());
				current_index_++;
			}
			else{
				current_char_ptr_++;
				current_index_++;
			}
			return *this;
		}

		iterator operator++(int) {
			iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const iterator& other) const {
			return current_char_ptr_ == other.current_char_ptr_;
		}

		bool operator!=(const iterator& other) const {
			return current_char_ptr_ != other.current_char_ptr_;
		}

	};
	class const_iterator {};
private:

	char buffer_[20];
	std::string string_;
	size_t size_;


};

MyString::MyString(): string_(), size_(0) {
}

MyString::MyString(const char *text) {
	size_ = strlen(text);
	if (size_ <= initialBufferSize_) {
		strcpy(buffer_, text);
	}
	else {
		strncpy(buffer_, text, initialBufferSize_);
		buffer_[initialBufferSize_] = '\0';
		string_.append(text, initialBufferSize_, size_);
	}

}
MyString::MyString(const MyString &text) {
	strcpy(this->buffer_, text.buffer_);
	this->string_ = text.string_;
	this->size_ = text.size_;
}

void MyString::clear() {
	string_.clear();
	size_ = 0;
}

std::ostream& operator<<(std::ostream& os, const MyString& mystr){
	if (mystr.size_ < MyString::initialBufferSize_) {
		for (size_t i = 0; i < mystr.size_; i++) {
			os << mystr.buffer_[i];
		}
	}
	else {
		os << mystr.buffer_ << mystr.string_;
	}
	return os;
}

std::istream& operator>>(std::istream& is, MyString& mystr) {
	size_t index = 0;
	char buf;
	while (index < MyString::initialBufferSize_ && is.get(buf)) {
		mystr.buffer_[index] = buf;
		mystr.size_++;
		index++;
	}
	if (index == MyString::initialBufferSize_) {
		while (!is.eof()) {
			mystr.string_.append(1, is.get());
			mystr.size_++;
		}
	}
	return is;
}

char MyString::operator[](size_t index) const {
	if (index >= size_) { throw std::out_of_range("MyString::operator[]"); }
	if (index < initialBufferSize_) {
		return buffer_[index];
	}
	else {
		return string_[index - initialBufferSize_];
	}
}

void MyString::trim() {
    if (size_ == 0) {
        return;
    }
    std::string temp_full_string;
    temp_full_string.reserve(size_); // Pre-allocate for efficiency

    if (size_ <= initialBufferSize_) {
        temp_full_string.assign(buffer_, size_);
    } else {
        temp_full_string.assign(buffer_, initialBufferSize_);
        temp_full_string.append(string_);
    }

    auto first_char_it = std::find_if_not(temp_full_string.begin(), temp_full_string.end(), isspace);

    auto last_char_it = std::find_if_not(temp_full_string.rbegin(), temp_full_string.rend(), isspace);

    if (first_char_it == temp_full_string.end()) {
        clear();
    } else {
        std::string::iterator actual_end = last_char_it.base();

        std::string trimmed_string(first_char_it, actual_end);

        this->clear();

        size_t new_size = trimmed_string.length();
        if (new_size == 0) {
        } else if (new_size <= initialBufferSize_) {
            std::strncpy(buffer_, trimmed_string.c_str(), new_size);
            if (new_size < initialBufferSize_) {
                buffer_[new_size] = '\0';
            }
            size_ = new_size;
        } else {
            std::strncpy(buffer_, trimmed_string.c_str(), initialBufferSize_);
            string_.assign(trimmed_string.c_str() + initialBufferSize_, new_size - initialBufferSize_);
            size_ = new_size;
        }
    }
}

MyString MyString::operator+=(const char text) {
	if (size_ < initialBufferSize_) {
		buffer_[size_] = text;
	}
	else {
		string_.push_back(text);
	}
	size_++;
	return *this;
}

MyString::iterator MyString::begin() {
	return iterator(this);
}
inline MyString::iterator MyString::end() {
	iterator it = iterator(this);
	for (size_t i = 0; i < size_ ;i++) {
			it++;
	}
	return it++;
}

std::set<MyString> MyString::getUniqueWords() const {
	std::string full_string;
	full_string.reserve(size_);

	if (size_ <= initialBufferSize_) {
		full_string.assign(buffer_, size_);
	} else {
		full_string.assign(buffer_, initialBufferSize_);
		full_string.append(string_);
	}
	std::transform(full_string.begin(), full_string.end(), full_string.begin(), tolower);

	std::set<MyString> result;
	std::set<char> stop_chars {' ', '.', ',', '?', '!', ':'};
	char buf[60];
	int turtle = 0, rabbit = 0;
	for (; rabbit < (int)full_string.length(); rabbit++) {
		if (stop_chars.contains(full_string.at(rabbit))) {
			if (rabbit > turtle) {
				strcpy(buf, full_string.substr(turtle, rabbit-turtle).c_str());
				buf[rabbit-turtle] = '\0';
				result.insert(MyString(buf));
			}
			turtle = rabbit + 1;
		}
	}
	if (rabbit > turtle) {
		strcpy(buf, full_string.substr(turtle, rabbit-turtle).c_str());
		result.insert(MyString(buf));
	}

	return result;

}

bool MyString::operator<(const MyString& other) const {
	if (size_ < initialBufferSize_ || other.size_ < initialBufferSize_) {
		return strcmp(buffer_, other.buffer_) < 0;
	}
	else {
		int buf_bool = strcmp(buffer_, other.buffer_);
		if (buf_bool == 0) {
			return string_.compare(other.string_) < 0;
		}
		else {
			return buf_bool < 0;
		}
	}
}

std::map<MyString, size_t> MyString::countWordsUsageIgnoringCases() const {
	std::string full_string;
	full_string.reserve(size_);

	if (size_ <= initialBufferSize_) {
		full_string.assign(buffer_, size_);
	} else {
		full_string.assign(buffer_, initialBufferSize_);
		full_string.append(string_);
	}
	std::transform(full_string.begin(), full_string.end(), full_string.begin(), tolower);

	std::map<MyString, size_t> result;
	std::set<char> stop_chars {' ', '.', ',', '?', '!', ':', '\"', '(', ')', '/', '\\', '\n', '\t', '\r'};
	char buf[60];
	int turtle = 0, rabbit = 0;
	for (; rabbit < (int)full_string.length(); rabbit++) {
		if (stop_chars.contains(full_string.at(rabbit))) {
			if (rabbit > turtle) {
				strcpy(buf, full_string.substr(turtle, rabbit-turtle).c_str());
				buf[rabbit-turtle] = '\0';
				MyString temp = MyString(buf);
				if (result.contains(temp)) {
					result[temp] += 1;
				}
				else {
					result.insert_or_assign(temp, (size_t)1);
				}
			}
			turtle = rabbit + 1;
		}
	}
	if (rabbit > turtle) {
		strcpy(buf, full_string.substr(turtle, rabbit-turtle).c_str());
		buf[rabbit-turtle] = '\0';
		MyString temp = MyString(buf);
		if (result.contains(temp)) {
			result[temp] += 1;
		}
		else {
			result.insert_or_assign(temp, (size_t)1);
		}
	}

	return result;

}

bool MyString::operator==(const MyString& other) const {
	if (size_ < initialBufferSize_ || other.size_ < initialBufferSize_) {
		return strcmp(buffer_, other.buffer_) == 0;
	}
	else {
		int buf_bool = strcmp(buffer_, other.buffer_);
		if (buf_bool == 0) {
			return string_.compare(other.string_) == 0;
		}
		else {
			return buf_bool == 0;
		}
	}
}
bool MyString::operator!=(const MyString& other) const {
	if (size_ < initialBufferSize_ || other.size_ < initialBufferSize_) {
		return strcmp(buffer_, other.buffer_) != 0;
	}
	else {
		int buf_bool = strcmp(buffer_, other.buffer_);
		if (buf_bool == 0) {
			return string_.compare(other.string_) != 0;
		}
		else {
			return buf_bool != 0;
		}
	}
}

void MyString::toLower() {
	if (size_ < initialBufferSize_) {
		for (size_t i = 0; i < size_; i++) {
			buffer_[i] = tolower(buffer_[i]);
		}
	}
	else {
		for (size_t i = 0; i < initialBufferSize_; i++) {
			buffer_[i] = tolower(buffer_[i]);
		}
		for (size_t i = 0; i < string_.length(); i++) {
			string_[i] = tolower(string_[i]);
		}
	}
}

MyString MyString::generateRandomWord(size_t length) {
	srand(time(NULL));
	std::string word;
	word.reserve(length);
	for (size_t i = 0; i < length; i++) {
		int if_capital = rand() % 2;
		word.push_back((char)(((rand() % 26) + 65) + (if_capital * 32)));
	}
	word.shrink_to_fit();
	return MyString(word.c_str());
}

bool MyString::startsWith(const char* text) const {
	std::string full_string;
	full_string.reserve(size_);

	if (size_ <= initialBufferSize_) {
		full_string.assign(buffer_, size_);
	} else {
		full_string.assign(buffer_, initialBufferSize_);
		full_string.append(string_);
	}

	std::map<MyString, size_t> result;
	std::set<char> stop_chars {' ', '.', ',', '?', '!', ':', '\"', '(', ')', '/', '\\', '\n', '\t', '\r'};
	char buf[60];
	int turtle = 0, rabbit = 0;
	for (; rabbit < (int)full_string.length(); rabbit++) {
		if (stop_chars.contains(full_string.at(rabbit))) {
			if (rabbit > turtle) {
				strcpy(buf, full_string.substr(turtle, rabbit-turtle).c_str());
				buf[rabbit-turtle] = '\0';
				rabbit = (int)full_string.length();
			}
		}
	}
	return strcmp(buf, text) == 0;
}

bool MyString::endsWith(const char* text) const {
	std::string full_string;
	full_string.reserve(size_);

	if (size_ <= initialBufferSize_) {
		full_string.assign(buffer_, size_);
	} else {
		full_string.assign(buffer_, initialBufferSize_);
		full_string.append(string_);
	}

	std::map<MyString, size_t> result;
	std::set<char> stop_chars {' ', '.', ',', '?', '!', ':', '\"', '(', ')', '/', '\\', '\n', '\t', '\r'};
	char buf[60];
	size_t n = strlen(text);
	if (size_ < n) return false;
	else {
		strcpy(buf,full_string.substr(full_string.length()-n, n).c_str());
	}

	return strcmp(buf, text) == 0;
}

MyString MyString::join(const std::vector<MyString>& texts) const {
	std::string separator {buffer_};
	std::string full_string_;

	std::string temp_string;
	temp_string.reserve(texts[0].size_);
	if (texts[0].size_ <= initialBufferSize_) {
		temp_string.assign(texts[0].buffer_, texts[0].size_);
	} else {
		temp_string.assign(texts[0].buffer_, initialBufferSize_);
		temp_string.append(texts[0].string_);
	}
	full_string_.append(temp_string);
	for (size_t i = 1; i < texts.size(); i++) {
		full_string_.append(separator);

		temp_string.clear();
		temp_string.reserve(texts[i].size_);
		if (texts[i].size_ <= initialBufferSize_) {
			temp_string.assign(texts[i].buffer_, texts[i].size_);
		} else {
			temp_string.assign(texts[i].buffer_, initialBufferSize_);
			temp_string.append(texts[i].string_);
		}
		full_string_.append(temp_string);
	}
	return MyString(full_string_.c_str());
}

bool MyString::all_of(std::function<bool(char)> predicate) const {
	std::string temp_string;
	temp_string.reserve(size_);
	if (size_ <= initialBufferSize_) {
		temp_string.assign(buffer_, size_);
	} else {
		temp_string.assign(buffer_, initialBufferSize_);
		temp_string.append(string_);
	}
	return std::all_of(temp_string.begin(), temp_string.end(), predicate);
}


#endif //MYSTRING_H
