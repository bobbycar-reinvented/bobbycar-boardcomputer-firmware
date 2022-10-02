#include "resetnvsaction.h"

// system includes
#include <esp_system.h>
#include <nvs_flash.h>

void ResetNVSAction::triggered()
{
    nvs_flash_erase();
    esp_restart();
}
