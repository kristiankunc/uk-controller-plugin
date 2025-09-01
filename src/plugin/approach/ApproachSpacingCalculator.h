#pragma once

namespace UKControllerPlugin {
    namespace Airfield {
        class AirfieldCollection;
    } // namespace Airfield
    namespace Euroscope {
        class EuroscopePluginLoopbackInterface;
    } // namespace Euroscope
    namespace Wake {
        class WakeCategoryMapperCollection;
    } // namespace Wake
} // namespace UKControllerPlugin

namespace UKControllerPlugin::Approach {
    class ApproachSequencedAircraft;
    class ApproachSequencerOptions;

    /**
     * Calculates the required distance between an aircraft and the previous aircraft.
     */
    class ApproachSpacingCalculator
    {
        public:
        ApproachSpacingCalculator(
            ApproachSequencerOptions& sequencerOptions,
            const Airfield::AirfieldCollection& airfields,
            const Wake::WakeCategoryMapperCollection& wakeMappers,
            Euroscope::EuroscopePluginLoopbackInterface& plugin);
        [[nodiscard]] auto
        Calculate(const std::string& airfield, const ApproachSequencedAircraft& aircraft) const -> double;
        [[nodiscard]] auto AirfieldMinimumSeparation(const std::string& airfield) const -> double;
        [[nodiscard]] static auto NoSpacing() -> double;

        private:
        [[nodiscard]] static auto GreaterOf(double value1, double value2) -> double;

        inline static const double NO_SPACING_DETECTED = -1.0;

        // Sequencer options
        ApproachSequencerOptions& sequencerOptions;

        // All the airfields
        const Airfield::AirfieldCollection& airfields;

        // The wake schemes
        const Wake::WakeCategoryMapperCollection& wakeMappers;

        // Plugin for getting flightplans
        Euroscope::EuroscopePluginLoopbackInterface& plugin;
    };
} // namespace UKControllerPlugin::Approach
