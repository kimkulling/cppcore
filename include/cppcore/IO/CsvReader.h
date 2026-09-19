/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2026 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		CsvReader
///	@ingroup	CPPCore

/// @brief  This class provides some common OS-specific file operations.
//-------------------------------------------------------------------------------------------------
class CsvReader {
public:

    /// @brief  Read CSV file robustly, handling quoted fields and commas within quotes.
    /// @param[in] filepath The path to the CSV file to be read.
    /// @return A vector of vectors of strings representing the CSV data.
    static std::vector<std::vector<std::string>> readFromFile(const std::string& filepath) {
        std::vector<std::vector<std::string>> data;
        std::ifstream file(filepath);
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> row;
            std::string cell;
            bool inQuotes = false;

            for (char c : line) {
                if (c == '"') {
                    inQuotes = !inQuotes;
                } else if (c == ',' && !inQuotes) {
                    row.push_back(cell);
                    cell.clear();
                } else {
                    cell += c;
                }
            }
            row.push_back(cell); // Add last cell
            data.push_back(row);
        }
        return data;
    }
};

}
