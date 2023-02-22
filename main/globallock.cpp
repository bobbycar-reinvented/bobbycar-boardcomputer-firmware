#include "globallock.h"

namespace bobby {

cpputils::DelayedConstruction<espcpputils::recursive_mutex_semaphore> global_lock;

} // namespace bobby
