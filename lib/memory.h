#pragma once
#define WIN32_LEAN_AND_MEAN
#include <cstdint>
#include <string_view>
#include <Windows.h>
#include <TlHelp32.h>

class Memory {
private:
	std::uintptr_t processId = 0;
	void* handle = nullptr;

public:
	Memory(const std::string_view process) noexcept;
	~Memory();

	void* gethandle();
	const std::uintptr_t getAddress(const std::string_view module) const noexcept;

	const std::uintptr_t read(const std::uintptr_t& address) const noexcept;
	void write(const std::uintptr_t& address, const std::uintptr_t value) const noexcept;
};

Memory::Memory(const std::string_view process) noexcept {
	::PROCESSENTRY32 entry = {};
	entry.dwSize = sizeof(::PROCESSENTRY32);
	const auto snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (::Process32Next(snapshot, &entry)) {
		if (!process.compare(entry.szExeFile)) {
			processId = entry.th32ProcessID;
			handle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
			break;
		}
	}

	if (snapshot) {
		::CloseHandle(snapshot);
	}
}

Memory::~Memory() {
	if (handle) {
		::CloseHandle(handle);
	}
}

void* Memory::gethandle() {
	return handle;
}

const std::uintptr_t Memory::getAddress(const std::string_view module) const noexcept {
	::MODULEENTRY32 entry = {};
	entry.dwSize = sizeof(::MODULEENTRY32);
	const auto snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

	std::uintptr_t address = 0;

	while (::Module32Next(snapshot, &entry)) {
		if (!module.compare(entry.szModule)) {
			address = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
			break;
		}
	}

	if (snapshot) {
		::CloseHandle(snapshot);
	}
	return address;
}

const std::uintptr_t Memory::read(const std::uintptr_t& address) const noexcept {
	std::uintptr_t value = {};
	::ReadProcessMemory(handle, reinterpret_cast<const void*>(address), &value, sizeof(std::uintptr_t), NULL);
	return value;
}

void Memory::write(const std::uintptr_t& address, const std::uintptr_t value) const noexcept {
	::WriteProcessMemory(handle, reinterpret_cast<void*>(address), &value, sizeof(std::uintptr_t), NULL);
}
