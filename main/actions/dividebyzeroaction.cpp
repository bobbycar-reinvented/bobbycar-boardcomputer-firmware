#include "dividebyzeroaction.h"

// esp-idf includes
#include <esp_log.h>

void DivideByZeroAction::triggered()
{
    int i = 1;
    i--;
    int goodbye = 42 / i;
    ESP_LOGW("BOBBY", "divide by zero %i", goodbye);
}
