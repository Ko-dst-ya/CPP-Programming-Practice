#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>

// https://stackoverflow.com/questions/56788745/how-to-convert-stdfilesystemfile-time-type-to-a-string-using-gcc-9/58237530#58237530
template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                        + system_clock::now());
    return system_clock::to_time_t(sctp);
}

auto compute_file_size(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path))
	{
		auto file_size = std::filesystem::file_size(path);

		if (file_size != static_cast <uintmax_t> (-1))
		{
			return file_size;
		}
	}

	return static_cast <uintmax_t> (-1);
}

auto compute_directory_size(const std::filesystem::path & path)
{
	uintmax_t size = 0ULL;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (auto const & entry : std::filesystem::recursive_directory_iterator(path))
		{
			if (std::filesystem::is_regular_file(entry.status()) || std::filesystem::is_symlink(entry.status()))
			{
				auto file_size = std::filesystem::file_size(entry);

				if (file_size != static_cast <uintmax_t> (-1))
				{
					size += file_size;
				}
			}
		}
	}

	return size;
}

void view_directory(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto & entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();
            auto ftime = std::filesystem::last_write_time(file_name);
            std::time_t cftime = to_time_t(ftime);

			std::cout << file_name << " write time is " << std::asctime(std::localtime(&cftime)) << std::endl;
		}
	}
}

int main(int argc, char ** argv)
{
	system("chcp 1251");

	std::cout << compute_file_size("./Source.cpp") << std::endl;

	std::cout << compute_directory_size(std::filesystem::current_path()) << std::endl;

	view_directory(std::filesystem::current_path());

	system("pause");

	return EXIT_SUCCESS;
}
