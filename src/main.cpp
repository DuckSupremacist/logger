#include "log.h"

int main() {
    // Example: Logger with int, float
    Logger<int, std::string> logger("quantity", "weight");

    logger.log(6, "36.6f");
    logger.log(5, "30.5f");

    return 0;
}
