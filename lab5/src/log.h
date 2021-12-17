#pragma once
#include <iostream>
#include <mutex>
#include <sstream>

/** Thread safe cout class
 * Exemple of use:
 *    PrintThread{} << "Hello world!" << std::endl;
 */
#pragma once
class PrintThread : public std::ostringstream {
public:
    PrintThread() = default;

    ~PrintThread() {
        std::lock_guard<std::mutex> guard(_mutexPrint);
        std::cout << this->str();
    }

private:
    static std::mutex _mutexPrint;
};
