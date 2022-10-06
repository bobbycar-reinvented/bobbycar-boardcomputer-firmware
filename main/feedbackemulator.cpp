#include "feedbackemulator.h"

// 3rdparty lib includes
#include <esprandom.h>
#include <randomutils.h>

// local includes
#include "globals.h"

namespace feedbackemulator {
void init()
{}

void update()
{
    if (!configs.emulateFeedback.value())
    {
        return;
    }

    for (auto &controller: controllers)
    {
        controller.feedback.left.dcLink = cpputils::randomNumber<int16_t>(-500, 500, espcpputils::esp_random_device{});
        controller.feedback.right.dcLink = cpputils::randomNumber<int16_t>(-500, 500, espcpputils::esp_random_device{});
        controller.feedback.left.speed = cpputils::randomNumber<int16_t>(-1000, 1000, espcpputils::esp_random_device{});
        controller.feedback.right.speed = cpputils::randomNumber<int16_t>(-1000, 1000, espcpputils::esp_random_device{});
        controller.feedback.left.error = cpputils::randomNumber(0, 4, espcpputils::esp_random_device{});
        controller.feedback.right.error = cpputils::randomNumber(0, 4, espcpputils::esp_random_device{});
        controller.feedback.left.angle = 0;
        controller.feedback.right.angle = 0;
        controller.feedback.left.dcPhaA = cpputils::randomNumber<int16_t>(-5, 5, espcpputils::esp_random_device{});
        controller.feedback.right.dcPhaA = cpputils::randomNumber<int16_t>(-5, 5, espcpputils::esp_random_device{});
        controller.feedback.left.dcPhaB = cpputils::randomNumber<int16_t>(-5, 5, espcpputils::esp_random_device{});
        controller.feedback.right.dcPhaB = cpputils::randomNumber<int16_t>(-5, 5, espcpputils::esp_random_device{});
        controller.feedback.left.dcPhaC = cpputils::randomNumber<int16_t>(-5, 5, espcpputils::esp_random_device{});
        controller.feedback.right.dcPhaC = cpputils::randomNumber<int16_t>(-5, 5, espcpputils::esp_random_device{});
        controller.feedback.left.chops = 0;
        controller.feedback.right.chops = 0;
        controller.feedback.left.hallA = true;
        controller.feedback.left.hallB = false;
        controller.feedback.left.hallC = true;
        controller.feedback.right.hallA = false;
        controller.feedback.right.hallB = true;
        controller.feedback.right.hallC = false;
        controller.feedback.batVoltage = cpputils::randomNumber<int16_t>(3000, 5000, espcpputils::esp_random_device{});
        controller.feedback.boardTemp = cpputils::randomNumber<int16_t>(200, 600, espcpputils::esp_random_device{});
        controller.feedback.left.id = 0;
        controller.feedback.right.id = 0;
        controller.feedback.left.iq = 0;
        controller.feedback.right.iq = 0;

        controller.feedbackValid = true;
    }
}
} // feedbackemulator
