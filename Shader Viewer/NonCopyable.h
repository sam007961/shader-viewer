#pragma once
class NonCopyable {
protected:
	NonCopyable() {}

private:
	NonCopyable(const NonCopyable& other) = delete;
	NonCopyable& operator=(const NonCopyable& other) = delete;
};
