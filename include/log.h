//
// Created by theo1 on 26/01/2025.
//

#pragma once

#include <array>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

// Variadic template class for logging
template<typename... Fields>
class Logger {
  public:
    static constexpr std::size_t FIELD_COUNT = sizeof...(Fields);

    // Variadic constructor template for the field_names
    template<typename... StringTypes>
    explicit Logger(StringTypes&&... field_names)
        : _field_names{{std::forward<StringTypes>(field_names)... } }
    {
        static_assert(sizeof...(Fields) == sizeof...(StringTypes),
                      "Number of field_names must match number of template fields.");
    }

    // Log method that takes FIELD_COUNT values
    void log(const Fields&... values) const {
        logImpl(std::index_sequence_for<Fields...>(), values...);
    }

  private:
    // Array to store the names corresponding to each type
    std::array<std::string, FIELD_COUNT> _field_names;

    // Helper function to handle logging using index sequences
    template<std::size_t... Indices>
    void logImpl(std::index_sequence<Indices...>, const Fields&... values) const {
        // Get current time in milliseconds
        std::chrono::time_point now = std::chrono::system_clock::now();
        std::chrono::duration ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

        // epoch is total seconds, remainder is the milliseconds part
        std::time_t epoch_seconds = ms.count() / std::chrono::milliseconds::period::den;
        auto milliseconds = ms.count() % std::chrono::milliseconds::period::den;

        // Print "<epoch>, <milliseconds>"
        std::stringstream log_line;
        log_line << epoch_seconds << ", " << milliseconds;

        // Print each "name=value" pair, comma-separated
        // We add a comma before each name=value, so it becomes:
        // <epoch>, <milliseconds>, <name1>=<value1>, <name2>=<value2>, ...
        ((log_line << ", " << _field_names[Indices] << "=" << values), ...);

        // End the line
        log_line << std::endl;

        // Print the log line TODO: Replace with actual logging
        std::cout << log_line.str();
    }
};