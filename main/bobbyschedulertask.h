#pragma once

// 3rdparty lib includes
#include <schedulertask.h>

#include <esp_log.h>

class BobbySchedulerTask : public espcpputils::SchedulerTask {
public:
    // using SchedulerTask::SchedulerTask; -> we need to add one more parameter
    BobbySchedulerTask(const char *name, void (&setupCallback)(), void (&loopCallback)(),
                       espchrono::millis_clock::duration loopInterval, bool use_in_recovery = false,
                       bool intervalImportant = false,
                       std::string (*perfInfo)() = nullptr) :
        espcpputils::SchedulerTask(name, setupCallback, loopCallback, loopInterval, intervalImportant, perfInfo),
        m_use_in_recovery{use_in_recovery}
    {
    }
    void setup(bool in_recovery = false)
    {
        m_in_recovery = in_recovery;
        if (in_recovery && !m_use_in_recovery)
        {
            ESP_LOGI("BobbySchedulerTask", "Skipping setup of %s (%s)", name(), m_use_in_recovery ? "use in recovery" : "no use in recovery");
            return;
        }
        SchedulerTask::setup();
        m_wasInitialized = true;
        ESP_LOGI("BobbySchedulerTask", "Task %s initialized", name());
    }
    void loop()
    {
        if (!m_in_recovery || m_use_in_recovery)
        {
            // ESP_LOGI("BobbySchedulerTask", "Loop %s", name());
            SchedulerTask::loop();
        }
    }
    bool isInitialized() const { return m_wasInitialized; }
private:
    mutable bool m_wasInitialized{false};
    const bool m_use_in_recovery;
    bool m_in_recovery{false};
};
