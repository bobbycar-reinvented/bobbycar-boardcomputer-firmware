#include "cloudtexthelpers.h"

// 3rdparty lib includes
#include "fmt/core.h"

// local includes
#include "cloud.h"

namespace bobby {

std::string CloudCreatedText::text() const
{
    return fmt::format("created: {}", cloud::cloudClient ? "true" : "false");
}

std::string CloudStartedText::text() const
{
    std::string text = "started: ";
    if (cloud::cloudClient)
        text += cloud::cloudStarted ? "true" : "false";
    return text;
}

std::string CloudConnectedText::text() const
{
    std::string text = "connected: ";
    if (cloud::cloudClient)
        text += cloud::cloudClient.is_connected() ? "true" : "false";
    return text;
}

} // namespace bobby
