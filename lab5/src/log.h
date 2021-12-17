#pragma once
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

/** Thread safe cout class
 * Exemple of use:
 *    PrintThread{} << "Hello world!" << std::endl;
 */

class PrintThread : public std::ostringstream {
public:
    PrintThread() = default;

    ~PrintThread() {
        std::lock_guard<std::mutex> guard(_mutexPrint);
        std::cout << "thread #" << std::this_thread::get_id() << this->str();
    }

private:
    static std::mutex _mutexPrint;
};
