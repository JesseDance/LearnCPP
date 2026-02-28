#include <iostream>
#include <ostream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

namespace fs = std::filesystem;

enum class Language {
	CPP,
	JAVA,
	PYTHON,
	UNKOWN
};

struct FileStats {
	int totalLines = 0;
	int blankLines = 0;
	int commentLines = 0;
	int codeLines = 0;
};

struct LanguageStats {
	int files = 0;
	FileStats stats;
};

bool isSourceFile (const fs::path& path) {
	static const std::unordered_set<std::string> extensions = {
		".cpp", ".h", ".java", ".py", ".c"
	};

	return extensions.count(path.extension().string()) > 0;
}

Language detectLanguage(const fs::path& path) {
	std::string ext = path.extension().string();

	if(ext == ".cpp" || ext == ".h") return Language::CPP;
	if(ext == ".java") return Language::JAVA;
	if(ext == ".py") return Language::PYTHON;

	return Language::UNKOWN;
}

std::string languageName(Language lang) {
	switch (lang) {
	case Language::CPP: return "C/C++";
	case Language::JAVA: return "Java";
	case Language::PYTHON: return "Python";
	default: return "Unknown";
	}
}

FileStats analyzeFile(const fs::path& path, Language lang) {
	FileStats stats;
	std::ifstream file(path);

	if(!file.is_open()) {
		std::cerr << "Warning: Could not open file " << path << std::endl;
		return stats;
	}

	bool inBlockComment = false;
	std::string line;

	while (std::getline(file, line)) {
		stats.totalLines++;

		//trim whitespace
		auto firstNonSpace = line.find_first_not_of(" \t");
		if(firstNonSpace == std::string::npos) {
			stats.blankLines++;
			continue;
		}

		//python comments
		if (lang == Language::PYTHON) {
			if(line[firstNonSpace] == '#') {
				stats.commentLines++;
			} else {
				stats.codeLines++;
			}
			continue;
		}

		if(inBlockComment) {
			stats.commentLines++;
			if(line.find("*/") != std::string::npos) {
				inBlockComment = false;
			}
			continue;
		}

		if(line.find("//", firstNonSpace) == firstNonSpace) {
			stats.commentLines++;
		} else if(line.find("/*", firstNonSpace) == firstNonSpace) {
			stats.commentLines++;
			if(line.find("*/", firstNonSpace + 2) == std::string::npos) {
				inBlockComment = true;
			}
		} else {
			stats.codeLines++;
		}
	}

	return stats;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		std::cerr << "Usage: app.exe <directory/path>\n";
		return 1;
	}

	fs::path rootPath = argv[1];

	if(!fs::exists(rootPath)) {
		std::cerr << "Error: Path does not exist\n";
		return 1;
	}

	if(!fs::is_directory((rootPath))) {
		std::cerr << "Error: Path is not a directory\n";
		return 1;
	}

	std::unordered_map<Language, LanguageStats> perLanguage;
	FileStats totalStats;
	int fileCount = 0;

	std::cout << "Scanning directory: " << rootPath << "\n";

	for (const auto& entry : fs::recursive_directory_iterator(rootPath)) {
		if(!entry.is_regular_file()) {
			continue;
		}

		if(!isSourceFile(entry.path())) {
			continue;
		}

		Language lang = detectLanguage(entry.path());
		if(lang == Language::UNKOWN) continue;

		FileStats stats = analyzeFile(entry.path(), lang);

		auto& langStats = perLanguage[lang];

	    langStats.files++;
	    langStats.stats.totalLines += stats.totalLines;
	    langStats.stats.codeLines += stats.codeLines;
	    langStats.stats.commentLines += stats.commentLines;
	    langStats.stats.blankLines += stats.blankLines;

		totalStats.totalLines += stats.totalLines;
		totalStats.blankLines += stats.blankLines;
		totalStats.commentLines += stats.commentLines;
		totalStats.codeLines += stats.codeLines;
		fileCount++;
	}

	std::cout << "Files scanned: " << fileCount << std::endl;
	std::cout << "Lines of Code: " << totalStats.codeLines << std::endl;
	std::cout << "Comment Lines: " << totalStats.commentLines << std::endl;
	std::cout << "Blank Lines: " << totalStats.blankLines << std::endl;
	std::cout << "Total lines: " << totalStats.totalLines << std::endl;

	for(const auto& [lang, data] : perLanguage) {
		std::cout << "  " << languageName(lang) << std::endl;
		std::cout << "    Files: " << data.files << std::endl;
		std::cout << "    Lines of Code: " << data.stats.codeLines << std::endl;
		std::cout << "    Comment Lines: " << data.stats.commentLines << std::endl;
		std::cout << "    Blank Lines " << data.stats.blankLines << std::endl;
	}

	return 0;
}