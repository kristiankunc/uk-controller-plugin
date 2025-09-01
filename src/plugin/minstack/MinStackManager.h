#pragma once
#include "push/PushEventProcessorInterface.h"

namespace UKControllerPlugin::TaskManager {
    class TaskRunnerInterface;
} // namespace UKControllerPlugin::TaskManager

namespace UKControllerPlugin::MinStack {

    struct MinStackLevel;

    /*
        Class for handling Minimum Stack Level Calculations
        and display.
    */
    class MinStackManager : public Push::PushEventProcessorInterface
    {
        public:
        MinStackManager();
        void AcknowledgeMsl(const std::string& key);
        void AddMsl(const std::string& key, std::string type, std::string name, unsigned int msl);
        [[nodiscard]] auto GetAllMslKeys() const -> std::set<std::string>;
        [[nodiscard]] auto
        GetMinStackLevel(const std::string& key) const -> const UKControllerPlugin::MinStack::MinStackLevel&;
        [[nodiscard]] static auto GetMslKeyAirfield(const std::string& airfield) -> std::string;
        [[nodiscard]] static auto GetMslKeyTma(const std::string& tma) -> std::string;
        [[nodiscard]] static auto GetNameFromKey(const std::string& key) -> std::string;
        void SetMinStackLevel(const std::string& key, unsigned int msl);
        void UpdateAllMsls(nlohmann::json mslData);
        void ProcessPushEvent(const Push::PushEvent& message) override;
        [[nodiscard]] auto GetPushEventSubscriptions() const -> std::set<Push::PushEventSubscription> override;
        void PluginEventsSynced() override;
        [[nodiscard]] auto InvalidMsl() const -> const MinStackLevel&;

        private:
        const std::shared_ptr<MinStackLevel> invalidMsl;

        // Map of identifier to MSL
        std::map<std::string, std::shared_ptr<UKControllerPlugin::MinStack::MinStackLevel>> mslMap;
    };
} // namespace UKControllerPlugin::MinStack
