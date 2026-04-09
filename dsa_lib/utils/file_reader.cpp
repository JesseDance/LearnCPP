#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

struct File {
  std::string_view contents() const noexcept;

  static std::optional<File> open(std::string_view path);

private:
  explicit File(std::string contents);

  std::string d_contents;
};

File::File(std::string contents) : d_contents(std::move(contents)) {}

std::string_view File::contents() const noexcept {
  return std::string_view{d_contents};
}

std::optional<File> File::open(std::string_view file_name) {
  std::filesystem::path path{file_name};
  std::ifstream file{path};
  if (!file)
    return std::nullopt;

  std::stringstream buffer;
  buffer << file.rdbuf();
  return File{buffer.str()};
}