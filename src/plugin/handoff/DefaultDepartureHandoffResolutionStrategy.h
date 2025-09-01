#pragma once
#include "DepartureHandoffResolutionStrategy.h"

namespace UKControllerPlugin {
    namespace Controller {
        class ActiveCallsign;
        class ActiveCallsignCollection;
        class ControllerPosition;
        class ControllerPositionHierarchy;
    } // namespace Controller
    namespace Euroscope {
        class EuroScopeCFlightPlanInterface;
    } // namespace Euroscope
} // namespace UKControllerPlugin

namespace UKControllerPlugin::Handoff {
    class FlightplanSidHandoffMapper;
    class FlightplanAirfieldHandoffMapper;
    struct HandoffOrder;
    struct ResolvedHandoff;

    /**
     * Given a flightplan, resolves the handoff frequency
     * that should be used for the after departure TAG item.
     */
    class DefaultDepartureHandoffResolutionStrategy : public DepartureHandoffResolutionStrategy
    {
        public:
        DefaultDepartureHandoffResolutionStrategy(
            const FlightplanSidHandoffMapper& sidMapper,
            const FlightplanAirfieldHandoffMapper& airfieldMapper,
            const Controller::ActiveCallsignCollection& activeCallsigns);
        virtual ~DefaultDepartureHandoffResolutionStrategy() = default;

        [[nodiscard]] auto Resolve(const Euroscope::EuroScopeCFlightPlanInterface& flightplan) const
            -> std::shared_ptr<const ResolvedHandoff> override;

        private:
        [[nodiscard]] auto
        ResolveController(const HandoffOrder& handoff) const -> std::shared_ptr<Controller::ControllerPosition>;

        // Maps flightplans to sids to handoffs
        const FlightplanSidHandoffMapper& sidMapper;

        // Maps flightplans to airfields to handoffs
        const FlightplanAirfieldHandoffMapper& airfieldMapper;

        // All the active controllers
        const Controller::ActiveCallsignCollection& activeCallsigns;

        // The unicom frequency
        inline static const double UNICOM_FREQUENCY = 122.800;

        // The unicom controller for default values
        const std::shared_ptr<Controller::ControllerPosition> unicomController;
    };
} // namespace UKControllerPlugin::Handoff
